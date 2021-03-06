#include <field.h>
#include <ndebug.h>
#include <yamlutils.h>


static Pvoid_t field_JS = NULL; /* (char *field_name) -> (struct field *field) */


/*	field_free()
 */
void field_free(void *arg)
{
	if (!arg)
		return;
	struct field *fl = arg;
	NB_wrn("erase field %s", fl->name);
	NB_err_if(fl->refcnt, "field '%s' free with non-zero refcount", fl->name);

	js_delete(&field_JS, fl->name);
	free(fl->name);
	free(fl);
}

/*	field_free_all()
 */
void __attribute__((destructor)) field_free_all()
{
	JS_LOOP(&field_JS,
		field_free(val);
	);
}

/*	field_new()
 * Create a new field.
 */
struct field *field_new	(const char *name, long offt, long len, long mask)
{
	struct field *ret = NULL;
	NB_die_if(!name, "no name given for field");

	/* A '0' mask is irrational.
	 * If a mask is not provided, assume 0xff.
	 * Do this _before_ checking for identical duplicates.
	 */
	if (!mask)
		mask = 0xff;

	/* return already existing ONLY if identical */
	if ((ret = js_get(&field_JS, name))) {
		if (ret->set.offt == offt && ret->set.len == len && ret->set.mask == mask)
			return ret;
		NB_wrn("field '%s' already exists but not identical: deleting", name);
		field_free(ret);
	}

	NB_die_if(!(
		ret = malloc(sizeof(struct field))
		), "fail alloc sz %zu", sizeof(struct field));
	ret->refcnt = 0;
	
	size_t name_len = strnlen(name, MAXLINELEN);
	NB_die_if(name_len >= MAXLINELEN, "rule name overflow '%s'", name);
	NB_die_if(!(
		ret->name = malloc(name_len +1)
		), "fail alloc size %zu", name_len +1);
	snprintf(ret->name, name_len+1, "%s", name);

	/* see 'test/overflow_test.c' for a proof that this is kosher */
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Waddress-of-packed-member"
	NB_die_if(__builtin_add_overflow(offt, 0, &ret->set.offt),
		"offt '%ld' out of bounds", offt);
	NB_die_if(__builtin_add_overflow(len, 0, &ret->set.len),
		"len '%ld' out of bounds", len);
	NB_die_if(__builtin_add_overflow(mask, 0, &ret->set.mask),
		"mask '%ld' out of bounds", mask);
	ret->set.flags = 0;
	#pragma GCC diagnostic pop

	NB_die_if(
		js_insert(&field_JS, ret->name, ret, true)
		, "");

	return ret;
die:
	field_free(ret);
	return NULL;
}


/*	field_release()
 */
void field_release(struct field *field)
{
	if (!field)
		return;
	field->refcnt--;
}

/*	field_get()
 * Increments refcount, don't call from inside this file.
 */
struct field *field_get(const char *field_name)
{
	struct field *ret = js_get(&field_JS, field_name);
	if (ret)
		ret->refcnt++;
	return ret;
}


/*	field_hash()
 * Adds the fnv1a hash of 'set' _and_ the bytes of 'pkt' described by 'set'
 * to the fnv1a in 'outhash'.
 *
 * Returns 0 on success; non-zero return indicates inability to hash
 * (e.g. 'pkt' is NULL, 'plen' shorter than offset in 'set', etc),
 * and in this case the contents of 'outhash' are unchanged.
 *
 * These semantics are so that the caller can calculate the compound hash
 * of multiple sets (ANDing multiple matches).
 * Caller must PREPARE 'outhash' with a call to fnv_hash64()
 * before the first call to field_hash(), e.g.:
 * ```
 * uint64_t le_hash = fnv_hash64(NULL, NULL, 0);
 * field_hash(a_set, a_pkt, a_size, &le_hash);
 * ```
 */
int __attribute__((hot)) field_hash(struct field_set set, const void *pkt, size_t plen, uint64_t *outhash)
{
	/* see field.h */
	FIELD_PACKET_INDEXING
	FIELD_PACKET_HASHING
	return 0;
}


/*	field_parse()
 * Parse 'root' according to 'mode' (add | rem | prn).
 * NOTE: 'outdoc' and 'outlist' are ONLY handled by field_emit(),
 * which makes them optional if caller doesn't want parser to emit.
 * Returns 0 on success.
 */
int field_parse(enum parse_mode	mode,
		yaml_document_t *doc, yaml_node_t *mapping,
		yaml_document_t *outdoc, int outlist)
{
	int err_cnt = 0;
	struct field *field = NULL;

	/* possible params for a new field.
	 * All 'long' because we use strtol() to parse.
	 */
	const char *name = NULL;
	long offt = 0;
	long len = 0;
	long mask = 0;

	/* parse mapping */
	for (yaml_node_pair_t *pair = mapping->data.mapping.pairs.start;
		pair < mapping->data.mapping.pairs.top;
		pair++)
	{
		/* loop boilerplate */
		yaml_node_t *key = yaml_document_get_node(doc, pair->key);
		const char *keyname = (const char *)key->data.scalar.value;

		yaml_node_t *val = yaml_document_get_node(doc, pair->value);
		NB_die_if(val->type != YAML_SCALAR_NODE,
			"'%s' in field not a scalar", keyname);
		const char *valtxt = (const char *)val->data.scalar.value;

		/* Match field names and populate 'local' */
		if (!strcmp("field", keyname) || !strcmp("f", keyname)) {
			name = valtxt;

		} else if (!strcmp("offt", keyname) || !strcmp("o", keyname)) {
			offt = strtol(valtxt, NULL, 0);
			NB_die_if(errno, "'%s': '%s' could not be parsed", keyname, valtxt);

		} else if (!strcmp("len", keyname) || !strcmp("l", keyname)) {
			len = strtol(valtxt, NULL, 0);
			NB_die_if(errno, "'%s': '%s' could not be parsed", keyname, valtxt);

		} else if (!strcmp("mask", keyname) || !strcmp("m", keyname)) {
			mask = strtol(valtxt, NULL, 0);
			NB_die_if(errno, "'%s': '%s' could not be parsed", keyname, valtxt);

		} else {
			NB_err("'iface' does not implement '%s'", keyname);
		}
	}

	/* process based on 'mode' */
	switch (mode) {
	case PARSE_ADD:
	{
		NB_die_if(!(
			field = field_new(name, offt, len, mask)
			), "could not create new field '%s'", name);
		NB_die_if(field_emit(field, outdoc, outlist), "");
		break;
	}

	case PARSE_DEL:
		NB_die_if(!(
			field = js_get(&field_JS, name)
			), "could not get field '%s'", name);
		NB_die_if(field->refcnt, "field '%s' still in use", name);
		NB_die_if(
			field_emit(field, outdoc, outlist)
			, "");
		field_free(field);
		break;

	case PARSE_PRN:
		/* if nothing is given, print all */
		if (!strcmp("", name)) {
			JS_LOOP(&field_JS,
				NB_die_if(
					field_emit(val, outdoc, outlist)
					, "");
			);
		/* otherwise, search for a literal match */
		} else if ((field = js_get(&field_JS, name))) {
			NB_die_if(field_emit(field, outdoc, outlist), "");
		}
		break;

	default:
		NB_err("unknown mode %s", parse_mode_prn(mode));
	};

die:
	return err_cnt;
}

/*	field_emit()
 * Emit an interface as a mapping under 'outlist' in 'outdoc'.
 */
int field_emit(struct field *field, yaml_document_t *outdoc, int outlist)
{
	/* allow internal/test parsing without an output doc */
	if (!outdoc)
		return 0;

	int err_cnt = 0;
	int reply = yaml_document_add_mapping(outdoc, NULL, YAML_BLOCK_MAPPING_STYLE);
	NB_die_if(
		y_pair_insert(outdoc, reply, "field", field->name)
		|| y_pair_insert_nf(outdoc, reply, "offt", "%d", field->set.offt)
		|| y_pair_insert_nf(outdoc, reply, "len", "%u", field->set.len)
		, "");
	/* elide a 0xff mask (aka: no mask) */
	if (field->set.mask != 0xff) {
		NB_die_if(
			y_pair_insert_nf(outdoc, reply, "mask", "0x%x", field->set.mask)
			, "");
	}
	NB_die_if(!(
		yaml_document_append_sequence_item(outdoc, outlist, reply)
		), "");
die:
	return err_cnt;
}

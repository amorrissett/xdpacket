/*	field_test.c
 * Verify invariant bitfield and hashing manipulation math
 * (c) 2018 Sirio Balmelli
 * (c) 2018 Alan Morrissett
 */
#include <nonlibc.h>
#include <stdio.h>
#include <zed_dbg.h>
#include "field.h"

/* Separate code for creating test packet set for clarity */
#include "test_pkt.c"


/*	len_check()
 * Validate length calculation from mask values.
 */
int len_check()
{
	int err_cnt = 0;

	/* tuple: test-only data structure
	 * @mlen = number of ones in the mask
	 * @size = number of bytes to hash (field length)
	 */
	struct tuple {
		uint16_t mlen;
		size_t size;
	};
	/* TODO: add some edge cases to tests list */
	const struct tuple tests[] = {
		{ .mlen = 0, .size = 0 },
		{ .mlen = 1, .size = 1 },
		{ .mlen = 8, .size = 1 },
		{ .mlen = 9, .size = 2 },
		{ .mlen = 40, .size = 5 }
	};

	for (int i=0; i < NLC_ARRAY_LEN(tests); i++) {
		size_t check = xdpk_field_len(tests[i].mlen);
		Z_err_if(check != tests[i].size, "mlen %d -> %ld != %ld",
			tests[i].mlen, check, tests[i].size);
	}

	return err_cnt;
}

#include "hashtests.c"

/*	field_check()
 * Validate that field hashing matches known values.
 */
int field_check()
{
	printf("Calling init_pkts()\n");
	init_pkts();
	//init_tests();

	int err_cnt = 0;

	for (int i=0; i < NLC_ARRAY_LEN(hash_pos_tst); i++) {
		const struct htuple *tt = &hash_pos_tst[i];
		struct pkt *pkt = &pkts[tt->npkt];
		dump_pkt(pkt);
		uint64_t hash = xdpk_field_hash(tt->matcher, 
				pkt->data, pkt->len);
		Z_err_if(hash != tt->hash, "0x%lx 0x%lx len %zu",
			hash, tt->hash, pkt->len);
	}
	printf("number of positive field_check tests == %ld\n", 
			NLC_ARRAY_LEN(hash_pos_tst));

	for (int i=0; i < NLC_ARRAY_LEN(hash_neg_tst); i++) {
		const struct htuple *tt = &hash_neg_tst[i];
		struct pkt *pkt = &pkts[tt->npkt];
		dump_pkt(pkt);
		uint64_t hash = xdpk_field_hash(tt->matcher, 
				pkt->data, pkt->len);
		Z_err_if(hash == tt->hash, "0x%lx 0x%lx len %zu",
			hash, tt->hash, pkt->len);
	}
	printf("number of negative field_check tests == %ld\n", 
			NLC_ARRAY_LEN(hash_neg_tst));

	free_pkts();

	return err_cnt;
}

int main()
{
	int err_cnt = 0;
	err_cnt += len_check();
	err_cnt += field_check();
	return err_cnt;
}

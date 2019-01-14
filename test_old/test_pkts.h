/*	test_pkts.h
 * Define test packets.
 * (c) 2018 Sirio Balmelli
 * (c) 2018 Alan Morrissett
 */

static char *cpkts[] =
{
	"626c616172",			/* "blaar" */

	"58626c616172",			/* "Xblaar" */

	"58585858585858"		/* XXXXXXXblaarYYYYYY */
	"626c616172595959595959",

	"00000000626c6161720000000000000000000000"
	"0000000000000000000000000000000000000000"
	"0000000000000000000000000000000000000000"
	"0000000000000000000000000000000000000000"
	"000000000000000000000626c616172000000000",

	/*
	"The goal blaar of the Linux Documentati\n"
	"on Project (LDP) is to create and distr\n"
	"ibute the canonical set of free GNU/Lin\n"
	"ux documentation. While GNU/Linux appli\n"
	"cations and utilities may come with the\n"
	"ir blaar own documentation, LDP documen\n"
	"tation fills in the numerous gaps.  The\n"
	" hundreds of existing LDP documents pre\n"
	"sent both overviews and details of: the\n"
	" GNU/Linux Operating System, System Adm\n"
	"inistration, Hardware, Networks, Server\n"
	"s, GUIs, Programming, Language Support,\n"
	" etc. Not every important topic is curr\n"
	"ently covered so LDP is seeking new aut\n"
	"hors to fill in the gaps.  An additiona\n"
	"l goal is to collaborate on all of the \n"
	"issues of GNU/Linux documentation. We h\n"
	"ope to establish a system of documentat\n"
	"ion that is easy to use and search. Thi\n"
	"s includes the integration of all avail\n"
	"able documents.  We freely distribute o\n"
	"ur documents via the Internet. Some maj\n"
	"or distributions of Linux include them \n"
	"on CDs. If you are interested in publis\n"
	"hing any of the LDP works, see the sect\n"
	"ion 'Publishing LDP Documents' below.  \n"
	"The LDP is essentially a loose team of \n"
	"volunteers with minimal central organiz\n"
	"ation. Anyone who would like to help is\n"
	" welcome to join in this effort. We fee\n"
	"l that working together informally and \n"
	"discussing projects on our mailing list\n"
	"s is the best way to go. When we disagr\n"
	"ee on things, we try to reason with eac\n"
	"h other until we reach an informed cons\n"
	"ensus.     blaar                       \n"
	*/
	"54686520676f616c20626c616172206f66207468"
	"65204c696e757820446f63756d656e746174690a"
	"6f6e2050726f6a65637420284c44502920697320"
	"746f2063726561746520616e642064697374720a"
	"6962757465207468652063616e6f6e6963616c20"
	"736574206f66206672656520474e552f4c696e0a"
	"757820646f63756d656e746174696f6e2e205768"
	"696c6520474e552f4c696e7578206170706c690a"
	"636174696f6e7320616e64207574696c69746965"
	"73206d617920636f6d652077697468207468650a"
	"697220626c616172206f776e20646f63756d656e"
	"746174696f6e2c204c445020646f63756d656e0a"
	"746174696f6e2066696c6c7320696e2074686520"
	"6e756d65726f757320676170732e20205468650a"
	"2068756e6472656473206f66206578697374696e"
	"67204c445020646f63756d656e7473207072650a"
	"73656e7420626f7468206f766572766965777320"
	"616e642064657461696c73206f663a207468650a"
	"20474e552f4c696e7578204f7065726174696e67"
	"2053797374656d2c2053797374656d2041646d0a"
	"696e697374726174696f6e2c2048617264776172"
	"652c204e6574776f726b732c205365727665720a"
	"732c20475549732c2050726f6772616d6d696e67"
	"2c204c616e677561676520537570706f72742c0a"
	"206574632e204e6f7420657665727920696d706f"
	"7274616e7420746f70696320697320637572720a"
	"656e746c7920636f766572656420736f204c4450"
	"206973207365656b696e67206e6577206175740a"
	"686f727320746f2066696c6c20696e2074686520"
	"676170732e2020416e206164646974696f6e610a"
	"6c20676f616c20697320746f20636f6c6c61626f"
	"72617465206f6e20616c6c206f6620746865200a"
	"697373756573206f6620474e552f4c696e757820"
	"646f63756d656e746174696f6e2e20576520680a"
	"6f706520746f2065737461626c69736820612073"
	"797374656d206f6620646f63756d656e7461740a"
	"696f6e2074686174206973206561737920746f20"
	"75736520616e64207365617263682e205468690a"
	"7320696e636c756465732074686520696e746567"
	"726174696f6e206f6620616c6c20617661696c0a"
	"61626c6520646f63756d656e74732e2020576520"
	"667265656c792064697374726962757465206f0a"
	"757220646f63756d656e74732076696120746865"
	"20496e7465726e65742e20536f6d65206d616a0a"
	"6f7220646973747269627574696f6e73206f6620"
	"4c696e757820696e636c756465207468656d200a"
	"6f6e204344732e20496620796f75206172652069"
	"6e746572657374656420696e207075626c69730a"
	"68696e6720616e79206f6620746865204c445020"
	"776f726b732c207365652074686520736563740a"
	"696f6e20225075626c697368696e67204c445020"
	"446f63756d656e7473222062656c6f772e20200a"
	"546865204c445020697320657373656e7469616c"
	"6c792061206c6f6f7365207465616d206f66200a"
	"766f6c756e74656572732077697468206d696e69"
	"6d616c2063656e7472616c206f7267616e697a0a"
	"6174696f6e2e20416e796f6e652077686f20776f"
	"756c64206c696b6520746f2068656c702069730a"
	"2077656c636f6d6520746f206a6f696e20696e20"
	"74686973206566666f72742e205765206665650a"
	"6c207468617420776f726b696e6720746f676574"
	"68657220696e666f726d616c6c7920616e64200a"
	"64697363757373696e672070726f6a6563747320"
	"6f6e206f7572206d61696c696e67206c6973740a"
	"732069732074686520626573742077617920746f"
	"20676f2e205768656e207765206469736167720a"
	"6565206f6e207468696e67732c20776520747279"
	"20746f20726561736f6e2077697468206561630a"
	"68206f7468657220756e74696c20776520726561"
	"636820616e20696e666f726d656420636f6e730a"
	"656e7375732e2020202020626c61617220202020"
	"202020202020202020202020202020202020200a",

	"200cc84315cdecf4bb1f5a7b08004500"	// Ethernet wrapped
	"00342d1b400080060000c0a801088061"	// TCP packet
	"1b25d5940050e1670c23000000008002"	//
	"20005d5d0000020405b4010303080101"	//
	"0402",					//

	"ecf4bb1f5a7b2c9efc5db66508004500"	// Ethernet wrapped
	"0041bf8b0000ff1178c0c0a80107c0a8"	// UDP packet
	"010821a2f451002dd7b04d464e508232"	//
	"00003fb600000000001500000000464b"	//
	"eaaa00000005000000000000000000"


	"feff2000010000000100000008004500"	// ��...........E.
	"02070f4540008006901091fea0ed41d0"	// ...E@......���A�
	"e4df0d2c005038affe14114c618c5018"	// ��.,.P8��..La.P.
	"25bca9580000474554202f646f776e6c"	// %��X..GET/downl
	"6f61642e68746d6c20485454502f312e"	// oad.htmlHTTP/1.
	"310d0a486f73743a207777772e657468"	// 1..Host:www.eth
	"657265616c2e636f6d0d0a557365722d"	// ereal.com..User-
	"4167656e743a204d6f7a696c6c612f35"	// Agent:Mozilla/5
	"2e30202857696e646f77733b20553b20"	// .0(Windows;U;
	"57696e646f7773204e5420352e313b20"	// WindowsNT5.1;
	"656e2d55533b2072763a312e36292047"	// en-US;rv:1.6)G
	"65636b6f2f32303034303131330d0a41"	// ecko/20040113..A
	"63636570743a20746578742f786d6c2c"	// ccept:text/xml,
	"6170706c69636174696f6e2f786d6c2c"	// application/xml,
	"6170706c69636174696f6e2f7868746d"	// application/xhtm
	"6c2b786d6c2c746578742f68746d6c3b"	// l+xml,text/html;
	"713d302e392c746578742f706c61696e"	// q=0.9,text/plain
	"3b713d302e382c696d6167652f706e67"	// ;q=0.8,image/png
	"2c696d6167652f6a7065672c696d6167"	// ,image/jpeg,imag
	"652f6769663b713d302e322c2a2f2a3b"	// e/gif;q=0.2,*/*;
	"713d302e310d0a4163636570742d4c61"	// q=0.1..Accept-La
	"6e67756167653a20656e2d75732c656e"	// nguage:en-us,en
	"3b713d302e350d0a4163636570742d45"	// ;q=0.5..Accept-E
	"6e636f64696e673a20677a69702c6465"	// ncoding:gzip,de
	"666c6174650d0a4163636570742d4368"	// flate..Accept-Ch
	"61727365743a2049534f2d383835392d"	// arset:ISO-8859-
	"312c7574662d383b713d302e372c2a3b"	// 1,utf-8;q=0.7,*;
	"713d302e370d0a4b6565702d416c6976"	// q=0.7..Keep-Aliv
	"653a203330300d0a436f6e6e65637469"	// e:300..Connecti
	"6f6e3a206b6565702d616c6976650d0a"	// on:keep-alive..
	"526566657265723a20687474703a2f2f"	// Referer:http://
	"7777772e657468657265616c2e636f6d"	// www.ethereal.com
	"2f646576656c6f706d656e742e68746d"	// /development.htm
	"6c0d0a0d0a",				// l....

};
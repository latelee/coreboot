{ /* 4GB (16Gb + 16Gb) for dual rank dram setting */
	{
		.impedance_drvp = 0x9,
		.impedance_drvn = 0xa,
		.datlat_ucfirst = 19,

		.ca_train = {
			[CHANNEL_A] = { 8, 7, 6, 7, 4, 2, 2, 3, 4, 5},
			[CHANNEL_B] = { 0, 0, 1, 0, 0, 5, 5, 3, 6, 5}
		},

		.ca_train_center = {
			[CHANNEL_A] = 2,
			[CHANNEL_B] = 0
		},

		.wr_level = {
			[CHANNEL_A] = { 5, 6, 5, 6},
			[CHANNEL_B] = { 6, 6, 6, 4}
		},

		.gating_win = {
			[CHANNEL_A] = {
					{ 28, 56},
					{ 28, 56}
			},
			[CHANNEL_B] = {
					{ 28, 56},
					{ 28, 56}
			}
		},

		.rx_dqs_dly = {
			[CHANNEL_A] = 0x110e0b0b,
			[CHANNEL_B] = 0x12100d0d
		},

		.rx_dq_dly = {
			[CHANNEL_A] = {
						0x01040302,
						0x04010300,
						0x02040300,
						0x04030302,
						0x04070400,
						0x07070707,
						0x05070808,
						0x00010404
			},
			[CHANNEL_B] = {
						0x05060604,
						0x04010400,
						0x05070300,
						0x05030504,
						0x07090500,
						0x08090707,
						0x080a0a0a,
						0x02000604
			}
		},
	},
	{
		.actim     = 0xaafd478c,
		.actim1    = 0x91001f59,
		.actim05t  = 0x000025e1,
		.conf1     = 0x00048403,
		.conf2     = 0x030000a9,
		.ddr2ctl   = 0x000063b1,
		.gddr3ctl1 = 0x11000000,
		.misctl0   = 0x21000000,
		.pd_ctrl   = 0xd1976442,
		.rkcfg     = 0x002156c1,
		.test2_3   = 0xbfc70401,
		.test2_4   = 0x2801110d
	},
	{
		.cona     = 0xa053a057,
		.conb     = 0x17283544,
		.conc     = 0x0a1a0b1a,
		.cond     = 0x00000000,
		.cone     = 0xffff0848,
		.conf     = 0x08420000,
		.cong     = 0x2b2b2a38,
		.conh     = 0x00000000,
		.conm_1   = 0x40000500,
		.conm_2   = 0x400005ff,
		.mdct_1   = 0x80030303,
		.mdct_2   = 0x34220c3f,
		.test0    = 0xcccccccc,
		.test1    = 0xcccccccc,
		.testb    = 0x00060124,
		.testc    = 0x38470000,
		.testd    = 0x00000000,
		.arba     = 0x7f077a49,
		.arbc     = 0xa0a070dd,
		.arbd     = 0x07007046,
		.arbe     = 0x40407046,
		.arbf     = 0xa0a070c6,
		.arbg     = 0xffff7047,
		.arbi     = 0x20406188,
		.arbj     = 0x9719595e,
		.arbk     = 0x64f3fc79,
		.slct_1   = 0x00010800,
		.slct_2   = 0xff03ff00,
		.bmen     = 0x00ff0001
	},
	{
		.mrs_1  = 0x00830001,
		.mrs_2  = 0x001c0002,
		.mrs_3  = 0x00010003,
		.mrs_10 = 0x00ff000a,
		.mrs_11 = 0x0000000b,
		.mrs_63 = 0x0000003f
	},
	.type = TYPE_LPDDR3,
	.dram_freq = 896 * MHz,
},

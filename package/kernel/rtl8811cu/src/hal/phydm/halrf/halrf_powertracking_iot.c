/******************************************************************************
 *
 * Copyright(c) 2007 - 2017  Realtek Corporation.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * The full GNU General Public License is included in this distribution in the
 * file called LICENSE.
 *
 * Contact Information:
 * wlanfae <wlanfae@realtek.com>
 * Realtek Corporation, No. 2, Innovation Road II, Hsinchu Science Park,
 * Hsinchu 300, Taiwan.
 *
 * Larry Finger <Larry.Finger@lwfinger.net>
 *
 *****************************************************************************/

/*============================================================	*/
/* include files												*/
/*============================================================	*/
#include "mp_precomp.h"
#include "phydm_precomp.h"

/* ************************************************************
 * Global var
 * ************************************************************
 */

const u32 ofdm_swing_table[OFDM_TABLE_SIZE] = {
	0x7f8001fe,	/* 0, +6.0dB */
	0x788001e2,	/* 1, +5.5dB */
	0x71c001c7,	/* 2, +5.0dB*/
	0x6b8001ae,	/* 3, +4.5dB*/
	0x65400195,	/* 4, +4.0dB*/
	0x5fc0017f,	/* 5, +3.5dB*/
	0x5a400169,	/* 6, +3.0dB*/
	0x55400155,	/* 7, +2.5dB*/
	0x50800142,	/* 8, +2.0dB*/
	0x4c000130,	/* 9, +1.5dB*/
	0x47c0011f,	/* 10, +1.0dB*/
	0x43c0010f,	/* 11, +0.5dB*/
	0x40000100,	/* 12, +0dB*/
	0x3c8000f2,	/* 13, -0.5dB*/
	0x390000e4,	/* 14, -1.0dB*/
	0x35c000d7,	/* 15, -1.5dB*/
	0x32c000cb,	/* 16, -2.0dB*/
	0x300000c0,	/* 17, -2.5dB*/
	0x2d4000b5,	/* 18, -3.0dB*/
	0x2ac000ab,	/* 19, -3.5dB*/
	0x288000a2,	/* 20, -4.0dB*/
	0x26000098,	/* 21, -4.5dB*/
	0x24000090,	/* 22, -5.0dB*/
	0x22000088,	/* 23, -5.5dB*/
	0x20000080,	/* 24, -6.0dB*/
	0x1e400079,	/* 25, -6.5dB*/
	0x1c800072,	/* 26, -7.0dB*/
	0x1b00006c,	/* 27. -7.5dB*/
	0x19800066,	/* 28, -8.0dB*/
	0x18000060,	/* 29, -8.5dB*/
	0x16c0005b,	/* 30, -9.0dB*/
	0x15800056,	/* 31, -9.5dB*/
	0x14400051,	/* 32, -10.0dB*/
	0x1300004c,	/* 33, -10.5dB*/
	0x12000048,	/* 34, -11.0dB*/
	0x11000044,	/* 35, -11.5dB*/
	0x10000040,	/* 36, -12.0dB*/
};

const u8 cck_swing_table_ch1_ch13[CCK_TABLE_SIZE][8] = {
	{0x36, 0x35, 0x2e, 0x25, 0x1c, 0x12, 0x09, 0x04},	/* 0, +0dB */
	{0x33, 0x32, 0x2b, 0x23, 0x1a, 0x11, 0x08, 0x04},	/* 1, -0.5dB */
	{0x30, 0x2f, 0x29, 0x21, 0x19, 0x10, 0x08, 0x03},	/* 2, -1.0dB*/
	{0x2d, 0x2d, 0x27, 0x1f, 0x18, 0x0f, 0x08, 0x03},	/* 3, -1.5dB*/
	{0x2b, 0x2a, 0x25, 0x1e, 0x16, 0x0e, 0x07, 0x03},	/* 4, -2.0dB */
	{0x28, 0x28, 0x22, 0x1c, 0x15, 0x0d, 0x07, 0x03},	/* 5, -2.5dB*/
	{0x26, 0x25, 0x21, 0x1b, 0x14, 0x0d, 0x06, 0x03},	/* 6, -3.0dB*/
	{0x24, 0x23, 0x1f, 0x19, 0x13, 0x0c, 0x06, 0x03},	/* 7, -3.5dB*/
	{0x22, 0x21, 0x1d, 0x18, 0x11, 0x0b, 0x06, 0x02},	/* 8, -4.0dB */
	{0x20, 0x20, 0x1b, 0x16, 0x11, 0x08, 0x05, 0x02},	/* 9, -4.5dB*/
	{0x1f, 0x1e, 0x1a, 0x15, 0x10, 0x0a, 0x05, 0x02},	/* 10, -5.0dB */
	{0x1d, 0x1c, 0x18, 0x14, 0x0f, 0x0a, 0x05, 0x02},	/* 11, -5.5dB*/
	{0x1b, 0x1a, 0x17, 0x13, 0x0e, 0x09, 0x04, 0x02},	/* 12, -6.0dB <== default */
	{0x1a, 0x19, 0x16, 0x12, 0x0d, 0x09, 0x04, 0x02},	/* 13, -6.5dB*/
	{0x18, 0x17, 0x15, 0x11, 0x0c, 0x08, 0x04, 0x02},	/* 14, -7.0dB */
	{0x17, 0x16, 0x13, 0x10, 0x0c, 0x08, 0x04, 0x02},	/* 15, -7.5dB*/
	{0x16, 0x15, 0x12, 0x0f, 0x0b, 0x07, 0x04, 0x01},	/* 16, -8.0dB */
	{0x14, 0x14, 0x11, 0x0e, 0x0b, 0x07, 0x03, 0x02},	/* 17, -8.5dB*/
	{0x13, 0x13, 0x10, 0x0d, 0x0a, 0x06, 0x03, 0x01},	/* 18, -9.0dB */
	{0x12, 0x12, 0x0f, 0x0c, 0x09, 0x06, 0x03, 0x01},	/* 19, -9.5dB*/
	{0x11, 0x11, 0x0f, 0x0c, 0x09, 0x06, 0x03, 0x01},	/* 20, -10.0dB*/
	{0x10, 0x10, 0x0e, 0x0b, 0x08, 0x05, 0x03, 0x01},	/* 21, -10.5dB*/
	{0x0f, 0x0f, 0x0d, 0x0b, 0x08, 0x05, 0x03, 0x01},	/* 22, -11.0dB*/
	{0x0e, 0x0e, 0x0c, 0x0a, 0x08, 0x05, 0x02, 0x01},	/* 23, -11.5dB*/
	{0x0d, 0x0d, 0x0c, 0x0a, 0x07, 0x05, 0x02, 0x01},	/* 24, -12.0dB*/
	{0x0d, 0x0c, 0x0b, 0x09, 0x07, 0x04, 0x02, 0x01},	/* 25, -12.5dB*/
	{0x0c, 0x0c, 0x0a, 0x09, 0x06, 0x04, 0x02, 0x01},	/* 26, -13.0dB*/
	{0x0b, 0x0b, 0x0a, 0x08, 0x06, 0x04, 0x02, 0x01},	/* 27, -13.5dB*/
	{0x0b, 0x0a, 0x09, 0x08, 0x06, 0x04, 0x02, 0x01},	/* 28, -14.0dB*/
	{0x0a, 0x0a, 0x09, 0x07, 0x05, 0x03, 0x02, 0x01},	/* 29, -14.5dB*/
	{0x0a, 0x09, 0x08, 0x07, 0x05, 0x03, 0x02, 0x01},	/* 30, -15.0dB*/
	{0x09, 0x09, 0x08, 0x06, 0x05, 0x03, 0x01, 0x01},	/* 31, -15.5dB*/
	{0x09, 0x08, 0x07, 0x06, 0x04, 0x03, 0x01, 0x01}	/* 32, -16.0dB*/
};

const u8 cck_swing_table_ch14[CCK_TABLE_SIZE][8] = {
	{0x36, 0x35, 0x2e, 0x1b, 0x00, 0x00, 0x00, 0x00},	/* 0, +0dB */
	{0x33, 0x32, 0x2b, 0x19, 0x00, 0x00, 0x00, 0x00},	/* 1, -0.5dB */
	{0x30, 0x2f, 0x29, 0x18, 0x00, 0x00, 0x00, 0x00},	/* 2, -1.0dB */
	{0x2d, 0x2d, 0x17, 0x17, 0x00, 0x00, 0x00, 0x00},	/* 3, -1.5dB*/
	{0x2b, 0x2a, 0x25, 0x15, 0x00, 0x00, 0x00, 0x00},	/* 4, -2.0dB */
	{0x28, 0x28, 0x24, 0x14, 0x00, 0x00, 0x00, 0x00},	/* 5, -2.5dB*/
	{0x26, 0x25, 0x21, 0x13, 0x00, 0x00, 0x00, 0x00},	/* 6, -3.0dB */
	{0x24, 0x23, 0x1f, 0x12, 0x00, 0x00, 0x00, 0x00},	/* 7, -3.5dB */
	{0x22, 0x21, 0x1d, 0x11, 0x00, 0x00, 0x00, 0x00},	/* 8, -4.0dB */
	{0x20, 0x20, 0x1b, 0x10, 0x00, 0x00, 0x00, 0x00},	/* 9, -4.5dB*/
	{0x1f, 0x1e, 0x1a, 0x0f, 0x00, 0x00, 0x00, 0x00},	/* 10, -5.0dB */
	{0x1d, 0x1c, 0x18, 0x0e, 0x00, 0x00, 0x00, 0x00},	/* 11, -5.5dB*/
	{0x1b, 0x1a, 0x17, 0x0e, 0x00, 0x00, 0x00, 0x00},	/* 12, -6.0dB  <== default*/
	{0x1a, 0x19, 0x16, 0x0d, 0x00, 0x00, 0x00, 0x00},	/* 13, -6.5dB */
	{0x18, 0x17, 0x15, 0x0c, 0x00, 0x00, 0x00, 0x00},	/* 14, -7.0dB */
	{0x17, 0x16, 0x13, 0x0b, 0x00, 0x00, 0x00, 0x00},	/* 15, -7.5dB*/
	{0x16, 0x15, 0x12, 0x0b, 0x00, 0x00, 0x00, 0x00},	/* 16, -8.0dB */
	{0x14, 0x14, 0x11, 0x0a, 0x00, 0x00, 0x00, 0x00},	/* 17, -8.5dB*/
	{0x13, 0x13, 0x10, 0x0a, 0x00, 0x00, 0x00, 0x00},	/* 18, -9.0dB */
	{0x12, 0x12, 0x0f, 0x09, 0x00, 0x00, 0x00, 0x00},	/* 19, -9.5dB*/
	{0x11, 0x11, 0x0f, 0x09, 0x00, 0x00, 0x00, 0x00},	/* 20, -10.0dB*/
	{0x10, 0x10, 0x0e, 0x08, 0x00, 0x00, 0x00, 0x00},	/* 21, -10.5dB*/
	{0x0f, 0x0f, 0x0d, 0x08, 0x00, 0x00, 0x00, 0x00},	/* 22, -11.0dB*/
	{0x0e, 0x0e, 0x0c, 0x07, 0x00, 0x00, 0x00, 0x00},	/* 23, -11.5dB*/
	{0x0d, 0x0d, 0x0c, 0x07, 0x00, 0x00, 0x00, 0x00},	/* 24, -12.0dB*/
	{0x0d, 0x0c, 0x0b, 0x06, 0x00, 0x00, 0x00, 0x00},	/* 25, -12.5dB*/
	{0x0c, 0x0c, 0x0a, 0x06, 0x00, 0x00, 0x00, 0x00},	/* 26, -13.0dB*/
	{0x0b, 0x0b, 0x0a, 0x06, 0x00, 0x00, 0x00, 0x00},	/* 27, -13.5dB*/
	{0x0b, 0x0a, 0x09, 0x05, 0x00, 0x00, 0x00, 0x00},	/* 28, -14.0dB*/
	{0x0a, 0x0a, 0x09, 0x05, 0x00, 0x00, 0x00, 0x00},	/* 29, -14.5dB*/
	{0x0a, 0x09, 0x08, 0x05, 0x00, 0x00, 0x00, 0x00},	/* 30, -15.0dB*/
	{0x09, 0x09, 0x08, 0x05, 0x00, 0x00, 0x00, 0x00},	/* 31, -15.5dB*/
	{0x09, 0x08, 0x07, 0x04, 0x00, 0x00, 0x00, 0x00}	/* 32, -16.0dB*/
};

const u32 ofdm_swing_table_new[OFDM_TABLE_SIZE] = {
	0x0b40002d, /* 0,  -15.0dB	*/
	0x0c000030, /* 1,  -14.5dB*/
	0x0cc00033, /* 2,  -14.0dB*/
	0x0d800036, /* 3,  -13.5dB*/
	0x0e400039, /* 4,  -13.0dB */
	0x0f00003c, /* 5,  -12.5dB*/
	0x10000040, /* 6,  -12.0dB*/
	0x11000044, /* 7,  -11.5dB*/
	0x12000048, /* 8,  -11.0dB*/
	0x1300004c, /* 9,  -10.5dB*/
	0x14400051, /* 10, -10.0dB*/
	0x15800056, /* 11, -9.5dB*/
	0x16c0005b, /* 12, -9.0dB*/
	0x18000060, /* 13, -8.5dB*/
	0x19800066, /* 14, -8.0dB*/
	0x1b00006c, /* 15, -7.5dB*/
	0x1c800072, /* 16, -7.0dB*/
	0x1e400079, /* 17, -6.5dB*/
	0x20000080, /* 18, -6.0dB*/
	0x22000088, /* 19, -5.5dB*/
	0x24000090, /* 20, -5.0dB*/
	0x26000098, /* 21, -4.5dB*/
	0x288000a2, /* 22, -4.0dB*/
	0x2ac000ab, /* 23, -3.5dB*/
	0x2d4000b5, /* 24, -3.0dB*/
	0x300000c0, /* 25, -2.5dB*/
	0x32c000cb, /* 26, -2.0dB*/
	0x35c000d7, /* 27, -1.5dB*/
	0x390000e4, /* 28, -1.0dB*/
	0x3c8000f2, /* 29, -0.5dB*/
	0x40000100, /* 30, +0dB*/
	0x43c0010f, /* 31, +0.5dB*/
	0x47c0011f, /* 32, +1.0dB*/
	0x4c000130, /* 33, +1.5dB*/
	0x50800142, /* 34, +2.0dB*/
	0x55400155, /* 35, +2.5dB*/
	0x5a400169, /* 36, +3.0dB*/
	0x5fc0017f, /* 37, +3.5dB*/
	0x65400195, /* 38, +4.0dB*/
	0x6b8001ae, /* 39, +4.5dB*/
	0x71c001c7, /* 40, +5.0dB*/
	0x788001e2, /* 41, +5.5dB*/
	0x7f8001fe  /* 42, +6.0dB*/
};

const u8 cck_swing_table_ch1_ch14_88f[CCK_TABLE_SIZE_88F][16] = {
	{0x44, 0x42, 0x3C, 0x33, 0x28, 0x1C, 0x13, 0x0B, 0x05, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},    /*-16dB*/
	{0x48, 0x46, 0x3F, 0x36, 0x2A, 0x1E, 0x14, 0x0B, 0x05, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},    /*-15.5dB*/
	{0x4D, 0x4A, 0x43, 0x39, 0x2C, 0x20, 0x15, 0x0C, 0x06, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},    /*-15dB*/
	{0x51, 0x4F, 0x47, 0x3C, 0x2F, 0x22, 0x16, 0x0D, 0x06, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},    /*-14.5dB*/
	{0x56, 0x53, 0x4B, 0x40, 0x32, 0x24, 0x17, 0x0E, 0x06, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},    /*-14dB*/
	{0x5B, 0x58, 0x50, 0x43, 0x35, 0x26, 0x19, 0x0E, 0x07, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},    /*-13.5dB*/
	{0x60, 0x5D, 0x54, 0x47, 0x38, 0x28, 0x1A, 0x0F, 0x07, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},    /*-13dB*/
	{0x66, 0x63, 0x59, 0x4C, 0x3B, 0x2B, 0x1C, 0x10, 0x08, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},    /*-12.5dB*/
	{0x6C, 0x69, 0x5F, 0x50, 0x3F, 0x2D, 0x1E, 0x11, 0x08, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},    /*-12dB*/
	{0x73, 0x6F, 0x64, 0x55, 0x42, 0x30, 0x1F, 0x12, 0x08, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},    /*-11.5dB*/
	{0x79, 0x76, 0x6A, 0x5A, 0x46, 0x33, 0x21, 0x13, 0x09, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},    /*-11dB*/
	{0x81, 0x7C, 0x71, 0x5F, 0x4A, 0x36, 0x23, 0x14, 0x0A, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},    /*-10.5dB*/
	{0x88, 0x84, 0x77, 0x65, 0x4F, 0x39, 0x25, 0x15, 0x0A, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},    /*-10dB*/
	{0x90, 0x8C, 0x7E, 0x6B, 0x54, 0x3C, 0x27, 0x17, 0x0B, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},    /*-9.5dB*/
	{0x99, 0x94, 0x86, 0x71, 0x58, 0x40, 0x2A, 0x18, 0x0B, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},    /*-9dB*/
	{0xA2, 0x9D, 0x8E, 0x78, 0x5E, 0x43, 0x2C, 0x19, 0x0C, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},    /*-8.5dB*/
	{0xAC, 0xA6, 0x96, 0x7F, 0x63, 0x47, 0x2F, 0x1B, 0x0D, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},    /*-8dB*/
	{0xB6, 0xB0, 0x9F, 0x87, 0x69, 0x4C, 0x32, 0x1D, 0x0D, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},    /*-7.5dB*/
	{0xC1, 0xBA, 0xA8, 0x8F, 0x6F, 0x50, 0x35, 0x1E, 0x0E, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},    /*-7dB*/
	{0xCC, 0xC5, 0xB2, 0x97, 0x76, 0x55, 0x38, 0x20, 0x0F, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},    /*-6.5dB*/
	{0xD8, 0xD1, 0xBD, 0xA0, 0x7D, 0x5A, 0x3B, 0x22, 0x10, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}     /*-6dB*/
};

const u8 cck_swing_table_ch1_ch13_88f[CCK_TABLE_SIZE_88F][16] = {
	{0x44, 0x42, 0x3C, 0x33, 0x28, 0x1C, 0x13, 0x0B, 0x05, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},    /*-16dB*/
	{0x48, 0x46, 0x3F, 0x36, 0x2A, 0x1E, 0x14, 0x0B, 0x05, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},    /*-15.5dB*/
	{0x4D, 0x4A, 0x43, 0x39, 0x2C, 0x20, 0x15, 0x0C, 0x06, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},    /*-15dB*/
	{0x51, 0x4F, 0x47, 0x3C, 0x2F, 0x22, 0x16, 0x0D, 0x06, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},    /*-14.5dB*/
	{0x56, 0x53, 0x4B, 0x40, 0x32, 0x24, 0x17, 0x0E, 0x06, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},    /*-14dB*/
	{0x5B, 0x58, 0x50, 0x43, 0x35, 0x26, 0x19, 0x0E, 0x07, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},    /*-13.5dB*/
	{0x60, 0x5D, 0x54, 0x47, 0x38, 0x28, 0x1A, 0x0F, 0x07, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},    /*-13dB*/
	{0x66, 0x63, 0x59, 0x4C, 0x3B, 0x2B, 0x1C, 0x10, 0x08, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},    /*-12.5dB*/
	{0x6C, 0x69, 0x5F, 0x50, 0x3F, 0x2D, 0x1E, 0x11, 0x08, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},    /*-12dB*/
	{0x73, 0x6F, 0x64, 0x55, 0x42, 0x30, 0x1F, 0x12, 0x08, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},    /*-11.5dB*/
	{0x79, 0x76, 0x6A, 0x5A, 0x46, 0x33, 0x21, 0x13, 0x09, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},    /*-11dB*/
	{0x81, 0x7C, 0x71, 0x5F, 0x4A, 0x36, 0x23, 0x14, 0x0A, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},    /*-10.5dB*/
	{0x88, 0x84, 0x77, 0x65, 0x4F, 0x39, 0x25, 0x15, 0x0A, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},    /*-10dB*/
	{0x90, 0x8C, 0x7E, 0x6B, 0x54, 0x3C, 0x27, 0x17, 0x0B, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},    /*-9.5dB*/
	{0x99, 0x94, 0x86, 0x71, 0x58, 0x40, 0x2A, 0x18, 0x0B, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},    /*-9dB*/
	{0xA2, 0x9D, 0x8E, 0x78, 0x5E, 0x43, 0x2C, 0x19, 0x0C, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},    /*-8.5dB*/
	{0xAC, 0xA6, 0x96, 0x7F, 0x63, 0x47, 0x2F, 0x1B, 0x0D, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},    /*-8dB*/
	{0xB6, 0xB0, 0x9F, 0x87, 0x69, 0x4C, 0x32, 0x1D, 0x0D, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},    /*-7.5dB*/
	{0xC1, 0xBA, 0xA8, 0x8F, 0x6F, 0x50, 0x35, 0x1E, 0x0E, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},    /*-7dB*/
	{0xCC, 0xC5, 0xB2, 0x97, 0x76, 0x55, 0x38, 0x20, 0x0F, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},    /*-6.5dB*/
	{0xD8, 0xD1, 0xBD, 0xA0, 0x7D, 0x5A, 0x3B, 0x22, 0x10, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}     /*-6dB*/
};

const u8 cck_swing_table_ch14_88f[CCK_TABLE_SIZE_88F][16] = {
	{0x44,	 0x42, 0x3C, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},    /*-16dB*/
	{0x48, 0x46, 0x3F, 0x2A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},    /*-15.5dB*/
	{0x4D, 0x4A, 0x43, 0x2C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},    /*-15dB*/
	{0x51, 0x4F, 0x47, 0x2F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	    /*-14.5dB*/
	{0x56, 0x53, 0x4B, 0x32, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},    /*-14dB*/
	{0x5B, 0x58, 0x50, 0x35, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},    /*-13.5dB*/
	{0x60, 0x5D, 0x54, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},    /*-13dB*/
	{0x66, 0x63, 0x59, 0x3B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},    /*-12.5dB*/
	{0x6C, 0x69, 0x5F, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},    /*-12dB*/
	{0x73, 0x6F, 0x64, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},    /*-11.5dB*/
	{0x79, 0x76, 0x6A, 0x46, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},    /*-11dB*/
	{0x81, 0x7C, 0x71, 0x4A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},    /*-10.5dB*/
	{0x88, 0x84, 0x77, 0x4F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},    /*-10dB*/
	{0x90, 0x8C, 0x7E, 0x54, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},    /*-9.5dB*/
	{0x99, 0x94, 0x86, 0x58, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},    /*-9dB*/
	{0xA2, 0x9D, 0x8E, 0x5E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},    /*-8.5dB*/
	{0xAC, 0xA6, 0x96, 0x63, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},    /*-8dB*/
	{0xB6, 0xB0, 0x9F, 0x69, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},    /*-7.5dB*/
	{0xC1, 0xBA, 0xA8, 0x6F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},    /*-7dB*/
	{0xCC, 0xC5, 0xB2, 0x76, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},    /*-6.5dB*/
	{0xD8, 0xD1, 0xBD, 0x7D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}     /*-6dB*/
};

const u8 cck_swing_table_ch1_ch13_new[CCK_TABLE_SIZE][8] = {
	{0x09, 0x08, 0x07, 0x06, 0x04, 0x03, 0x01, 0x01},	/*  0, -16.0dB*/
	{0x09, 0x09, 0x08, 0x06, 0x05, 0x03, 0x01, 0x01},	/*   1, -15.5dB*/
	{0x0a, 0x09, 0x08, 0x07, 0x05, 0x03, 0x02, 0x01},	/*  2, -15.0dB*/
	{0x0a, 0x0a, 0x09, 0x07, 0x05, 0x03, 0x02, 0x01},	/*   3, -14.5dB*/
	{0x0b, 0x0a, 0x09, 0x08, 0x06, 0x04, 0x02, 0x01},	/*   4, -14.0dB*/
	{0x0b, 0x0b, 0x0a, 0x08, 0x06, 0x04, 0x02, 0x01},	/*   5, -13.5dB*/
	{0x0c, 0x0c, 0x0a, 0x09, 0x06, 0x04, 0x02, 0x01},	/*   6, -13.0dB*/
	{0x0d, 0x0c, 0x0b, 0x09, 0x07, 0x04, 0x02, 0x01},	/*   7, -12.5dB*/
	{0x0d, 0x0d, 0x0c, 0x0a, 0x07, 0x05, 0x02, 0x01},	/*  8, -12.0dB*/
	{0x0e, 0x0e, 0x0c, 0x0a, 0x08, 0x05, 0x02, 0x01},	/*   9, -11.5dB*/
	{0x0f, 0x0f, 0x0d, 0x0b, 0x08, 0x05, 0x03, 0x01},	/*  10, -11.0dB*/
	{0x10, 0x10, 0x0e, 0x0b, 0x08, 0x05, 0x03, 0x01},	/*  11, -10.5dB*/
	{0x11, 0x11, 0x0f, 0x0c, 0x09, 0x06, 0x03, 0x01},	/*  12, -10.0dB*/
	{0x12, 0x12, 0x0f, 0x0c, 0x09, 0x06, 0x03, 0x01},	/*  13, -9.5dB*/
	{0x13, 0x13, 0x10, 0x0d, 0x0a, 0x06, 0x03, 0x01},	/*  14, -9.0dB */
	{0x14, 0x14, 0x11, 0x0e, 0x0b, 0x07, 0x03, 0x02},	/*  15, -8.5dB*/
	{0x16, 0x15, 0x12, 0x0f, 0x0b, 0x07, 0x04, 0x01},	/*  16, -8.0dB */
	{0x17, 0x16, 0x13, 0x10, 0x0c, 0x08, 0x04, 0x02},	/*  17, -7.5dB*/
	{0x18, 0x17, 0x15, 0x11, 0x0c, 0x08, 0x04, 0x02},	/*  18, -7.0dB */
	{0x1a, 0x19, 0x16, 0x12, 0x0d, 0x09, 0x04, 0x02},	/*  19, -6.5dB*/
	{0x1b, 0x1a, 0x17, 0x13, 0x0e, 0x09, 0x04, 0x02},	/*20, -6.0dB */
	{0x1d, 0x1c, 0x18, 0x14, 0x0f, 0x0a, 0x05, 0x02},	/*  21, -5.5dB*/
	{0x1f, 0x1e, 0x1a, 0x15, 0x10, 0x0a, 0x05, 0x02},	/* 22, -5.0dB */
	{0x20, 0x20, 0x1b, 0x16, 0x11, 0x08, 0x05, 0x02},	/*  23, -4.5dB*/
	{0x22, 0x21, 0x1d, 0x18, 0x11, 0x0b, 0x06, 0x02},	/*  24, -4.0dB */
	{0x24, 0x23, 0x1f, 0x19, 0x13, 0x0c, 0x06, 0x03},	/*  25, -3.5dB*/
	{0x26, 0x25, 0x21, 0x1b, 0x14, 0x0d, 0x06, 0x03},	/*  26, -3.0dB*/
	{0x28, 0x28, 0x22, 0x1c, 0x15, 0x0d, 0x07, 0x03},	/*  27, -2.5dB*/
	{0x2b, 0x2a, 0x25, 0x1e, 0x16, 0x0e, 0x07, 0x03},	/*  28, -2.0dB */
	{0x2d, 0x2d, 0x27, 0x1f, 0x18, 0x0f, 0x08, 0x03},	/*  29, -1.5dB*/
	{0x30, 0x2f, 0x29, 0x21, 0x19, 0x10, 0x08, 0x03},	/*  30, -1.0dB*/
	{0x33, 0x32, 0x2b, 0x23, 0x1a, 0x11, 0x08, 0x04},	/*  31, -0.5dB*/
	{0x36, 0x35, 0x2e, 0x25, 0x1c, 0x12, 0x09, 0x04}	/*  32, +0dB*/
};

const u8 cck_swing_table_ch14_new[CCK_TABLE_SIZE][8] = {
	{0x09, 0x08, 0x07, 0x04, 0x00, 0x00, 0x00, 0x00},	/*  0, -16.0dB*/
	{0x09, 0x09, 0x08, 0x05, 0x00, 0x00, 0x00, 0x00},	/* 1, -15.5dB*/
	{0x0a, 0x09, 0x08, 0x05, 0x00, 0x00, 0x00, 0x00},	/*  2, -15.0dB*/
	{0x0a, 0x0a, 0x09, 0x05, 0x00, 0x00, 0x00, 0x00},	/* 3, -14.5dB*/
	{0x0b, 0x0a, 0x09, 0x05, 0x00, 0x00, 0x00, 0x00},	/*  4, -14.0dB*/
	{0x0b, 0x0b, 0x0a, 0x06, 0x00, 0x00, 0x00, 0x00},	/*5, -13.5dB*/
	{0x0c, 0x0c, 0x0a, 0x06, 0x00, 0x00, 0x00, 0x00},	/* 6, -13.0dB*/
	{0x0d, 0x0c, 0x0b, 0x06, 0x00, 0x00, 0x00, 0x00},	/*  7, -12.5dB*/
	{0x0d, 0x0d, 0x0c, 0x07, 0x00, 0x00, 0x00, 0x00},	/* 8, -12.0dB*/
	{0x0e, 0x0e, 0x0c, 0x07, 0x00, 0x00, 0x00, 0x00},	/* 9, -11.5dB*/
	{0x0f, 0x0f, 0x0d, 0x08, 0x00, 0x00, 0x00, 0x00},	/* 10, -11.0dB*/
	{0x10, 0x10, 0x0e, 0x08, 0x00, 0x00, 0x00, 0x00},	/*11, -10.5dB*/
	{0x11, 0x11, 0x0f, 0x09, 0x00, 0x00, 0x00, 0x00},	/* 12, -10.0dB*/
	{0x12, 0x12, 0x0f, 0x09, 0x00, 0x00, 0x00, 0x00},	/* 13, -9.5dB*/
	{0x13, 0x13, 0x10, 0x0a, 0x00, 0x00, 0x00, 0x00},	/*14, -9.0dB */
	{0x14, 0x14, 0x11, 0x0a, 0x00, 0x00, 0x00, 0x00},	/* 15, -8.5dB*/
	{0x16, 0x15, 0x12, 0x0b, 0x00, 0x00, 0x00, 0x00},	/* 16, -8.0dB */
	{0x17, 0x16, 0x13, 0x0b, 0x00, 0x00, 0x00, 0x00},	/* 17, -7.5dB*/
	{0x18, 0x17, 0x15, 0x0c, 0x00, 0x00, 0x00, 0x00},	/* 18, -7.0dB */
	{0x1a, 0x19, 0x16, 0x0d, 0x00, 0x00, 0x00, 0x00},	/* 19, -6.5dB */
	{0x1b, 0x1a, 0x17, 0x0e, 0x00, 0x00, 0x00, 0x00},	/* 20, -6.0dB */
	{0x1d, 0x1c, 0x18, 0x0e, 0x00, 0x00, 0x00, 0x00},	/* 21, -5.5dB*/
	{0x1f, 0x1e, 0x1a, 0x0f, 0x00, 0x00, 0x00, 0x00},	/* 22, -5.0dB */
	{0x20, 0x20, 0x1b, 0x10, 0x00, 0x00, 0x00, 0x00},	/*23, -4.5dB*/
	{0x22, 0x21, 0x1d, 0x11, 0x00, 0x00, 0x00, 0x00},	/* 24, -4.0dB */
	{0x24, 0x23, 0x1f, 0x12, 0x00, 0x00, 0x00, 0x00},	/* 25, -3.5dB */
	{0x26, 0x25, 0x21, 0x13, 0x00, 0x00, 0x00, 0x00},	/* 26, -3.0dB */
	{0x28, 0x28, 0x24, 0x14, 0x00, 0x00, 0x00, 0x00},	/*27, -2.5dB*/
	{0x2b, 0x2a, 0x25, 0x15, 0x00, 0x00, 0x00, 0x00},	/* 28, -2.0dB */
	{0x2d, 0x2d, 0x17, 0x17, 0x00, 0x00, 0x00, 0x00},	/*29, -1.5dB*/
	{0x30, 0x2f, 0x29, 0x18, 0x00, 0x00, 0x00, 0x00},	/* 30, -1.0dB */
	{0x33, 0x32, 0x2b, 0x19, 0x00, 0x00, 0x00, 0x00},	/* 31, -0.5dB */
	{0x36, 0x35, 0x2e, 0x1b, 0x00, 0x00, 0x00, 0x00}	/* 32, +0dB	*/
};

const u32 cck_swing_table_ch1_ch14_8723d[CCK_TABLE_SIZE_8723D] = {
	0x0CD,          /*0 ,    -20dB*/
	0x0D9,
	0x0E6,
	0x0F3,
	0x102,
	0x111,
	0x121,
	0x132,
	0x144,
	0x158,
	0x16C,
	0x182,
	0x198,
	0x1B1,
	0x1CA,
	0x1E5,
	0x202,
	0x221,
	0x241,
	0x263,
	0x287,
	0x2AE,
	0x2D6,
	0x301,
	0x32F,
	0x35F,
	0x392,
	0x3C9,
	0x402,
	0x43F,
	0x47F,
	0x4C3,
	0x50C,
	0x558,
	0x5A9,
	0x5FF,
	0x65A,
	0x6BA,
	0x720,
	0x78C,
	0x7FF,
};

/* JJ ADD 20161014 */
const u32 cck_swing_table_ch1_ch14_8710b[CCK_TABLE_SIZE_8710B] = {
	0x0CD,          /*0 ,    -20dB*/
	0x0D9,
	0x0E6,
	0x0F3,
	0x102,
	0x111,
	0x121,
	0x132,
	0x144,
	0x158,
	0x16C,
	0x182,
	0x198,
	0x1B1,
	0x1CA,
	0x1E5,
	0x202,
	0x221,
	0x241,
	0x263,
	0x287,
	0x2AE,
	0x2D6,
	0x301,
	0x32F,
	0x35F,
	0x392,
	0x3C9,
	0x402,
	0x43F,
	0x47F,
	0x4C3,
	0x50C,
	0x558,
	0x5A9,
	0x5FF,
	0x65A,
	0x6BA,
	0x720,
	0x78C,
	0x7FF,
};

/* Winnita ADD 20171116 PathA 0xAB4[10:0],PathB 0xAB4[21:11]*/
const u32 cck_swing_table_ch1_ch14_8192f[CCK_TABLE_SIZE_8192F] = {
	0x0CD,			 /*0 ,    -20dB*/
	0x0D9,
	0x0E6,
	0x0F3,
	0x102,
	0x111,
	0x121,
	0x132,
	0x144,
	0x158,
	0x16C,
	0x182,
	0x198,
	0x1B1,
	0x1CA,
	0x1E5,
	0x202,
	0x221,
	0x241,
	0x263,		/*19*/
	0x287,		/*20*/
	0x2AE,		/*21*/
	0x2D6,		/*22*/
	0x301,		/*23*/
	0x32F,		/*24*/
	0x35F,		/*25*/
	0x392,		/*26*/
	0x3C9,		/*27*/
	0x402,		/*28*/
	0x43F,		/*29*/
	0x47F,		/*30*/
	0x4C3,		/*31*/
	0x50C,		/*32*/
	0x558,		/*33*/
	0x5A9,		/*34*/
	0x5FF,		/*35*/
	0x65A,		/*36*/
	0x6BA,
	0x720,
	0x78C,
	0x7FF,
};

/* Winnita ADD 201805 PathA 0xAB4[10:0]*/
const u32 cck_swing_table_ch1_ch14_8721d[CCK_TABLE_SIZE_8721D] = {
	0x0CD,			 /*0 ,    -20dB*/
	0x0D9,
	0x0E6,
	0x0F3,
	0x102,
	0x111,
	0x121,
	0x132,
	0x144,
	0x158,
	0x16C,
	0x182,
	0x198,
	0x1B1,
	0x1CA,
	0x1E5,
	0x202,
	0x221,
	0x241,
	0x263,		/*19*/
	0x287,		/*20*/
	0x2AE,		/*21*/
	0x2D6,		/*22*/
	0x301,		/*23*/
	0x32F,		/*24*/
	0x35F,		/*25*/
	0x392,		/*26*/
	0x3C9,		/*27*/
	0x402,		/*28*/
	0x43F,		/*29*/
	0x47F,		/*30*/
	0x4C3,		/*31*/
	0x50C,		/*32*/
	0x558,		/*33*/
	0x5A9,		/*34*/
	0x5FF,		/*35*/
	0x65A,		/*36*/
	0x6BA,
	0x720,
	0x78C,
	0x7FF,
};

const u32 cck_swing_table_ch1_ch14_8710c[CCK_TABLE_SIZE_8710C] = {
	0x0CD,          /*0 ,    -20dB*/
	0x0D9,
	0x0E6,
	0x0F3,
	0x102,
	0x111,
	0x121,
	0x132,
	0x144,
	0x158,
	0x16C,
	0x182,
	0x198,
	0x1B1,
	0x1CA,
	0x1E5,
	0x202,
	0x221,
	0x241,
	0x263,
	0x287,
	0x2AE,
	0x2D6,
	0x301,
	0x32F,
	0x35F,
	0x392,
	0x3C9,
	0x402,
	0x43F,
	0x47F,
	0x4C3,
	0x50C,
	0x558,
	0x5A9,
	0x5FF,
	0x65A,
	0x6BA,
	0x720,
	0x78C,
	0x7FF,
};

const u32 cck_swing_table_03db_ch1_ch14_8710c[CCK_03DB_TABLE_SIZE_8710C] = {
	0x143,		/*0 ,    -4dB*/
	0x14C,		/*1 ,    -3.75dB*/
	0x156,		/*2 ,    -3.5dB*/
	0x160,
	0x16A,
	0x175,
	0x17F,
	0x18B,
	0x196,
	0x1A2,
	0x1AE,
	0x1BB,
	0x1C8,
	0x1D5,
	0x1E3,
	0x1F1,
	0x200,
	0x20F,
	0x21E,
	0x22F,
	0x23F,
	0x250,
	0x261,
	0x273,
	0x285,
	0x298,
	0x2AB,
	0x2BF,
	0x2D6,
	0x2E9,
	0x2FF,
	0x315,
	0x32C,
	0x344,
	0x35C,
	0x375,
	0x390,
	0x3AA,
	0x3C5,
	0x3E1,
	0x402,		/*40 ,    +6dB	default*/
	0x41C,
	0x43B,
	0x45A,
	0x47C,
	0x49C,
	0x4BF,
	0x4E2,
	0x510,
	0x52C,
	0x553,
	0x57B,
	0x5A5,
	0x5CE,
	0x5F9,
	0x626,
	0x655,
	0x683,
	0x6B5,
	0x6E6,
	0x71E,
	0x74E,
	0x786,
	0x7BD,
	0x7F9,
	0x832,
	0x871,
	0x8AF,
	0x8F2,
	0x932,
	0x977,
	0x9BE,
	0xA0E,
	0xA52,
	0xAA1,
	0xAEE,
	0xB54,
	0xB95,
	0xBEB,
	0xC43,
	0xCA3		/*80 ,    +16dB*/
};

const u32 ofdm_swing_table_03DB_8710c[OFDM_03DB_TABLE_SIZE_8710C] = {
	0xE4,		/*0 ,    -7dB*/
	0xEB,		/*1 ,    -6.75dB*/
	0xF2,		/*2 ,    -6.5dB*/
	0xF9,
	0x100,
	0x108,
	0x110,
	0x118,
	0x11F,
	0x128,
	0x131,
	0x13A,
	0x143,
	0x14C,
	0x156,
	0x160,
	0x16A,
	0x175,
	0x180,
	0x18B,
	0x196,
	0x1A2,
	0x1AE,
	0x1BB,
	0x1C8,
	0x1D5,
	0x1E3,
	0x1F1,
	0x200,
	0x20F,
	0x21F,
	0x22F,
	0x23F,
	0x250,
	0x261,
	0x273,
	0x286,
	0x298,
	0x2AB,
	0x2BF,
	0x2D6,		/*40 ,    +3dB default*/
	0x2E9,
	0x2FF,
	0x315,
	0x32C,
	0x344,
	0x35C,
	0x375,
	0x390,
	0x3AA,
	0x3C5,
	0x3E1,
	0x3FF,
	0x41C,
	0x43B,
	0x45A,
	0x47B,
	0x49C,
	0x4BF,
	0x4E2,
	0x507,
	0x52C,
	0x553,
	0x57B,
	0x5A4,
	0x5CE,
	0x5F9,
	0x626,
	0x654,
	0x683,
	0x6B4,
	0x6E6,
	0x71B,
	0x74E,
	0x785,
	0x7BD,
	0x7F7,
	0x832,
	0x870,
	0x8AF,
	0x8F0		/*80 ,    +13dB*/
};



const u32 tx_scaling_table_jaguar[TXSCALE_TABLE_SIZE] = {
	0x081, /* 0,  -12.0dB*/
	0x088, /* 1,  -11.5dB*/
	0x090, /* 2,  -11.0dB*/
	0x099, /* 3,  -10.5dB*/
	0x0A2, /* 4,  -10.0dB*/
	0x0AC, /* 5,  -9.5dB*/
	0x0B6, /* 6,  -9.0dB*/
	0x0C0, /*7,  -8.5dB*/
	0x0CC, /* 8,  -8.0dB*/
	0x0D8, /* 9,  -7.5dB*/
	0x0E5, /* 10, -7.0dB*/
	0x0F2, /* 11, -6.5dB*/
	0x101, /* 12, -6.0dB*/
	0x110, /* 13, -5.5dB*/
	0x120, /* 14, -5.0dB*/
	0x131, /* 15, -4.5dB*/
	0x143, /* 16, -4.0dB*/
	0x156, /* 17, -3.5dB*/
	0x16A, /* 18, -3.0dB*/
	0x180, /* 19, -2.5dB*/
	0x197, /* 20, -2.0dB*/
	0x1AF, /* 21, -1.5dB*/
	0x1C8, /* 22, -1.0dB*/
	0x1E3, /* 23, -0.5dB*/
	0x200, /* 24, +0  dB*/
	0x21E, /* 25, +0.5dB*/
	0x23E, /* 26, +1.0dB*/
	0x261, /* 27, +1.5dB*/
	0x285,/* 28, +2.0dB*/
	0x2AB, /* 29, +2.5dB*/
	0x2D3, /*30, +3.0dB*/
	0x2FE, /* 31, +3.5dB*/
	0x32B, /* 32, +4.0dB*/
	0x35C, /* 33, +4.5dB*/
	0x38E, /* 34, +5.0dB*/
	0x3C4, /* 35, +5.5dB*/
	0x3FE  /* 36, +6.0dB	*/
};

void
odm_txpowertracking_init(
	void	*dm_void
)
{
	struct dm_struct	*dm = (struct dm_struct *)dm_void;

	odm_txpowertracking_thermal_meter_init(dm);
}

u8
get_swing_index(
	void	*dm_void
)
{
	struct dm_struct *dm = (struct dm_struct *)dm_void;

	u8 i = 0;
	u32 bb_swing;
	u32 swing_table_size;
	u32 *swing_table;
	u32 table_value;

#if (RTL8710C_SUPPORT == 1)
	if (dm->support_ic_type == ODM_RTL8710C) {
		bb_swing = odm_get_bb_reg(dm, R_0xcc8, 0x000007ff);

		for (i = 0; i < OFDM_03DB_TABLE_SIZE_8710C; i++) {
			if (bb_swing == ofdm_swing_table_03DB_8710c[i])
				break;
		}
	}
#elif (RTL8195B_SUPPORT == 1)
	if (dm->support_ic_type == ODM_RTL8195B) {
		bb_swing = odm_get_bb_reg(dm, R_0xc1c, 0xFFE00000);
		swing_table = (u32*)tx_scaling_table_jaguar;
		swing_table_size = TXSCALE_TABLE_SIZE;

		for (i = 0; i < swing_table_size; i++) {
			table_value = swing_table[i];

			table_value = table_value;
			if (bb_swing == table_value)
				break;
		}
	}
#endif
	return i;
}

u8
get_cck_swing_index(
	void		*dm_void
)
{
	struct dm_struct *dm = (struct dm_struct *)dm_void;

	u8 i = 0;
	u32 bb_cck_swing;

#if (RTL8188E_SUPPORT == 1 || RTL8723B_SUPPORT == 1 || RTL8192E_SUPPORT == 1)
	if (dm->support_ic_type == ODM_RTL8188E || dm->support_ic_type == ODM_RTL8723B ||
	    dm->support_ic_type == ODM_RTL8192E) {
		bb_cck_swing = odm_read_1byte(dm, 0xa22);

		for (i = 0; i < CCK_TABLE_SIZE; i++) {
			if (bb_cck_swing == cck_swing_table_ch1_ch13_new[i][0])
				break;
		}
	}
#elif (RTL8703B_SUPPORT == 1)
	if (dm->support_ic_type == ODM_RTL8703B) {
		bb_cck_swing = odm_read_1byte(dm, 0xa22);

		for (i = 0; i < CCK_TABLE_SIZE_88F; i++) {
			if (bb_cck_swing == cck_swing_table_ch1_ch14_88f[i][0])
				break;
		}
	}
#elif (RTL8710C_SUPPORT == 1)
	if (dm->support_ic_type == ODM_RTL8710C) {
		bb_cck_swing = odm_get_bb_reg(dm, R_0xab4, 0x7ff);

		RF_DBG(dm, DBG_RF_TX_PWR_TRACK,
		       "bb_cck_swing = 0x%x\n", bb_cck_swing);

		for (i = 0; i < CCK_03DB_TABLE_SIZE_8710C; i++) {
			if (bb_cck_swing == cck_swing_table_03db_ch1_ch14_8710c[i])
				break;
		}
	}
#endif

	return i;
}

s8
get_txagc_default_index(
	void *dm_void
)
{
	struct dm_struct *dm = (struct dm_struct *)dm_void;
	s8 tmp;

	if (dm->support_ic_type == ODM_RTL8814B) {
		tmp = (s8)(odm_get_bb_reg(dm, R_0x18a0, 0x7f) & 0xff);
		if (tmp & BIT(6))
			tmp = tmp | 0x80;
		return tmp;
	} else
		return 0;
}

void
odm_txpowertracking_thermal_meter_init(
	void	*dm_void
)
{
	struct dm_struct	*dm = (struct dm_struct *)dm_void;
	u8 default_swing_index;
	u8 p = 0;
	struct dm_rf_calibration_struct	*cali_info = &dm->rf_calibrate_info;
	struct _hal_rf_ *rf = &dm->rf_table;

	if (!(*dm->mp_mode))
		cali_info->txpowertrack_control = true;
	else
		cali_info->txpowertrack_control = false;

	RF_DBG(dm, DBG_RF_TX_PWR_TRACK, "dm txpowertrack_control = %d\n", cali_info->txpowertrack_control);

	/* dm->rf_calibrate_info.txpowertrack_control = true; */
	cali_info->thermal_value = rf->eeprom_thermal;
	cali_info->thermal_value_iqk = rf->eeprom_thermal;
	cali_info->thermal_value_lck = rf->eeprom_thermal;

	if (!cali_info->default_bb_swing_index_flag) {
		if (dm->support_ic_type == ODM_RTL8195B) {
			default_swing_index = get_swing_index(dm);
			cali_info->default_ofdm_index = (default_swing_index >= TXSCALE_TABLE_SIZE) ? 24 : default_swing_index;
			cali_info->default_cck_index = 24;
		} else if (dm->support_ic_type == ODM_RTL8721D) {
			cali_info->default_ofdm_index = 28;	/*OFDM: -1dB*/
			cali_info->default_cck_index = 28;	/*CCK: -6dB*/
		} else if (dm->support_ic_type == ODM_RTL8710C) {
			cali_info->default_ofdm_index = get_swing_index(dm);
			cali_info->default_cck_index = get_cck_swing_index(dm);
		}
		cali_info->default_bb_swing_index_flag = true;
	}

	cali_info->bb_swing_idx_cck_base = cali_info->default_cck_index;
	cali_info->CCK_index = cali_info->default_cck_index;

	for (p = RF_PATH_A; p < MAX_RF_PATH; ++p) {
		cali_info->bb_swing_idx_ofdm_base[p] = cali_info->default_ofdm_index;
		cali_info->OFDM_index[p] = cali_info->default_ofdm_index;
		cali_info->delta_power_index[p] = 0;
		cali_info->delta_power_index_last[p] = 0;
		cali_info->power_index_offset[p] = 0;
	}
	cali_info->modify_tx_agc_value_ofdm = 0;
	cali_info->modify_tx_agc_value_cck = 0;
	cali_info->tm_trigger = 0;
}

void
odm_txpowertracking_check(
	void	*dm_void
)
{
	struct dm_struct	*dm = (struct dm_struct *)dm_void;

	odm_txpowertracking_check_iot(dm);
}

void
odm_txpowertracking_check_iot(
	void	*dm_void
)
{
	struct dm_struct	*dm = (struct dm_struct *)dm_void;
	struct _hal_rf_		*rf = &dm->rf_table;

	if (!(rf->rf_supportability & HAL_RF_TX_PWR_TRACK))
		return;

	if (!dm->rf_calibrate_info.tm_trigger) {
		if (dm->support_ic_type == ODM_RTL8195B)
			odm_set_rf_reg(dm, RF_PATH_A, RF_T_METER_NEW, (BIT(17) | BIT(16)), 0x03);
		else if (dm->support_ic_type == ODM_RTL8721D ||
			dm->support_ic_type == ODM_RTL8710C)
			odm_set_rf_reg(dm, RF_PATH_A, RF_T_METER_NEW,
				       (BIT(12) | BIT(11)), 0x03);

		dm->rf_calibrate_info.tm_trigger = 1;
		return;
	}
	odm_txpowertracking_callback_thermal_meter(dm);
	dm->rf_calibrate_info.tm_trigger = 0;
}

void
odm_txpowertracking_check_mp(
	void	*dm_void
)
{
#if (DM_ODM_SUPPORT_TYPE == ODM_WIN)
	struct dm_struct		*dm = (struct dm_struct *)dm_void;
	void	*adapter = dm->adapter;

	if (odm_check_power_status(adapter) == false) {
		RT_TRACE(COMP_POWER_TRACKING, DBG_LOUD, ("check_pow_status, return false\n"));
		return;
	}

	odm_txpowertracking_thermal_meter_check(adapter);
#endif
}

void
odm_txpowertracking_check_ap(
	void	*dm_void
)
{
#if (DM_ODM_SUPPORT_TYPE == ODM_AP)
	struct dm_struct		*dm = (struct dm_struct *)dm_void;
	struct rtl8192cd_priv	*priv		= dm->priv;

	return;

#endif
}

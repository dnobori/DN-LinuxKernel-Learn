#include "linux/generated/autoconf.h"
/* linux/drivers/video/samsung/s6e63m0_brightness.h
 *
 * Gamma level definitions.
 *
 * Copyright (c) 2009 Samsung Electronics
 * InKi Dae <inki.dae@samsung.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#ifndef _S6E63M0_BRIGHTNESS_H
#define _S6E63M0_BRIGHTNESS_H

#define MAX_GAMMA_LEVEL		11
#define GAMMA_TABLE_COUNT	21

/* gamma value: 2.2 */
static const unsigned int s6e63m0_22_300[] = {
	0x18, 0x08, 0x24, 0x5f, 0x50, 0x2d, 0xB6,
	0xB9, 0xA7, 0xAd, 0xB1, 0x9f, 0xbe, 0xC0,
	0xB5, 0x00, 0xa0, 0x00, 0xa4, 0x00, 0xdb
};

static const unsigned int s6e63m0_22_280[] = {
	0x18, 0x08, 0x24, 0x64, 0x56, 0x33, 0xB6,
	0xBA, 0xA8, 0xAC, 0xB1, 0x9D, 0xC1, 0xC1,
	0xB7, 0x00, 0x9C, 0x00, 0x9F, 0x00, 0xD6
};

static const unsigned int s6e63m0_22_260[] = {
	0x18, 0x08, 0x24, 0x66, 0x58, 0x34, 0xB6,
	0xBA, 0xA7, 0xAF, 0xB3, 0xA0, 0xC1, 0xC2,
	0xB7, 0x00, 0x97, 0x00, 0x9A, 0x00, 0xD1

};

static const unsigned int s6e63m0_22_240[] = {
	0x18, 0x08, 0x24, 0x62, 0x54, 0x30, 0xB9,
	0xBB, 0xA9, 0xB0, 0xB3, 0xA1, 0xC1, 0xC3,
	0xB7, 0x00, 0x91, 0x00, 0x95, 0x00, 0xDA

};
static const unsigned int s6e63m0_22_220[] = {
	0x18, 0x08, 0x24, 0x63, 0x53, 0x31, 0xB8,
	0xBC, 0xA9, 0xB0, 0xB5, 0xA2, 0xC4, 0xC4,
	0xB8, 0x00, 0x8B, 0x00, 0x8E, 0x00, 0xC2
};

static const unsigned int s6e63m0_22_200[] = {
	0x18, 0x08, 0x24, 0x66, 0x55, 0x34, 0xBA,
	0xBD, 0xAB, 0xB1, 0xB5, 0xA3, 0xC5, 0xC6,
	0xB9, 0x00, 0x85, 0x00, 0x88, 0x00, 0xBA
};

static const unsigned int s6e63m0_22_170[] = {
	0x18, 0x08, 0x24, 0x69, 0x54, 0x37, 0xBB,
	0xBE, 0xAC, 0xB4, 0xB7, 0xA6, 0xC7, 0xC8,
	0xBC, 0x00, 0x7B, 0x00, 0x7E, 0x00, 0xAB
};

static const unsigned int s6e63m0_22_140[] = {
	0x18, 0x08, 0x24, 0x6C, 0x54, 0x3A, 0xBC,
	0xBF, 0xAC, 0xB7, 0xBB, 0xA9, 0xC9, 0xC9,
	0xBE, 0x00, 0x71, 0x00, 0x73, 0x00, 0x9E
};

static const unsigned int s6e63m0_22_110[] = {
	0x18, 0x08, 0x24, 0x70, 0x51, 0x3E, 0xBF,
	0xC1, 0xAF, 0xB9, 0xBC, 0xAB, 0xCC, 0xCC,
	0xC2, 0x00, 0x65, 0x00, 0x67, 0x00, 0x8D
};

static const unsigned int s6e63m0_22_90[] = {
	0x18, 0x08, 0x24, 0x73, 0x4A, 0x3D, 0xC0,
	0xC2, 0xB1, 0xBB, 0xBE, 0xAC, 0xCE, 0xCF,
	0xC5, 0x00, 0x5D, 0x00, 0x5E, 0x00, 0x82
};

static const unsigned int s6e63m0_22_30[] = {
	0x18, 0x08, 0x24, 0x78, 0xEC, 0x3D, 0xC8,
	0xC2, 0xB6, 0xC4, 0xC7, 0xB6, 0xD5, 0xD7,
	0xCC, 0x00, 0x39, 0x00, 0x36, 0x00, 0x51
};

/* gamma value: 1.9 */
static const unsigned int s6e63m0_19_300[] = {
	0x18, 0x08, 0x24, 0x61, 0x5F, 0x39, 0xBA,
	0xBD, 0xAD, 0xB1, 0xB6, 0xA5, 0xC4, 0xC5,
	0xBC, 0x00, 0xA0, 0x00, 0xA4, 0x00, 0xDB
};

static const unsigned int s6e63m0_19_280[] = {
	0x18, 0x08, 0x24, 0x61, 0x60, 0x39, 0xBB,
	0xBE, 0xAD, 0xB2, 0xB6, 0xA6, 0xC5, 0xC7,
	0xBD, 0x00, 0x9B, 0x00, 0x9E, 0x00, 0xD5
};

static const unsigned int s6e63m0_19_260[] = {
	0x18, 0x08, 0x24, 0x63, 0x61, 0x3B, 0xBA,
	0xBE, 0xAC, 0xB3, 0xB8, 0xA7, 0xC6, 0xC8,
	0xBD, 0x00, 0x96, 0x00, 0x98, 0x00, 0xCF
};

static const unsigned int s6e63m0_19_240[] = {
	0x18, 0x08, 0x24, 0x67, 0x64, 0x3F, 0xBB,
	0xBE, 0xAD, 0xB3, 0xB9, 0xA7, 0xC8, 0xC9,
	0xBE, 0x00, 0x90, 0x00, 0x92, 0x00, 0xC8
};

static const unsigned int s6e63m0_19_220[] = {
	0x18, 0x08, 0x24, 0x68, 0x64, 0x40, 0xBC,
	0xBF, 0xAF, 0xB4, 0xBA, 0xA9, 0xC8, 0xCA,
	0xBE, 0x00, 0x8B, 0x00, 0x8C, 0x00, 0xC0
};

static const unsigned int s6e63m0_19_200[] = {
	0x18, 0x08, 0x24, 0x68, 0x64, 0x3F, 0xBE,
	0xC0, 0xB0, 0xB6, 0xBB, 0xAB, 0xC8, 0xCB,
	0xBF, 0x00, 0x85, 0x00, 0x86, 0x00, 0xB8
};

static const unsigned int s6e63m0_19_170[] = {
	0x18, 0x08, 0x24, 0x69, 0x64, 0x40, 0xBF,
	0xC1, 0xB0, 0xB9, 0xBE, 0xAD, 0xCB, 0xCD,
	0xC2, 0x00, 0x7A, 0x00, 0x7B, 0x00, 0xAA
};

static const unsigned int s6e63m0_19_140[] = {
	0x18, 0x08, 0x24, 0x6E, 0x65, 0x45, 0xC0,
	0xC3, 0xB2, 0xBA, 0xBE, 0xAE, 0xCD, 0xD0,
	0xC4, 0x00, 0x70, 0x00, 0x70, 0x00, 0x9C
};

static const unsigned int s6e63m0_19_110[] = {
	0x18, 0x08, 0x24, 0x6F, 0x65, 0x46, 0xC2,
	0xC4, 0xB3, 0xBF, 0xC2, 0xB2, 0xCF, 0xD1,
	0xC6, 0x00, 0x64, 0x00, 0x64, 0x00, 0x8D
};

static const unsigned int s6e63m0_19_90[] = {
	0x18, 0x08, 0x24, 0x74, 0x60, 0x4A, 0xC3,
	0xC6, 0xB5, 0xBF, 0xC3, 0xB2, 0xD2, 0xD3,
	0xC8, 0x00, 0x5B, 0x00, 0x5B, 0x00, 0x81
};

static const unsigned int s6e63m0_19_30[] = {
	0x18, 0x08, 0x24, 0x84, 0x45, 0x4F, 0xCA,
	0xCB, 0xBC, 0xC9, 0xCB, 0xBC, 0xDA, 0xDA,
	0xD0, 0x00, 0x35, 0x00, 0x34, 0x00, 0x4E
};

/* gamma value: 1.7 */
static const unsigned int s6e63m0_17_300[] = {
	0x18, 0x08, 0x24, 0x70, 0x70, 0x4F, 0xBF,
	0xC2, 0xB2, 0xB8, 0xBC, 0xAC, 0xCB, 0xCD,
	0xC3, 0x00, 0xA0, 0x00, 0xA4, 0x00, 0xDB
};

static const unsigned int s6e63m0_17_280[] = {
	0x18, 0x08, 0x24, 0x71, 0x71, 0x50, 0xBF,
	0xC2, 0xB2, 0xBA, 0xBE, 0xAE, 0xCB, 0xCD,
	0xC3, 0x00, 0x9C, 0x00, 0x9F, 0x00, 0xD6
};

static const unsigned int s6e63m0_17_260[] = {
	0x18, 0x08, 0x24, 0x72, 0x72, 0x50, 0xC0,
	0xC3, 0xB4, 0xB9, 0xBE, 0xAE, 0xCC, 0xCF,
	0xC4, 0x00, 0x97, 0x00, 0x9A, 0x00, 0xD1
};

static const unsigned int s6e63m0_17_240[] = {
	0x18, 0x08, 0x24, 0x71, 0x72, 0x4F, 0xC2,
	0xC4, 0xB5, 0xBB, 0xBF, 0xB0, 0xCC, 0xCF,
	0xC3, 0x00, 0x91, 0x00, 0x95, 0x00, 0xCA
};

static const unsigned int s6e63m0_17_220[] = {
	0x18, 0x08, 0x24, 0x71, 0x73, 0x4F, 0xC2,
	0xC5, 0xB5, 0xBD, 0xC0, 0xB2, 0xCD, 0xD1,
	0xC5, 0x00, 0x8B, 0x00, 0x8E, 0x00, 0xC2
};

static const unsigned int s6e63m0_17_200[] = {
	0x18, 0x08, 0x24, 0x72, 0x75, 0x51, 0xC2,
	0xC6, 0xB5, 0xBF, 0xC1, 0xB3, 0xCE, 0xD1,
	0xC6, 0x00, 0x85, 0x00, 0x88, 0x00, 0xBA
};

static const unsigned int s6e63m0_17_170[] = {
	0x18, 0x08, 0x24, 0x75, 0x77, 0x54, 0xC3,
	0xC7, 0xB7, 0xC0, 0xC3, 0xB4, 0xD1, 0xD3,
	0xC9, 0x00, 0x7B, 0x00, 0x7E, 0x00, 0xAB
};

static const unsigned int s6e63m0_17_140[] = {
	0x18, 0x08, 0x24, 0x7B, 0x77, 0x58, 0xC3,
	0xC8, 0xB8, 0xC2, 0xC6, 0xB6, 0xD3, 0xD4,
	0xCA, 0x00, 0x71, 0x00, 0x73, 0x00, 0x9E
};

static const unsigned int s6e63m0_17_110[] = {
	0x18, 0x08, 0x24, 0x81, 0x7B, 0x5D, 0xC6,
	0xCA, 0xBB, 0xC3, 0xC7, 0xB8, 0xD6, 0xD8,
	0xCD, 0x00, 0x65, 0x00, 0x67, 0x00, 0x8D
};

static const unsigned int s6e63m0_17_90[] = {
	0x18, 0x08, 0x24, 0x82, 0x7A, 0x5B, 0xC8,
	0xCB, 0xBD, 0xC5, 0xCA, 0xBA, 0xD6, 0xD8,
	0xCE, 0x00, 0x5D, 0x00, 0x5E, 0x00, 0x82
};

static const unsigned int s6e63m0_17_30[] = {
	0x18, 0x08, 0x24, 0x8F, 0x73, 0x63, 0xD1,
	0xD0, 0xC5, 0xCC, 0xD1, 0xC2, 0xDE, 0xE0,
	0xD6, 0x00, 0x39, 0x00, 0x36, 0x00, 0x51
};

struct s6e63m0_gamma {
	unsigned int *gamma_22_table[MAX_GAMMA_LEVEL];
	unsigned int *gamma_19_table[MAX_GAMMA_LEVEL];
	unsigned int *gamma_17_table[MAX_GAMMA_LEVEL];
};

static struct s6e63m0_gamma gamma_table = {
	.gamma_22_table[0] = (unsigned int *)&s6e63m0_22_30,
	.gamma_22_table[1] = (unsigned int *)&s6e63m0_22_90,
	.gamma_22_table[2] = (unsigned int *)&s6e63m0_22_110,
	.gamma_22_table[3] = (unsigned int *)&s6e63m0_22_140,
	.gamma_22_table[4] = (unsigned int *)&s6e63m0_22_170,
	.gamma_22_table[5] = (unsigned int *)&s6e63m0_22_200,
	.gamma_22_table[6] = (unsigned int *)&s6e63m0_22_220,
	.gamma_22_table[7] = (unsigned int *)&s6e63m0_22_240,
	.gamma_22_table[8] = (unsigned int *)&s6e63m0_22_260,
	.gamma_22_table[9] = (unsigned int *)&s6e63m0_22_280,
	.gamma_22_table[10] = (unsigned int *)&s6e63m0_22_300,

	.gamma_19_table[0] = (unsigned int *)&s6e63m0_19_30,
	.gamma_19_table[1] = (unsigned int *)&s6e63m0_19_90,
	.gamma_19_table[2] = (unsigned int *)&s6e63m0_19_110,
	.gamma_19_table[3] = (unsigned int *)&s6e63m0_19_140,
	.gamma_19_table[4] = (unsigned int *)&s6e63m0_19_170,
	.gamma_19_table[5] = (unsigned int *)&s6e63m0_19_200,
	.gamma_19_table[6] = (unsigned int *)&s6e63m0_19_220,
	.gamma_19_table[7] = (unsigned int *)&s6e63m0_19_240,
	.gamma_19_table[8] = (unsigned int *)&s6e63m0_19_260,
	.gamma_19_table[9] = (unsigned int *)&s6e63m0_19_280,
	.gamma_19_table[10] = (unsigned int *)&s6e63m0_19_300,

	.gamma_17_table[0] = (unsigned int *)&s6e63m0_17_30,
	.gamma_17_table[1] = (unsigned int *)&s6e63m0_17_90,
	.gamma_17_table[2] = (unsigned int *)&s6e63m0_17_110,
	.gamma_17_table[3] = (unsigned int *)&s6e63m0_17_140,
	.gamma_17_table[4] = (unsigned int *)&s6e63m0_17_170,
	.gamma_17_table[5] = (unsigned int *)&s6e63m0_17_200,
	.gamma_17_table[6] = (unsigned int *)&s6e63m0_17_220,
	.gamma_17_table[7] = (unsigned int *)&s6e63m0_17_240,
	.gamma_17_table[8] = (unsigned int *)&s6e63m0_17_260,
	.gamma_17_table[9] = (unsigned int *)&s6e63m0_17_280,
	.gamma_17_table[10] = (unsigned int *)&s6e63m0_17_300,
};

#endif


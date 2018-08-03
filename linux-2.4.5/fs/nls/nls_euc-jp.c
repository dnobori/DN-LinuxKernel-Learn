#include "linux/autoconf.h"
/*
 * linux/fs/nls_euc-jp.c
 *
 * Added `OSF/JVC Recommended Code Set Conversion Specification
 * between Japanese EUC and Shift-JIS' support: <hirofumi@mail.parknet.co.jp>
 * (http://www.opengroup.or.jp/jvc/cde/sjis-euc-e.html)
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/string.h>
#include <linux/nls.h>
#include <linux/errno.h>

static struct nls_table *p_nls;

#define IS_SJIS_LOW_BYTE(l)	((0x40 <= (l)) && ((l) <= 0xFC) && ((l) != 0x7F))
/* JIS X 0208 (include NEC spesial characters) */
#define IS_SJIS_JISX0208(h, l)	((((0x81 <= (h)) && ((h) <= 0x9F))	\
				 || ((0xE0 <= (h)) && ((h) <= 0xEA)))	\
				 && IS_SJIS_LOW_BYTE(l))
#define IS_SJIS_JISX0201KANA(c)	((0xA1 <= (c)) && ((c) <= 0xDF))
#define IS_SJIS_UDC_LOW(h, l)	(((0xF0 <= (h)) && ((h) <= 0xF4))	\
				 && IS_SJIS_LOW_BYTE(l))
#define IS_SJIS_UDC_HI(h, l)	(((0xF5 <= (h)) && ((h) <= 0xF9))	\
				 && IS_SJIS_LOW_BYTE(l))
#define IS_SJIS_IBM(h, l)	(((0xFA <= (h)) && ((h) <= 0xFC))	\
				 && IS_SJIS_LOW_BYTE(l))
#define IS_SJIS_NECIBM(h, l)	(((0xED <= (h)) && ((h) <= 0xEE))	\
				 && IS_SJIS_LOW_BYTE(l))
#define MAP_SJIS2EUC(sjis_hi, sjis_lo, sjis_p, euc_hi, euc_lo, euc_p) {		\
	if ((sjis_lo) >= 0x9F) {						\
		(euc_hi) = (sjis_hi) * 2 - (((sjis_p) * 2 - (euc_p)) - 1);	\
		(euc_lo) = (sjis_lo) + 2;					\
	} else {								\
		(euc_hi) = (sjis_hi) * 2 - ((sjis_p) * 2 - (euc_p));		\
		(euc_lo) = (sjis_lo) + ((sjis_lo) >= 0x7F ? 0x60 : 0x61);	\
	}									\
} while(0)

#define SS2		(0x8E)		/* Single Shift 2 */
#define SS3		(0x8F)		/* Single Shift 3 */
#define IS_EUC_BYTE(c)		((0xA1 <= (c)) && ((c) <= 0xFE))
#define IS_EUC_JISX0208(h, l)	(IS_EUC_BYTE(h) && IS_EUC_BYTE(l))
#define IS_EUC_JISX0201KANA(h, l)	(((h) == SS2) && (0xA1 <= (l) && (l) <= 0xDF))
#define IS_EUC_UDC_LOW(h, l)	(((0xF5 <= (h)) && ((h) <= 0xFE))	\
				 && IS_EUC_BYTE(l))
#define IS_EUC_UDC_HI(h, l)	IS_EUC_UDC_LOW(h, l) /* G3 block */
#define MAP_EUC2SJIS(euc_hi, euc_lo, euc_p, sjis_hi, sjis_lo, sjis_p) {		\
	if ((euc_hi) & 1) {							\
		(sjis_hi) = (euc_hi) / 2 + ((sjis_p) - (euc_p) / 2);		\
		(sjis_lo) = (euc_lo) - ((euc_lo) >= 0xE0 ? 0x60 : 0x61);	\
	} else {								\
		(sjis_hi) = (euc_hi) / 2 + (((sjis_p) - (euc_p) / 2) - 1);	\
		(sjis_lo) = (euc_lo) - 2;					\
	}									\
} while(0)

/* SJIS IBM extended characters to EUC map */
static unsigned char sjisibm2euc_map[][2] = {
	{0xF3, 0xF3}, {0xF3, 0xF4}, {0xF3, 0xF5}, {0xF3, 0xF6}, {0xF3, 0xF7},
	{0xF3, 0xF8}, {0xF3, 0xF9}, {0xF3, 0xFA}, {0xF3, 0xFB}, {0xF3, 0xFC},
	{0xF3, 0xFD}, {0xF3, 0xFE}, {0xF4, 0xA1}, {0xF4, 0xA2}, {0xF4, 0xA3},
	{0xF4, 0xA4}, {0xF4, 0xA5}, {0xF4, 0xA6}, {0xF4, 0xA7}, {0xF4, 0xA8},
	{0xA2, 0xCC}, {0xA2, 0xC3}, {0xF4, 0xA9}, {0xF4, 0xAA}, {0xF4, 0xAB},
	{0xF4, 0xAC}, {0xF4, 0xAD}, {0xA2, 0xE8}, {0xD4, 0xE3}, {0xDC, 0xDF},
	{0xE4, 0xE9}, {0xE3, 0xF8}, {0xD9, 0xA1}, {0xB1, 0xBB}, {0xF4, 0xAE},
	{0xC2, 0xAD}, {0xC3, 0xFC}, {0xE4, 0xD0}, {0xC2, 0xBF}, {0xBC, 0xF4},
	{0xB0, 0xA9}, {0xB0, 0xC8}, {0xF4, 0xAF}, {0xB0, 0xD2}, {0xB0, 0xD4},
	{0xB0, 0xE3}, {0xB0, 0xEE}, {0xB1, 0xA7}, {0xB1, 0xA3}, {0xB1, 0xAC},
	{0xB1, 0xA9}, {0xB1, 0xBE}, {0xB1, 0xDF}, {0xB1, 0xD8}, {0xB1, 0xC8},
	{0xB1, 0xD7}, {0xB1, 0xE3}, {0xB1, 0xF4}, {0xB1, 0xE1}, {0xB2, 0xA3},
	{0xF4, 0xB0}, {0xB2, 0xBB}, {0xB2, 0xE6}, {0x00, 0x00}, {0xB2, 0xED},
	{0xB2, 0xF5}, {0xB2, 0xFC}, {0xF4, 0xB1}, {0xB3, 0xB5}, {0xB3, 0xD8},
	{0xB3, 0xDB}, {0xB3, 0xE5}, {0xB3, 0xEE}, {0xB3, 0xFB}, {0xF4, 0xB2},
	{0xF4, 0xB3}, {0xB4, 0xC0}, {0xB4, 0xC7}, {0xB4, 0xD0}, {0xB4, 0xDE},
	{0xF4, 0xB4}, {0xB5, 0xAA}, {0xF4, 0xB5}, {0xB5, 0xAF}, {0xB5, 0xC4},
	{0xB5, 0xE8}, {0xF4, 0xB6}, {0xB7, 0xC2}, {0xB7, 0xE4}, {0xB7, 0xE8},
	{0xB7, 0xE7}, {0xF4, 0xB7}, {0xF4, 0xB8}, {0xF4, 0xB9}, {0xB8, 0xCE},
	{0xB8, 0xE1}, {0xB8, 0xF5}, {0xB8, 0xF7}, {0xB8, 0xF8}, {0xB8, 0xFC},
	{0xB9, 0xAF}, {0xB9, 0xB7}, {0xBA, 0xBE}, {0xBA, 0xDB}, {0xCD, 0xAA},
	{0xBA, 0xE1}, {0xF4, 0xBA}, {0xBA, 0xEB}, {0xBB, 0xB3}, {0xBB, 0xB8},
	{0xF4, 0xBB}, {0xBB, 0xCA}, {0xF4, 0xBC}, {0xF4, 0xBD}, {0xBB, 0xD0},
	{0xBB, 0xDE}, {0xBB, 0xF4}, {0xBB, 0xF5}, {0xBB, 0xF9}, {0xBC, 0xE4},
	{0xBC, 0xED}, {0xBC, 0xFE}, {0xF4, 0xBE}, {0xBD, 0xC2}, {0xBD, 0xE7},
	{0xF4, 0xBF}, {0xBD, 0xF0}, {0xBE, 0xB0}, {0xBE, 0xAC}, {0xF4, 0xC0},
	{0xBE, 0xB3}, {0xBE, 0xBD}, {0xBE, 0xCD}, {0xBE, 0xC9}, {0xBE, 0xE4},
	{0xBF, 0xA8}, {0xBF, 0xC9}, {0xC0, 0xC4}, {0xC0, 0xE4}, {0xC0, 0xF4},
	{0xC1, 0xA6}, {0xF4, 0xC1}, {0xC1, 0xF5}, {0xC1, 0xFC}, {0xF4, 0xC2},
	{0xC1, 0xF8}, {0xC2, 0xAB}, {0xC2, 0xA1}, {0xC2, 0xA5}, {0xF4, 0xC3},
	{0xC2, 0xB8}, {0xC2, 0xBA}, {0xF4, 0xC4}, {0xC2, 0xC4}, {0xC2, 0xD2},
	{0xC2, 0xD7}, {0xC2, 0xDB}, {0xC2, 0xDE}, {0xC2, 0xED}, {0xC2, 0xF0},
	{0xF4, 0xC5}, {0xC3, 0xA1}, {0xC3, 0xB5}, {0xC3, 0xC9}, {0xC3, 0xB9},
	{0xF4, 0xC6}, {0xC3, 0xD8}, {0xC3, 0xFE}, {0xF4, 0xC7}, {0xC4, 0xCC},
	{0xF4, 0xC8}, {0xC4, 0xD9}, {0xC4, 0xEA}, {0xC4, 0xFD}, {0xF4, 0xC9},
	{0xC5, 0xA7}, {0xC5, 0xB5}, {0xC5, 0xB6}, {0xF4, 0xCA}, {0xC5, 0xD5},
	{0xC6, 0xB8}, {0xC6, 0xD7}, {0xC6, 0xE0}, {0xC6, 0xEA}, {0xC6, 0xE3},
	{0xC7, 0xA1}, {0xC7, 0xAB}, {0xC7, 0xC7}, {0xC7, 0xC3}, {0xC7, 0xCB},
	{0xC7, 0xCF}, {0xC7, 0xD9}, {0xF4, 0xCB}, {0xF4, 0xCC}, {0xC7, 0xE6},
	{0xC7, 0xEE}, {0xC7, 0xFC}, {0xC7, 0xEB}, {0xC7, 0xF0}, {0xC8, 0xB1},
	{0xC8, 0xE5}, {0xC8, 0xF8}, {0xC9, 0xA6}, {0xC9, 0xAB}, {0xC9, 0xAD},
	{0xF4, 0xCD}, {0xC9, 0xCA}, {0xC9, 0xD3}, {0xC9, 0xE9}, {0xC9, 0xE3},
	{0xC9, 0xFC}, {0xC9, 0xF4}, {0xC9, 0xF5}, {0xF4, 0xCE}, {0xCA, 0xB3},
	{0xCA, 0xBD}, {0xCA, 0xEF}, {0xCA, 0xF1}, {0xCB, 0xAE}, {0xF4, 0xCF},
	{0xCB, 0xCA}, {0xCB, 0xE6}, {0xCB, 0xEA}, {0xCB, 0xF0}, {0xCB, 0xF4},
	{0xCB, 0xEE}, {0xCC, 0xA5}, {0xCB, 0xF9}, {0xCC, 0xAB}, {0xCC, 0xAE},
	{0xCC, 0xAD}, {0xCC, 0xB2}, {0xCC, 0xC2}, {0xCC, 0xD0}, {0xCC, 0xD9},
	{0xF4, 0xD0}, {0xCD, 0xBB}, {0xF4, 0xD1}, {0xCE, 0xBB}, {0xF4, 0xD2},
	{0xCE, 0xBA}, {0xCE, 0xC3}, {0xF4, 0xD3}, {0xCE, 0xF2}, {0xB3, 0xDD},
	{0xCF, 0xD5}, {0xCF, 0xE2}, {0xCF, 0xE9}, {0xCF, 0xED}, {0xF4, 0xD4},
	{0xF4, 0xD5}, {0xF4, 0xD6}, {0x00, 0x00}, {0xF4, 0xD7}, {0xD0, 0xE5},
	{0xF4, 0xD8}, {0xD0, 0xE9}, {0xD1, 0xE8}, {0xF4, 0xD9}, {0xF4, 0xDA},
	{0xD1, 0xEC}, {0xD2, 0xBB}, {0xF4, 0xDB}, {0xD3, 0xE1}, {0xD3, 0xE8},
	{0xD4, 0xA7}, {0xF4, 0xDC}, {0xF4, 0xDD}, {0xD4, 0xD4}, {0xD4, 0xF2},
	{0xD5, 0xAE}, {0xF4, 0xDE}, {0xD7, 0xDE}, {0xF4, 0xDF}, {0xD8, 0xA2},
	{0xD8, 0xB7}, {0xD8, 0xC1}, {0xD8, 0xD1}, {0xD8, 0xF4}, {0xD9, 0xC6},
	{0xD9, 0xC8}, {0xD9, 0xD1}, {0xF4, 0xE0}, {0xF4, 0xE1}, {0xF4, 0xE2},
	{0xF4, 0xE3}, {0xF4, 0xE4}, {0xDC, 0xD3}, {0xDD, 0xC8}, {0xDD, 0xD4},
	{0xDD, 0xEA}, {0xDD, 0xFA}, {0xDE, 0xA4}, {0xDE, 0xB0}, {0xF4, 0xE5},
	{0xDE, 0xB5}, {0xDE, 0xCB}, {0xF4, 0xE6}, {0xDF, 0xB9}, {0xF4, 0xE7},
	{0xDF, 0xC3}, {0xF4, 0xE8}, {0xF4, 0xE9}, {0xE0, 0xD9}, {0xF4, 0xEA},
	{0xF4, 0xEB}, {0xE1, 0xE2}, {0xF4, 0xEC}, {0xF4, 0xED}, {0xF4, 0xEE},
	{0xE2, 0xC7}, {0xE3, 0xA8}, {0xE3, 0xA6}, {0xE3, 0xA9}, {0xE3, 0xAF},
	{0xE3, 0xB0}, {0xE3, 0xAA}, {0xE3, 0xAB}, {0xE3, 0xBC}, {0xE3, 0xC1},
	{0xE3, 0xBF}, {0xE3, 0xD5}, {0xE3, 0xD8}, {0xE3, 0xD6}, {0xE3, 0xDF},
	{0xE3, 0xE3}, {0xE3, 0xE1}, {0xE3, 0xD4}, {0xE3, 0xE9}, {0xE4, 0xA6},
	{0xE3, 0xF1}, {0xE3, 0xF2}, {0xE4, 0xCB}, {0xE4, 0xC1}, {0xE4, 0xC3},
	{0xE4, 0xBE}, {0xF4, 0xEF}, {0xE4, 0xC0}, {0xE4, 0xC7}, {0xE4, 0xBF},
	{0xE4, 0xE0}, {0xE4, 0xDE}, {0xE4, 0xD1}, {0xF4, 0xF0}, {0xE4, 0xDC},
	{0xE4, 0xD2}, {0xE4, 0xDB}, {0xE4, 0xD4}, {0xE4, 0xFA}, {0xE4, 0xEF},
	{0xE5, 0xB3}, {0xE5, 0xBF}, {0xE5, 0xC9}, {0xE5, 0xD0}, {0xE5, 0xE2},
	{0xE5, 0xEA}, {0xE5, 0xEB}, {0xF4, 0xF1}, {0xF4, 0xF2}, {0xF4, 0xF3},
	{0xE6, 0xE8}, {0xE6, 0xEF}, {0xE7, 0xAC}, {0xF4, 0xF4}, {0xE7, 0xAE},
	{0xF4, 0xF5}, {0xE7, 0xB1}, {0xF4, 0xF6}, {0xE7, 0xB2}, {0xE8, 0xB1},
	{0xE8, 0xB6}, {0xF4, 0xF7}, {0xF4, 0xF8}, {0xE8, 0xDD}, {0xF4, 0xF9},
	{0xF4, 0xFA}, {0xE9, 0xD1}, {0xF4, 0xFB}, {0xE9, 0xED}, {0xEA, 0xCD},
	{0xF4, 0xFC}, {0xEA, 0xDB}, {0xEA, 0xE6}, {0xEA, 0xEA}, {0xEB, 0xA5},
	{0xEB, 0xFB}, {0xEB, 0xFA}, {0xF4, 0xFD}, {0xEC, 0xD6}, {0xF4, 0xFE},
};

#define IS_EUC_IBM2JISX0208(h, l) \
		(((h) == 0xA2 && (l) == 0xCC) || ((h) == 0xA2 && (l) == 0xE8))

/* EUC to SJIS IBM extended characters map (G3 JIS X 0212 block) */
static struct {
	unsigned short euc;
	unsigned char sjis[2];
} euc2sjisibm_jisx0212_map[] = {
	{0xA2C3, {0xFA, 0x55}}, {0xB0A9, {0xFA, 0x68}}, {0xB0C8, {0xFA, 0x69}},
	{0xB0D2, {0xFA, 0x6B}}, {0xB0D4, {0xFA, 0x6C}}, {0xB0E3, {0xFA, 0x6D}},
	{0xB0EE, {0xFA, 0x6E}}, {0xB1A3, {0xFA, 0x70}}, {0xB1A7, {0xFA, 0x6F}},
	{0xB1A9, {0xFA, 0x72}}, {0xB1AC, {0xFA, 0x71}}, {0xB1BB, {0xFA, 0x61}},
	{0xB1BE, {0xFA, 0x73}}, {0xB1C8, {0xFA, 0x76}}, {0xB1D7, {0xFA, 0x77}},
	{0xB1D8, {0xFA, 0x75}}, {0xB1DF, {0xFA, 0x74}}, {0xB1E1, {0xFA, 0x7A}},
	{0xB1E3, {0xFA, 0x78}}, {0xB1F4, {0xFA, 0x79}}, {0xB2A3, {0xFA, 0x7B}},
	{0xB2BB, {0xFA, 0x7D}}, {0xB2E6, {0xFA, 0x7E}}, {0xB2ED, {0xFA, 0x80}},
	{0xB2F5, {0xFA, 0x81}}, {0xB2FC, {0xFA, 0x82}}, {0xB3B5, {0xFA, 0x84}},
	{0xB3D8, {0xFA, 0x85}}, {0xB3DB, {0xFA, 0x86}}, {0xB3DD, {0xFB, 0x77}},
	{0xB3E5, {0xFA, 0x87}}, {0xB3EE, {0xFA, 0x88}}, {0xB3FB, {0xFA, 0x89}},
	{0xB4C0, {0xFA, 0x8C}}, {0xB4C7, {0xFA, 0x8D}}, {0xB4D0, {0xFA, 0x8E}},
	{0xB4DE, {0xFA, 0x8F}}, {0xB5AA, {0xFA, 0x91}}, {0xB5AF, {0xFA, 0x93}},
	{0xB5C4, {0xFA, 0x94}}, {0xB5E8, {0xFA, 0x95}}, {0xB7C2, {0xFA, 0x97}},
	{0xB7E4, {0xFA, 0x98}}, {0xB7E7, {0xFA, 0x9A}}, {0xB7E8, {0xFA, 0x99}},
	{0xB8CE, {0xFA, 0x9E}}, {0xB8E1, {0xFA, 0x9F}}, {0xB8F5, {0xFA, 0xA0}},
	{0xB8F7, {0xFA, 0xA1}}, {0xB8F8, {0xFA, 0xA2}}, {0xB8FC, {0xFA, 0xA3}},
	{0xB9AF, {0xFA, 0xA4}}, {0xB9B7, {0xFA, 0xA5}}, {0xBABE, {0xFA, 0xA6}},
	{0xBADB, {0xFA, 0xA7}}, {0xBAE1, {0xFA, 0xA9}}, {0xBAEB, {0xFA, 0xAB}},
	{0xBBB3, {0xFA, 0xAC}}, {0xBBB8, {0xFA, 0xAD}}, {0xBBCA, {0xFA, 0xAF}},
	{0xBBD0, {0xFA, 0xB2}}, {0xBBDE, {0xFA, 0xB3}}, {0xBBF4, {0xFA, 0xB4}},
	{0xBBF5, {0xFA, 0xB5}}, {0xBBF9, {0xFA, 0xB6}}, {0xBCE4, {0xFA, 0xB7}},
	{0xBCED, {0xFA, 0xB8}}, {0xBCF4, {0xFA, 0x67}}, {0xBCFE, {0xFA, 0xB9}},
	{0xBDC2, {0xFA, 0xBB}}, {0xBDE7, {0xFA, 0xBC}}, {0xBDF0, {0xFA, 0xBE}},
	{0xBEAC, {0xFA, 0xC0}}, {0xBEB0, {0xFA, 0xBF}}, {0xBEB3, {0xFA, 0xC2}},
	{0xBEBD, {0xFA, 0xC3}}, {0xBEC9, {0xFA, 0xC5}}, {0xBECD, {0xFA, 0xC4}},
	{0xBEE4, {0xFA, 0xC6}}, {0xBFA8, {0xFA, 0xC7}}, {0xBFC9, {0xFA, 0xC8}},
	{0xC0C4, {0xFA, 0xC9}}, {0xC0E4, {0xFA, 0xCA}}, {0xC0F4, {0xFA, 0xCB}},
	{0xC1A6, {0xFA, 0xCC}}, {0xC1F5, {0xFA, 0xCE}}, {0xC1F8, {0xFA, 0xD1}},
	{0xC1FC, {0xFA, 0xCF}}, {0xC2A1, {0xFA, 0xD3}}, {0xC2A5, {0xFA, 0xD4}},
	{0xC2AB, {0xFA, 0xD2}}, {0xC2AD, {0xFA, 0x63}}, {0xC2B8, {0xFA, 0xD6}},
	{0xC2BA, {0xFA, 0xD7}}, {0xC2BF, {0xFA, 0x66}}, {0xC2C4, {0xFA, 0xD9}},
	{0xC2D2, {0xFA, 0xDA}}, {0xC2D7, {0xFA, 0xDB}}, {0xC2DB, {0xFA, 0xDC}},
	{0xC2DE, {0xFA, 0xDD}}, {0xC2ED, {0xFA, 0xDE}}, {0xC2F0, {0xFA, 0xDF}},
	{0xC3A1, {0xFA, 0xE1}}, {0xC3B5, {0xFA, 0xE2}}, {0xC3B9, {0xFA, 0xE4}},
	{0xC3C9, {0xFA, 0xE3}}, {0xC3D8, {0xFA, 0xE6}}, {0xC3FC, {0xFA, 0x64}},
	{0xC3FE, {0xFA, 0xE7}}, {0xC4CC, {0xFA, 0xE9}}, {0xC4D9, {0xFA, 0xEB}},
	{0xC4EA, {0xFA, 0xEC}}, {0xC4FD, {0xFA, 0xED}}, {0xC5A7, {0xFA, 0xEF}},
	{0xC5B5, {0xFA, 0xF0}}, {0xC5B6, {0xFA, 0xF1}}, {0xC5D5, {0xFA, 0xF3}},
	{0xC6B8, {0xFA, 0xF4}}, {0xC6D7, {0xFA, 0xF5}}, {0xC6E0, {0xFA, 0xF6}},
	{0xC6E3, {0xFA, 0xF8}}, {0xC6EA, {0xFA, 0xF7}}, {0xC7A1, {0xFA, 0xF9}},
	{0xC7AB, {0xFA, 0xFA}}, {0xC7C3, {0xFA, 0xFC}}, {0xC7C7, {0xFA, 0xFB}},
	{0xC7CB, {0xFB, 0x40}}, {0xC7CF, {0xFB, 0x41}}, {0xC7D9, {0xFB, 0x42}},
	{0xC7E6, {0xFB, 0x45}}, {0xC7EB, {0xFB, 0x48}}, {0xC7EE, {0xFB, 0x46}},
	{0xC7F0, {0xFB, 0x49}}, {0xC7FC, {0xFB, 0x47}}, {0xC8B1, {0xFB, 0x4A}},
	{0xC8E5, {0xFB, 0x4B}}, {0xC8F8, {0xFB, 0x4C}}, {0xC9A6, {0xFB, 0x4D}},
	{0xC9AB, {0xFB, 0x4E}}, {0xC9AD, {0xFB, 0x4F}}, {0xC9CA, {0xFB, 0x51}},
	{0xC9D3, {0xFB, 0x52}}, {0xC9E3, {0xFB, 0x54}}, {0xC9E9, {0xFB, 0x53}},
	{0xC9F4, {0xFB, 0x56}}, {0xC9F5, {0xFB, 0x57}}, {0xC9FC, {0xFB, 0x55}},
	{0xCAB3, {0xFB, 0x59}}, {0xCABD, {0xFB, 0x5A}}, {0xCAEF, {0xFB, 0x5B}},
	{0xCAF1, {0xFB, 0x5C}}, {0xCBAE, {0xFB, 0x5D}}, {0xCBCA, {0xFB, 0x5F}},
	{0xCBE6, {0xFB, 0x60}}, {0xCBEA, {0xFB, 0x61}}, {0xCBEE, {0xFB, 0x64}},
	{0xCBF0, {0xFB, 0x62}}, {0xCBF4, {0xFB, 0x63}}, {0xCBF9, {0xFB, 0x66}},
	{0xCCA5, {0xFB, 0x65}}, {0xCCAB, {0xFB, 0x67}}, {0xCCAD, {0xFB, 0x69}},
	{0xCCAE, {0xFB, 0x68}}, {0xCCB2, {0xFB, 0x6A}}, {0xCCC2, {0xFB, 0x6B}},
	{0xCCD0, {0xFB, 0x6C}}, {0xCCD9, {0xFB, 0x6D}}, {0xCDAA, {0xFA, 0xA8}},
	{0xCDBB, {0xFB, 0x6F}}, {0xCEBA, {0xFB, 0x73}}, {0xCEBB, {0xFB, 0x71}},
	{0xCEC3, {0xFB, 0x74}}, {0xCEF2, {0xFB, 0x76}}, {0xCFD5, {0xFB, 0x78}},
	{0xCFE2, {0xFB, 0x79}}, {0xCFE9, {0xFB, 0x7A}}, {0xCFED, {0xFB, 0x7B}},
	{0xD0E5, {0xFB, 0x81}}, {0xD0E9, {0xFB, 0x83}}, {0xD1E8, {0xFB, 0x84}},
	{0xD1EC, {0xFB, 0x87}}, {0xD2BB, {0xFB, 0x88}}, {0xD3E1, {0xFB, 0x8A}},
	{0xD3E8, {0xFB, 0x8B}}, {0xD4A7, {0xFB, 0x8C}}, {0xD4D4, {0xFB, 0x8F}},
	{0xD4E3, {0xFA, 0x5C}}, {0xD4F2, {0xFB, 0x90}}, {0xD5AE, {0xFB, 0x91}},
	{0xD7DE, {0xFB, 0x93}}, {0xD8A2, {0xFB, 0x95}}, {0xD8B7, {0xFB, 0x96}},
	{0xD8C1, {0xFB, 0x97}}, {0xD8D1, {0xFB, 0x98}}, {0xD8F4, {0xFB, 0x99}},
	{0xD9A1, {0xFA, 0x60}}, {0xD9C6, {0xFB, 0x9A}}, {0xD9C8, {0xFB, 0x9B}},
	{0xD9D1, {0xFB, 0x9C}}, {0xDCD3, {0xFB, 0xA2}}, {0xDCDF, {0xFA, 0x5D}},
	{0xDDC8, {0xFB, 0xA3}}, {0xDDD4, {0xFB, 0xA4}}, {0xDDEA, {0xFB, 0xA5}},
	{0xDDFA, {0xFB, 0xA6}}, {0xDEA4, {0xFB, 0xA7}}, {0xDEB0, {0xFB, 0xA8}},
	{0xDEB5, {0xFB, 0xAA}}, {0xDECB, {0xFB, 0xAB}}, {0xDFB9, {0xFB, 0xAD}},
	{0xDFC3, {0xFB, 0xAF}}, {0xE0D9, {0xFB, 0xB2}}, {0xE1E2, {0xFB, 0xB5}},
	{0xE2C7, {0xFB, 0xB9}}, {0xE3A6, {0xFB, 0xBB}}, {0xE3A8, {0xFB, 0xBA}},
	{0xE3A9, {0xFB, 0xBC}}, {0xE3AA, {0xFB, 0xBF}}, {0xE3AB, {0xFB, 0xC0}},
	{0xE3AF, {0xFB, 0xBD}}, {0xE3B0, {0xFB, 0xBE}}, {0xE3BC, {0xFB, 0xC1}},
	{0xE3BF, {0xFB, 0xC3}}, {0xE3C1, {0xFB, 0xC2}}, {0xE3D4, {0xFB, 0xCA}},
	{0xE3D5, {0xFB, 0xC4}}, {0xE3D6, {0xFB, 0xC6}}, {0xE3D8, {0xFB, 0xC5}},
	{0xE3DF, {0xFB, 0xC7}}, {0xE3E1, {0xFB, 0xC9}}, {0xE3E3, {0xFB, 0xC8}},
	{0xE3E9, {0xFB, 0xCB}}, {0xE3F1, {0xFB, 0xCD}}, {0xE3F2, {0xFB, 0xCE}},
	{0xE3F8, {0xFA, 0x5F}}, {0xE4A6, {0xFB, 0xCC}}, {0xE4BE, {0xFB, 0xD2}},
	{0xE4BF, {0xFB, 0xD6}}, {0xE4C0, {0xFB, 0xD4}}, {0xE4C1, {0xFB, 0xD0}},
	{0xE4C3, {0xFB, 0xD1}}, {0xE4C7, {0xFB, 0xD5}}, {0xE4CB, {0xFB, 0xCF}},
	{0xE4D0, {0xFA, 0x65}}, {0xE4D1, {0xFB, 0xD9}}, {0xE4D2, {0xFB, 0xDC}},
	{0xE4D4, {0xFB, 0xDE}}, {0xE4DB, {0xFB, 0xDD}}, {0xE4DC, {0xFB, 0xDB}},
	{0xE4DE, {0xFB, 0xD8}}, {0xE4E0, {0xFB, 0xD7}}, {0xE4E9, {0xFA, 0x5E}},
	{0xE4EF, {0xFB, 0xE0}}, {0xE4FA, {0xFB, 0xDF}}, {0xE5B3, {0xFB, 0xE1}},
	{0xE5BF, {0xFB, 0xE2}}, {0xE5C9, {0xFB, 0xE3}}, {0xE5D0, {0xFB, 0xE4}},
	{0xE5E2, {0xFB, 0xE5}}, {0xE5EA, {0xFB, 0xE6}}, {0xE5EB, {0xFB, 0xE7}},
	{0xE6E8, {0xFB, 0xEB}}, {0xE6EF, {0xFB, 0xEC}}, {0xE7AC, {0xFB, 0xED}},
	{0xE7AE, {0xFB, 0xEF}}, {0xE7B1, {0xFB, 0xF1}}, {0xE7B2, {0xFB, 0xF3}},
	{0xE8B1, {0xFB, 0xF4}}, {0xE8B6, {0xFB, 0xF5}}, {0xE8DD, {0xFB, 0xF8}},
	{0xE9D1, {0xFB, 0xFB}}, {0xE9ED, {0xFC, 0x40}}, {0xEACD, {0xFC, 0x41}},
	{0xEADB, {0xFC, 0x43}}, {0xEAE6, {0xFC, 0x44}}, {0xEAEA, {0xFC, 0x45}},
	{0xEBA5, {0xFC, 0x46}}, {0xEBFA, {0xFC, 0x48}}, {0xEBFB, {0xFC, 0x47}},
	{0xECD6, {0xFC, 0x4A}},
};

/* EUC to SJIS IBM extended characters map (G3 Upper block) */
static unsigned char euc2sjisibm_g3upper_map[][2] = {
	{0xFA, 0x40}, {0xFA, 0x41}, {0xFA, 0x42}, {0xFA, 0x43}, {0xFA, 0x44},
	{0xFA, 0x45}, {0xFA, 0x46}, {0xFA, 0x47}, {0xFA, 0x48}, {0xFA, 0x49},
	{0xFA, 0x4A}, {0xFA, 0x4B}, {0xFA, 0x4C}, {0xFA, 0x4D}, {0xFA, 0x4E},
	{0xFA, 0x4F}, {0xFA, 0x50}, {0xFA, 0x51}, {0xFA, 0x52}, {0xFA, 0x53},
	{0xFA, 0x56}, {0xFA, 0x57}, {0xFA, 0x58}, {0xFA, 0x59}, {0xFA, 0x5A},
	{0xFA, 0x62}, {0xFA, 0x6A}, {0xFA, 0x7C}, {0xFA, 0x83}, {0xFA, 0x8A},
	{0xFA, 0x8B}, {0xFA, 0x90}, {0xFA, 0x92}, {0xFA, 0x96}, {0xFA, 0x9B},
	{0xFA, 0x9C}, {0xFA, 0x9D}, {0xFA, 0xAA}, {0xFA, 0xAE}, {0xFA, 0xB0},
	{0xFA, 0xB1}, {0xFA, 0xBA}, {0xFA, 0xBD}, {0xFA, 0xC1}, {0xFA, 0xCD},
	{0xFA, 0xD0}, {0xFA, 0xD5}, {0xFA, 0xD8}, {0xFA, 0xE0}, {0xFA, 0xE5},
	{0xFA, 0xE8}, {0xFA, 0xEA}, {0xFA, 0xEE}, {0xFA, 0xF2}, {0xFB, 0x43},
	{0xFB, 0x44}, {0xFB, 0x50}, {0xFB, 0x58}, {0xFB, 0x5E}, {0xFB, 0x6E},
	{0xFB, 0x70}, {0xFB, 0x72}, {0xFB, 0x75}, {0xFB, 0x7C}, {0xFB, 0x7D},
	{0xFB, 0x7E}, {0xFB, 0x80}, {0xFB, 0x82}, {0xFB, 0x85}, {0xFB, 0x86},
	{0xFB, 0x89}, {0xFB, 0x8D}, {0xFB, 0x8E}, {0xFB, 0x92}, {0xFB, 0x94},
	{0xFB, 0x9D}, {0xFB, 0x9E}, {0xFB, 0x9F}, {0xFB, 0xA0}, {0xFB, 0xA1},
	{0xFB, 0xA9}, {0xFB, 0xAC}, {0xFB, 0xAE}, {0xFB, 0xB0}, {0xFB, 0xB1},
	{0xFB, 0xB3}, {0xFB, 0xB4}, {0xFB, 0xB6}, {0xFB, 0xB7}, {0xFB, 0xB8},
	{0xFB, 0xD3}, {0xFB, 0xDA}, {0xFB, 0xE8}, {0xFB, 0xE9}, {0xFB, 0xEA},
	{0xFB, 0xEE}, {0xFB, 0xF0}, {0xFB, 0xF2}, {0xFB, 0xF6}, {0xFB, 0xF7},
	{0xFB, 0xF9}, {0xFB, 0xFA}, {0xFB, 0xFC}, {0xFC, 0x42}, {0xFC, 0x49},
	{0xFC, 0x4B},
};

#define MAP_ELEMENT_OF(map)	(sizeof(map) / sizeof(map[0]))

static inline int sjisibm2euc(unsigned char *euc, const unsigned char sjis_hi,
			      const unsigned char sjis_lo);
static inline int euc2sjisibm_jisx0212(unsigned char *sjis, const unsigned char euc_hi,
				       const unsigned char euc_lo);
static inline int euc2sjisibm_g3upper(unsigned char *sjis, const unsigned char euc_hi,
				      const unsigned char euc_lo);
static inline int euc2sjisibm(unsigned char *sjis, const unsigned char euc_hi,
			      const unsigned char euc_lo);
static inline int sjisnec2sjisibm(unsigned char *sjisibm,
				  const unsigned char sjisnec_hi,
				  const unsigned char sjisnec_lo);

/* SJIS IBM extended characters to EUC */
static inline int sjisibm2euc(unsigned char *euc, const unsigned char sjis_hi,
			      const unsigned char sjis_lo)
{
	int index;

	index = ((sjis_hi - 0xFA) * (0xFD - 0x40)) + (sjis_lo - 0x40);
	if (IS_EUC_IBM2JISX0208(sjisibm2euc_map[index][0],
				sjisibm2euc_map[index][1])) {
		euc[0] = sjisibm2euc_map[index][0];
		euc[1] = sjisibm2euc_map[index][1];
		return 2;
	} else {
		euc[0] = SS3;
		euc[1] = sjisibm2euc_map[index][0];
		euc[2] = sjisibm2euc_map[index][1];
		return 3;
	}
}

/* EUC to SJIS IBM extended characters (G3 JIS X 0212 block) */
static inline int euc2sjisibm_jisx0212(unsigned char *sjis, const unsigned char euc_hi,
				       const unsigned char euc_lo)
{
	int index, min_index, max_index;
	unsigned short euc;

	min_index = 0;
	max_index = MAP_ELEMENT_OF(euc2sjisibm_jisx0212_map) - 1;
	euc = (euc_hi << 8) | euc_lo;

	while (min_index <= max_index) {
		index = (min_index + max_index) / 2;
		if (euc < euc2sjisibm_jisx0212_map[index].euc)
			max_index = index - 1;
		else
			min_index = index + 1;
		if (euc == euc2sjisibm_jisx0212_map[index].euc) {
			sjis[0] = euc2sjisibm_jisx0212_map[index].sjis[0];
			sjis[1] = euc2sjisibm_jisx0212_map[index].sjis[1];
			return 3;
		}
	}
	return 0;
}

/* EUC to SJIS IBM extended characters (G3 Upper block) */
static inline int euc2sjisibm_g3upper(unsigned char *sjis, const unsigned char euc_hi,
				      const unsigned char euc_lo)
{
	int index;

	if (euc_hi == 0xF3)
		index = ((euc_hi << 8) | euc_lo) - 0xF3F3;
	else
		index = ((euc_hi << 8) | euc_lo) - 0xF4A1 + 12;

	if ((index < 0) || (index >= MAP_ELEMENT_OF(euc2sjisibm_g3upper_map)))
		return 0;

	sjis[0] = euc2sjisibm_g3upper_map[index][0];
	sjis[1] = euc2sjisibm_g3upper_map[index][1];

	return 3;
}

/* EUC to SJIS IBM extended characters (G3 block) */
static inline int euc2sjisibm(unsigned char *sjis, const unsigned char euc_hi,
			      const unsigned char euc_lo)
{
	int n;

#if 0
	if ((euc_hi == 0xA2) && (euc_lo == 0xCC)) {
		sjis[0] = 0xFA;
		sjis[1] = 0x54;
		return 2;
	} else if ((euc_hi == 0xA2) && (euc_lo == 0xE8)) {
		sjis[0] = 0xFA;
		sjis[1] = 0x5B;
		return 2;
	}
#endif
	if ((n = euc2sjisibm_g3upper(sjis, euc_hi, euc_lo))) {
		return n;
	} else if ((n = euc2sjisibm_jisx0212(sjis, euc_hi, euc_lo))) {
		return n;
	}

	return 0;
}

/* NEC/IBM extended characters to IBM extended characters */
static inline int sjisnec2sjisibm(unsigned char *sjisibm,
				  const unsigned char sjisnec_hi,
				  const unsigned char sjisnec_lo)
{
	int count;

	if (! IS_SJIS_NECIBM(sjisnec_hi, sjisnec_lo))
		return 0;

	if ((sjisnec_hi == 0xEE) && (sjisnec_lo == 0xF9)) {
		sjisibm[0] = 0x81;
		sjisibm[1] = 0xCA;
		return 2;
	}

	if ((sjisnec_hi == 0xEE) && (sjisnec_lo >= 0xEF)) {
		count = (sjisnec_hi << 8 | sjisnec_lo)
			- (sjisnec_lo <= 0xF9 ? 0xEEEF : (0xEEEF - 10));
	} else {
		count = (sjisnec_hi - 0xED) * (0xFC - 0x40)
			+ (sjisnec_lo - 0x40) + (0x5C - 0x40);
		if (sjisnec_lo >= 0x7F)
			count--;
	}

	sjisibm[0] = 0xFA + (count / (0xFC - 0x40));
	sjisibm[1] = 0x40 + (count % (0xFC - 0x40));
	if (sjisibm[1] >= 0x7F)
		sjisibm[1]++;

	return 2;
}

static int uni2char(const wchar_t uni,
		    unsigned char *out, int boundlen)
{
	int n;

	if (!p_nls)
		return -EINVAL;
	if ((n = p_nls->uni2char(uni, out, boundlen)) < 0)
		return n;

	/* translate SJIS into EUC-JP */
	if (n == 1) {
		if (IS_SJIS_JISX0201KANA(out[0])) {
			/* JIS X 0201 KANA */
			if (boundlen < 2)
				return -ENAMETOOLONG;

			out[1] = out[0];
			out[0] = SS2;
			return 2;
		}
	} else if (n == 2) {
		/* NEC/IBM extended characters to IBM extended characters */
		sjisnec2sjisibm(out, out[0], out[1]);

		if (IS_SJIS_UDC_LOW(out[0], out[1])) {
			/* User defined characters half low */
			MAP_SJIS2EUC(out[0], out[1], 0xF0, out[0], out[1], 0xF5);
		} else if (IS_SJIS_UDC_HI(out[0], out[1])) {
			/* User defined characters half high */
			unsigned char ch, cl;

			if (boundlen < 3)
				return -ENAMETOOLONG;

			n = 3; ch = out[0]; cl = out[1];
			out[0] = SS3;
			MAP_SJIS2EUC(ch, cl, 0xF5, out[1], out[2], 0xF5);
		} else if (IS_SJIS_IBM(out[0], out[1])) {
			/* IBM extended characters */
			unsigned char euc[3], i;

			n = sjisibm2euc(euc, out[0], out[1]);
			if (boundlen < n)
				return -ENAMETOOLONG;
			for (i = 0; i < n; i++)
				out[i] = euc[i];
		} else if (IS_SJIS_JISX0208(out[0], out[1])) {
			/* JIS X 0208 (include NEC special characters) */
			out[0] = (out[0]^0xA0)*2 + 0x5F;
			if (out[1] > 0x9E)
				out[0]++;

			if (out[1] < 0x7F)
				out[1] = out[1] + 0x61;
			else if (out[1] < 0x9F)
				out[1] = out[1] + 0x60;
			else
				out[1] = out[1] + 0x02;
		} else {
			/* Invalid characters */
			return -EINVAL;
		}
	}
	else
		return -EINVAL;

	return n;
}

static int char2uni(const unsigned char *rawstring, int boundlen,
		    wchar_t *uni)
{
	unsigned char sjis_temp[2];
	int euc_offset, n;

	if ( !p_nls )
		return -EINVAL;
	if (boundlen <= 0)
		return -ENAMETOOLONG;

	/* translate EUC-JP into SJIS */
	if (rawstring[0] > 0x7F) {
		if (rawstring[0] == SS3) {
			if (boundlen < 3)
				return -EINVAL;
			euc_offset = 3;

			if (IS_EUC_UDC_HI(rawstring[1], rawstring[2])) {
				/* User defined characters half high */
				MAP_EUC2SJIS(rawstring[1], rawstring[2], 0xF5,
					     sjis_temp[0], sjis_temp[1], 0xF5);
			} else if (euc2sjisibm(sjis_temp,rawstring[1],rawstring[2])) {
				/* IBM extended characters */
			} else {
				/* JIS X 0212 and Invalid characters*/
				return -EINVAL;

				/* 'GETA' with SJIS coding */
				/* sjis_temp[0] = 0x81; */
				/* sjis_temp[1] = 0xAC; */
			}
		} else {
			if (boundlen < 2)
				return -EINVAL;
			euc_offset = 2;

			if (IS_EUC_JISX0201KANA(rawstring[0], rawstring[1])) {
				/* JIS X 0201 KANA */
				sjis_temp[0] = rawstring[1];
				sjis_temp[1] = 0x00;
			} else if (IS_EUC_UDC_LOW(rawstring[0], rawstring[1])) {
				/* User defined characters half low */
				MAP_EUC2SJIS(rawstring[0], rawstring[1], 0xF5,
					     sjis_temp[0], sjis_temp[1], 0xF0);
			} else if (IS_EUC_JISX0208(rawstring[0], rawstring[1])) {
				/* JIS X 0208 (include NEC spesial characters) */
				sjis_temp[0] = ((rawstring[0]-0x5f)/2) ^ 0xA0;
				if (!(rawstring[0] & 1))
					sjis_temp[1] = rawstring[1] - 0x02;
				else if (rawstring[1] < 0xE0)
					sjis_temp[1] = rawstring[1] - 0x61;
				else
					sjis_temp[1] = rawstring[1] - 0x60;
			} else {
				/* Invalid characters */
				return -EINVAL;
			}
		}
	} else {
		euc_offset = 1;

		/* JIS X 0201 ROMAJI */
		sjis_temp[0] = rawstring[0];
		sjis_temp[1] = 0x00;
	}

	if ( (n = p_nls->char2uni(sjis_temp, sizeof(sjis_temp), uni)) < 0)
		return n;

	return euc_offset;
}

static struct nls_table table = {
	"euc-jp",
	uni2char,
	char2uni,
	NULL,
	NULL,
	THIS_MODULE,
};

static int __init init_nls_euc_jp(void)
{
	p_nls = load_nls("cp932");

	if (p_nls) {
		table.charset2upper = p_nls->charset2upper;
		table.charset2lower = p_nls->charset2lower;
		return register_nls(&table);
	}

	return -EINVAL;
}

static void __exit exit_nls_euc_jp(void)
{
	unregister_nls(&table);
	unload_nls(p_nls);
}

module_init(init_nls_euc_jp)
module_exit(exit_nls_euc_jp)

/*
 * Overrides for Emacs so that we follow Linus's tabbing style.
 * Emacs will notice this stuff at the end of the file and automatically
 * adjust the settings for this buffer only.  This must remain at the end
 * of the file.
 *
---------------------------------------------------------------------------
 * Local variables:
 * c-indent-level: 8
 * c-brace-imaginary-offset: 0
 * c-brace-offset: -8
 * c-argdecl-indent: 8
 * c-label-offset: -8
 * c-continued-statement-offset: 8
 * c-continued-brace-offset: 0
 * End:
 */

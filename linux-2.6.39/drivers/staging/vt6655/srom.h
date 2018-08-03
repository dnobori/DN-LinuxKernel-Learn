#include "linux/generated/autoconf.h"
/*
 * Copyright (c) 1996, 2003 VIA Networking Technologies, Inc.
 * All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 *
 * File: srom.h
 *
 * Purpose: Implement functions to access eeprom
 *
 * Author: Jerry Chen
 *
 * Date: Jan 29, 2003
 *
 */

#ifndef __SROM_H__
#define __SROM_H__

#include "ttype.h"

/*---------------------  Export Definitions -------------------------*/

#define EEP_MAX_CONTEXT_SIZE    256

#define CB_EEPROM_READBYTE_WAIT 900     //us

#define W_MAX_I2CRETRY          0x0fff

//
// Contents in the EEPROM
//
#define EEP_OFS_PAR         0x00        // physical address
#define EEP_OFS_ANTENNA     0x16
#define EEP_OFS_RADIOCTL    0x17
#define EEP_OFS_RFTYPE      0x1B        // for select RF
#define EEP_OFS_MINCHANNEL  0x1C        // Min Channel #
#define EEP_OFS_MAXCHANNEL  0x1D        // Max Channel #
#define EEP_OFS_SIGNATURE   0x1E        //
#define EEP_OFS_ZONETYPE    0x1F        //
#define EEP_OFS_RFTABLE     0x20        // RF POWER TABLE
#define EEP_OFS_PWR_CCK     0x20
#define EEP_OFS_SETPT_CCK   0x21
#define EEP_OFS_PWR_OFDMG   0x23
#define EEP_OFS_SETPT_OFDMG 0x24
#define EEP_OFS_PWR_FORMULA_OST  0x26   //
#define EEP_OFS_MAJOR_VER 0x2E
#define EEP_OFS_MINOR_VER 0x2F
#define EEP_OFS_CCK_PWR_TBL     0x30
#define EEP_OFS_CCK_PWR_dBm     0x3F
#define EEP_OFS_OFDM_PWR_TBL    0x40
#define EEP_OFS_OFDM_PWR_dBm    0x4F
//{{ RobertYu: 20041124
#define EEP_OFS_SETPT_OFDMA         0x4E
#define EEP_OFS_OFDMA_PWR_TBL       0x50
//}}
#define EEP_OFS_OFDMA_PWR_dBm       0xD2


//----------need to remove --------------------
#define EEP_OFS_BBTAB_LEN   0x70        // BB Table Length
#define EEP_OFS_BBTAB_ADR   0x71        // BB Table Offset
#define EEP_OFS_CHECKSUM    0xFF        // reserved area for baseband 28h ~ 78h

#define EEP_I2C_DEV_ID      0x50        // EEPROM device address on the I2C bus


//
// Bits in EEP_OFS_ANTENNA
//
#define EEP_ANTENNA_MAIN    0x01
#define EEP_ANTENNA_AUX     0x02
#define EEP_ANTINV          0x04

//
// Bits in EEP_OFS_RADIOCTL
//
#define EEP_RADIOCTL_ENABLE 0x80
#define EEP_RADIOCTL_INV    0x01

/*---------------------  Export Types  ------------------------------*/

// AT24C02 eeprom contents
//      2048 bits = 256 bytes = 128 words
//
typedef struct tagSSromReg {
    unsigned char abyPAR[6];                  // 0x00 (unsigned short)

    unsigned short wSUB_VID;                   // 0x03 (unsigned short)
    unsigned short wSUB_SID;

    unsigned char byBCFG0;                    // 0x05 (unsigned short)
    unsigned char byBCFG1;

    unsigned char byFCR0;                     // 0x06 (unsigned short)
    unsigned char byFCR1;
    unsigned char byPMC0;                     // 0x07 (unsigned short)
    unsigned char byPMC1;
    unsigned char byMAXLAT;                   // 0x08 (unsigned short)
    unsigned char byMINGNT;
    unsigned char byCFG0;                     // 0x09 (unsigned short)
    unsigned char byCFG1;
    unsigned short wCISPTR;                    // 0x0A (unsigned short)
    unsigned short wRsv0;                      // 0x0B (unsigned short)
    unsigned short wRsv1;                      // 0x0C (unsigned short)
    unsigned char byBBPAIR;                   // 0x0D (unsigned short)
    unsigned char byRFTYPE;
    unsigned char byMinChannel;               // 0x0E (unsigned short)
    unsigned char byMaxChannel;
    unsigned char bySignature;                // 0x0F (unsigned short)
    unsigned char byCheckSum;

    unsigned char abyReserved0[96];           // 0x10 (unsigned short)
    unsigned char abyCIS[128];                // 0x80 (unsigned short)
} SSromReg, *PSSromReg;

/*---------------------  Export Macros ------------------------------*/

/*---------------------  Export Classes  ----------------------------*/

/*---------------------  Export Variables  --------------------------*/

/*---------------------  Export Functions  --------------------------*/

unsigned char SROMbyReadEmbedded(unsigned long dwIoBase, unsigned char byContntOffset);
bool SROMbWriteEmbedded(unsigned long dwIoBase, unsigned char byContntOffset, unsigned char byData);

void SROMvRegBitsOn(unsigned long dwIoBase, unsigned char byContntOffset, unsigned char byBits);
void SROMvRegBitsOff(unsigned long dwIoBase, unsigned char byContntOffset, unsigned char byBits);

bool SROMbIsRegBitsOn(unsigned long dwIoBase, unsigned char byContntOffset, unsigned char byTestBits);
bool SROMbIsRegBitsOff(unsigned long dwIoBase, unsigned char byContntOffset, unsigned char byTestBits);

void SROMvReadAllContents(unsigned long dwIoBase, unsigned char *pbyEepromRegs);
void SROMvWriteAllContents(unsigned long dwIoBase, unsigned char *pbyEepromRegs);

void SROMvReadEtherAddress(unsigned long dwIoBase, unsigned char *pbyEtherAddress);
void SROMvWriteEtherAddress(unsigned long dwIoBase, unsigned char *pbyEtherAddress);

void SROMvReadSubSysVenId(unsigned long dwIoBase, unsigned long *pdwSubSysVenId);

bool SROMbAutoLoad (unsigned long dwIoBase);

#endif // __EEPROM_H__

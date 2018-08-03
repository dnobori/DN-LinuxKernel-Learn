#include "linux/generated/autoconf.h"
/*  *********************************************************************
    *  SB1250 Board Support Package
    *
    *  LDT constants				File: sb1250_ldt.h
    *
    *  This module contains constants and macros to describe
    *  the LDT interface on the SB1250.
    *
    *  SB1250 specification level:  User's manual 1/02/02
    *
    *********************************************************************
    *
    *  Copyright 2000, 2001, 2002, 2003
    *  Broadcom Corporation. All rights reserved.
    *
    *  This program is free software; you can redistribute it and/or
    *  modify it under the terms of the GNU General Public License as
    *  published by the Free Software Foundation; either version 2 of
    *  the License, or (at your option) any later version.
    *
    *  This program is distributed in the hope that it will be useful,
    *  but WITHOUT ANY WARRANTY; without even the implied warranty of
    *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    *  GNU General Public License for more details.
    *
    *  You should have received a copy of the GNU General Public License
    *  along with this program; if not, write to the Free Software
    *  Foundation, Inc., 59 Temple Place, Suite 330, Boston,
    *  MA 02111-1307 USA
    ********************************************************************* */


#ifndef _SB1250_LDT_H
#define _SB1250_LDT_H

#include "sb1250_defs.h"

#define K_LDT_VENDOR_SIBYTE	0x166D
#define K_LDT_DEVICE_SB1250	0x0002

/*
 * LDT Interface Type 1 (bridge) configuration header
 */

#define R_LDT_TYPE1_DEVICEID	0x0000
#define R_LDT_TYPE1_CMDSTATUS	0x0004
#define R_LDT_TYPE1_CLASSREV	0x0008
#define R_LDT_TYPE1_DEVHDR	0x000C
#define R_LDT_TYPE1_BAR0	0x0010	/* not used */
#define R_LDT_TYPE1_BAR1	0x0014	/* not used */

#define R_LDT_TYPE1_BUSID	0x0018	/* bus ID register */
#define R_LDT_TYPE1_SECSTATUS	0x001C	/* secondary status / I/O base/limit */
#define R_LDT_TYPE1_MEMLIMIT	0x0020
#define R_LDT_TYPE1_PREFETCH	0x0024
#define R_LDT_TYPE1_PREF_BASE	0x0028
#define R_LDT_TYPE1_PREF_LIMIT	0x002C
#define R_LDT_TYPE1_IOLIMIT	0x0030
#define R_LDT_TYPE1_CAPPTR	0x0034
#define R_LDT_TYPE1_ROMADDR	0x0038
#define R_LDT_TYPE1_BRCTL	0x003C
#define R_LDT_TYPE1_CMD		0x0040
#define R_LDT_TYPE1_LINKCTRL	0x0044
#define R_LDT_TYPE1_LINKFREQ	0x0048
#define R_LDT_TYPE1_RESERVED1	0x004C
#define R_LDT_TYPE1_SRICMD	0x0050
#define R_LDT_TYPE1_SRITXNUM	0x0054
#define R_LDT_TYPE1_SRIRXNUM	0x0058
#define R_LDT_TYPE1_ERRSTATUS   0x0068
#define R_LDT_TYPE1_SRICTRL	0x006C
#if SIBYTE_HDR_FEATURE(1250, PASS2) || SIBYTE_HDR_FEATURE(112x, PASS1)
#define R_LDT_TYPE1_ADDSTATUS	0x0070
#endif /* 1250 PASS2 || 112x PASS1 */
#define R_LDT_TYPE1_TXBUFCNT	0x00C8
#define R_LDT_TYPE1_EXPCRC	0x00DC
#define R_LDT_TYPE1_RXCRC	0x00F0


/*
 * LDT Device ID register
 */

#define S_LDT_DEVICEID_VENDOR		0
#define M_LDT_DEVICEID_VENDOR		_SB_MAKEMASK_32(16, S_LDT_DEVICEID_VENDOR)
#define V_LDT_DEVICEID_VENDOR(x)	_SB_MAKEVALUE_32(x, S_LDT_DEVICEID_VENDOR)
#define G_LDT_DEVICEID_VENDOR(x)	_SB_GETVALUE_32(x, S_LDT_DEVICEID_VENDOR, M_LDT_DEVICEID_VENDOR)

#define S_LDT_DEVICEID_DEVICEID		16
#define M_LDT_DEVICEID_DEVICEID		_SB_MAKEMASK_32(16, S_LDT_DEVICEID_DEVICEID)
#define V_LDT_DEVICEID_DEVICEID(x)	_SB_MAKEVALUE_32(x, S_LDT_DEVICEID_DEVICEID)
#define G_LDT_DEVICEID_DEVICEID(x)	_SB_GETVALUE_32(x, S_LDT_DEVICEID_DEVICEID, M_LDT_DEVICEID_DEVICEID)


/*
 * LDT Command Register (Table 8-13)
 */

#define M_LDT_CMD_IOSPACE_EN		_SB_MAKEMASK1_32(0)
#define M_LDT_CMD_MEMSPACE_EN		_SB_MAKEMASK1_32(1)
#define M_LDT_CMD_MASTER_EN		_SB_MAKEMASK1_32(2)
#define M_LDT_CMD_SPECCYC_EN		_SB_MAKEMASK1_32(3)
#define M_LDT_CMD_MEMWRINV_EN		_SB_MAKEMASK1_32(4)
#define M_LDT_CMD_VGAPALSNP_EN		_SB_MAKEMASK1_32(5)
#define M_LDT_CMD_PARERRRESP		_SB_MAKEMASK1_32(6)
#define M_LDT_CMD_WAITCYCCTRL		_SB_MAKEMASK1_32(7)
#define M_LDT_CMD_SERR_EN		_SB_MAKEMASK1_32(8)
#define M_LDT_CMD_FASTB2B_EN		_SB_MAKEMASK1_32(9)

/*
 * LDT class and revision registers
 */

#define S_LDT_CLASSREV_REV		0
#define M_LDT_CLASSREV_REV		_SB_MAKEMASK_32(8, S_LDT_CLASSREV_REV)
#define V_LDT_CLASSREV_REV(x)		_SB_MAKEVALUE_32(x, S_LDT_CLASSREV_REV)
#define G_LDT_CLASSREV_REV(x)		_SB_GETVALUE_32(x, S_LDT_CLASSREV_REV, M_LDT_CLASSREV_REV)

#define S_LDT_CLASSREV_CLASS		8
#define M_LDT_CLASSREV_CLASS		_SB_MAKEMASK_32(24, S_LDT_CLASSREV_CLASS)
#define V_LDT_CLASSREV_CLASS(x)		_SB_MAKEVALUE_32(x, S_LDT_CLASSREV_CLASS)
#define G_LDT_CLASSREV_CLASS(x)		_SB_GETVALUE_32(x, S_LDT_CLASSREV_CLASS, M_LDT_CLASSREV_CLASS)

#define K_LDT_REV			0x01
#define K_LDT_CLASS			0x060000

/*
 * Device Header (offset 0x0C)
 */

#define S_LDT_DEVHDR_CLINESZ		0
#define M_LDT_DEVHDR_CLINESZ		_SB_MAKEMASK_32(8, S_LDT_DEVHDR_CLINESZ)
#define V_LDT_DEVHDR_CLINESZ(x)		_SB_MAKEVALUE_32(x, S_LDT_DEVHDR_CLINESZ)
#define G_LDT_DEVHDR_CLINESZ(x)		_SB_GETVALUE_32(x, S_LDT_DEVHDR_CLINESZ, M_LDT_DEVHDR_CLINESZ)

#define S_LDT_DEVHDR_LATTMR		8
#define M_LDT_DEVHDR_LATTMR		_SB_MAKEMASK_32(8, S_LDT_DEVHDR_LATTMR)
#define V_LDT_DEVHDR_LATTMR(x)		_SB_MAKEVALUE_32(x, S_LDT_DEVHDR_LATTMR)
#define G_LDT_DEVHDR_LATTMR(x)		_SB_GETVALUE_32(x, S_LDT_DEVHDR_LATTMR, M_LDT_DEVHDR_LATTMR)

#define S_LDT_DEVHDR_HDRTYPE		16
#define M_LDT_DEVHDR_HDRTYPE		_SB_MAKEMASK_32(8, S_LDT_DEVHDR_HDRTYPE)
#define V_LDT_DEVHDR_HDRTYPE(x)		_SB_MAKEVALUE_32(x, S_LDT_DEVHDR_HDRTYPE)
#define G_LDT_DEVHDR_HDRTYPE(x)		_SB_GETVALUE_32(x, S_LDT_DEVHDR_HDRTYPE, M_LDT_DEVHDR_HDRTYPE)

#define K_LDT_DEVHDR_HDRTYPE_TYPE1	1

#define S_LDT_DEVHDR_BIST		24
#define M_LDT_DEVHDR_BIST		_SB_MAKEMASK_32(8, S_LDT_DEVHDR_BIST)
#define V_LDT_DEVHDR_BIST(x)		_SB_MAKEVALUE_32(x, S_LDT_DEVHDR_BIST)
#define G_LDT_DEVHDR_BIST(x)		_SB_GETVALUE_32(x, S_LDT_DEVHDR_BIST, M_LDT_DEVHDR_BIST)



/*
 * LDT Status Register (Table 8-14).  Note that these constants
 * assume you've read the command and status register
 * together (32-bit read at offset 0x04)
 *
 * These bits also apply to the secondary status
 * register (Table 8-15), offset 0x1C
 */

#if SIBYTE_HDR_FEATURE(1250, PASS2) || SIBYTE_HDR_FEATURE(112x, PASS1)
#define M_LDT_STATUS_VGAEN		_SB_MAKEMASK1_32(3)
#endif /* 1250 PASS2 || 112x PASS1 */
#define M_LDT_STATUS_CAPLIST		_SB_MAKEMASK1_32(20)
#define M_LDT_STATUS_66MHZCAP		_SB_MAKEMASK1_32(21)
#define M_LDT_STATUS_RESERVED2		_SB_MAKEMASK1_32(22)
#define M_LDT_STATUS_FASTB2BCAP		_SB_MAKEMASK1_32(23)
#define M_LDT_STATUS_MSTRDPARERR	_SB_MAKEMASK1_32(24)

#define S_LDT_STATUS_DEVSELTIMING	25
#define M_LDT_STATUS_DEVSELTIMING	_SB_MAKEMASK_32(2, S_LDT_STATUS_DEVSELTIMING)
#define V_LDT_STATUS_DEVSELTIMING(x)	_SB_MAKEVALUE_32(x, S_LDT_STATUS_DEVSELTIMING)
#define G_LDT_STATUS_DEVSELTIMING(x)	_SB_GETVALUE_32(x, S_LDT_STATUS_DEVSELTIMING, M_LDT_STATUS_DEVSELTIMING)

#define M_LDT_STATUS_SIGDTGTABORT	_SB_MAKEMASK1_32(27)
#define M_LDT_STATUS_RCVDTGTABORT	_SB_MAKEMASK1_32(28)
#define M_LDT_STATUS_RCVDMSTRABORT	_SB_MAKEMASK1_32(29)
#define M_LDT_STATUS_SIGDSERR		_SB_MAKEMASK1_32(30)
#define M_LDT_STATUS_DETPARERR		_SB_MAKEMASK1_32(31)

/*
 * Bridge Control Register (Table 8-16).  Note that these
 * constants assume you've read the register as a 32-bit
 * read (offset 0x3C)
 */

#define M_LDT_BRCTL_PARERRRESP_EN	_SB_MAKEMASK1_32(16)
#define M_LDT_BRCTL_SERR_EN		_SB_MAKEMASK1_32(17)
#define M_LDT_BRCTL_ISA_EN		_SB_MAKEMASK1_32(18)
#define M_LDT_BRCTL_VGA_EN		_SB_MAKEMASK1_32(19)
#define M_LDT_BRCTL_MSTRABORTMODE	_SB_MAKEMASK1_32(21)
#define M_LDT_BRCTL_SECBUSRESET		_SB_MAKEMASK1_32(22)
#define M_LDT_BRCTL_FASTB2B_EN		_SB_MAKEMASK1_32(23)
#define M_LDT_BRCTL_PRIDISCARD		_SB_MAKEMASK1_32(24)
#define M_LDT_BRCTL_SECDISCARD		_SB_MAKEMASK1_32(25)
#define M_LDT_BRCTL_DISCARDSTAT		_SB_MAKEMASK1_32(26)
#define M_LDT_BRCTL_DISCARDSERR_EN	_SB_MAKEMASK1_32(27)

/*
 * LDT Command Register (Table 8-17).  Note that these constants
 * assume you've read the command and status register together
 * 32-bit read at offset 0x40
 */

#define M_LDT_CMD_WARMRESET		_SB_MAKEMASK1_32(16)
#define M_LDT_CMD_DOUBLEENDED		_SB_MAKEMASK1_32(17)

#define S_LDT_CMD_CAPTYPE		29
#define M_LDT_CMD_CAPTYPE		_SB_MAKEMASK_32(3, S_LDT_CMD_CAPTYPE)
#define V_LDT_CMD_CAPTYPE(x)		_SB_MAKEVALUE_32(x, S_LDT_CMD_CAPTYPE)
#define G_LDT_CMD_CAPTYPE(x)		_SB_GETVALUE_32(x, S_LDT_CMD_CAPTYPE, M_LDT_CMD_CAPTYPE)

/*
 * LDT link control register (Table 8-18), and (Table 8-19)
 */

#define M_LDT_LINKCTRL_CAPSYNCFLOOD_EN	_SB_MAKEMASK1_32(1)
#define M_LDT_LINKCTRL_CRCSTARTTEST	_SB_MAKEMASK1_32(2)
#define M_LDT_LINKCTRL_CRCFORCEERR	_SB_MAKEMASK1_32(3)
#define M_LDT_LINKCTRL_LINKFAIL		_SB_MAKEMASK1_32(4)
#define M_LDT_LINKCTRL_INITDONE		_SB_MAKEMASK1_32(5)
#define M_LDT_LINKCTRL_EOC		_SB_MAKEMASK1_32(6)
#define M_LDT_LINKCTRL_XMITOFF		_SB_MAKEMASK1_32(7)

#define S_LDT_LINKCTRL_CRCERR		8
#define M_LDT_LINKCTRL_CRCERR		_SB_MAKEMASK_32(4, S_LDT_LINKCTRL_CRCERR)
#define V_LDT_LINKCTRL_CRCERR(x)	_SB_MAKEVALUE_32(x, S_LDT_LINKCTRL_CRCERR)
#define G_LDT_LINKCTRL_CRCERR(x)	_SB_GETVALUE_32(x, S_LDT_LINKCTRL_CRCERR, M_LDT_LINKCTRL_CRCERR)

#define S_LDT_LINKCTRL_MAXIN		16
#define M_LDT_LINKCTRL_MAXIN		_SB_MAKEMASK_32(3, S_LDT_LINKCTRL_MAXIN)
#define V_LDT_LINKCTRL_MAXIN(x)		_SB_MAKEVALUE_32(x, S_LDT_LINKCTRL_MAXIN)
#define G_LDT_LINKCTRL_MAXIN(x)		_SB_GETVALUE_32(x, S_LDT_LINKCTRL_MAXIN, M_LDT_LINKCTRL_MAXIN)

#define M_LDT_LINKCTRL_DWFCLN		_SB_MAKEMASK1_32(19)

#define S_LDT_LINKCTRL_MAXOUT		20
#define M_LDT_LINKCTRL_MAXOUT		_SB_MAKEMASK_32(3, S_LDT_LINKCTRL_MAXOUT)
#define V_LDT_LINKCTRL_MAXOUT(x)	_SB_MAKEVALUE_32(x, S_LDT_LINKCTRL_MAXOUT)
#define G_LDT_LINKCTRL_MAXOUT(x)	_SB_GETVALUE_32(x, S_LDT_LINKCTRL_MAXOUT, M_LDT_LINKCTRL_MAXOUT)

#define M_LDT_LINKCTRL_DWFCOUT		_SB_MAKEMASK1_32(23)

#define S_LDT_LINKCTRL_WIDTHIN		24
#define M_LDT_LINKCTRL_WIDTHIN		_SB_MAKEMASK_32(3, S_LDT_LINKCTRL_WIDTHIN)
#define V_LDT_LINKCTRL_WIDTHIN(x)	_SB_MAKEVALUE_32(x, S_LDT_LINKCTRL_WIDTHIN)
#define G_LDT_LINKCTRL_WIDTHIN(x)	_SB_GETVALUE_32(x, S_LDT_LINKCTRL_WIDTHIN, M_LDT_LINKCTRL_WIDTHIN)

#define M_LDT_LINKCTRL_DWFCLIN_EN	_SB_MAKEMASK1_32(27)

#define S_LDT_LINKCTRL_WIDTHOUT		28
#define M_LDT_LINKCTRL_WIDTHOUT		_SB_MAKEMASK_32(3, S_LDT_LINKCTRL_WIDTHOUT)
#define V_LDT_LINKCTRL_WIDTHOUT(x)	_SB_MAKEVALUE_32(x, S_LDT_LINKCTRL_WIDTHOUT)
#define G_LDT_LINKCTRL_WIDTHOUT(x)	_SB_GETVALUE_32(x, S_LDT_LINKCTRL_WIDTHOUT, M_LDT_LINKCTRL_WIDTHOUT)

#define M_LDT_LINKCTRL_DWFCOUT_EN	_SB_MAKEMASK1_32(31)

/*
 * LDT Link frequency register  (Table 8-20) offset 0x48
 */

#define S_LDT_LINKFREQ_FREQ		8
#define M_LDT_LINKFREQ_FREQ		_SB_MAKEMASK_32(4, S_LDT_LINKFREQ_FREQ)
#define V_LDT_LINKFREQ_FREQ(x)		_SB_MAKEVALUE_32(x, S_LDT_LINKFREQ_FREQ)
#define G_LDT_LINKFREQ_FREQ(x)		_SB_GETVALUE_32(x, S_LDT_LINKFREQ_FREQ, M_LDT_LINKFREQ_FREQ)

#define K_LDT_LINKFREQ_200MHZ		0
#define K_LDT_LINKFREQ_300MHZ		1
#define K_LDT_LINKFREQ_400MHZ		2
#define K_LDT_LINKFREQ_500MHZ		3
#define K_LDT_LINKFREQ_600MHZ		4
#define K_LDT_LINKFREQ_800MHZ		5
#define K_LDT_LINKFREQ_1000MHZ		6

/*
 * LDT SRI Command Register (Table 8-21).  Note that these constants
 * assume you've read the command and status register together
 * 32-bit read at offset 0x50
 */

#define M_LDT_SRICMD_SIPREADY		_SB_MAKEMASK1_32(16)
#define M_LDT_SRICMD_SYNCPTRCTL		_SB_MAKEMASK1_32(17)
#define M_LDT_SRICMD_REDUCESYNCZERO	_SB_MAKEMASK1_32(18)
#if SIBYTE_HDR_FEATURE_UP_TO(1250, PASS1)
#define M_LDT_SRICMD_DISSTARVATIONCNT	_SB_MAKEMASK1_32(19)	/* PASS1 */
#endif /* up to 1250 PASS1 */
#if SIBYTE_HDR_FEATURE(1250, PASS2) || SIBYTE_HDR_FEATURE(112x, PASS1)
#define M_LDT_SRICMD_DISMULTTXVLD	_SB_MAKEMASK1_32(19)
#define M_LDT_SRICMD_EXPENDIAN		_SB_MAKEMASK1_32(26)
#endif /* 1250 PASS2 || 112x PASS1 */


#define S_LDT_SRICMD_RXMARGIN		20
#define M_LDT_SRICMD_RXMARGIN		_SB_MAKEMASK_32(5, S_LDT_SRICMD_RXMARGIN)
#define V_LDT_SRICMD_RXMARGIN(x)	_SB_MAKEVALUE_32(x, S_LDT_SRICMD_RXMARGIN)
#define G_LDT_SRICMD_RXMARGIN(x)	_SB_GETVALUE_32(x, S_LDT_SRICMD_RXMARGIN, M_LDT_SRICMD_RXMARGIN)

#define M_LDT_SRICMD_LDTPLLCOMPAT	_SB_MAKEMASK1_32(25)

#define S_LDT_SRICMD_TXINITIALOFFSET	28
#define M_LDT_SRICMD_TXINITIALOFFSET	_SB_MAKEMASK_32(3, S_LDT_SRICMD_TXINITIALOFFSET)
#define V_LDT_SRICMD_TXINITIALOFFSET(x)	_SB_MAKEVALUE_32(x, S_LDT_SRICMD_TXINITIALOFFSET)
#define G_LDT_SRICMD_TXINITIALOFFSET(x)	_SB_GETVALUE_32(x, S_LDT_SRICMD_TXINITIALOFFSET, M_LDT_SRICMD_TXINITIALOFFSET)

#define M_LDT_SRICMD_LINKFREQDIRECT	_SB_MAKEMASK1_32(31)

/*
 * LDT Error control and status register (Table 8-22) (Table 8-23)
 */

#define M_LDT_ERRCTL_PROTFATAL_EN	_SB_MAKEMASK1_32(0)
#define M_LDT_ERRCTL_PROTNONFATAL_EN	_SB_MAKEMASK1_32(1)
#define M_LDT_ERRCTL_PROTSYNCFLOOD_EN	_SB_MAKEMASK1_32(2)
#define M_LDT_ERRCTL_OVFFATAL_EN	_SB_MAKEMASK1_32(3)
#define M_LDT_ERRCTL_OVFNONFATAL_EN	_SB_MAKEMASK1_32(4)
#define M_LDT_ERRCTL_OVFSYNCFLOOD_EN	_SB_MAKEMASK1_32(5)
#define M_LDT_ERRCTL_EOCNXAFATAL_EN	_SB_MAKEMASK1_32(6)
#define M_LDT_ERRCTL_EOCNXANONFATAL_EN	_SB_MAKEMASK1_32(7)
#define M_LDT_ERRCTL_EOCNXASYNCFLOOD_EN	_SB_MAKEMASK1_32(8)
#define M_LDT_ERRCTL_CRCFATAL_EN	_SB_MAKEMASK1_32(9)
#define M_LDT_ERRCTL_CRCNONFATAL_EN	_SB_MAKEMASK1_32(10)
#define M_LDT_ERRCTL_SERRFATAL_EN	_SB_MAKEMASK1_32(11)
#define M_LDT_ERRCTL_SRCTAGFATAL_EN	_SB_MAKEMASK1_32(12)
#define M_LDT_ERRCTL_SRCTAGNONFATAL_EN	_SB_MAKEMASK1_32(13)
#define M_LDT_ERRCTL_SRCTAGSYNCFLOOD_EN	_SB_MAKEMASK1_32(14)
#define M_LDT_ERRCTL_MAPNXAFATAL_EN	_SB_MAKEMASK1_32(15)
#define M_LDT_ERRCTL_MAPNXANONFATAL_EN	_SB_MAKEMASK1_32(16)
#define M_LDT_ERRCTL_MAPNXASYNCFLOOD_EN	_SB_MAKEMASK1_32(17)

#define M_LDT_ERRCTL_PROTOERR		_SB_MAKEMASK1_32(24)
#define M_LDT_ERRCTL_OVFERR		_SB_MAKEMASK1_32(25)
#define M_LDT_ERRCTL_EOCNXAERR		_SB_MAKEMASK1_32(26)
#define M_LDT_ERRCTL_SRCTAGERR		_SB_MAKEMASK1_32(27)
#define M_LDT_ERRCTL_MAPNXAERR		_SB_MAKEMASK1_32(28)

/*
 * SRI Control register (Table 8-24, 8-25)  Offset 0x6C
 */

#define S_LDT_SRICTRL_NEEDRESP		0
#define M_LDT_SRICTRL_NEEDRESP		_SB_MAKEMASK_32(2, S_LDT_SRICTRL_NEEDRESP)
#define V_LDT_SRICTRL_NEEDRESP(x)	_SB_MAKEVALUE_32(x, S_LDT_SRICTRL_NEEDRESP)
#define G_LDT_SRICTRL_NEEDRESP(x)	_SB_GETVALUE_32(x, S_LDT_SRICTRL_NEEDRESP, M_LDT_SRICTRL_NEEDRESP)

#define S_LDT_SRICTRL_NEEDNPREQ		2
#define M_LDT_SRICTRL_NEEDNPREQ		_SB_MAKEMASK_32(2, S_LDT_SRICTRL_NEEDNPREQ)
#define V_LDT_SRICTRL_NEEDNPREQ(x)	_SB_MAKEVALUE_32(x, S_LDT_SRICTRL_NEEDNPREQ)
#define G_LDT_SRICTRL_NEEDNPREQ(x)	_SB_GETVALUE_32(x, S_LDT_SRICTRL_NEEDNPREQ, M_LDT_SRICTRL_NEEDNPREQ)

#define S_LDT_SRICTRL_NEEDPREQ		4
#define M_LDT_SRICTRL_NEEDPREQ		_SB_MAKEMASK_32(2, S_LDT_SRICTRL_NEEDPREQ)
#define V_LDT_SRICTRL_NEEDPREQ(x)	_SB_MAKEVALUE_32(x, S_LDT_SRICTRL_NEEDPREQ)
#define G_LDT_SRICTRL_NEEDPREQ(x)	_SB_GETVALUE_32(x, S_LDT_SRICTRL_NEEDPREQ, M_LDT_SRICTRL_NEEDPREQ)

#define S_LDT_SRICTRL_WANTRESP		8
#define M_LDT_SRICTRL_WANTRESP		_SB_MAKEMASK_32(2, S_LDT_SRICTRL_WANTRESP)
#define V_LDT_SRICTRL_WANTRESP(x)	_SB_MAKEVALUE_32(x, S_LDT_SRICTRL_WANTRESP)
#define G_LDT_SRICTRL_WANTRESP(x)	_SB_GETVALUE_32(x, S_LDT_SRICTRL_WANTRESP, M_LDT_SRICTRL_WANTRESP)

#define S_LDT_SRICTRL_WANTNPREQ		10
#define M_LDT_SRICTRL_WANTNPREQ		_SB_MAKEMASK_32(2, S_LDT_SRICTRL_WANTNPREQ)
#define V_LDT_SRICTRL_WANTNPREQ(x)	_SB_MAKEVALUE_32(x, S_LDT_SRICTRL_WANTNPREQ)
#define G_LDT_SRICTRL_WANTNPREQ(x)	_SB_GETVALUE_32(x, S_LDT_SRICTRL_WANTNPREQ, M_LDT_SRICTRL_WANTNPREQ)

#define S_LDT_SRICTRL_WANTPREQ		12
#define M_LDT_SRICTRL_WANTPREQ		_SB_MAKEMASK_32(2, S_LDT_SRICTRL_WANTPREQ)
#define V_LDT_SRICTRL_WANTPREQ(x)	_SB_MAKEVALUE_32(x, S_LDT_SRICTRL_WANTPREQ)
#define G_LDT_SRICTRL_WANTPREQ(x)	_SB_GETVALUE_32(x, S_LDT_SRICTRL_WANTPREQ, M_LDT_SRICTRL_WANTPREQ)

#define S_LDT_SRICTRL_BUFRELSPACE	16
#define M_LDT_SRICTRL_BUFRELSPACE	_SB_MAKEMASK_32(4, S_LDT_SRICTRL_BUFRELSPACE)
#define V_LDT_SRICTRL_BUFRELSPACE(x)	_SB_MAKEVALUE_32(x, S_LDT_SRICTRL_BUFRELSPACE)
#define G_LDT_SRICTRL_BUFRELSPACE(x)	_SB_GETVALUE_32(x, S_LDT_SRICTRL_BUFRELSPACE, M_LDT_SRICTRL_BUFRELSPACE)

/*
 * LDT SRI Transmit Buffer Count register (Table 8-26)
 */

#define S_LDT_TXBUFCNT_PCMD		0
#define M_LDT_TXBUFCNT_PCMD		_SB_MAKEMASK_32(4, S_LDT_TXBUFCNT_PCMD)
#define V_LDT_TXBUFCNT_PCMD(x)		_SB_MAKEVALUE_32(x, S_LDT_TXBUFCNT_PCMD)
#define G_LDT_TXBUFCNT_PCMD(x)		_SB_GETVALUE_32(x, S_LDT_TXBUFCNT_PCMD, M_LDT_TXBUFCNT_PCMD)

#define S_LDT_TXBUFCNT_PDATA		4
#define M_LDT_TXBUFCNT_PDATA		_SB_MAKEMASK_32(4, S_LDT_TXBUFCNT_PDATA)
#define V_LDT_TXBUFCNT_PDATA(x)		_SB_MAKEVALUE_32(x, S_LDT_TXBUFCNT_PDATA)
#define G_LDT_TXBUFCNT_PDATA(x)		_SB_GETVALUE_32(x, S_LDT_TXBUFCNT_PDATA, M_LDT_TXBUFCNT_PDATA)

#define S_LDT_TXBUFCNT_NPCMD		8
#define M_LDT_TXBUFCNT_NPCMD		_SB_MAKEMASK_32(4, S_LDT_TXBUFCNT_NPCMD)
#define V_LDT_TXBUFCNT_NPCMD(x)		_SB_MAKEVALUE_32(x, S_LDT_TXBUFCNT_NPCMD)
#define G_LDT_TXBUFCNT_NPCMD(x)		_SB_GETVALUE_32(x, S_LDT_TXBUFCNT_NPCMD, M_LDT_TXBUFCNT_NPCMD)

#define S_LDT_TXBUFCNT_NPDATA		12
#define M_LDT_TXBUFCNT_NPDATA		_SB_MAKEMASK_32(4, S_LDT_TXBUFCNT_NPDATA)
#define V_LDT_TXBUFCNT_NPDATA(x)	_SB_MAKEVALUE_32(x, S_LDT_TXBUFCNT_NPDATA)
#define G_LDT_TXBUFCNT_NPDATA(x)	_SB_GETVALUE_32(x, S_LDT_TXBUFCNT_NPDATA, M_LDT_TXBUFCNT_NPDATA)

#define S_LDT_TXBUFCNT_RCMD		16
#define M_LDT_TXBUFCNT_RCMD		_SB_MAKEMASK_32(4, S_LDT_TXBUFCNT_RCMD)
#define V_LDT_TXBUFCNT_RCMD(x)		_SB_MAKEVALUE_32(x, S_LDT_TXBUFCNT_RCMD)
#define G_LDT_TXBUFCNT_RCMD(x)		_SB_GETVALUE_32(x, S_LDT_TXBUFCNT_RCMD, M_LDT_TXBUFCNT_RCMD)

#define S_LDT_TXBUFCNT_RDATA		20
#define M_LDT_TXBUFCNT_RDATA		_SB_MAKEMASK_32(4, S_LDT_TXBUFCNT_RDATA)
#define V_LDT_TXBUFCNT_RDATA(x)		_SB_MAKEVALUE_32(x, S_LDT_TXBUFCNT_RDATA)
#define G_LDT_TXBUFCNT_RDATA(x)		_SB_GETVALUE_32(x, S_LDT_TXBUFCNT_RDATA, M_LDT_TXBUFCNT_RDATA)

#if SIBYTE_HDR_FEATURE(1250, PASS2) || SIBYTE_HDR_FEATURE(112x, PASS1)
/*
 * Additional Status Register
 */

#define S_LDT_ADDSTATUS_TGTDONE		0
#define M_LDT_ADDSTATUS_TGTDONE		_SB_MAKEMASK_32(8, S_LDT_ADDSTATUS_TGTDONE)
#define V_LDT_ADDSTATUS_TGTDONE(x)	_SB_MAKEVALUE_32(x, S_LDT_ADDSTATUS_TGTDONE)
#define G_LDT_ADDSTATUS_TGTDONE(x)	_SB_GETVALUE_32(x, S_LDT_ADDSTATUS_TGTDONE, M_LDT_ADDSTATUS_TGTDONE)
#endif /* 1250 PASS2 || 112x PASS1 */

#endif

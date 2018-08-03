#include "linux/autoconf.h"
#ifndef __ASM_SH_HITACHI_SE_H
#define __ASM_SH_HITACHI_SE_H

/*
 * linux/include/asm-sh/hitachi_se.h
 *
 * Copyright (C) 2000  Kazumoto Kojima
 *
 * Hitachi SolutionEngine support
 */

/* Box specific addresses.  */

#define PA_ROM		0x00000000	/* EPROM */
#define PA_ROM_SIZE	0x00400000	/* EPROM size 4M byte */
#define PA_FROM		0x01000000	/* EPROM */
#define PA_FROM_SIZE	0x00400000	/* EPROM size 4M byte */
#define PA_EXT1		0x04000000
#define PA_EXT1_SIZE	0x04000000
#define PA_EXT2		0x08000000
#define PA_EXT2_SIZE	0x04000000
#define PA_SDRAM	0x0c000000
#define PA_SDRAM_SIZE	0x04000000

#define PA_EXT4		0x12000000
#define PA_EXT4_SIZE	0x02000000
#define PA_EXT5		0x14000000
#define PA_EXT5_SIZE	0x04000000
#define PA_PCIC		0x18000000	/* MR-SHPC-01 PCMCIA */

#define PA_83902	0xb0000000	/* DP83902A */
#define PA_83902_IF	0xb0040000	/* DP83902A remote io port */
#define PA_83902_RST	0xb0080000	/* DP83902A reset port */

#define PA_SUPERIO	0xb0400000	/* SMC37C935A super io chip */
#define PA_DIPSW0	0xb0800000	/* Dip switch 5,6 */
#define PA_DIPSW1	0xb0800002	/* Dip switch 7,8 */
#define PA_LED		0xb0c00000	/* LED */
#define PA_BCR		0xb1400000	/* FPGA */

#define PA_MRSHPC	0xb83fffe0	/* MR-SHPC-01 PCMCIA controler */
#define PA_MRSHPC_MW1	0xb8400000	/* MR-SHPC-01 memory window base */
#define PA_MRSHPC_MW2	0xb8500000	/* MR-SHPC-01 attribute window base */
#define PA_MRSHPC_IO	0xb8600000	/* MR-SHPC-01 I/O window base */
#define MRSHPC_OPTION   (PA_MRSHPC + 6)
#define MRSHPC_CSR      (PA_MRSHPC + 8)
#define MRSHPC_ISR      (PA_MRSHPC + 10)
#define MRSHPC_ICR      (PA_MRSHPC + 12)
#define MRSHPC_CPWCR    (PA_MRSHPC + 14)
#define MRSHPC_MW0CR1   (PA_MRSHPC + 16)
#define MRSHPC_MW1CR1   (PA_MRSHPC + 18)
#define MRSHPC_IOWCR1   (PA_MRSHPC + 20)
#define MRSHPC_MW0CR2   (PA_MRSHPC + 22)
#define MRSHPC_MW1CR2   (PA_MRSHPC + 24)
#define MRSHPC_IOWCR2   (PA_MRSHPC + 26)
#define MRSHPC_CDCR     (PA_MRSHPC + 28)
#define MRSHPC_PCIC_INFO (PA_MRSHPC + 30)

#define BCR_ILCRA	(PA_BCR + 0)
#define BCR_ILCRB	(PA_BCR + 2)
#define BCR_ILCRC	(PA_BCR + 4)
#define BCR_ILCRD	(PA_BCR + 6)
#define BCR_ILCRE	(PA_BCR + 8)
#define BCR_ILCRF	(PA_BCR + 10)
#define BCR_ILCRG	(PA_BCR + 12)

#define IRQ_STNIC	10

#endif  /* __ASM_SH_HITACHI_SE_H */

#include "linux/autoconf.h"
/*
 * linux/include/asm-mips/tx4938/rbtx4938.h
 * Definitions for TX4937/TX4938
 *
 * 2003-2005 (c) MontaVista Software, Inc. This file is licensed under the
 * terms of the GNU General Public License version 2. This program is
 * licensed "as is" without any warranty of any kind, whether express
 * or implied.
 *
 * Support for TX4938 in 2.6 - Manish Lachwani (mlachwani@mvista.com)
 */
#ifndef __ASM_TX_BOARDS_RBTX4938_H
#define __ASM_TX_BOARDS_RBTX4938_H

#include <asm/addrspace.h>
#include <asm/tx4938/tx4938.h>

/* CS */
#define RBTX4938_CE0	0x1c000000	/* 64M */
#define RBTX4938_CE2	0x17f00000	/* 1M */

/* Address map */
#define RBTX4938_FPGA_REG_ADDR	(KSEG1 + RBTX4938_CE2 + 0x00000000)
#define RBTX4938_FPGA_REV_ADDR	(KSEG1 + RBTX4938_CE2 + 0x00000002)
#define RBTX4938_CONFIG1_ADDR	(KSEG1 + RBTX4938_CE2 + 0x00000004)
#define RBTX4938_CONFIG2_ADDR	(KSEG1 + RBTX4938_CE2 + 0x00000006)
#define RBTX4938_CONFIG3_ADDR	(KSEG1 + RBTX4938_CE2 + 0x00000008)
#define RBTX4938_LED_ADDR	(KSEG1 + RBTX4938_CE2 + 0x00001000)
#define RBTX4938_DIPSW_ADDR	(KSEG1 + RBTX4938_CE2 + 0x00001002)
#define RBTX4938_BDIPSW_ADDR	(KSEG1 + RBTX4938_CE2 + 0x00001004)
#define RBTX4938_IMASK_ADDR	(KSEG1 + RBTX4938_CE2 + 0x00002000)
#define RBTX4938_IMASK2_ADDR	(KSEG1 + RBTX4938_CE2 + 0x00002002)
#define RBTX4938_INTPOL_ADDR	(KSEG1 + RBTX4938_CE2 + 0x00002004)
#define RBTX4938_ISTAT_ADDR	(KSEG1 + RBTX4938_CE2 + 0x00002006)
#define RBTX4938_ISTAT2_ADDR	(KSEG1 + RBTX4938_CE2 + 0x00002008)
#define RBTX4938_IMSTAT_ADDR	(KSEG1 + RBTX4938_CE2 + 0x0000200a)
#define RBTX4938_IMSTAT2_ADDR	(KSEG1 + RBTX4938_CE2 + 0x0000200c)
#define RBTX4938_SOFTINT_ADDR	(KSEG1 + RBTX4938_CE2 + 0x00003000)
#define RBTX4938_PIOSEL_ADDR	(KSEG1 + RBTX4938_CE2 + 0x00005000)
#define RBTX4938_SPICS_ADDR	(KSEG1 + RBTX4938_CE2 + 0x00005002)
#define RBTX4938_SFPWR_ADDR	(KSEG1 + RBTX4938_CE2 + 0x00005008)
#define RBTX4938_SFVOL_ADDR	(KSEG1 + RBTX4938_CE2 + 0x0000500a)
#define RBTX4938_SOFTRESET_ADDR	(KSEG1 + RBTX4938_CE2 + 0x00007000)
#define RBTX4938_SOFTRESETLOCK_ADDR	(KSEG1 + RBTX4938_CE2 + 0x00007002)
#define RBTX4938_PCIRESET_ADDR	(KSEG1 + RBTX4938_CE2 + 0x00007004)
#define RBTX4938_ETHER_BASE	(KSEG1 + RBTX4938_CE2 + 0x00020000)

/* Ethernet port address (Jumperless Mode (W12:Open)) */
#define RBTX4938_ETHER_ADDR	(RBTX4938_ETHER_BASE + 0x280)

/* bits for ISTAT/IMASK/IMSTAT */
#define RBTX4938_INTB_PCID	0
#define RBTX4938_INTB_PCIC	1
#define RBTX4938_INTB_PCIB	2
#define RBTX4938_INTB_PCIA	3
#define RBTX4938_INTB_RTC	4
#define RBTX4938_INTB_ATA	5
#define RBTX4938_INTB_MODEM	6
#define RBTX4938_INTB_SWINT	7
#define RBTX4938_INTF_PCID	(1 << RBTX4938_INTB_PCID)
#define RBTX4938_INTF_PCIC	(1 << RBTX4938_INTB_PCIC)
#define RBTX4938_INTF_PCIB	(1 << RBTX4938_INTB_PCIB)
#define RBTX4938_INTF_PCIA	(1 << RBTX4938_INTB_PCIA)
#define RBTX4938_INTF_RTC	(1 << RBTX4938_INTB_RTC)
#define RBTX4938_INTF_ATA	(1 << RBTX4938_INTB_ATA)
#define RBTX4938_INTF_MODEM	(1 << RBTX4938_INTB_MODEM)
#define RBTX4938_INTF_SWINT	(1 << RBTX4938_INTB_SWINT)

#define rbtx4938_fpga_rev_ptr	\
	((volatile unsigned char *)RBTX4938_FPGA_REV_ADDR)
#define rbtx4938_led_ptr	\
	((volatile unsigned char *)RBTX4938_LED_ADDR)
#define rbtx4938_dipsw_ptr	\
	((volatile unsigned char *)RBTX4938_DIPSW_ADDR)
#define rbtx4938_bdipsw_ptr	\
	((volatile unsigned char *)RBTX4938_BDIPSW_ADDR)
#define rbtx4938_imask_ptr	\
	((volatile unsigned char *)RBTX4938_IMASK_ADDR)
#define rbtx4938_imask2_ptr	\
	((volatile unsigned char *)RBTX4938_IMASK2_ADDR)
#define rbtx4938_intpol_ptr	\
	((volatile unsigned char *)RBTX4938_INTPOL_ADDR)
#define rbtx4938_istat_ptr	\
	((volatile unsigned char *)RBTX4938_ISTAT_ADDR)
#define rbtx4938_istat2_ptr	\
	((volatile unsigned char *)RBTX4938_ISTAT2_ADDR)
#define rbtx4938_imstat_ptr	\
	((volatile unsigned char *)RBTX4938_IMSTAT_ADDR)
#define rbtx4938_imstat2_ptr	\
	((volatile unsigned char *)RBTX4938_IMSTAT2_ADDR)
#define rbtx4938_softint_ptr	\
	((volatile unsigned char *)RBTX4938_SOFTINT_ADDR)
#define rbtx4938_piosel_ptr	\
	((volatile unsigned char *)RBTX4938_PIOSEL_ADDR)
#define rbtx4938_spics_ptr	\
	((volatile unsigned char *)RBTX4938_SPICS_ADDR)
#define rbtx4938_sfpwr_ptr	\
	((volatile unsigned char *)RBTX4938_SFPWR_ADDR)
#define rbtx4938_sfvol_ptr	\
	((volatile unsigned char *)RBTX4938_SFVOL_ADDR)
#define rbtx4938_softreset_ptr	\
	((volatile unsigned char *)RBTX4938_SOFTRESET_ADDR)
#define rbtx4938_softresetlock_ptr	\
	((volatile unsigned char *)RBTX4938_SOFTRESETLOCK_ADDR)
#define rbtx4938_pcireset_ptr	\
	((volatile unsigned char *)RBTX4938_PCIRESET_ADDR)

/* SPI */
#define RBTX4938_SEEPROM1_CHIPID	0
#define RBTX4938_SEEPROM2_CHIPID	1
#define RBTX4938_SEEPROM3_CHIPID	2
#define RBTX4938_SRTC_CHIPID	3

/*
 * IRQ mappings
 */

#define RBTX4938_SOFT_INT0	0	/* not used */
#define RBTX4938_SOFT_INT1	1	/* not used */
#define RBTX4938_IRC_INT	2
#define RBTX4938_TIMER_INT	7

/* These are the virtual IRQ numbers, we divide all IRQ's into
 * 'spaces', the 'space' determines where and how to enable/disable
 * that particular IRQ on an RBTX4938 machine.  Add new 'spaces' as new
 * IRQ hardware is supported.
 */
#define RBTX4938_NR_IRQ_LOCAL	8
#define RBTX4938_NR_IRQ_IRC	32	/* On-Chip IRC */
#define RBTX4938_NR_IRQ_IOC	8

#define MI8259_IRQ_ISA_RAW_BEG   0	/* optional backplane i8259 */
#define MI8259_IRQ_ISA_RAW_END  15
#define TX4938_IRQ_CP0_RAW_BEG   0	/* tx4938 cpu built-in cp0 */
#define TX4938_IRQ_CP0_RAW_END   7
#define TX4938_IRQ_PIC_RAW_BEG   0	/* tx4938 cpu build-in pic */
#define TX4938_IRQ_PIC_RAW_END  31

#define MI8259_IRQ_ISA_BEG                          MI8259_IRQ_ISA_RAW_BEG	/*  0 */
#define MI8259_IRQ_ISA_END                          MI8259_IRQ_ISA_RAW_END	/* 15 */

#define TX4938_IRQ_CP0_BEG  ((MI8259_IRQ_ISA_END+1)+TX4938_IRQ_CP0_RAW_BEG)	/* 16 */
#define TX4938_IRQ_CP0_END  ((MI8259_IRQ_ISA_END+1)+TX4938_IRQ_CP0_RAW_END)	/* 23 */

#define TX4938_IRQ_PIC_BEG  ((TX4938_IRQ_CP0_END+1)+TX4938_IRQ_PIC_RAW_BEG)	/* 24 */
#define TX4938_IRQ_PIC_END  ((TX4938_IRQ_CP0_END+1)+TX4938_IRQ_PIC_RAW_END)	/* 55 */
#define TX4938_IRQ_NEST_EXT_ON_PIC  (TX4938_IRQ_PIC_BEG+2)
#define TX4938_IRQ_NEST_PIC_ON_CP0  (TX4938_IRQ_CP0_BEG+2)
#define TX4938_IRQ_USER0            (TX4938_IRQ_CP0_BEG+0)
#define TX4938_IRQ_USER1            (TX4938_IRQ_CP0_BEG+1)
#define TX4938_IRQ_CPU_TIMER        (TX4938_IRQ_CP0_BEG+7)

#define TOSHIBA_RBTX4938_IRQ_IOC_RAW_BEG   0
#define TOSHIBA_RBTX4938_IRQ_IOC_RAW_END   7

#define TOSHIBA_RBTX4938_IRQ_IOC_BEG  ((TX4938_IRQ_PIC_END+1)+TOSHIBA_RBTX4938_IRQ_IOC_RAW_BEG) /* 56 */
#define TOSHIBA_RBTX4938_IRQ_IOC_END  ((TX4938_IRQ_PIC_END+1)+TOSHIBA_RBTX4938_IRQ_IOC_RAW_END) /* 63 */
#define RBTX4938_IRQ_LOCAL	TX4938_IRQ_CP0_BEG
#define RBTX4938_IRQ_IRC	(RBTX4938_IRQ_LOCAL + RBTX4938_NR_IRQ_LOCAL)
#define RBTX4938_IRQ_IOC	(RBTX4938_IRQ_IRC + RBTX4938_NR_IRQ_IRC)
#define RBTX4938_IRQ_END	(RBTX4938_IRQ_IOC + RBTX4938_NR_IRQ_IOC)

#define RBTX4938_IRQ_LOCAL_SOFT0	(RBTX4938_IRQ_LOCAL + RBTX4938_SOFT_INT0)
#define RBTX4938_IRQ_LOCAL_SOFT1	(RBTX4938_IRQ_LOCAL + RBTX4938_SOFT_INT1)
#define RBTX4938_IRQ_LOCAL_IRC	(RBTX4938_IRQ_LOCAL + RBTX4938_IRC_INT)
#define RBTX4938_IRQ_LOCAL_TIMER	(RBTX4938_IRQ_LOCAL + RBTX4938_TIMER_INT)
#define RBTX4938_IRQ_IRC_ECCERR	(RBTX4938_IRQ_IRC + TX4938_IR_ECCERR)
#define RBTX4938_IRQ_IRC_WTOERR	(RBTX4938_IRQ_IRC + TX4938_IR_WTOERR)
#define RBTX4938_IRQ_IRC_INT(n)	(RBTX4938_IRQ_IRC + TX4938_IR_INT(n))
#define RBTX4938_IRQ_IRC_SIO(n)	(RBTX4938_IRQ_IRC + TX4938_IR_SIO(n))
#define RBTX4938_IRQ_IRC_DMA(ch,n)	(RBTX4938_IRQ_IRC + TX4938_IR_DMA(ch,n))
#define RBTX4938_IRQ_IRC_PIO	(RBTX4938_IRQ_IRC + TX4938_IR_PIO)
#define RBTX4938_IRQ_IRC_PDMAC	(RBTX4938_IRQ_IRC + TX4938_IR_PDMAC)
#define RBTX4938_IRQ_IRC_PCIC	(RBTX4938_IRQ_IRC + TX4938_IR_PCIC)
#define RBTX4938_IRQ_IRC_TMR(n)	(RBTX4938_IRQ_IRC + TX4938_IR_TMR(n))
#define RBTX4938_IRQ_IRC_NDFMC	(RBTX4938_IRQ_IRC + TX4938_IR_NDFMC)
#define RBTX4938_IRQ_IRC_PCIERR	(RBTX4938_IRQ_IRC + TX4938_IR_PCIERR)
#define RBTX4938_IRQ_IRC_PCIPME	(RBTX4938_IRQ_IRC + TX4938_IR_PCIPME)
#define RBTX4938_IRQ_IRC_ACLC	(RBTX4938_IRQ_IRC + TX4938_IR_ACLC)
#define RBTX4938_IRQ_IRC_ACLCPME	(RBTX4938_IRQ_IRC + TX4938_IR_ACLCPME)
#define RBTX4938_IRQ_IRC_PCIC1	(RBTX4938_IRQ_IRC + TX4938_IR_PCIC1)
#define RBTX4938_IRQ_IRC_SPI	(RBTX4938_IRQ_IRC + TX4938_IR_SPI)
#define RBTX4938_IRQ_IOC_PCID	(RBTX4938_IRQ_IOC + RBTX4938_INTB_PCID)
#define RBTX4938_IRQ_IOC_PCIC	(RBTX4938_IRQ_IOC + RBTX4938_INTB_PCIC)
#define RBTX4938_IRQ_IOC_PCIB	(RBTX4938_IRQ_IOC + RBTX4938_INTB_PCIB)
#define RBTX4938_IRQ_IOC_PCIA	(RBTX4938_IRQ_IOC + RBTX4938_INTB_PCIA)
#define RBTX4938_IRQ_IOC_RTC	(RBTX4938_IRQ_IOC + RBTX4938_INTB_RTC)
#define RBTX4938_IRQ_IOC_ATA	(RBTX4938_IRQ_IOC + RBTX4938_INTB_ATA)
#define RBTX4938_IRQ_IOC_MODEM	(RBTX4938_IRQ_IOC + RBTX4938_INTB_MODEM)
#define RBTX4938_IRQ_IOC_SWINT	(RBTX4938_IRQ_IOC + RBTX4938_INTB_SWINT)


/* IOC (PCI, etc) */
#define RBTX4938_IRQ_IOCINT	(TX4938_IRQ_NEST_EXT_ON_PIC)
/* Onboard 10M Ether */
#define RBTX4938_IRQ_ETHER	(TX4938_IRQ_NEST_EXT_ON_PIC + 1)

#define RBTX4938_RTL_8019_BASE (RBTX4938_ETHER_ADDR - mips_io_port_base)
#define RBTX4938_RTL_8019_IRQ  (RBTX4938_IRQ_ETHER)

/* IRCR : Int. Control */
#define TX4938_IRCR_LOW  0x00000000
#define TX4938_IRCR_HIGH 0x00000001
#define TX4938_IRCR_DOWN 0x00000002
#define TX4938_IRCR_UP   0x00000003

#endif /* __ASM_TX_BOARDS_RBTX4938_H */

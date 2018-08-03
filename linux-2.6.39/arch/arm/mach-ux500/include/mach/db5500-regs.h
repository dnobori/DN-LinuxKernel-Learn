#include "linux/generated/autoconf.h"
/*
 * Copyright (C) ST-Ericsson SA 2010
 *
 * License terms: GNU General Public License (GPL) version 2
 */

#ifndef __MACH_DB5500_REGS_H
#define __MACH_DB5500_REGS_H

#define U5500_PER1_BASE		0xA0020000
#define U5500_PER2_BASE		0xA0010000
#define U5500_PER3_BASE		0x80140000
#define U5500_PER4_BASE		0x80150000
#define U5500_PER5_BASE		0x80100000
#define U5500_PER6_BASE		0x80120000

#define U5500_GIC_DIST_BASE	0xA0411000
#define U5500_GIC_CPU_BASE	0xA0410100
#define U5500_DMA_BASE		0x90030000
#define U5500_MCDE_BASE		0xA0400000
#define U5500_MODEM_BASE	0xB0000000
#define U5500_L2CC_BASE		0xA0412000
#define U5500_SCU_BASE		0xA0410000
#define U5500_DSI1_BASE		0xA0401000
#define U5500_DSI2_BASE		0xA0402000
#define U5500_SIA_BASE		0xA0100000
#define U5500_SVA_BASE		0x80200000
#define U5500_HSEM_BASE		0xA0000000
#define U5500_NAND0_BASE	0x60000000
#define U5500_NAND1_BASE	0x70000000
#define U5500_TWD_BASE		0xa0410600
#define U5500_B2R2_BASE		0xa0200000

#define U5500_FSMC_BASE		(U5500_PER1_BASE + 0x0000)
#define U5500_SDI0_BASE		(U5500_PER1_BASE + 0x1000)
#define U5500_SDI2_BASE		(U5500_PER1_BASE + 0x2000)
#define U5500_UART0_BASE	(U5500_PER1_BASE + 0x3000)
#define U5500_I2C1_BASE		(U5500_PER1_BASE + 0x4000)
#define U5500_MSP0_BASE		(U5500_PER1_BASE + 0x5000)
#define U5500_GPIO0_BASE	(U5500_PER1_BASE + 0xE000)
#define U5500_CLKRST1_BASE	(U5500_PER1_BASE + 0xF000)

#define U5500_USBOTG_BASE	(U5500_PER2_BASE + 0x0000)
#define U5500_GPIO1_BASE	(U5500_PER2_BASE + 0xE000)
#define U5500_CLKRST2_BASE	(U5500_PER2_BASE + 0xF000)

#define U5500_KEYPAD_BASE	(U5500_PER3_BASE + 0x0000)
#define U5500_PWM_BASE		(U5500_PER3_BASE + 0x1000)
#define U5500_GPIO3_BASE	(U5500_PER3_BASE + 0xE000)
#define U5500_CLKRST3_BASE	(U5500_PER3_BASE + 0xF000)

#define U5500_BACKUPRAM0_BASE	(U5500_PER4_BASE + 0x0000)
#define U5500_BACKUPRAM1_BASE	(U5500_PER4_BASE + 0x1000)
#define U5500_RTT0_BASE		(U5500_PER4_BASE + 0x2000)
#define U5500_RTT1_BASE		(U5500_PER4_BASE + 0x3000)
#define U5500_RTC_BASE		(U5500_PER4_BASE + 0x4000)
#define U5500_SCR_BASE		(U5500_PER4_BASE + 0x5000)
#define U5500_DMC_BASE		(U5500_PER4_BASE + 0x6000)
#define U5500_PRCMU_BASE	(U5500_PER4_BASE + 0x7000)
#define U5500_MSP1_BASE		(U5500_PER4_BASE + 0x9000)
#define U5500_GPIO2_BASE	(U5500_PER4_BASE + 0xA000)
#define U5500_CDETECT_BASE	(U5500_PER4_BASE + 0xF000)

#define U5500_SPI0_BASE		(U5500_PER5_BASE + 0x0000)
#define U5500_SPI1_BASE		(U5500_PER5_BASE + 0x1000)
#define U5500_SPI2_BASE		(U5500_PER5_BASE + 0x2000)
#define U5500_SPI3_BASE		(U5500_PER5_BASE + 0x3000)
#define U5500_UART1_BASE	(U5500_PER5_BASE + 0x4000)
#define U5500_UART2_BASE	(U5500_PER5_BASE + 0x5000)
#define U5500_UART3_BASE	(U5500_PER5_BASE + 0x6000)
#define U5500_SDI1_BASE		(U5500_PER5_BASE + 0x7000)
#define U5500_SDI3_BASE		(U5500_PER5_BASE + 0x8000)
#define U5500_SDI4_BASE		(U5500_PER5_BASE + 0x9000)
#define U5500_I2C2_BASE		(U5500_PER5_BASE + 0xA000)
#define U5500_I2C3_BASE		(U5500_PER5_BASE + 0xB000)
#define U5500_MSP2_BASE		(U5500_PER5_BASE + 0xC000)
#define U5500_IRDA_BASE		(U5500_PER5_BASE + 0xD000)
#define U5500_IRRC_BASE		(U5500_PER5_BASE + 0x10000)
#define U5500_GPIO4_BASE	(U5500_PER5_BASE + 0x1E000)
#define U5500_CLKRST5_BASE	(U5500_PER5_BASE + 0x1F000)

#define U5500_RNG_BASE		(U5500_PER6_BASE + 0x0000)
#define U5500_HASH0_BASE	(U5500_PER6_BASE + 0x1000)
#define U5500_HASH1_BASE	(U5500_PER6_BASE + 0x2000)
#define U5500_PKA_BASE		(U5500_PER6_BASE + 0x4000)
#define U5500_PKAM_BASE		(U5500_PER6_BASE + 0x5000)
#define U5500_MTU0_BASE		(U5500_PER6_BASE + 0x6000)
#define U5500_MTU1_BASE		(U5500_PER6_BASE + 0x7000)
#define U5500_CR_BASE		(U5500_PER6_BASE + 0x8000)
#define U5500_CRYP0_BASE	(U5500_PER6_BASE + 0xA000)
#define U5500_CRYP1_BASE	(U5500_PER6_BASE + 0xB000)
#define U5500_CLKRST6_BASE	(U5500_PER6_BASE + 0xF000)

#define U5500_GPIOBANK0_BASE	U5500_GPIO0_BASE
#define U5500_GPIOBANK1_BASE	(U5500_GPIO0_BASE + 0x80)
#define U5500_GPIOBANK2_BASE	U5500_GPIO1_BASE
#define U5500_GPIOBANK3_BASE	U5500_GPIO2_BASE
#define U5500_GPIOBANK4_BASE	U5500_GPIO3_BASE
#define U5500_GPIOBANK5_BASE	U5500_GPIO4_BASE
#define U5500_GPIOBANK6_BASE	(U5500_GPIO4_BASE + 0x80)
#define U5500_GPIOBANK7_BASE	(U5500_GPIO4_BASE + 0x100)

#define U5500_MBOX_BASE		(U5500_MODEM_BASE + 0xFFD1000)
#define U5500_MBOX0_PEER_START	(U5500_MBOX_BASE + 0x40)
#define U5500_MBOX0_PEER_END	(U5500_MBOX_BASE + 0x5F)
#define U5500_MBOX0_LOCAL_START	(U5500_MBOX_BASE + 0x60)
#define U5500_MBOX0_LOCAL_END	(U5500_MBOX_BASE + 0x7F)
#define U5500_MBOX1_PEER_START	(U5500_MBOX_BASE + 0x80)
#define U5500_MBOX1_PEER_END	(U5500_MBOX_BASE + 0x9F)
#define U5500_MBOX1_LOCAL_START	(U5500_MBOX_BASE + 0xA0)
#define U5500_MBOX1_LOCAL_END	(U5500_MBOX_BASE + 0xBF)
#define U5500_MBOX2_PEER_START	(U5500_MBOX_BASE + 0x00)
#define U5500_MBOX2_PEER_END	(U5500_MBOX_BASE + 0x1F)
#define U5500_MBOX2_LOCAL_START	(U5500_MBOX_BASE + 0x20)
#define U5500_MBOX2_LOCAL_END	(U5500_MBOX_BASE + 0x3F)

#define U5500_ESRAM_BASE		0x40000000
#define U5500_ESRAM_DMA_LCPA_OFFSET	0x10000
#define U5500_DMA_LCPA_BASE    (U5500_ESRAM_BASE + U5500_ESRAM_DMA_LCPA_OFFSET)

#endif

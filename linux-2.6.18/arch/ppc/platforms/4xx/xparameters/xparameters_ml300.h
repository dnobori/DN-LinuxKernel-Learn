#include "linux/autoconf.h"
/*******************************************************************
*
*     Author: Xilinx, Inc.
*
*
*     This program is free software; you can redistribute it and/or modify it
*     under the terms of the GNU General Public License as published by the
*     Free Software Foundation; either version 2 of the License, or (at your
*     option) any later version.
*
*
*     XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS" AS A
*     COURTESY TO YOU. BY PROVIDING THIS DESIGN, CODE, OR INFORMATION AS
*     ONE POSSIBLE IMPLEMENTATION OF THIS FEATURE, APPLICATION OR STANDARD,
*     XILINX IS MAKING NO REPRESENTATION THAT THIS IMPLEMENTATION IS FREE
*     FROM ANY CLAIMS OF INFRINGEMENT, AND YOU ARE RESPONSIBLE FOR OBTAINING
*     ANY THIRD PARTY RIGHTS YOU MAY REQUIRE FOR YOUR IMPLEMENTATION.
*     XILINX EXPRESSLY DISCLAIMS ANY WARRANTY WHATSOEVER WITH RESPECT TO
*     THE ADEQUACY OF THE IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO ANY
*     WARRANTIES OR REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE FROM
*     CLAIMS OF INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY AND
*     FITNESS FOR A PARTICULAR PURPOSE.
*
*
*     Xilinx hardware products are not intended for use in life support
*     appliances, devices, or systems. Use in such applications is
*     expressly prohibited.
*
*
*     (c) Copyright 2002-2004 Xilinx Inc.
*     All rights reserved.
*
*
*     You should have received a copy of the GNU General Public License along
*     with this program; if not, write to the Free Software Foundation, Inc.,
*     675 Mass Ave, Cambridge, MA 02139, USA.
*
* Description: Driver parameters
*
*******************************************************************/

#define XPAR_XPCI_NUM_INSTANCES 1
#define XPAR_XPCI_CLOCK_HZ 33333333
#define XPAR_OPB_PCI_REF_0_DEVICE_ID 0
#define XPAR_OPB_PCI_REF_0_BASEADDR 0x20000000
#define XPAR_OPB_PCI_REF_0_HIGHADDR 0x3FFFFFFF
#define XPAR_OPB_PCI_REF_0_CONFIG_ADDR 0x3C000000
#define XPAR_OPB_PCI_REF_0_CONFIG_DATA 0x3C000004
#define XPAR_OPB_PCI_REF_0_LCONFIG_ADDR 0x3E000000
#define XPAR_OPB_PCI_REF_0_MEM_BASEADDR 0x20000000
#define XPAR_OPB_PCI_REF_0_MEM_HIGHADDR 0x37FFFFFF
#define XPAR_OPB_PCI_REF_0_IO_BASEADDR 0x38000000
#define XPAR_OPB_PCI_REF_0_IO_HIGHADDR 0x3BFFFFFF

/******************************************************************/

#define XPAR_XEMAC_NUM_INSTANCES 1
#define XPAR_OPB_ETHERNET_0_BASEADDR 0x60000000
#define XPAR_OPB_ETHERNET_0_HIGHADDR 0x60003FFF
#define XPAR_OPB_ETHERNET_0_DEVICE_ID 0
#define XPAR_OPB_ETHERNET_0_ERR_COUNT_EXIST 1
#define XPAR_OPB_ETHERNET_0_DMA_PRESENT 1
#define XPAR_OPB_ETHERNET_0_MII_EXIST 1

/******************************************************************/

#define XPAR_MY_OPB_GPIO_0_DEVICE_ID_0 0
#define XPAR_MY_OPB_GPIO_0_BASEADDR_0 0x90000000
#define XPAR_MY_OPB_GPIO_0_HIGHADDR_0 (0x90000000+0x7)
#define XPAR_MY_OPB_GPIO_0_DEVICE_ID_1 1
#define XPAR_MY_OPB_GPIO_0_BASEADDR_1 (0x90000000+0x8)
#define XPAR_MY_OPB_GPIO_0_HIGHADDR_1 (0x90000000+0x1F)
#define XPAR_XGPIO_NUM_INSTANCES 2

/******************************************************************/

#define XPAR_XIIC_NUM_INSTANCES 1
#define XPAR_OPB_IIC_0_BASEADDR 0xA8000000
#define XPAR_OPB_IIC_0_HIGHADDR 0xA80001FF
#define XPAR_OPB_IIC_0_DEVICE_ID 0
#define XPAR_OPB_IIC_0_TEN_BIT_ADR 0

/******************************************************************/

#define XPAR_XUARTNS550_NUM_INSTANCES 2
#define XPAR_XUARTNS550_CLOCK_HZ 100000000
#define XPAR_OPB_UART16550_0_BASEADDR 0xA0000000
#define XPAR_OPB_UART16550_0_HIGHADDR 0xA0001FFF
#define XPAR_OPB_UART16550_0_DEVICE_ID 0
#define XPAR_OPB_UART16550_1_BASEADDR 0xA0010000
#define XPAR_OPB_UART16550_1_HIGHADDR 0xA0011FFF
#define XPAR_OPB_UART16550_1_DEVICE_ID 1

/******************************************************************/

#define XPAR_XSPI_NUM_INSTANCES 1
#define XPAR_OPB_SPI_0_BASEADDR 0xA4000000
#define XPAR_OPB_SPI_0_HIGHADDR 0xA400007F
#define XPAR_OPB_SPI_0_DEVICE_ID 0
#define XPAR_OPB_SPI_0_FIFO_EXIST 1
#define XPAR_OPB_SPI_0_SPI_SLAVE_ONLY 0
#define XPAR_OPB_SPI_0_NUM_SS_BITS 1

/******************************************************************/

#define XPAR_XPS2_NUM_INSTANCES 2
#define XPAR_OPB_PS2_DUAL_REF_0_DEVICE_ID_0 0
#define XPAR_OPB_PS2_DUAL_REF_0_BASEADDR_0 0xA9000000
#define XPAR_OPB_PS2_DUAL_REF_0_HIGHADDR_0 (0xA9000000+0x3F)
#define XPAR_OPB_PS2_DUAL_REF_0_DEVICE_ID_1 1
#define XPAR_OPB_PS2_DUAL_REF_0_BASEADDR_1 (0xA9000000+0x1000)
#define XPAR_OPB_PS2_DUAL_REF_0_HIGHADDR_1 (0xA9000000+0x103F)

/******************************************************************/

#define XPAR_XTOUCHSCREEN_NUM_INSTANCES 1
#define XPAR_OPB_TSD_REF_0_BASEADDR 0xAA000000
#define XPAR_OPB_TSD_REF_0_HIGHADDR 0xAA000007
#define XPAR_OPB_TSD_REF_0_DEVICE_ID 0

/******************************************************************/

#define XPAR_OPB_AC97_CONTROLLER_REF_0_BASEADDR 0xA6000000
#define XPAR_OPB_AC97_CONTROLLER_REF_0_HIGHADDR 0xA60000FF
#define XPAR_OPB_PAR_PORT_REF_0_BASEADDR 0x90010000
#define XPAR_OPB_PAR_PORT_REF_0_HIGHADDR 0x900100FF
#define XPAR_PLB_DDR_0_BASEADDR 0x00000000
#define XPAR_PLB_DDR_0_HIGHADDR 0x0FFFFFFF

/******************************************************************/

#define XPAR_XINTC_HAS_IPR 1
#define XPAR_INTC_MAX_NUM_INTR_INPUTS 18
#define XPAR_XINTC_USE_DCR 0
#define XPAR_XINTC_NUM_INSTANCES 1
#define XPAR_DCR_INTC_0_BASEADDR 0xD0000FC0
#define XPAR_DCR_INTC_0_HIGHADDR 0xD0000FDF
#define XPAR_DCR_INTC_0_DEVICE_ID 0
#define XPAR_DCR_INTC_0_KIND_OF_INTR 0x00038000

/******************************************************************/

#define XPAR_DCR_INTC_0_MISC_LOGIC_0_PHY_MII_INT_INTR 0
#define XPAR_DCR_INTC_0_OPB_ETHERNET_0_IP2INTC_IRPT_INTR 1
#define XPAR_DCR_INTC_0_MISC_LOGIC_0_IIC_TEMP_CRIT_INTR 2
#define XPAR_DCR_INTC_0_MISC_LOGIC_0_IIC_IRQ_INTR 3
#define XPAR_DCR_INTC_0_OPB_IIC_0_IP2INTC_IRPT_INTR 4
#define XPAR_DCR_INTC_0_OPB_SYSACE_0_SYSACE_IRQ_INTR 5
#define XPAR_DCR_INTC_0_OPB_UART16550_0_IP2INTC_IRPT_INTR 6
#define XPAR_DCR_INTC_0_OPB_UART16550_1_IP2INTC_IRPT_INTR 7
#define XPAR_DCR_INTC_0_OPB_PS2_DUAL_REF_0_SYS_INTR1_INTR 8
#define XPAR_DCR_INTC_0_OPB_PS2_DUAL_REF_0_SYS_INTR2_INTR 9
#define XPAR_DCR_INTC_0_OPB_SPI_0_IP2INTC_IRPT_INTR 10
#define XPAR_DCR_INTC_0_OPB_TSD_REF_0_INTR_INTR 11
#define XPAR_DCR_INTC_0_OPB_AC97_CONTROLLER_REF_0_PLAYBACK_INTERRUPT_INTR 12
#define XPAR_DCR_INTC_0_OPB_AC97_CONTROLLER_REF_0_RECORD_INTERRUPT_INTR 13
#define XPAR_DCR_INTC_0_OPB_PCI_REF_0_INTR_OUT_INTR 14
#define XPAR_DCR_INTC_0_PLB2OPB_BRIDGE_0_BUS_ERROR_DET_INTR 15
#define XPAR_DCR_INTC_0_PLB_V34_0_BUS_ERROR_DET_INTR 16
#define XPAR_DCR_INTC_0_OPB2PLB_BRIDGE_0_BUS_ERROR_DET_INTR 17

/******************************************************************/

#define XPAR_XTFT_NUM_INSTANCES 1
#define XPAR_PLB_TFT_CNTLR_REF_0_DCR_BASEADDR 0xD0000200
#define XPAR_PLB_TFT_CNTLR_REF_0_DCR_HIGHADDR 0xD0000207
#define XPAR_PLB_TFT_CNTLR_REF_0_DEVICE_ID 0

/******************************************************************/

#define XPAR_XSYSACE_MEM_WIDTH 8
#define XPAR_XSYSACE_NUM_INSTANCES 1
#define XPAR_OPB_SYSACE_0_BASEADDR 0xCF000000
#define XPAR_OPB_SYSACE_0_HIGHADDR 0xCF0001FF
#define XPAR_OPB_SYSACE_0_DEVICE_ID 0
#define XPAR_OPB_SYSACE_0_MEM_WIDTH 8

/******************************************************************/

#define XPAR_CPU_PPC405_CORE_CLOCK_FREQ_HZ 300000000

/******************************************************************/

/******************************************************************/

/* Linux Redefines */

/******************************************************************/

#define XPAR_UARTNS550_0_BASEADDR (XPAR_OPB_UART16550_0_BASEADDR+0x1000)
#define XPAR_UARTNS550_0_HIGHADDR XPAR_OPB_UART16550_0_HIGHADDR
#define XPAR_UARTNS550_0_CLOCK_FREQ_HZ XPAR_XUARTNS550_CLOCK_HZ
#define XPAR_UARTNS550_0_DEVICE_ID XPAR_OPB_UART16550_0_DEVICE_ID
#define XPAR_UARTNS550_1_BASEADDR (XPAR_OPB_UART16550_1_BASEADDR+0x1000)
#define XPAR_UARTNS550_1_HIGHADDR XPAR_OPB_UART16550_1_HIGHADDR
#define XPAR_UARTNS550_1_CLOCK_FREQ_HZ XPAR_XUARTNS550_CLOCK_HZ
#define XPAR_UARTNS550_1_DEVICE_ID XPAR_OPB_UART16550_1_DEVICE_ID

/******************************************************************/

#define XPAR_GPIO_0_BASEADDR XPAR_MY_OPB_GPIO_0_BASEADDR_0
#define XPAR_GPIO_0_HIGHADDR XPAR_MY_OPB_GPIO_0_HIGHADDR_0
#define XPAR_GPIO_0_DEVICE_ID XPAR_MY_OPB_GPIO_0_DEVICE_ID_0
#define XPAR_GPIO_1_BASEADDR XPAR_MY_OPB_GPIO_0_BASEADDR_1
#define XPAR_GPIO_1_HIGHADDR XPAR_MY_OPB_GPIO_0_HIGHADDR_1
#define XPAR_GPIO_1_DEVICE_ID XPAR_MY_OPB_GPIO_0_DEVICE_ID_1

/******************************************************************/

#define XPAR_IIC_0_BASEADDR XPAR_OPB_IIC_0_BASEADDR
#define XPAR_IIC_0_HIGHADDR XPAR_OPB_IIC_0_HIGHADDR
#define XPAR_IIC_0_TEN_BIT_ADR XPAR_OPB_IIC_0_TEN_BIT_ADR
#define XPAR_IIC_0_DEVICE_ID XPAR_OPB_IIC_0_DEVICE_ID

/******************************************************************/

#define XPAR_SYSACE_0_BASEADDR XPAR_OPB_SYSACE_0_BASEADDR
#define XPAR_SYSACE_0_HIGHADDR XPAR_OPB_SYSACE_0_HIGHADDR
#define XPAR_SYSACE_0_DEVICE_ID XPAR_OPB_SYSACE_0_DEVICE_ID

/******************************************************************/

#define XPAR_INTC_0_BASEADDR XPAR_DCR_INTC_0_BASEADDR
#define XPAR_INTC_0_HIGHADDR XPAR_DCR_INTC_0_HIGHADDR
#define XPAR_INTC_0_KIND_OF_INTR XPAR_DCR_INTC_0_KIND_OF_INTR
#define XPAR_INTC_0_DEVICE_ID XPAR_DCR_INTC_0_DEVICE_ID

/******************************************************************/

#define XPAR_INTC_0_EMAC_0_VEC_ID XPAR_DCR_INTC_0_OPB_ETHERNET_0_IP2INTC_IRPT_INTR
#define XPAR_INTC_0_IIC_0_VEC_ID XPAR_DCR_INTC_0_OPB_IIC_0_IP2INTC_IRPT_INTR
#define XPAR_INTC_0_SYSACE_0_VEC_ID XPAR_DCR_INTC_0_OPB_SYSACE_0_SYSACE_IRQ_INTR
#define XPAR_INTC_0_UARTNS550_0_VEC_ID XPAR_DCR_INTC_0_OPB_UART16550_0_IP2INTC_IRPT_INTR
#define XPAR_INTC_0_UARTNS550_1_VEC_ID XPAR_DCR_INTC_0_OPB_UART16550_1_IP2INTC_IRPT_INTR
#define XPAR_INTC_0_PS2_0_VEC_ID XPAR_DCR_INTC_0_OPB_PS2_DUAL_REF_0_SYS_INTR1_INTR
#define XPAR_INTC_0_PS2_1_VEC_ID XPAR_DCR_INTC_0_OPB_PS2_DUAL_REF_0_SYS_INTR2_INTR
#define XPAR_INTC_0_SPI_0_VEC_ID XPAR_DCR_INTC_0_OPB_SPI_0_IP2INTC_IRPT_INTR
#define XPAR_INTC_0_TOUCHSCREEN_0_VEC_ID XPAR_DCR_INTC_0_OPB_TSD_REF_0_INTR_INTR
#define XPAR_INTC_0_PCI_0_VEC_ID_A XPAR_DCR_INTC_0_OPB_PCI_REF_0_INTR_OUT_INTR
#define XPAR_INTC_0_PCI_0_VEC_ID_B XPAR_DCR_INTC_0_OPB_PCI_REF_0_INTR_OUT_INTR
#define XPAR_INTC_0_PCI_0_VEC_ID_C XPAR_DCR_INTC_0_OPB_PCI_REF_0_INTR_OUT_INTR
#define XPAR_INTC_0_PCI_0_VEC_ID_D XPAR_DCR_INTC_0_OPB_PCI_REF_0_INTR_OUT_INTR

/******************************************************************/

#define XPAR_EMAC_0_BASEADDR XPAR_OPB_ETHERNET_0_BASEADDR
#define XPAR_EMAC_0_HIGHADDR XPAR_OPB_ETHERNET_0_HIGHADDR
#define XPAR_EMAC_0_DMA_PRESENT XPAR_OPB_ETHERNET_0_DMA_PRESENT
#define XPAR_EMAC_0_MII_EXIST XPAR_OPB_ETHERNET_0_MII_EXIST
#define XPAR_EMAC_0_ERR_COUNT_EXIST XPAR_OPB_ETHERNET_0_ERR_COUNT_EXIST
#define XPAR_EMAC_0_DEVICE_ID XPAR_OPB_ETHERNET_0_DEVICE_ID

/******************************************************************/

#define XPAR_SPI_0_BASEADDR XPAR_OPB_SPI_0_BASEADDR
#define XPAR_SPI_0_HIGHADDR XPAR_OPB_SPI_0_HIGHADDR
#define XPAR_SPI_0_DEVICE_ID XPAR_OPB_SPI_0_DEVICE_ID

/******************************************************************/

#define XPAR_TOUCHSCREEN_0_BASEADDR XPAR_OPB_TSD_REF_0_BASEADDR
#define XPAR_TOUCHSCREEN_0_HIGHADDR XPAR_OPB_TSD_REF_0_HIGHADDR
#define XPAR_TOUCHSCREEN_0_DEVICE_ID XPAR_OPB_TSD_REF_0_DEVICE_ID

/******************************************************************/

#define XPAR_TFT_0_BASEADDR XPAR_PLB_TFT_CNTLR_REF_0_DCR_BASEADDR

/******************************************************************/

#define XPAR_PCI_0_BASEADDR XPAR_OPB_PCI_REF_0_BASEADDR
#define XPAR_PCI_0_HIGHADDR XPAR_OPB_PCI_REF_0_HIGHADDR
#define XPAR_PCI_0_CONFIG_ADDR XPAR_OPB_PCI_REF_0_CONFIG_ADDR
#define XPAR_PCI_0_CONFIG_DATA XPAR_OPB_PCI_REF_0_CONFIG_DATA
#define XPAR_PCI_0_LCONFIG_ADDR XPAR_OPB_PCI_REF_0_LCONFIG_ADDR
#define XPAR_PCI_0_MEM_BASEADDR XPAR_OPB_PCI_REF_0_MEM_BASEADDR
#define XPAR_PCI_0_MEM_HIGHADDR XPAR_OPB_PCI_REF_0_MEM_HIGHADDR
#define XPAR_PCI_0_IO_BASEADDR XPAR_OPB_PCI_REF_0_IO_BASEADDR
#define XPAR_PCI_0_IO_HIGHADDR XPAR_OPB_PCI_REF_0_IO_HIGHADDR
#define XPAR_PCI_0_CLOCK_FREQ_HZ XPAR_XPCI_CLOCK_HZ
#define XPAR_PCI_0_DEVICE_ID XPAR_OPB_PCI_REF_0_DEVICE_ID

/******************************************************************/

#define XPAR_PS2_0_BASEADDR XPAR_OPB_PS2_DUAL_REF_0_BASEADDR_0
#define XPAR_PS2_0_HIGHADDR XPAR_OPB_PS2_DUAL_REF_0_HIGHADDR_0
#define XPAR_PS2_0_DEVICE_ID XPAR_OPB_PS2_DUAL_REF_0_DEVICE_ID_0
#define XPAR_PS2_1_BASEADDR XPAR_OPB_PS2_DUAL_REF_0_BASEADDR_1
#define XPAR_PS2_1_HIGHADDR XPAR_OPB_PS2_DUAL_REF_0_HIGHADDR_1
#define XPAR_PS2_1_DEVICE_ID XPAR_OPB_PS2_DUAL_REF_0_DEVICE_ID_1

/******************************************************************/

#define XPAR_PLB_CLOCK_FREQ_HZ 100000000
#define XPAR_CORE_CLOCK_FREQ_HZ XPAR_CPU_PPC405_CORE_CLOCK_FREQ_HZ
#define XPAR_DDR_0_SIZE 0x08000000

/******************************************************************/

#define XPAR_PERSISTENT_0_IIC_0_BASEADDR 0x00000400
#define XPAR_PERSISTENT_0_IIC_0_HIGHADDR 0x000007FF
#define XPAR_PERSISTENT_0_IIC_0_EEPROMADDR 0xA0

/******************************************************************/

#define XPAR_POWER_0_POWERDOWN_BASEADDR 0x90000004
#define XPAR_POWER_0_POWERDOWN_HIGHADDR 0x90000007
#define XPAR_POWER_0_POWERDOWN_VALUE 0xFF

/******************************************************************/

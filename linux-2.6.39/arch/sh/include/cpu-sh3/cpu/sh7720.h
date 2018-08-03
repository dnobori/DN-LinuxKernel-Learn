#include "linux/generated/autoconf.h"
#ifndef __ASM_SH7720_H__
#define __ASM_SH7720_H__

enum {
	/* PTA */
	GPIO_PTA7, GPIO_PTA6, GPIO_PTA5, GPIO_PTA4,
	GPIO_PTA3, GPIO_PTA2, GPIO_PTA1, GPIO_PTA0,

	/* PTB */
	GPIO_PTB7, GPIO_PTB6, GPIO_PTB5, GPIO_PTB4,
	GPIO_PTB3, GPIO_PTB2, GPIO_PTB1, GPIO_PTB0,

	/* PTC */
	GPIO_PTC7, GPIO_PTC6, GPIO_PTC5, GPIO_PTC4,
	GPIO_PTC3, GPIO_PTC2, GPIO_PTC1, GPIO_PTC0,

	/* PTD */
	GPIO_PTD7, GPIO_PTD6, GPIO_PTD5, GPIO_PTD4,
	GPIO_PTD3, GPIO_PTD2, GPIO_PTD1, GPIO_PTD0,

	/* PTE */
	GPIO_PTE6, GPIO_PTE5, GPIO_PTE4, GPIO_PTE3,
	GPIO_PTE2, GPIO_PTE1, GPIO_PTE0,

	/* PTF */
	GPIO_PTF6, GPIO_PTF5, GPIO_PTF4, GPIO_PTF3,
	GPIO_PTF2, GPIO_PTF1, GPIO_PTF0, GPIO_PTG6,

	/* PTG */
	GPIO_PTG5, GPIO_PTG4, GPIO_PTG3, GPIO_PTG2,
	GPIO_PTG1, GPIO_PTG0,

	/* PTH */
	GPIO_PTH6, GPIO_PTH5, GPIO_PTH4, GPIO_PTH3,
	GPIO_PTH2, GPIO_PTH1, GPIO_PTH0,

	/* PTJ */
	GPIO_PTJ6, GPIO_PTJ5, GPIO_PTJ4, GPIO_PTJ3,
	GPIO_PTJ2, GPIO_PTJ1, GPIO_PTJ0,

	/* PTK */
	GPIO_PTK3, GPIO_PTK2, GPIO_PTK1, GPIO_PTK0,

	/* PTL */
	GPIO_PTL7, GPIO_PTL6, GPIO_PTL5, GPIO_PTL4, GPIO_PTL3,

	/* PTM */
	GPIO_PTM7, GPIO_PTM6, GPIO_PTM5, GPIO_PTM4,
	GPIO_PTM3, GPIO_PTM2, GPIO_PTM1, GPIO_PTM0,

	/* PTP */
	GPIO_PTP4, GPIO_PTP3, GPIO_PTP2, GPIO_PTP1, GPIO_PTP0,

	/* PTR */
	GPIO_PTR7, GPIO_PTR6, GPIO_PTR5, GPIO_PTR4,
	GPIO_PTR3, GPIO_PTR2, GPIO_PTR1, GPIO_PTR0,

	/* PTS */
	GPIO_PTS4, GPIO_PTS3, GPIO_PTS2, GPIO_PTS1, GPIO_PTS0,

	/* PTT */
	GPIO_PTT4, GPIO_PTT3, GPIO_PTT2, GPIO_PTT1, GPIO_PTT0,

	/* PTU */
	GPIO_PTU4, GPIO_PTU3, GPIO_PTU2, GPIO_PTU1, GPIO_PTU0,

	/* PTV */
	GPIO_PTV4, GPIO_PTV3, GPIO_PTV2, GPIO_PTV1, GPIO_PTV0,

	/* BSC */
	GPIO_FN_D31, GPIO_FN_D30, GPIO_FN_D29, GPIO_FN_D28,
	GPIO_FN_D27, GPIO_FN_D26, GPIO_FN_D25, GPIO_FN_D24,
	GPIO_FN_D23, GPIO_FN_D22, GPIO_FN_D21, GPIO_FN_D20,
	GPIO_FN_D19, GPIO_FN_D18, GPIO_FN_D17, GPIO_FN_D16,
	GPIO_FN_IOIS16, GPIO_FN_RAS, GPIO_FN_CAS, GPIO_FN_CKE,
	GPIO_FN_CS5B_CE1A, GPIO_FN_CS6B_CE1B,
	GPIO_FN_A25, GPIO_FN_A24, GPIO_FN_A23, GPIO_FN_A22,
	GPIO_FN_A21, GPIO_FN_A20, GPIO_FN_A19, GPIO_FN_A0,
	GPIO_FN_REFOUT, GPIO_FN_IRQOUT,

	/* LCDC */
	GPIO_FN_LCD_DATA15, GPIO_FN_LCD_DATA14,
	GPIO_FN_LCD_DATA13, GPIO_FN_LCD_DATA12,
	GPIO_FN_LCD_DATA11, GPIO_FN_LCD_DATA10,
	GPIO_FN_LCD_DATA9, GPIO_FN_LCD_DATA8,
	GPIO_FN_LCD_DATA7, GPIO_FN_LCD_DATA6,
	GPIO_FN_LCD_DATA5, GPIO_FN_LCD_DATA4,
	GPIO_FN_LCD_DATA3, GPIO_FN_LCD_DATA2,
	GPIO_FN_LCD_DATA1, GPIO_FN_LCD_DATA0,
	GPIO_FN_LCD_M_DISP,
	GPIO_FN_LCD_CL1, GPIO_FN_LCD_CL2,
	GPIO_FN_LCD_DON, GPIO_FN_LCD_FLM,
	GPIO_FN_LCD_VEPWC, GPIO_FN_LCD_VCPWC,

	/* AFEIF */
	GPIO_FN_AFE_RXIN, GPIO_FN_AFE_RDET,
	GPIO_FN_AFE_FS, GPIO_FN_AFE_TXOUT,
	GPIO_FN_AFE_SCLK, GPIO_FN_AFE_RLYCNT,
	GPIO_FN_AFE_HC1,

	/* IIC */
	GPIO_FN_IIC_SCL, GPIO_FN_IIC_SDA,

	/* DAC */
	GPIO_FN_DA1, GPIO_FN_DA0,

	/* ADC */
	GPIO_FN_AN3, GPIO_FN_AN2, GPIO_FN_AN1, GPIO_FN_AN0, GPIO_FN_ADTRG,

	/* USB */
	GPIO_FN_USB1D_RCV, GPIO_FN_USB1D_TXSE0,
	GPIO_FN_USB1D_TXDPLS, GPIO_FN_USB1D_DMNS,
	GPIO_FN_USB1D_DPLS, GPIO_FN_USB1D_SPEED,
	GPIO_FN_USB1D_TXENL, GPIO_FN_USB2_PWR_EN,
	GPIO_FN_USB1_PWR_EN_USBF_UPLUP, GPIO_FN_USB1D_SUSPEND,

	/* INTC */
	GPIO_FN_IRQ5, GPIO_FN_IRQ4,
	GPIO_FN_IRQ3_IRL3, GPIO_FN_IRQ2_IRL2,
	GPIO_FN_IRQ1_IRL1, GPIO_FN_IRQ0_IRL0,

	/* PCC */
	GPIO_FN_PCC_REG, GPIO_FN_PCC_DRV,
	GPIO_FN_PCC_BVD2, GPIO_FN_PCC_BVD1,
	GPIO_FN_PCC_CD2, GPIO_FN_PCC_CD1,
	GPIO_FN_PCC_RESET, GPIO_FN_PCC_RDY,
	GPIO_FN_PCC_VS2, GPIO_FN_PCC_VS1,

	/* HUDI */
	GPIO_FN_AUDATA3, GPIO_FN_AUDATA2, GPIO_FN_AUDATA1, GPIO_FN_AUDATA0,
	GPIO_FN_AUDCK, GPIO_FN_AUDSYNC, GPIO_FN_ASEBRKAK, GPIO_FN_TRST,
	GPIO_FN_TMS, GPIO_FN_TDO, GPIO_FN_TDI, GPIO_FN_TCK,

	/* DMAC */
	GPIO_FN_DACK1, GPIO_FN_DREQ1, GPIO_FN_DACK0, GPIO_FN_DREQ0,
	GPIO_FN_TEND1, GPIO_FN_TEND0,

	/* SIOF0 */
	GPIO_FN_SIOF0_SYNC, GPIO_FN_SIOF0_MCLK,
	GPIO_FN_SIOF0_TXD, GPIO_FN_SIOF0_RXD,
	GPIO_FN_SIOF0_SCK,

	/* SIOF1 */
	GPIO_FN_SIOF1_SYNC, GPIO_FN_SIOF1_MCLK,
	GPIO_FN_SIOF1_TXD, GPIO_FN_SIOF1_RXD,
	GPIO_FN_SIOF1_SCK,

	/* SCIF0 */
	GPIO_FN_SCIF0_TXD, GPIO_FN_SCIF0_RXD,
	GPIO_FN_SCIF0_RTS, GPIO_FN_SCIF0_CTS, GPIO_FN_SCIF0_SCK,

	/* SCIF1 */
	GPIO_FN_SCIF1_TXD, GPIO_FN_SCIF1_RXD,
	GPIO_FN_SCIF1_RTS, GPIO_FN_SCIF1_CTS, GPIO_FN_SCIF1_SCK,

	/* TPU */
	GPIO_FN_TPU_TO1, GPIO_FN_TPU_TO0,
	GPIO_FN_TPU_TI3B, GPIO_FN_TPU_TI3A,
	GPIO_FN_TPU_TI2B, GPIO_FN_TPU_TI2A,
	GPIO_FN_TPU_TO3, GPIO_FN_TPU_TO2,

	/* SIM */
	GPIO_FN_SIM_D, GPIO_FN_SIM_CLK, GPIO_FN_SIM_RST,

	/* MMC */
	GPIO_FN_MMC_DAT, GPIO_FN_MMC_CMD,
	GPIO_FN_MMC_CLK, GPIO_FN_MMC_VDDON,
	GPIO_FN_MMC_ODMOD,

	/* SYSC */
	GPIO_FN_STATUS0, GPIO_FN_STATUS1,
};

#endif /* __ASM_SH7720_H__ */
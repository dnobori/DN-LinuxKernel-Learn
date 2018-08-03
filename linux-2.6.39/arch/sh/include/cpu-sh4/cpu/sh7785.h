#include "linux/generated/autoconf.h"
#ifndef __ASM_SH7785_H__
#define __ASM_SH7785_H__

/* Boot Mode Pins:
 *
 * MODE0: CPG - Initial Pck/Bck Frequency [FRQMR1]
 * MODE1: CPG - Initial Uck/SHck/DDRck Frequency [FRQMR1]
 * MODE2: CPG - Reserved (L: Normal operation)
 * MODE3: CPG - Reserved (L: Normal operation)
 * MODE4: CPG - Initial PLL setting (72x/36x)
 * MODE5: LBSC - Area0 Memory Type / Bus Width [CS0BCR.8]
 * MODE6: LBSC - Area0 Memory Type / Bus Width [CS0BCR.9]
 * MODE7: LBSC - Area0 Memory Type / Bus Width [CS0BCR.3]
 * MODE8: LBSC - Endian Mode (L: Big, H: Little) [BCR.31]
 * MODE9: LBSC - Master/Slave Mode (L: Slave) [BCR.30]
 * MODE10: CPG - Clock Input (L: Ext Clk, H: Crystal)
 * MODE11: PCI - Pin Mode (LL: PCI host, LH: PCI slave)
 * MODE12: PCI - Pin Mode (HL: Local bus, HH: DU)
 * MODE13: Boot Address Mode (L: 29-bit, H: 32-bit)
 * MODE14: Reserved (H: Normal operation)
 *
 * More information in sh7785 manual Rev.1.00, page 1628.
 */

/* Pin Function Controller:
 * GPIO_FN_xx - GPIO used to select pin function
 * GPIO_Pxx - GPIO mapped to real I/O pin on CPU
 */
enum {
	/* PA */
	GPIO_PA7, GPIO_PA6, GPIO_PA5, GPIO_PA4,
	GPIO_PA3, GPIO_PA2, GPIO_PA1, GPIO_PA0,

	/* PB */
	GPIO_PB7, GPIO_PB6, GPIO_PB5, GPIO_PB4,
	GPIO_PB3, GPIO_PB2, GPIO_PB1, GPIO_PB0,

	/* PC */
	GPIO_PC7, GPIO_PC6, GPIO_PC5, GPIO_PC4,
	GPIO_PC3, GPIO_PC2, GPIO_PC1, GPIO_PC0,

	/* PD */
	GPIO_PD7, GPIO_PD6, GPIO_PD5, GPIO_PD4,
	GPIO_PD3, GPIO_PD2, GPIO_PD1, GPIO_PD0,

	/* PE */
	GPIO_PE5, GPIO_PE4, GPIO_PE3, GPIO_PE2,
	GPIO_PE1, GPIO_PE0,

	/* PF */
	GPIO_PF7, GPIO_PF6, GPIO_PF5, GPIO_PF4,
	GPIO_PF3, GPIO_PF2, GPIO_PF1, GPIO_PF0,

	/* PG */
	GPIO_PG7, GPIO_PG6, GPIO_PG5, GPIO_PG4,
	GPIO_PG3, GPIO_PG2, GPIO_PG1, GPIO_PG0,

	/* PH */
	GPIO_PH7, GPIO_PH6, GPIO_PH5, GPIO_PH4,
	GPIO_PH3, GPIO_PH2, GPIO_PH1, GPIO_PH0,

	/* PJ */
	GPIO_PJ7, GPIO_PJ6, GPIO_PJ5, GPIO_PJ4,
	GPIO_PJ3, GPIO_PJ2, GPIO_PJ1, GPIO_PJ0,

	/* PK */
	GPIO_PK7, GPIO_PK6, GPIO_PK5, GPIO_PK4,
	GPIO_PK3, GPIO_PK2, GPIO_PK1, GPIO_PK0,

	/* PL */
	GPIO_PL7, GPIO_PL6, GPIO_PL5, GPIO_PL4,
	GPIO_PL3, GPIO_PL2, GPIO_PL1, GPIO_PL0,

	/* PM */
	GPIO_PM1, GPIO_PM0,

	/* PN */
	GPIO_PN7, GPIO_PN6, GPIO_PN5, GPIO_PN4,
	GPIO_PN3, GPIO_PN2, GPIO_PN1, GPIO_PN0,

	/* PP */
	GPIO_PP5, GPIO_PP4,
	GPIO_PP3, GPIO_PP2, GPIO_PP1, GPIO_PP0,

	/* PQ */
	GPIO_PQ4,
	GPIO_PQ3, GPIO_PQ2, GPIO_PQ1, GPIO_PQ0,

	/* PR */
	GPIO_PR3, GPIO_PR2, GPIO_PR1, GPIO_PR0,

	GPIO_FN_D63_AD31,
	GPIO_FN_D62_AD30,
	GPIO_FN_D61_AD29,
	GPIO_FN_D60_AD28,
	GPIO_FN_D59_AD27,
	GPIO_FN_D58_AD26,
	GPIO_FN_D57_AD25,
	GPIO_FN_D56_AD24,
	GPIO_FN_D55_AD23,
	GPIO_FN_D54_AD22,
	GPIO_FN_D53_AD21,
	GPIO_FN_D52_AD20,
	GPIO_FN_D51_AD19,
	GPIO_FN_D50_AD18,
	GPIO_FN_D49_AD17_DB5,
	GPIO_FN_D48_AD16_DB4,
	GPIO_FN_D47_AD15_DB3,
	GPIO_FN_D46_AD14_DB2,
	GPIO_FN_D45_AD13_DB1,
	GPIO_FN_D44_AD12_DB0,
	GPIO_FN_D43_AD11_DG5,
	GPIO_FN_D42_AD10_DG4,
	GPIO_FN_D41_AD9_DG3,
	GPIO_FN_D40_AD8_DG2,
	GPIO_FN_D39_AD7_DG1,
	GPIO_FN_D38_AD6_DG0,
	GPIO_FN_D37_AD5_DR5,
	GPIO_FN_D36_AD4_DR4,
	GPIO_FN_D35_AD3_DR3,
	GPIO_FN_D34_AD2_DR2,
	GPIO_FN_D33_AD1_DR1,
	GPIO_FN_D32_AD0_DR0,
	GPIO_FN_REQ1,
	GPIO_FN_REQ2,
	GPIO_FN_REQ3,
	GPIO_FN_GNT1,
	GPIO_FN_GNT2,
	GPIO_FN_GNT3,
	GPIO_FN_MMCCLK,
	GPIO_FN_D31,
	GPIO_FN_D30,
	GPIO_FN_D29,
	GPIO_FN_D28,
	GPIO_FN_D27,
	GPIO_FN_D26,
	GPIO_FN_D25,
	GPIO_FN_D24,
	GPIO_FN_D23,
	GPIO_FN_D22,
	GPIO_FN_D21,
	GPIO_FN_D20,
	GPIO_FN_D19,
	GPIO_FN_D18,
	GPIO_FN_D17,
	GPIO_FN_D16,
	GPIO_FN_SCIF1_SCK,
	GPIO_FN_SCIF1_RXD,
	GPIO_FN_SCIF1_TXD,
	GPIO_FN_SCIF0_CTS,
	GPIO_FN_INTD,
	GPIO_FN_FCE,
	GPIO_FN_SCIF0_RTS,
	GPIO_FN_HSPI_CS,
	GPIO_FN_FSE,
	GPIO_FN_SCIF0_SCK,
	GPIO_FN_HSPI_CLK,
	GPIO_FN_FRE,
	GPIO_FN_SCIF0_RXD,
	GPIO_FN_HSPI_RX,
	GPIO_FN_FRB,
	GPIO_FN_SCIF0_TXD,
	GPIO_FN_HSPI_TX,
	GPIO_FN_FWE,
	GPIO_FN_SCIF5_TXD,
	GPIO_FN_HAC1_SYNC,
	GPIO_FN_SSI1_WS,
	GPIO_FN_SIOF_TXD_PJ,
	GPIO_FN_HAC0_SDOUT,
	GPIO_FN_SSI0_SDATA,
	GPIO_FN_SIOF_RXD_PJ,
	GPIO_FN_HAC0_SDIN,
	GPIO_FN_SSI0_SCK,
	GPIO_FN_SIOF_SYNC_PJ,
	GPIO_FN_HAC0_SYNC,
	GPIO_FN_SSI0_WS,
	GPIO_FN_SIOF_MCLK_PJ,
	GPIO_FN_HAC_RES,
	GPIO_FN_SIOF_SCK_PJ,
	GPIO_FN_HAC0_BITCLK,
	GPIO_FN_SSI0_CLK,
	GPIO_FN_HAC1_BITCLK,
	GPIO_FN_SSI1_CLK,
	GPIO_FN_TCLK,
	GPIO_FN_IOIS16,
	GPIO_FN_STATUS0,
	GPIO_FN_DRAK0_PK3,
	GPIO_FN_STATUS1,
	GPIO_FN_DRAK1_PK2,
	GPIO_FN_DACK2,
	GPIO_FN_SCIF2_TXD,
	GPIO_FN_MMCCMD,
	GPIO_FN_SIOF_TXD_PK,
	GPIO_FN_DACK3,
	GPIO_FN_SCIF2_SCK,
	GPIO_FN_MMCDAT,
	GPIO_FN_SIOF_SCK_PK,
	GPIO_FN_DREQ0,
	GPIO_FN_DREQ1,
	GPIO_FN_DRAK0_PK1,
	GPIO_FN_DRAK1_PK0,
	GPIO_FN_DREQ2,
	GPIO_FN_INTB,
	GPIO_FN_DREQ3,
	GPIO_FN_INTC,
	GPIO_FN_DRAK2,
	GPIO_FN_CE2A,
	GPIO_FN_IRL4,
	GPIO_FN_FD4,
	GPIO_FN_IRL5,
	GPIO_FN_FD5,
	GPIO_FN_IRL6,
	GPIO_FN_FD6,
	GPIO_FN_IRL7,
	GPIO_FN_FD7,
	GPIO_FN_DRAK3,
	GPIO_FN_CE2B,
	GPIO_FN_BREQ_BSACK,
	GPIO_FN_BACK_BSREQ,
	GPIO_FN_SCIF5_RXD,
	GPIO_FN_HAC1_SDIN,
	GPIO_FN_SSI1_SCK,
	GPIO_FN_SCIF5_SCK,
	GPIO_FN_HAC1_SDOUT,
	GPIO_FN_SSI1_SDATA,
	GPIO_FN_SCIF3_TXD,
	GPIO_FN_FCLE,
	GPIO_FN_SCIF3_RXD,
	GPIO_FN_FALE,
	GPIO_FN_SCIF3_SCK,
	GPIO_FN_FD0,
	GPIO_FN_SCIF4_TXD,
	GPIO_FN_FD1,
	GPIO_FN_SCIF4_RXD,
	GPIO_FN_FD2,
	GPIO_FN_SCIF4_SCK,
	GPIO_FN_FD3,
	GPIO_FN_DEVSEL_DCLKOUT,
	GPIO_FN_STOP_CDE,
	GPIO_FN_LOCK_ODDF,
	GPIO_FN_TRDY_DISPL,
	GPIO_FN_IRDY_HSYNC,
	GPIO_FN_PCIFRAME_VSYNC,
	GPIO_FN_INTA,
	GPIO_FN_GNT0_GNTIN,
	GPIO_FN_REQ0_REQOUT,
	GPIO_FN_PERR,
	GPIO_FN_SERR,
	GPIO_FN_WE7_CBE3,
	GPIO_FN_WE6_CBE2,
	GPIO_FN_WE5_CBE1,
	GPIO_FN_WE4_CBE0,
	GPIO_FN_SCIF2_RXD,
	GPIO_FN_SIOF_RXD,
	GPIO_FN_MRESETOUT,
	GPIO_FN_IRQOUT,
};

#endif /* __ASM_SH7785_H__ */

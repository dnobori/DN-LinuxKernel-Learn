#include "linux/generated/autoconf.h"
/*
    Auvitek AU8522 QAM/8VSB demodulator driver

    Copyright (C) 2008 Steven Toth <stoth@linuxtv.org>
    Copyright (C) 2008 Devin Heitmueller <dheitmueller@linuxtv.org>
    Copyright (C) 2005-2008 Auvitek International, Ltd.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

*/

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/string.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/videodev2.h>
#include <media/v4l2-device.h>
#include <linux/i2c.h>
#include "dvb_frontend.h"
#include "au8522.h"
#include "tuner-i2c.h"

#define AU8522_ANALOG_MODE 0
#define AU8522_DIGITAL_MODE 1

struct au8522_state {
	struct i2c_client *c;
	struct i2c_adapter *i2c;

	u8 operational_mode;

	/* Used for sharing of the state between analog and digital mode */
	struct tuner_i2c_props i2c_props;
	struct list_head hybrid_tuner_instance_list;

	/* configuration settings */
	const struct au8522_config *config;

	struct dvb_frontend frontend;

	u32 current_frequency;
	fe_modulation_t current_modulation;

	u32 fe_status;
	unsigned int led_state;

	/* Analog settings */
	struct v4l2_subdev sd;
	v4l2_std_id std;
	int vid_input;
	int aud_input;
	u32 id;
	u32 rev;
	u8 brightness;
	u8 contrast;
	u8 saturation;
	s16 hue;
};

/* These are routines shared by both the VSB/QAM demodulator and the analog
   decoder */
int au8522_writereg(struct au8522_state *state, u16 reg, u8 data);
u8 au8522_readreg(struct au8522_state *state, u16 reg);
int au8522_init(struct dvb_frontend *fe);
int au8522_sleep(struct dvb_frontend *fe);

int au8522_get_state(struct au8522_state **state, struct i2c_adapter *i2c,
		     u8 client_address);
void au8522_release_state(struct au8522_state *state);

/* REGISTERS */
#define AU8522_INPUT_CONTROL_REG081H			0x081
#define AU8522_PGA_CONTROL_REG082H			0x082
#define AU8522_CLAMPING_CONTROL_REG083H			0x083

#define AU8522_MODULE_CLOCK_CONTROL_REG0A3H		0x0A3
#define AU8522_SYSTEM_MODULE_CONTROL_0_REG0A4H		0x0A4
#define AU8522_SYSTEM_MODULE_CONTROL_1_REG0A5H		0x0A5
#define AU8522_AGC_CONTROL_RANGE_REG0A6H		0x0A6
#define AU8522_SYSTEM_GAIN_CONTROL_REG0A7H		0x0A7
#define AU8522_TUNER_AGC_RF_STOP_REG0A8H  		0x0A8
#define AU8522_TUNER_AGC_RF_START_REG0A9H		0x0A9
#define AU8522_TUNER_RF_AGC_DEFAULT_REG0AAH		0x0AA
#define AU8522_TUNER_AGC_IF_STOP_REG0ABH		0x0AB
#define AU8522_TUNER_AGC_IF_START_REG0ACH		0x0AC
#define AU8522_TUNER_AGC_IF_DEFAULT_REG0ADH		0x0AD
#define AU8522_TUNER_AGC_STEP_REG0AEH			0x0AE
#define AU8522_TUNER_GAIN_STEP_REG0AFH			0x0AF

/* Receiver registers */
#define AU8522_FRMREGTHRD1_REG0B0H			0x0B0
#define AU8522_FRMREGAGC1H_REG0B1H 			0x0B1
#define AU8522_FRMREGSHIFT1_REG0B2H 			0x0B2
#define AU8522_TOREGAGC1_REG0B3H 			0x0B3
#define AU8522_TOREGASHIFT1_REG0B4H 			0x0B4
#define AU8522_FRMREGBBH_REG0B5H			0x0B5
#define AU8522_FRMREGBBM_REG0B6H 			0x0B6
#define AU8522_FRMREGBBL_REG0B7H     			0x0B7
/* 0xB8 TO 0xD7 are the filter coefficients */
#define AU8522_FRMREGTHRD2_REG0D8H 			0x0D8
#define AU8522_FRMREGAGC2H_REG0D9H 			0x0D9
#define AU8522_TOREGAGC2_REG0DAH 			0x0DA
#define AU8522_TOREGSHIFT2_REG0DBH 			0x0DB
#define AU8522_FRMREGPILOTH_REG0DCH			0x0DC
#define AU8522_FRMREGPILOTM_REG0DDH			0x0DD
#define AU8522_FRMREGPILOTL_REG0DEH			0x0DE
#define AU8522_TOREGFREQ_REG0DFH			0x0DF

#define AU8522_RX_PGA_RFOUT_REG0EBH			0x0EB
#define AU8522_RX_PGA_IFOUT_REG0ECH			0x0EC
#define AU8522_RX_PGA_PGAOUT_REG0EDH			0x0ED

#define AU8522_CHIP_MODE_REG0FEH			0x0FE

/* I2C bus control registers */
#define AU8522_I2C_CONTROL_REG0_REG090H    		0x090
#define AU8522_I2C_CONTROL_REG1_REG091H    		0x091
#define AU8522_I2C_STATUS_REG092H          		0x092
#define AU8522_I2C_WR_DATA0_REG093H			0x093
#define AU8522_I2C_WR_DATA1_REG094H			0x094
#define AU8522_I2C_WR_DATA2_REG095H			0x095
#define AU8522_I2C_WR_DATA3_REG096H			0x096
#define AU8522_I2C_WR_DATA4_REG097H			0x097
#define AU8522_I2C_WR_DATA5_REG098H			0x098
#define AU8522_I2C_WR_DATA6_REG099H			0x099
#define AU8522_I2C_WR_DATA7_REG09AH			0x09A
#define AU8522_I2C_RD_DATA0_REG09BH			0x09B
#define AU8522_I2C_RD_DATA1_REG09CH			0x09C
#define AU8522_I2C_RD_DATA2_REG09DH			0x09D
#define AU8522_I2C_RD_DATA3_REG09EH			0x09E
#define AU8522_I2C_RD_DATA4_REG09FH			0x09F
#define AU8522_I2C_RD_DATA5_REG0A0H			0x0A0
#define AU8522_I2C_RD_DATA6_REG0A1H			0x0A1
#define AU8522_I2C_RD_DATA7_REG0A2H			0x0A2

#define AU8522_ENA_USB_REG101H				0x101

#define AU8522_I2S_CTRL_0_REG110H  			0x110
#define AU8522_I2S_CTRL_1_REG111H 			0x111
#define AU8522_I2S_CTRL_2_REG112H 			0x112

#define AU8522_FRMREGFFECONTROL_REG121H    		0x121
#define AU8522_FRMREGDFECONTROL_REG122H    		0x122

#define AU8522_CARRFREQOFFSET0_REG201H 			0x201
#define AU8522_CARRFREQOFFSET1_REG202H			0x202

#define AU8522_DECIMATION_GAIN_REG21AH			0x21A
#define AU8522_FRMREGIFSLP_REG21BH 			0x21B
#define AU8522_FRMREGTHRDL2_REG21CH 			0x21C
#define AU8522_FRMREGSTEP3DB_REG21DH 			0x21D
#define AU8522_DAGC_GAIN_ADJUSTMENT_REG21EH		0x21E
#define AU8522_FRMREGPLLMODE_REG21FH 			0x21F
#define AU8522_FRMREGCSTHRD_REG220H 			0x220
#define AU8522_FRMREGCRLOCKDMAX_REG221H 		0x221
#define AU8522_FRMREGCRPERIODMASK_REG222H 		0x222
#define AU8522_FRMREGCRLOCK0THH_REG223H 		0x223
#define AU8522_FRMREGCRLOCK1THH_REG224H 		0x224
#define AU8522_FRMREGCRLOCK0THL_REG225H 		0x225
#define AU8522_FRMREGCRLOCK1THL_REG226H 		0x226
#define AU_FRMREGPLLACQPHASESCL_REG227H			0x227
#define AU8522_FRMREGFREQFBCTRL_REG228H 		0x228

/* Analog TV Decoder */
#define AU8522_TVDEC_STATUS_REG000H			0x000
#define AU8522_TVDEC_INT_STATUS_REG001H			0x001
#define AU8522_TVDEC_MACROVISION_STATUS_REG002H 	0x002
#define AU8522_TVDEC_SHARPNESSREG009H			0x009
#define AU8522_TVDEC_BRIGHTNESS_REG00AH			0x00A
#define AU8522_TVDEC_CONTRAST_REG00BH			0x00B
#define AU8522_TVDEC_SATURATION_CB_REG00CH		0x00C
#define AU8522_TVDEC_SATURATION_CR_REG00DH		0x00D
#define AU8522_TVDEC_HUE_H_REG00EH			0x00E
#define AU8522_TVDEC_HUE_L_REG00FH                   	0x00F
#define AU8522_TVDEC_INT_MASK_REG010H			0x010
#define AU8522_VIDEO_MODE_REG011H			0x011
#define AU8522_TVDEC_PGA_REG012H			0x012
#define AU8522_TVDEC_COMB_MODE_REG015H			0x015
#define AU8522_REG016H                            	0x016
#define AU8522_TVDED_DBG_MODE_REG060H			0x060
#define AU8522_TVDEC_FORMAT_CTRL1_REG061H		0x061
#define AU8522_TVDEC_FORMAT_CTRL2_REG062H		0x062
#define AU8522_TVDEC_VCR_DET_LLIM_REG063H		0x063
#define AU8522_TVDEC_VCR_DET_HLIM_REG064H		0x064
#define AU8522_TVDEC_COMB_VDIF_THR1_REG065H		0x065
#define AU8522_TVDEC_COMB_VDIF_THR2_REG066H		0x066
#define AU8522_TVDEC_COMB_VDIF_THR3_REG067H		0x067
#define AU8522_TVDEC_COMB_NOTCH_THR_REG068H		0x068
#define AU8522_TVDEC_COMB_HDIF_THR1_REG069H   		0x069
#define AU8522_TVDEC_COMB_HDIF_THR2_REG06AH		0x06A
#define AU8522_TVDEC_COMB_HDIF_THR3_REG06BH   		0x06B
#define AU8522_TVDEC_COMB_DCDIF_THR1_REG06CH  		0x06C
#define AU8522_TVDEC_COMB_DCDIF_THR2_REG06DH 		0x06D
#define AU8522_TVDEC_COMB_DCDIF_THR3_REG06EH       	0x06E
#define AU8522_TVDEC_UV_SEP_THR_REG06FH  		0x06F
#define AU8522_TVDEC_COMB_DC_THR1_NTSC_REG070H		0x070
#define AU8522_TVDEC_COMB_DC_THR2_NTSC_REG073H		0x073
#define AU8522_TVDEC_DCAGC_CTRL_REG077H			0x077
#define AU8522_TVDEC_PIC_START_ADJ_REG078H		0x078
#define AU8522_TVDEC_AGC_HIGH_LIMIT_REG079H		0x079
#define AU8522_TVDEC_MACROVISION_SYNC_THR_REG07AH	0x07A
#define AU8522_TVDEC_INTRP_CTRL_REG07BH			0x07B
#define AU8522_TVDEC_PLL_STATUS_REG07EH			0x07E
#define AU8522_TVDEC_FSC_FREQ_REG07FH			0x07F

#define AU8522_TVDEC_AGC_LOW_LIMIT_REG0E4H		0x0E4
#define AU8522_TOREGAAGC_REG0E5H			0x0E5

#define AU8522_TVDEC_CHROMA_AGC_REG401H		0x401
#define AU8522_TVDEC_CHROMA_SFT_REG402H		0x402
#define AU8522_FILTER_COEF_R410     		0x410
#define AU8522_FILTER_COEF_R411     		0x411
#define AU8522_FILTER_COEF_R412     		0x412
#define AU8522_FILTER_COEF_R413     		0x413
#define AU8522_FILTER_COEF_R414     		0x414
#define AU8522_FILTER_COEF_R415     		0x415
#define AU8522_FILTER_COEF_R416     		0x416
#define AU8522_FILTER_COEF_R417     		0x417
#define AU8522_FILTER_COEF_R418     		0x418
#define AU8522_FILTER_COEF_R419     		0x419
#define AU8522_FILTER_COEF_R41A     		0x41A
#define AU8522_FILTER_COEF_R41B     		0x41B
#define AU8522_FILTER_COEF_R41C     		0x41C
#define AU8522_FILTER_COEF_R41D     		0x41D
#define AU8522_FILTER_COEF_R41E     		0x41E
#define AU8522_FILTER_COEF_R41F     		0x41F
#define AU8522_FILTER_COEF_R420     		0x420
#define AU8522_FILTER_COEF_R421     		0x421
#define AU8522_FILTER_COEF_R422     		0x422
#define AU8522_FILTER_COEF_R423     		0x423
#define AU8522_FILTER_COEF_R424     		0x424
#define AU8522_FILTER_COEF_R425     		0x425
#define AU8522_FILTER_COEF_R426     		0x426
#define AU8522_FILTER_COEF_R427     		0x427
#define AU8522_FILTER_COEF_R428     		0x428
#define AU8522_FILTER_COEF_R429     		0x429
#define AU8522_FILTER_COEF_R42A     		0x42A
#define AU8522_FILTER_COEF_R42B     		0x42B
#define AU8522_FILTER_COEF_R42C     		0x42C
#define AU8522_FILTER_COEF_R42D     		0x42D

/* VBI Control Registers */
#define AU8522_TVDEC_VBI_RX_FIFO_CONTAIN_REG004H  	0x004
#define AU8522_TVDEC_VBI_TX_FIFO_CONTAIN_REG005H  	0x005
#define AU8522_TVDEC_VBI_RX_FIFO_READ_REG006H      	0x006
#define AU8522_TVDEC_VBI_FIFO_STATUS_REG007H       	0x007
#define AU8522_TVDEC_VBI_CTRL_H_REG017H			0x017
#define AU8522_TVDEC_VBI_CTRL_L_REG018H			0x018
#define AU8522_TVDEC_VBI_USER_TOTAL_BITS_REG019H	0x019
#define AU8522_TVDEC_VBI_USER_TUNIT_H_REG01AH		0x01A
#define AU8522_TVDEC_VBI_USER_TUNIT_L_REG01BH		0x01B
#define AU8522_TVDEC_VBI_USER_THRESH1_REG01CH		0x01C
#define AU8522_TVDEC_VBI_USER_FRAME_PAT2_REG01EH	0x01E
#define AU8522_TVDEC_VBI_USER_FRAME_PAT1_REG01FH   	0x01F
#define AU8522_TVDEC_VBI_USER_FRAME_PAT0_REG020H   	0x020
#define AU8522_TVDEC_VBI_USER_FRAME_MASK2_REG021H 	0x021
#define AU8522_TVDEC_VBI_USER_FRAME_MASK1_REG022H  	0x022
#define AU8522_TVDEC_VBI_USER_FRAME_MASK0_REG023H	0x023

#define AU8522_REG071H					0x071
#define AU8522_REG072H					0x072
#define AU8522_REG074H					0x074
#define AU8522_REG075H					0x075

/* Digital Demodulator Registers */
#define AU8522_FRAME_COUNT0_REG084H			0x084
#define AU8522_RS_STATUS_G0_REG085H			0x085
#define AU8522_RS_STATUS_B0_REG086H			0x086
#define AU8522_RS_STATUS_E_REG087H			0x087
#define AU8522_DEMODULATION_STATUS_REG088H		0x088
#define AU8522_TOREGTRESTATUS_REG0E6H			0x0E6
#define AU8522_TSPORT_CONTROL_REG10BH			0x10B
#define AU8522_TSTHES_REG10CH				0x10C
#define AU8522_FRMREGDFEKEEP_REG301H			0x301
#define AU8522_DFE_AVERAGE_REG302H			0x302
#define AU8522_FRMREGEQLERRWIN_REG303H			0x303
#define AU8522_FRMREGFFEKEEP_REG304H			0x304
#define AU8522_FRMREGDFECONTROL1_REG305H		0x305
#define AU8522_FRMREGEQLERRLOW_REG306H			0x306

#define AU8522_REG42EH				0x42E
#define AU8522_REG42FH				0x42F
#define AU8522_REG430H				0x430
#define AU8522_REG431H				0x431
#define AU8522_REG432H				0x432
#define AU8522_REG433H				0x433
#define AU8522_REG434H				0x434
#define AU8522_REG435H				0x435
#define AU8522_REG436H				0x436

/* GPIO Registers */
#define AU8522_GPIO_CONTROL_REG0E0H			0x0E0
#define AU8522_GPIO_STATUS_REG0E1H			0x0E1
#define AU8522_GPIO_DATA_REG0E2H			0x0E2

/* Audio Control Registers */
#define AU8522_AUDIOAGC_REG0EEH 			0x0EE
#define AU8522_AUDIO_STATUS_REG0F0H 			0x0F0
#define AU8522_AUDIO_MODE_REG0F1H 			0x0F1
#define AU8522_AUDIO_VOLUME_L_REG0F2H 			0x0F2
#define AU8522_AUDIO_VOLUME_R_REG0F3H 			0x0F3
#define AU8522_AUDIO_VOLUME_REG0F4H 			0x0F4
#define AU8522_FRMREGAUPHASE_REG0F7H 			0x0F7
#define AU8522_REG0F9H					0x0F9

#define AU8522_AUDIOAGC2_REG605H 			0x605
#define AU8522_AUDIOFREQ_REG606H 			0x606


/**************************************************************/

#define AU8522_INPUT_CONTROL_REG081H_ATSC               	0xC4
#define AU8522_INPUT_CONTROL_REG081H_ATVRF			0xC4
#define AU8522_INPUT_CONTROL_REG081H_ATVRF13			0xC4
#define AU8522_INPUT_CONTROL_REG081H_J83B64             	0xC4
#define AU8522_INPUT_CONTROL_REG081H_J83B256            	0xC4
#define AU8522_INPUT_CONTROL_REG081H_CVBS               	0x20
#define AU8522_INPUT_CONTROL_REG081H_CVBS_CH1			0xA2
#define AU8522_INPUT_CONTROL_REG081H_CVBS_CH2			0xA0
#define AU8522_INPUT_CONTROL_REG081H_CVBS_CH3			0x69
#define AU8522_INPUT_CONTROL_REG081H_CVBS_CH4			0x68
#define AU8522_INPUT_CONTROL_REG081H_CVBS_CH4_SIF        	0x28
/* CH1 AS Y,CH3 AS C */
#define AU8522_INPUT_CONTROL_REG081H_SVIDEO_CH13        	0x23
/* CH2 AS Y,CH4 AS C */
#define AU8522_INPUT_CONTROL_REG081H_SVIDEO_CH24        	0x20
#define AU8522_MODULE_CLOCK_CONTROL_REG0A3H_ATSC        	0x0C
#define AU8522_MODULE_CLOCK_CONTROL_REG0A3H_J83B64      	0x09
#define AU8522_MODULE_CLOCK_CONTROL_REG0A3H_J83B256    		0x09
#define AU8522_MODULE_CLOCK_CONTROL_REG0A3H_CVBS        	0x12
#define AU8522_MODULE_CLOCK_CONTROL_REG0A3H_ATVRF       	0x1A
#define AU8522_MODULE_CLOCK_CONTROL_REG0A3H_ATVRF13		0x1A
#define AU8522_MODULE_CLOCK_CONTROL_REG0A3H_SVIDEO		0x02

#define AU8522_SYSTEM_MODULE_CONTROL_0_REG0A4H_CLEAR		0x00
#define AU8522_SYSTEM_MODULE_CONTROL_0_REG0A4H_SVIDEO		0x9C
#define AU8522_SYSTEM_MODULE_CONTROL_0_REG0A4H_CVBS     	0x9D
#define AU8522_SYSTEM_MODULE_CONTROL_0_REG0A4H_ATSC		0xE8
#define AU8522_SYSTEM_MODULE_CONTROL_0_REG0A4H_J83B256 		0xCA
#define AU8522_SYSTEM_MODULE_CONTROL_0_REG0A4H_J83B64  		0xCA
#define AU8522_SYSTEM_MODULE_CONTROL_0_REG0A4H_ATVRF   		0xDD
#define AU8522_SYSTEM_MODULE_CONTROL_0_REG0A4H_ATVRF13		0xDD
#define AU8522_SYSTEM_MODULE_CONTROL_0_REG0A4H_PAL		0xDD
#define AU8522_SYSTEM_MODULE_CONTROL_0_REG0A4H_FM		0xDD

#define AU8522_SYSTEM_MODULE_CONTROL_1_REG0A5H_ATSC		0x80
#define AU8522_SYSTEM_MODULE_CONTROL_1_REG0A5H_J83B256 		0x80
#define AU8522_SYSTEM_MODULE_CONTROL_1_REG0A5H_J83B64  		0x80
#define AU8522_SYSTEM_MODULE_CONTROL_1_REG0A5H_DONGLE_ATSC	0x40
#define AU8522_SYSTEM_MODULE_CONTROL_1_REG0A5H_DONGLE_J83B256	0x40
#define AU8522_SYSTEM_MODULE_CONTROL_1_REG0A5H_DONGLE_J83B64	0x40
#define AU8522_SYSTEM_MODULE_CONTROL_1_REG0A5H_DONGLE_CLEAR	0x00
#define AU8522_SYSTEM_MODULE_CONTROL_1_REG0A5H_ATVRF		0x01
#define AU8522_SYSTEM_MODULE_CONTROL_1_REG0A5H_ATVRF13		0x01
#define AU8522_SYSTEM_MODULE_CONTROL_1_REG0A5H_SVIDEO  		0x04
#define AU8522_SYSTEM_MODULE_CONTROL_1_REG0A5H_CVBS		0x01
#define AU8522_SYSTEM_MODULE_CONTROL_1_REG0A5H_PWM     		0x03
#define AU8522_SYSTEM_MODULE_CONTROL_1_REG0A5H_IIS      	0x09
#define AU8522_SYSTEM_MODULE_CONTROL_1_REG0A5H_PAL		0x01
#define AU8522_SYSTEM_MODULE_CONTROL_1_REG0A5H_FM		0x01

/* STILL NEED TO BE REFACTORED @@@@@@@@@@@@@@ */
#define AU8522_TVDEC_CONTRAST_REG00BH_CVBS			0x79
#define AU8522_TVDEC_SATURATION_CB_REG00CH_CVBS			0x80
#define AU8522_TVDEC_SATURATION_CR_REG00DH_CVBS			0x80
#define AU8522_TVDEC_HUE_H_REG00EH_CVBS				0x00
#define AU8522_TVDEC_HUE_L_REG00FH_CVBS				0x00
#define AU8522_TVDEC_PGA_REG012H_CVBS				0x0F
#define AU8522_TVDEC_COMB_MODE_REG015H_CVBS			0x00
#define AU8522_REG016H_CVBS					0x00
#define AU8522_TVDED_DBG_MODE_REG060H_CVBS			0x00
#define AU8522_TVDEC_FORMAT_CTRL1_REG061H_CVBS			0x0B
#define AU8522_TVDEC_FORMAT_CTRL1_REG061H_CVBS13		0x03
#define AU8522_TVDEC_FORMAT_CTRL2_REG062H_CVBS13		0x00
#define AU8522_TVDEC_VCR_DET_LLIM_REG063H_CVBS			0x19
#define AU8522_REG0F9H_AUDIO					0x20
#define AU8522_TVDEC_VCR_DET_HLIM_REG064H_CVBS			0xA7
#define AU8522_TVDEC_COMB_VDIF_THR1_REG065H_CVBS		0x0A
#define AU8522_TVDEC_COMB_VDIF_THR2_REG066H_CVBS		0x32
#define AU8522_TVDEC_COMB_VDIF_THR3_REG067H_CVBS		0x19
#define AU8522_TVDEC_COMB_NOTCH_THR_REG068H_CVBS		0x23
#define AU8522_TVDEC_COMB_HDIF_THR1_REG069H_CVBS		0x41
#define AU8522_TVDEC_COMB_HDIF_THR2_REG06AH_CVBS		0x0A
#define AU8522_TVDEC_COMB_HDIF_THR3_REG06BH_CVBS		0x32
#define AU8522_TVDEC_COMB_DCDIF_THR1_REG06CH_CVBS		0x34
#define AU8522_TVDEC_COMB_DCDIF_THR1_REG06CH_SVIDEO		0x2a
#define AU8522_TVDEC_COMB_DCDIF_THR2_REG06DH_CVBS		0x05
#define AU8522_TVDEC_COMB_DCDIF_THR2_REG06DH_SVIDEO		0x15
#define AU8522_TVDEC_COMB_DCDIF_THR3_REG06EH_CVBS		0x6E
#define AU8522_TVDEC_UV_SEP_THR_REG06FH_CVBS			0x0F
#define AU8522_TVDEC_COMB_DC_THR1_NTSC_REG070H_CVBS		0x80
#define AU8522_REG071H_CVBS					0x18
#define AU8522_REG072H_CVBS					0x30
#define AU8522_TVDEC_COMB_DC_THR2_NTSC_REG073H_CVBS		0xF0
#define AU8522_REG074H_CVBS					0x80
#define AU8522_REG075H_CVBS					0xF0
#define AU8522_TVDEC_DCAGC_CTRL_REG077H_CVBS			0xFB
#define AU8522_TVDEC_PIC_START_ADJ_REG078H_CVBS			0x04
#define AU8522_TVDEC_AGC_HIGH_LIMIT_REG079H_CVBS		0x00
#define AU8522_TVDEC_MACROVISION_SYNC_THR_REG07AH_CVBS		0x00
#define AU8522_TVDEC_INTRP_CTRL_REG07BH_CVBS			0xEE
#define AU8522_TVDEC_AGC_LOW_LIMIT_REG0E4H_CVBS			0xFE
#define AU8522_TOREGAAGC_REG0E5H_CVBS				0x00
#define AU8522_TVDEC_VBI6A_REG035H_CVBS				0x40

/* Enables Closed captioning */
#define AU8522_TVDEC_VBI_CTRL_H_REG017H_CCON			0x21

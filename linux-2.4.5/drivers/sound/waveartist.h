#include "linux/autoconf.h"
/*
 * linux/drivers/sound/waveartist.h
 *
 * def file for Rockwell RWA010 chip set, as installed in Rebel.com NetWinder
 */

//registers
#define CMDR	0
#define DATR	2
#define CTLR	4
#define	STATR	5
#define	IRQSTAT	12

//bit defs
//reg STATR
#define	CMD_WE	0x80
#define	CMD_RF	0x40
#define	DAT_WE	0x20
#define	DAT_RF	0x10

#define	IRQ_REQ	0x08
#define	DMA1	0x04
#define	DMA0	0x02

//bit defs
//reg CTLR
#define	CMD_WEIE	0x80
#define	CMD_RFIE	0x40
#define	DAT_WEIE	0x20
#define	DAT_RFIE	0x10

#define	RESET	0x08
#define	DMA1_IE	0x04
#define	DMA0_IE	0x02
#define	IRQ_ACK	0x01

//commands

#define	WACMD_SYSTEMID		0x00
#define WACMD_GETREV		0x00
#define	WACMD_INPUTFORMAT	0x10	//0-8S, 1-16S, 2-8U
#define	WACMD_INPUTCHANNELS	0x11	//1-Mono, 2-Stereo
#define	WACMD_INPUTSPEED	0x12	//sampling rate
#define	WACMD_INPUTDMA		0x13	//0-8bit, 1-16bit, 2-PIO
#define	WACMD_INPUTSIZE		0x14	//samples to interrupt
#define	WACMD_INPUTSTART	0x15	//start ADC
#define	WACMD_INPUTPAUSE	0x16	//pause ADC
#define	WACMD_INPUTSTOP		0x17	//stop ADC
#define	WACMD_INPUTRESUME	0x18	//resume ADC
#define	WACMD_INPUTPIO		0x19	//PIO ADC

#define	WACMD_OUTPUTFORMAT	0x20	//0-8S, 1-16S, 2-8U
#define	WACMD_OUTPUTCHANNELS	0x21	//1-Mono, 2-Stereo
#define	WACMD_OUTPUTSPEED	0x22	//sampling rate
#define	WACMD_OUTPUTDMA		0x23	//0-8bit, 1-16bit, 2-PIO
#define	WACMD_OUTPUTSIZE	0x24	//samples to interrupt
#define	WACMD_OUTPUTSTART	0x25	//start ADC
#define	WACMD_OUTPUTPAUSE	0x26	//pause ADC
#define	WACMD_OUTPUTSTOP	0x27	//stop ADC
#define	WACMD_OUTPUTRESUME	0x28	//resume ADC
#define	WACMD_OUTPUTPIO		0x29	//PIO ADC

#define	WACMD_GET_LEVEL		0x30
#define	WACMD_SET_LEVEL		0x31
#define	WACMD_SET_MIXER		0x32
#define	WACMD_RST_MIXER		0x33
#define	WACMD_SET_MONO		0x34

int wa_sendcmd(unsigned int cmd);
int wa_writecmd(unsigned int cmd, unsigned int arg);

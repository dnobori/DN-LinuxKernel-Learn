#include "linux/generated/autoconf.h"
/* ************************************************************************* */
/* This file is autogenerated by IOPASM Version 1.2                          */
/* DO NOT EDIT THIS FILE - All changes will be lost!                         */
/* ************************************************************************* */



#ifndef __IOP_MPU_MACROS_H__
#define __IOP_MPU_MACROS_H__


/* ************************************************************************* */
/*                           REGISTER DEFINITIONS                            */
/* ************************************************************************* */
#define MPU_R0 (0x0)
#define MPU_R1 (0x1)
#define MPU_R2 (0x2)
#define MPU_R3 (0x3)
#define MPU_R4 (0x4)
#define MPU_R5 (0x5)
#define MPU_R6 (0x6)
#define MPU_R7 (0x7)
#define MPU_R8 (0x8)
#define MPU_R9 (0x9)
#define MPU_R10 (0xa)
#define MPU_R11 (0xb)
#define MPU_R12 (0xc)
#define MPU_R13 (0xd)
#define MPU_R14 (0xe)
#define MPU_R15 (0xf)
#define MPU_PC (0x2)
#define MPU_WSTS (0x3)
#define MPU_JADDR (0x4)
#define MPU_IRP (0x5)
#define MPU_SRP (0x6)
#define MPU_T0 (0x8)
#define MPU_T1 (0x9)
#define MPU_T2 (0xa)
#define MPU_T3 (0xb)
#define MPU_I0 (0x10)
#define MPU_I1 (0x11)
#define MPU_I2 (0x12)
#define MPU_I3 (0x13)
#define MPU_I4 (0x14)
#define MPU_I5 (0x15)
#define MPU_I6 (0x16)
#define MPU_I7 (0x17)
#define MPU_I8 (0x18)
#define MPU_I9 (0x19)
#define MPU_I10 (0x1a)
#define MPU_I11 (0x1b)
#define MPU_I12 (0x1c)
#define MPU_I13 (0x1d)
#define MPU_I14 (0x1e)
#define MPU_I15 (0x1f)
#define MPU_P2 (0x2)
#define MPU_P3 (0x3)
#define MPU_P5 (0x5)
#define MPU_P6 (0x6)
#define MPU_P8 (0x8)
#define MPU_P9 (0x9)
#define MPU_P10 (0xa)
#define MPU_P11 (0xb)
#define MPU_P16 (0x10)
#define MPU_P17 (0x12)
#define MPU_P18 (0x12)
#define MPU_P19 (0x13)
#define MPU_P20 (0x14)
#define MPU_P21 (0x15)
#define MPU_P22 (0x16)
#define MPU_P23 (0x17)
#define MPU_P24 (0x18)
#define MPU_P25 (0x19)
#define MPU_P26 (0x1a)
#define MPU_P27 (0x1b)
#define MPU_P28 (0x1c)
#define MPU_P29 (0x1d)
#define MPU_P30 (0x1e)
#define MPU_P31 (0x1f)
#define MPU_P1 (0x1)
#define MPU_REGA (0x1)



/* ************************************************************************* */
/*                              ADDRESS MACROS                               */
/* ************************************************************************* */
#define MK_DWORD_ADDR(ADDR) (ADDR >> 2)
#define MK_BYTE_ADDR(ADDR) (ADDR)



/* ************************************************************************* */
/*                            INSTRUCTION MACROS                             */
/* ************************************************************************* */
#define MPU_ADD_RRR(S,N,D) (0x4000008C | ((S & ((1 << 5) - 1)) << 16)\
                                | ((N & ((1 << 5) - 1)) << 11)\
                                | ((D & ((1 << 5) - 1)) << 21))

#define MPU_ADD_RRS(S,N,D) (0x4000048C | ((S & ((1 << 5) - 1)) << 16)\
                                | ((N & ((1 << 5) - 1)) << 11)\
                                | ((D & ((1 << 5) - 1)) << 21))

#define MPU_ADD_RSR(S,N,D) (0x4000018C | ((S & ((1 << 5) - 1)) << 16)\
                                | ((N & ((1 << 5) - 1)) << 11)\
                                | ((D & ((1 << 5) - 1)) << 21))

#define MPU_ADD_RSS(S,N,D) (0x4000058C | ((S & ((1 << 5) - 1)) << 16)\
                                | ((N & ((1 << 5) - 1)) << 11)\
                                | ((D & ((1 << 5) - 1)) << 21))

#define MPU_ADD_SRR(S,N,D) (0x4000028C | ((S & ((1 << 5) - 1)) << 16)\
                                | ((N & ((1 << 5) - 1)) << 11)\
                                | ((D & ((1 << 5) - 1)) << 21))

#define MPU_ADD_SRS(S,N,D) (0x4000068C | ((S & ((1 << 5) - 1)) << 16)\
                                | ((N & ((1 << 5) - 1)) << 11)\
                                | ((D & ((1 << 5) - 1)) << 21))

#define MPU_ADD_SSR(S,N,D) (0x4000038C | ((S & ((1 << 5) - 1)) << 16)\
                                | ((N & ((1 << 5) - 1)) << 11)\
                                | ((D & ((1 << 5) - 1)) << 21))

#define MPU_ADD_SSS(S,N,D) (0x4000078C | ((S & ((1 << 5) - 1)) << 16)\
                                | ((N & ((1 << 5) - 1)) << 11)\
                                | ((D & ((1 << 5) - 1)) << 21))

#define MPU_ADDQ_RIR(S,N,D) (0x10000000 | ((S & ((1 << 5) - 1)) << 16)\
                                 | ((N & ((1 << 16) - 1)) << 0)\
                                 | ((D & ((1 << 5) - 1)) << 21))

#define MPU_ADDQ_IRR(S,N,D) (0x10000000 | ((S & ((1 << 16) - 1)) << 0)\
                                 | ((N & ((1 << 5) - 1)) << 16)\
                                 | ((D & ((1 << 5) - 1)) << 21))

#define MPU_ADDX_IRR_INSTR(S,N,D) (0xC000008C | ((N & ((1 << 5) - 1)) << 16)\
                                       | ((D & ((1 << 5) - 1)) << 21))

#define MPU_ADDX_IRR_IMM(S,N,D) (S & 0xFFFFFFFF)

#define MPU_ADDX_RIR_INSTR(S,N,D) (0xC000008C | ((S & ((1 << 5) - 1)) << 16)\
                                       | ((D & ((1 << 5) - 1)) << 21))

#define MPU_ADDX_RIR_IMM(S,N,D) (N & 0xFFFFFFFF)

#define MPU_ADDX_ISR_INSTR(S,N,D) (0xC000028C | ((N & ((1 << 5) - 1)) << 16)\
                                       | ((D & ((1 << 5) - 1)) << 21))

#define MPU_ADDX_ISR_IMM(S,N,D) (S & 0xFFFFFFFF)

#define MPU_ADDX_SIR_INSTR(S,N,D) (0xC000028C | ((S & ((1 << 5) - 1)) << 16)\
                                       | ((D & ((1 << 5) - 1)) << 21))

#define MPU_ADDX_SIR_IMM(S,N,D) (N & 0xFFFFFFFF)

#define MPU_ADDX_IRS_INSTR(S,N,D) (0xC000048C | ((N & ((1 << 5) - 1)) << 16)\
                                       | ((D & ((1 << 5) - 1)) << 21))

#define MPU_ADDX_IRS_IMM(S,N,D) (S & 0xFFFFFFFF)

#define MPU_ADDX_RIS_INSTR(S,N,D) (0xC000048C | ((S & ((1 << 5) - 1)) << 16)\
                                       | ((D & ((1 << 5) - 1)) << 21))

#define MPU_ADDX_RIS_IMM(S,N,D) (N & 0xFFFFFFFF)

#define MPU_ADDX_ISS_INSTR(S,N,D) (0xC000068C | ((N & ((1 << 5) - 1)) << 16)\
                                       | ((D & ((1 << 5) - 1)) << 21))

#define MPU_ADDX_ISS_IMM(S,N,D) (S & 0xFFFFFFFF)

#define MPU_ADDX_SIS_INSTR(S,N,D) (0xC000068C | ((S & ((1 << 5) - 1)) << 16)\
                                       | ((D & ((1 << 5) - 1)) << 21))

#define MPU_ADDX_SIS_IMM(S,N,D) (N & 0xFFFFFFFF)

#define MPU_AND_RRR(S,N,D) (0x4000008A | ((S & ((1 << 5) - 1)) << 16)\
                                | ((N & ((1 << 5) - 1)) << 11)\
                                | ((D & ((1 << 5) - 1)) << 21))

#define MPU_AND_RRS(S,N,D) (0x4000048A | ((S & ((1 << 5) - 1)) << 16)\
                                | ((N & ((1 << 5) - 1)) << 11)\
                                | ((D & ((1 << 5) - 1)) << 21))

#define MPU_AND_RSR(S,N,D) (0x4000018A | ((S & ((1 << 5) - 1)) << 16)\
                                | ((N & ((1 << 5) - 1)) << 11)\
                                | ((D & ((1 << 5) - 1)) << 21))

#define MPU_AND_RSS(S,N,D) (0x4000058A | ((S & ((1 << 5) - 1)) << 16)\
                                | ((N & ((1 << 5) - 1)) << 11)\
                                | ((D & ((1 << 5) - 1)) << 21))

#define MPU_AND_SRR(S,N,D) (0x4000028A | ((S & ((1 << 5) - 1)) << 16)\
                                | ((N & ((1 << 5) - 1)) << 11)\
                                | ((D & ((1 << 5) - 1)) << 21))

#define MPU_AND_SRS(S,N,D) (0x4000068A | ((S & ((1 << 5) - 1)) << 16)\
                                | ((N & ((1 << 5) - 1)) << 11)\
                                | ((D & ((1 << 5) - 1)) << 21))

#define MPU_AND_SSR(S,N,D) (0x4000038A | ((S & ((1 << 5) - 1)) << 16)\
                                | ((N & ((1 << 5) - 1)) << 11)\
                                | ((D & ((1 << 5) - 1)) << 21))

#define MPU_AND_SSS(S,N,D) (0x4000078A | ((S & ((1 << 5) - 1)) << 16)\
                                | ((N & ((1 << 5) - 1)) << 11)\
                                | ((D & ((1 << 5) - 1)) << 21))

#define MPU_ANDQ_RIR(S,N,D) (0x08000000 | ((S & ((1 << 5) - 1)) << 16)\
                                 | ((N & ((1 << 16) - 1)) << 0)\
                                 | ((D & ((1 << 5) - 1)) << 21))

#define MPU_ANDQ_IRR(S,N,D) (0x08000000 | ((S & ((1 << 16) - 1)) << 0)\
                                 | ((N & ((1 << 5) - 1)) << 16)\
                                 | ((D & ((1 << 5) - 1)) << 21))

#define MPU_ANDX_RIR_INSTR(S,N,D) (0xC000008A | ((S & ((1 << 5) - 1)) << 16)\
                                       | ((D & ((1 << 5) - 1)) << 21))

#define MPU_ANDX_RIR_IMM(S,N,D) (N & 0xFFFFFFFF)

#define MPU_ANDX_IRR_INSTR(S,N,D) (0xC000008A | ((N & ((1 << 5) - 1)) << 16)\
                                       | ((D & ((1 << 5) - 1)) << 21))

#define MPU_ANDX_IRR_IMM(S,N,D) (S & 0xFFFFFFFF)

#define MPU_ANDX_ISR_INSTR(S,N,D) (0xC000028A | ((N & ((1 << 5) - 1)) << 16)\
                                       | ((D & ((1 << 5) - 1)) << 21))

#define MPU_ANDX_ISR_IMM(S,N,D) (S & 0xFFFFFFFF)

#define MPU_ANDX_SIR_INSTR(S,N,D) (0xC000028A | ((S & ((1 << 5) - 1)) << 16)\
                                       | ((D & ((1 << 5) - 1)) << 21))

#define MPU_ANDX_SIR_IMM(S,N,D) (N & 0xFFFFFFFF)

#define MPU_ANDX_IRS_INSTR(S,N,D) (0xC000048A | ((N & ((1 << 5) - 1)) << 16)\
                                       | ((D & ((1 << 5) - 1)) << 21))

#define MPU_ANDX_IRS_IMM(S,N,D) (S & 0xFFFFFFFF)

#define MPU_ANDX_ISS_INSTR(S,N,D) (0xC000068A | ((N & ((1 << 5) - 1)) << 16)\
                                       | ((D & ((1 << 5) - 1)) << 21))

#define MPU_ANDX_ISS_IMM(S,N,D) (S & 0xFFFFFFFF)

#define MPU_ANDX_RIS_INSTR(S,N,D) (0xC000048A | ((S & ((1 << 5) - 1)) << 16)\
                                       | ((D & ((1 << 5) - 1)) << 21))

#define MPU_ANDX_RIS_IMM(S,N,D) (N & 0xFFFFFFFF)

#define MPU_ANDX_SIS_INSTR(S,N,D) (0xC000068A | ((S & ((1 << 5) - 1)) << 16)\
                                       | ((D & ((1 << 5) - 1)) << 21))

#define MPU_ANDX_SIS_IMM(S,N,D) (N & 0xFFFFFFFF)

#define MPU_BA_I(S) (0x60000000 | ((S & ((1 << 16) - 1)) << 0))

#define MPU_BAR_R(S) (0x62000000 | ((S & ((1 << 5) - 1)) << 11))

#define MPU_BAR_S(S) (0x63000000 | ((S & ((1 << 5) - 1)) << 11))

#define MPU_BBC_RII(S,N,D) (0x78000000 | ((S & ((1 << 5) - 1)) << 16)\
                                | ((N & ((1 << 5) - 1)) << 21)\
                                | ((D & ((1 << 16) - 1)) << 0))

#define MPU_BBS_RII(S,N,D) (0x7C000000 | ((S & ((1 << 5) - 1)) << 16)\
                                | ((N & ((1 << 5) - 1)) << 21)\
                                | ((D & ((1 << 16) - 1)) << 0))

#define MPU_BNZ_RI(S,D) (0x74400000 | ((S & ((1 << 5) - 1)) << 16)\
                             | ((D & ((1 << 16) - 1)) << 0))

#define MPU_BMI_RI(S,D) (0x7FE00000 | ((S & ((1 << 5) - 1)) << 16)\
                             | ((D & ((1 << 16) - 1)) << 0))

#define MPU_BPL_RI(S,D) (0x7BE00000 | ((S & ((1 << 5) - 1)) << 16)\
                             | ((D & ((1 << 16) - 1)) << 0))

#define MPU_BZ_RI(S,D) (0x74000000 | ((S & ((1 << 5) - 1)) << 16)\
                            | ((D & ((1 << 16) - 1)) << 0))

#define MPU_DI() (0x40000001)

#define MPU_EI() (0x40000003)

#define MPU_HALT() (0x40000002)

#define MPU_JIR_I(S) (0x60200000 | ((S & ((1 << 16) - 1)) << 0))

#define MPU_JIR_R(S) (0x62200000 | ((S & ((1 << 5) - 1)) << 11))

#define MPU_JIR_S(S) (0x63200000 | ((S & ((1 << 5) - 1)) << 11))

#define MPU_JNT() (0x61000000)

#define MPU_JSR_I(S) (0x60400000 | ((S & ((1 << 16) - 1)) << 0))

#define MPU_JSR_R(S) (0x62400000 | ((S & ((1 << 5) - 1)) << 11))

#define MPU_JSR_S(S) (0x63400000 | ((S & ((1 << 5) - 1)) << 11))

#define MPU_LSL_RRR(S,N,D) (0x4000008E | ((S & ((1 << 5) - 1)) << 16)\
                                | ((N & ((1 << 5) - 1)) << 11)\
                                | ((D & ((1 << 5) - 1)) << 21))

#define MPU_LSL_RRS(S,N,D) (0x4000048E | ((S & ((1 << 5) - 1)) << 16)\
                                | ((N & ((1 << 5) - 1)) << 11)\
                                | ((D & ((1 << 5) - 1)) << 21))

#define MPU_LSL_RSR(S,N,D) (0x4000018E | ((S & ((1 << 5) - 1)) << 16)\
                                | ((N & ((1 << 5) - 1)) << 11)\
                                | ((D & ((1 << 5) - 1)) << 21))

#define MPU_LSL_RSS(S,N,D) (0x4000058E | ((S & ((1 << 5) - 1)) << 16)\
                                | ((N & ((1 << 5) - 1)) << 11)\
                                | ((D & ((1 << 5) - 1)) << 21))

#define MPU_LSL_SRR(S,N,D) (0x4000028E | ((S & ((1 << 5) - 1)) << 16)\
                                | ((N & ((1 << 5) - 1)) << 11)\
                                | ((D & ((1 << 5) - 1)) << 21))

#define MPU_LSL_SRS(S,N,D) (0x4000068E | ((S & ((1 << 5) - 1)) << 16)\
                                | ((N & ((1 << 5) - 1)) << 11)\
                                | ((D & ((1 << 5) - 1)) << 21))

#define MPU_LSL_SSR(S,N,D) (0x4000038E | ((S & ((1 << 5) - 1)) << 16)\
                                | ((N & ((1 << 5) - 1)) << 11)\
                                | ((D & ((1 << 5) - 1)) << 21))

#define MPU_LSL_SSS(S,N,D) (0x4000078E | ((S & ((1 << 5) - 1)) << 16)\
                                | ((N & ((1 << 5) - 1)) << 11)\
                                | ((D & ((1 << 5) - 1)) << 21))

#define MPU_LSLQ_RIR(S,N,D) (0x18000000 | ((S & ((1 << 5) - 1)) << 16)\
                                 | ((N & ((1 << 16) - 1)) << 0)\
                                 | ((D & ((1 << 5) - 1)) << 21))

#define MPU_LSR_RRR(S,N,D) (0x4000008F | ((S & ((1 << 5) - 1)) << 16)\
                                | ((N & ((1 << 5) - 1)) << 11)\
                                | ((D & ((1 << 5) - 1)) << 21))

#define MPU_LSR_RRS(S,N,D) (0x4000048F | ((S & ((1 << 5) - 1)) << 16)\
                                | ((N & ((1 << 5) - 1)) << 11)\
                                | ((D & ((1 << 5) - 1)) << 21))

#define MPU_LSR_RSR(S,N,D) (0x4000018F | ((S & ((1 << 5) - 1)) << 16)\
                                | ((N & ((1 << 5) - 1)) << 11)\
                                | ((D & ((1 << 5) - 1)) << 21))

#define MPU_LSR_RSS(S,N,D) (0x4000058F | ((S & ((1 << 5) - 1)) << 16)\
                                | ((N & ((1 << 5) - 1)) << 11)\
                                | ((D & ((1 << 5) - 1)) << 21))

#define MPU_LSR_SRR(S,N,D) (0x4000028F | ((S & ((1 << 5) - 1)) << 16)\
                                | ((N & ((1 << 5) - 1)) << 11)\
                                | ((D & ((1 << 5) - 1)) << 21))

#define MPU_LSR_SRS(S,N,D) (0x4000068F | ((S & ((1 << 5) - 1)) << 16)\
                                | ((N & ((1 << 5) - 1)) << 11)\
                                | ((D & ((1 << 5) - 1)) << 21))

#define MPU_LSR_SSR(S,N,D) (0x4000038F | ((S & ((1 << 5) - 1)) << 16)\
                                | ((N & ((1 << 5) - 1)) << 11)\
                                | ((D & ((1 << 5) - 1)) << 21))

#define MPU_LSR_SSS(S,N,D) (0x4000078F | ((S & ((1 << 5) - 1)) << 16)\
                                | ((N & ((1 << 5) - 1)) << 11)\
                                | ((D & ((1 << 5) - 1)) << 21))

#define MPU_LSRQ_RIR(S,N,D) (0x1C000000 | ((S & ((1 << 5) - 1)) << 16)\
                                 | ((N & ((1 << 16) - 1)) << 0)\
                                 | ((D & ((1 << 5) - 1)) << 21))

#define MPU_LW_IR(S,D) (0x64400000 | ((S & ((1 << 16) - 1)) << 0)\
                            | ((D & ((1 << 5) - 1)) << 16))

#define MPU_LW_IS(S,D) (0x64600000 | ((S & ((1 << 16) - 1)) << 0)\
                            | ((D & ((1 << 5) - 1)) << 16))

#define MPU_LW_RR(S,D) (0x66400000 | ((S & ((1 << 5) - 1)) << 11)\
                            | ((D & ((1 << 5) - 1)) << 16))

#define MPU_LW_RS(S,D) (0x66600000 | ((S & ((1 << 5) - 1)) << 11)\
                            | ((D & ((1 << 5) - 1)) << 16))

#define MPU_LW_SR(S,D) (0x67400000 | ((S & ((1 << 5) - 1)) << 11)\
                            | ((D & ((1 << 5) - 1)) << 16))

#define MPU_LW_SS(S,D) (0x67600000 | ((S & ((1 << 5) - 1)) << 11)\
                            | ((D & ((1 << 5) - 1)) << 16))

#define MPU_LW_RIR(S,N,D) (0x66400000 | ((S & ((1 << 5) - 1)) << 11)\
                               | ((N & ((1 << 8) - 1)) << 0)\
                               | ((D & ((1 << 5) - 1)) << 16))

#define MPU_LW_RIS(S,N,D) (0x66600000 | ((S & ((1 << 5) - 1)) << 11)\
                               | ((N & ((1 << 8) - 1)) << 0)\
                               | ((D & ((1 << 5) - 1)) << 16))

#define MPU_LW_SIR(S,N,D) (0x67400000 | ((S & ((1 << 5) - 1)) << 11)\
                               | ((N & ((1 << 8) - 1)) << 0)\
                               | ((D & ((1 << 5) - 1)) << 16))

#define MPU_LW_SIS(S,N,D) (0x67600000 | ((S & ((1 << 5) - 1)) << 11)\
                               | ((N & ((1 << 8) - 1)) << 0)\
                               | ((D & ((1 << 5) - 1)) << 16))

#define MPU_MOVE_RR(S,D) (0x40000081 | ((S & ((1 << 5) - 1)) << 11)\
                              | ((D & ((1 << 5) - 1)) << 21))

#define MPU_MOVE_RS(S,D) (0x40000481 | ((S & ((1 << 5) - 1)) << 11)\
                              | ((D & ((1 << 5) - 1)) << 21))

#define MPU_MOVE_SR(S,D) (0x40000181 | ((S & ((1 << 5) - 1)) << 11)\
                              | ((D & ((1 << 5) - 1)) << 21))

#define MPU_MOVE_SS(S,D) (0x40000581 | ((S & ((1 << 5) - 1)) << 11)\
                              | ((D & ((1 << 5) - 1)) << 21))

#define MPU_MOVEQ_IR(S,D) (0x24000000 | ((S & ((1 << 16) - 1)) << 0)\
                               | ((D & ((1 << 5) - 1)) << 21))

#define MPU_MOVEQ_IS(S,D) (0x2C000000 | ((S & ((1 << 16) - 1)) << 0)\
                               | ((D & ((1 << 5) - 1)) << 21))

#define MPU_MOVEX_IR_INSTR(S,D) (0xC0000081 | ((D & ((1 << 5) - 1)) << 21))

#define MPU_MOVEX_IR_IMM(S,D) (S & 0xFFFFFFFF)

#define MPU_MOVEX_IS_INSTR(S,D) (0xC0000481 | ((D & ((1 << 5) - 1)) << 21))

#define MPU_MOVEX_IS_IMM(S,D) (S & 0xFFFFFFFF)

#define MPU_NOP() (0x40000000)

#define MPU_NOT_RR(S,D) (0x40100081 | ((S & ((1 << 5) - 1)) << 11)\
                             | ((D & ((1 << 5) - 1)) << 21))

#define MPU_NOT_RS(S,D) (0x40100481 | ((S & ((1 << 5) - 1)) << 11)\
                             | ((D & ((1 << 5) - 1)) << 21))

#define MPU_NOT_SR(S,D) (0x40100181 | ((S & ((1 << 5) - 1)) << 11)\
                             | ((D & ((1 << 5) - 1)) << 21))

#define MPU_NOT_SS(S,D) (0x40100581 | ((S & ((1 << 5) - 1)) << 11)\
                             | ((D & ((1 << 5) - 1)) << 21))

#define MPU_OR_RRR(S,N,D) (0x4000008B | ((S & ((1 << 5) - 1)) << 16)\
                               | ((N & ((1 << 5) - 1)) << 11)\
                               | ((D & ((1 << 5) - 1)) << 21))

#define MPU_OR_RRS(S,N,D) (0x4000048B | ((S & ((1 << 5) - 1)) << 16)\
                               | ((N & ((1 << 5) - 1)) << 11)\
                               | ((D & ((1 << 5) - 1)) << 21))

#define MPU_OR_RSR(S,N,D) (0x4000018B | ((S & ((1 << 5) - 1)) << 16)\
                               | ((N & ((1 << 5) - 1)) << 11)\
                               | ((D & ((1 << 5) - 1)) << 21))

#define MPU_OR_RSS(S,N,D) (0x4000058B | ((S & ((1 << 5) - 1)) << 16)\
                               | ((N & ((1 << 5) - 1)) << 11)\
                               | ((D & ((1 << 5) - 1)) << 21))

#define MPU_OR_SRR(S,N,D) (0x4000028B | ((S & ((1 << 5) - 1)) << 16)\
                               | ((N & ((1 << 5) - 1)) << 11)\
                               | ((D & ((1 << 5) - 1)) << 21))

#define MPU_OR_SRS(S,N,D) (0x4000068B | ((S & ((1 << 5) - 1)) << 16)\
                               | ((N & ((1 << 5) - 1)) << 11)\
                               | ((D & ((1 << 5) - 1)) << 21))

#define MPU_OR_SSR(S,N,D) (0x4000038B | ((S & ((1 << 5) - 1)) << 16)\
                               | ((N & ((1 << 5) - 1)) << 11)\
                               | ((D & ((1 << 5) - 1)) << 21))

#define MPU_OR_SSS(S,N,D) (0x4000078B | ((S & ((1 << 5) - 1)) << 16)\
                               | ((N & ((1 << 5) - 1)) << 11)\
                               | ((D & ((1 << 5) - 1)) << 21))

#define MPU_ORQ_RIR(S,N,D) (0x0C000000 | ((S & ((1 << 5) - 1)) << 16)\
                                | ((N & ((1 << 16) - 1)) << 0)\
                                | ((D & ((1 << 5) - 1)) << 21))

#define MPU_ORQ_IRR(S,N,D) (0x0C000000 | ((S & ((1 << 16) - 1)) << 0)\
                                | ((N & ((1 << 5) - 1)) << 16)\
                                | ((D & ((1 << 5) - 1)) << 21))

#define MPU_ORX_RIR_INSTR(S,N,D) (0xC000008B | ((S & ((1 << 5) - 1)) << 16)\
                                      | ((D & ((1 << 5) - 1)) << 21))

#define MPU_ORX_RIR_IMM(S,N,D) (N & 0xFFFFFFFF)

#define MPU_ORX_IRR_INSTR(S,N,D) (0xC000008B | ((N & ((1 << 5) - 1)) << 16)\
                                      | ((D & ((1 << 5) - 1)) << 21))

#define MPU_ORX_IRR_IMM(S,N,D) (S & 0xFFFFFFFF)

#define MPU_ORX_SIR_INSTR(S,N,D) (0xC000028B | ((S & ((1 << 5) - 1)) << 16)\
                                      | ((D & ((1 << 5) - 1)) << 21))

#define MPU_ORX_SIR_IMM(S,N,D) (N & 0xFFFFFFFF)

#define MPU_ORX_ISR_INSTR(S,N,D) (0xC000028B | ((N & ((1 << 5) - 1)) << 16)\
                                      | ((D & ((1 << 5) - 1)) << 21))

#define MPU_ORX_ISR_IMM(S,N,D) (S & 0xFFFFFFFF)

#define MPU_ORX_RIS_INSTR(S,N,D) (0xC000048B | ((S & ((1 << 5) - 1)) << 16)\
                                      | ((D & ((1 << 5) - 1)) << 21))

#define MPU_ORX_RIS_IMM(S,N,D) (N & 0xFFFFFFFF)

#define MPU_ORX_IRS_INSTR(S,N,D) (0xC000048B | ((N & ((1 << 5) - 1)) << 16)\
                                      | ((D & ((1 << 5) - 1)) << 21))

#define MPU_ORX_IRS_IMM(S,N,D) (S & 0xFFFFFFFF)

#define MPU_ORX_SIS_INSTR(S,N,D) (0xC000068B | ((S & ((1 << 5) - 1)) << 16)\
                                      | ((D & ((1 << 5) - 1)) << 21))

#define MPU_ORX_SIS_IMM(S,N,D) (N & 0xFFFFFFFF)

#define MPU_ORX_ISS_INSTR(S,N,D) (0xC000068B | ((N & ((1 << 5) - 1)) << 16)\
                                      | ((D & ((1 << 5) - 1)) << 21))

#define MPU_ORX_ISS_IMM(S,N,D) (S & 0xFFFFFFFF)

#define MPU_RET() (0x63003000)

#define MPU_RETI() (0x63602800)

#define MPU_RR_IR(S,D) (0x50000000 | ((S & ((1 << 11) - 1)) << 0)\
                            | ((D & ((1 << 5) - 1)) << 21))

#define MPU_RR_SR(S,D) (0x50008000 | ((S & ((1 << 5) - 1)) << 16)\
                            | ((D & ((1 << 5) - 1)) << 21))

#define MPU_RW_RI(S,D) (0x56000000 | ((S & ((1 << 5) - 1)) << 11)\
                            | ((D & ((1 << 11) - 1)) << 0))

#define MPU_RW_RS(S,D) (0x57000000 | ((S & ((1 << 5) - 1)) << 11)\
                            | ((D & ((1 << 5) - 1)) << 16))

#define MPU_RWQ_II(S,D) (0x58000000 | ((S & ((1 << 16) - 1)) << 11)\
                             | ((D & ((1 << 11) - 1)) << 0))

#define MPU_RWQ_IS(S,D) (0x55000000 | ((S & ((1 << 16) - 1)) << 0)\
                             | ((D & ((1 << 5) - 1)) << 16))

#define MPU_RWX_II_INSTR(S,D) (0xD4000000 | ((D & ((1 << 11) - 1)) << 0))

#define MPU_RWX_II_IMM(S,D) (S & 0xFFFFFFFF)

#define MPU_RWX_IS_INSTR(S,D) (0xD5000000 | ((D & ((1 << 5) - 1)) << 16))

#define MPU_RWX_IS_IMM(S,D) (S & 0xFFFFFFFF)

#define MPU_SUB_RRR(S,N,D) (0x4000008D | ((S & ((1 << 5) - 1)) << 16)\
                                | ((N & ((1 << 5) - 1)) << 11)\
                                | ((D & ((1 << 5) - 1)) << 21))

#define MPU_SUB_RRS(S,N,D) (0x4000048D | ((S & ((1 << 5) - 1)) << 16)\
                                | ((N & ((1 << 5) - 1)) << 11)\
                                | ((D & ((1 << 5) - 1)) << 21))

#define MPU_SUB_RSR(S,N,D) (0x4000018D | ((S & ((1 << 5) - 1)) << 16)\
                                | ((N & ((1 << 5) - 1)) << 11)\
                                | ((D & ((1 << 5) - 1)) << 21))

#define MPU_SUB_RSS(S,N,D) (0x4000058D | ((S & ((1 << 5) - 1)) << 16)\
                                | ((N & ((1 << 5) - 1)) << 11)\
                                | ((D & ((1 << 5) - 1)) << 21))

#define MPU_SUB_SRR(S,N,D) (0x4000028D | ((S & ((1 << 5) - 1)) << 16)\
                                | ((N & ((1 << 5) - 1)) << 11)\
                                | ((D & ((1 << 5) - 1)) << 21))

#define MPU_SUB_SRS(S,N,D) (0x4000068D | ((S & ((1 << 5) - 1)) << 16)\
                                | ((N & ((1 << 5) - 1)) << 11)\
                                | ((D & ((1 << 5) - 1)) << 21))

#define MPU_SUB_SSR(S,N,D) (0x4000038D | ((S & ((1 << 5) - 1)) << 16)\
                                | ((N & ((1 << 5) - 1)) << 11)\
                                | ((D & ((1 << 5) - 1)) << 21))

#define MPU_SUB_SSS(S,N,D) (0x4000078D | ((S & ((1 << 5) - 1)) << 16)\
                                | ((N & ((1 << 5) - 1)) << 11)\
                                | ((D & ((1 << 5) - 1)) << 21))

#define MPU_SUBQ_RIR(S,N,D) (0x14000000 | ((S & ((1 << 5) - 1)) << 16)\
                                 | ((N & ((1 << 16) - 1)) << 0)\
                                 | ((D & ((1 << 5) - 1)) << 21))

#define MPU_SUBX_RIR_INSTR(S,N,D) (0xC000008D | ((S & ((1 << 5) - 1)) << 16)\
                                       | ((D & ((1 << 5) - 1)) << 21))

#define MPU_SUBX_RIR_IMM(S,N,D) (N & 0xFFFFFFFF)

#define MPU_SUBX_SIR_INSTR(S,N,D) (0xC000028D | ((S & ((1 << 5) - 1)) << 16)\
                                       | ((D & ((1 << 5) - 1)) << 21))

#define MPU_SUBX_SIR_IMM(S,N,D) (N & 0xFFFFFFFF)

#define MPU_SUBX_RIS_INSTR(S,N,D) (0xC000048D | ((S & ((1 << 5) - 1)) << 16)\
                                       | ((D & ((1 << 5) - 1)) << 21))

#define MPU_SUBX_RIS_IMM(S,N,D) (N & 0xFFFFFFFF)

#define MPU_SUBX_SIS_INSTR(S,N,D) (0xC000068D | ((S & ((1 << 5) - 1)) << 16)\
                                       | ((D & ((1 << 5) - 1)) << 21))

#define MPU_SUBX_SIS_IMM(S,N,D) (N & 0xFFFFFFFF)

#define MPU_SW_RI(S,D) (0x64000000 | ((S & ((1 << 5) - 1)) << 16)\
                            | ((D & ((1 << 16) - 1)) << 0))

#define MPU_SW_SI(S,D) (0x64200000 | ((S & ((1 << 5) - 1)) << 16)\
                            | ((D & ((1 << 16) - 1)) << 0))

#define MPU_SW_RR(S,D) (0x66000000 | ((S & ((1 << 5) - 1)) << 16)\
                            | ((D & ((1 << 5) - 1)) << 11))

#define MPU_SW_SR(S,D) (0x66200000 | ((S & ((1 << 5) - 1)) << 16)\
                            | ((D & ((1 << 5) - 1)) << 11))

#define MPU_SW_RS(S,D) (0x67000000 | ((S & ((1 << 5) - 1)) << 16)\
                            | ((D & ((1 << 5) - 1)) << 11))

#define MPU_SW_SS(S,D) (0x67200000 | ((S & ((1 << 5) - 1)) << 16)\
                            | ((D & ((1 << 5) - 1)) << 11))

#define MPU_SW_RIR(S,N,D) (0x66000000 | ((S & ((1 << 5) - 1)) << 16)\
                               | ((N & ((1 << 8) - 1)) << 0)\
                               | ((D & ((1 << 5) - 1)) << 11))

#define MPU_SW_SIR(S,N,D) (0x66200000 | ((S & ((1 << 5) - 1)) << 16)\
                               | ((N & ((1 << 8) - 1)) << 0)\
                               | ((D & ((1 << 5) - 1)) << 11))

#define MPU_SW_RIS(S,N,D) (0x67000000 | ((S & ((1 << 5) - 1)) << 16)\
                               | ((N & ((1 << 8) - 1)) << 0)\
                               | ((D & ((1 << 5) - 1)) << 11))

#define MPU_SW_SIS(S,N,D) (0x67200000 | ((S & ((1 << 5) - 1)) << 16)\
                               | ((N & ((1 << 8) - 1)) << 0)\
                               | ((D & ((1 << 5) - 1)) << 11))

#define MPU_SWX_II_INSTR(S,D) (0xE4000000 | ((D & ((1 << 16) - 1)) << 0))

#define MPU_SWX_II_IMM(S,D) (S & 0xFFFFFFFF)

#define MPU_SWX_IR_INSTR(S,D) (0xE6000000 | ((D & ((1 << 5) - 1)) << 11))

#define MPU_SWX_IR_IMM(S,D) (S & 0xFFFFFFFF)

#define MPU_SWX_IS_INSTR(S,D) (0xE7000000 | ((D & ((1 << 5) - 1)) << 11))

#define MPU_SWX_IS_IMM(S,D) (S & 0xFFFFFFFF)

#define MPU_SWX_IIR_INSTR(S,N,D) (0xE6000000 | ((N & ((1 << 8) - 1)) << 0)\
                                      | ((D & ((1 << 5) - 1)) << 11))

#define MPU_SWX_IIR_IMM(S,N,D) (S & 0xFFFFFFFF)

#define MPU_SWX_IIS_INSTR(S,N,D) (0xE7000000 | ((N & ((1 << 8) - 1)) << 0)\
                                      | ((D & ((1 << 5) - 1)) << 11))

#define MPU_SWX_IIS_IMM(S,N,D) (S & 0xFFFFFFFF)

#define MPU_XOR_RRR(S,N,D) (0x40000089 | ((S & ((1 << 5) - 1)) << 16)\
                                | ((N & ((1 << 5) - 1)) << 11)\
                                | ((D & ((1 << 5) - 1)) << 21))

#define MPU_XOR_RRS(S,N,D) (0x40000489 | ((S & ((1 << 5) - 1)) << 16)\
                                | ((N & ((1 << 5) - 1)) << 11)\
                                | ((D & ((1 << 5) - 1)) << 21))

#define MPU_XOR_RSR(S,N,D) (0x40000189 | ((S & ((1 << 5) - 1)) << 16)\
                                | ((N & ((1 << 5) - 1)) << 11)\
                                | ((D & ((1 << 5) - 1)) << 21))

#define MPU_XOR_RSS(S,N,D) (0x40000589 | ((S & ((1 << 5) - 1)) << 16)\
                                | ((N & ((1 << 5) - 1)) << 11)\
                                | ((D & ((1 << 5) - 1)) << 21))

#define MPU_XOR_SRR(S,N,D) (0x40000289 | ((S & ((1 << 5) - 1)) << 16)\
                                | ((N & ((1 << 5) - 1)) << 11)\
                                | ((D & ((1 << 5) - 1)) << 21))

#define MPU_XOR_SRS(S,N,D) (0x40000689 | ((S & ((1 << 5) - 1)) << 16)\
                                | ((N & ((1 << 5) - 1)) << 11)\
                                | ((D & ((1 << 5) - 1)) << 21))

#define MPU_XOR_SSR(S,N,D) (0x40000389 | ((S & ((1 << 5) - 1)) << 16)\
                                | ((N & ((1 << 5) - 1)) << 11)\
                                | ((D & ((1 << 5) - 1)) << 21))

#define MPU_XOR_SSS(S,N,D) (0x40000789 | ((S & ((1 << 5) - 1)) << 16)\
                                | ((N & ((1 << 5) - 1)) << 11)\
                                | ((D & ((1 << 5) - 1)) << 21))

#define MPU_XOR_RR(S,D) (0x40000088 | ((S & ((1 << 5) - 1)) << 11)\
                             | ((D & ((1 << 5) - 1)) << 21))

#define MPU_XOR_RS(S,D) (0x40000488 | ((S & ((1 << 5) - 1)) << 11)\
                             | ((D & ((1 << 5) - 1)) << 21))

#define MPU_XOR_SR(S,D) (0x40000188 | ((S & ((1 << 5) - 1)) << 11)\
                             | ((D & ((1 << 5) - 1)) << 21))

#define MPU_XOR_SS(S,D) (0x40000588 | ((S & ((1 << 5) - 1)) << 11)\
                             | ((D & ((1 << 5) - 1)) << 21))

#define MPU_XORQ_RIR(S,N,D) (0x04000000 | ((S & ((1 << 5) - 1)) << 16)\
                                 | ((N & ((1 << 16) - 1)) << 0)\
                                 | ((D & ((1 << 5) - 1)) << 21))

#define MPU_XORQ_IRR(S,N,D) (0x04000000 | ((S & ((1 << 16) - 1)) << 0)\
                                 | ((N & ((1 << 5) - 1)) << 16)\
                                 | ((D & ((1 << 5) - 1)) << 21))

#define MPU_XORX_RIR_INSTR(S,N,D) (0xC0000089 | ((S & ((1 << 5) - 1)) << 16)\
                                       | ((D & ((1 << 5) - 1)) << 21))

#define MPU_XORX_RIR_IMM(S,N,D) (N & 0xFFFFFFFF)

#define MPU_XORX_IRR_INSTR(S,N,D) (0xC0000089 | ((N & ((1 << 5) - 1)) << 16)\
                                       | ((D & ((1 << 5) - 1)) << 21))

#define MPU_XORX_IRR_IMM(S,N,D) (S & 0xFFFFFFFF)

#define MPU_XORX_SIR_INSTR(S,N,D) (0xC0000289 | ((S & ((1 << 5) - 1)) << 16)\
                                       | ((D & ((1 << 5) - 1)) << 21))

#define MPU_XORX_SIR_IMM(S,N,D) (N & 0xFFFFFFFF)

#define MPU_XORX_ISR_INSTR(S,N,D) (0xC0000289 | ((N & ((1 << 5) - 1)) << 16)\
                                       | ((D & ((1 << 5) - 1)) << 21))

#define MPU_XORX_ISR_IMM(S,N,D) (S & 0xFFFFFFFF)

#define MPU_XORX_RIS_INSTR(S,N,D) (0xC0000489 | ((S & ((1 << 5) - 1)) << 16)\
                                       | ((D & ((1 << 5) - 1)) << 21))

#define MPU_XORX_RIS_IMM(S,N,D) (N & 0xFFFFFFFF)

#define MPU_XORX_IRS_INSTR(S,N,D) (0xC0000489 | ((N & ((1 << 5) - 1)) << 16)\
                                       | ((D & ((1 << 5) - 1)) << 21))

#define MPU_XORX_IRS_IMM(S,N,D) (S & 0xFFFFFFFF)

#define MPU_XORX_SIS_INSTR(S,N,D) (0xC0000689 | ((S & ((1 << 5) - 1)) << 16)\
                                       | ((D & ((1 << 5) - 1)) << 21))

#define MPU_XORX_SIS_IMM(S,N,D) (N & 0xFFFFFFFF)

#define MPU_XORX_ISS_INSTR(S,N,D) (0xC0000689 | ((N & ((1 << 5) - 1)) << 16)\
                                       | ((D & ((1 << 5) - 1)) << 21))

#define MPU_XORX_ISS_IMM(S,N,D) (S & 0xFFFFFFFF)


#endif /* end of __IOP_MPU_MACROS_H__ */
/* End of iop_mpu_macros.h */

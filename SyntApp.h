/*******************************************************************************
File name: SyntApp.c                                                        ****
File description:   TX and RX Synthesizers (ADF-5355) Application manager.  ****
MCU:                PIC18F45k22                                             ****
Date modified: 28/01/2018 16:14.                                            ****
Author: RoeeZ (Comm-IT).                                                    ****
*******************************************************************************/

#ifndef SYNTAPP_H
#define	SYNTAPP_H

#include "SystemCommon.h"

#define SYNTH_DELAY_BETWEEN_WORDS_MSEC 250

#define REG_DATA_BYTES_SIZE 6
#define NUM_OF_REGISTERS 13

// Stored registers
#define SYNTH_REG_10    0xC0193A    
#define SYNTH_REG_06    0x35006076
#define SYNTH_REG_04    0x30008384

// Registers params:
#define SYNTH_F_PFD     40.0
#define SYNTH_MOD1      16777216
#define SYNTH_MOD2      0x15550     // MOD2(5461) << 4
#define SYNTH_AUTOCAL   0x200000

// Registers will be write on opposite direction.
const uint32_t PLL_INIT_REGISTERS[13] = 
{
    0x0001041C,     /* R12  */
    0x0061300B,     /* R11  */
    0x00C0323A,     /* R10  */
    0x2221BCC9,     /* R09  */
    0x102D0428,     /* R08  */
    0x120000E7,     /* R07  */
    0x35012076,     /* R06  */
    0x00800025,     /* R05  */
    0x34009B84,     /* R04  */
    0x00000003,     /* R03  */
    0x00000012,     /* R02  */
    0x06000001,     /* R01  */
    0x00200340      /* R00  */
};  

void PLLUartInitialize(char* data);
void PLLInitialize(void);

void UpdateSynthFreq(MODULE_TYPE cType, char* data);
bool CalcSynthRegParams(int32_t* regArray, int32_t inputFreq);

#endif	/* SYNTAPP_H */


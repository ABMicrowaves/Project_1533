/*******************************************************************************
File name: SystemCommon.c                                                   ****
File description:   Include MCU run-time system common parameters           ****
 *                  and functions.                                          ****
MCU:                PIC18F45k22                                             ****
Date modified: 28/01/2018 16:14.                                            ****
Author: RoeeZ (Comm-IT).                                                    ****
****************************************************************************** */

#ifndef SYSTEMCOMMON_H
#define	SYSTEMCOMMON_H

#include <math.h>
#include <stdint.h>
#include <ctype.h>
#include <stdio.h>

typedef enum
{
	TX_TYPE,
	RX_TYPE,
}MODULE_TYPE;

typedef enum
{
    SYNTH_TX = 0,
    SYNTH_RX,
    EXT_DAC
}SPI_PERIPHERAL;

#include "mcc_generated_files/mcc.h"
#include "MessageFunctions.h"
#include "FlashApp.h"
#include "AdcApp.h"
#include "DacApp.h"
#include "EusartApp.h"
#include "SevenSegmentApp.h"
#include "SyntApp.h"
#include "LedsApp.h"
#include "SyntApp.h"
#include "SwSpiApp.h"

// define special types
#define ULONG uint32_t
#define UCHAR uint8_t
#define MAX_UART_BYTES_SIZE         8
#define END_UART_STREAM_CHAR        0x40
#define NUM_OF_BITS_SYNTH_REG       32


unsigned char crc8(char* dataArray, int dataSize);
uint8_t make8(uint32_t data, uint8_t dataLocation);
void ZeroArray(char* array, int size);
uint32_t GetIntFromUartData(char* data);
void Make32bitsArray(bool* array, uint32_t data);

void StoreIntInEeprom(uint32_t data, uint8_t address, int numOfByes);
uint32_t ReadIntFromEeprom(uint8_t address, int numOfByes);

// System common functions
void ResetMcu(void);
void SendSystemStartAck(void);
void set_system_type(char* data);
void SetUartRefrashRate (char* data);
void SetUartMode (char* data);
#endif	/* SYSTEMCOMMON_H */


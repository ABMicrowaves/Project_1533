/*******************************************************************************
File name: EusartApp.h                                                      ****
File description:   EUASRT driver application manager.                      ****
MCU:                PIC18F45k22                                             ****
Date modified: 28/01/2018 16:14.                                            ****
Author: RoeeZ (Comm-IT).                                                    ****
*******************************************************************************/

#ifndef EUSARTAPP_H
#define	EUSARTAPP_H

#include <string.h>
#include "SystemCommon.h"
#include <stdlib.h>


#define MSG_MAGIC_A                 (0x24)    // 0x24 == '$'
#define CHAR_CARRIAGE_RETURN        (0xd)
#define DELAY_BETWEEN_MESSAGE_READ  (500)
#define MIN_RX_MSG_SIZE             (0x4)
#define MSG_RX_MAX_DATA_SIZE        (0x14)

// Locations
#define MSG_MAGIC_LOCATION          (0x0)
#define MSG_GROUP_LOCATION          (0x1)
#define MSG_REQUEST_LOCATION        (0x2)
#define MSG_DATA_SIZE_LOCATION      (0x0)
#define MSG_DATA_LOCATION           (0x2)


// ACK message
#define ACK_MESSAGE_PACKET_SIZE     (0x5)

typedef enum
{
    FLASH_RAW_DATA = 64,
}TX_MESSAGE_TYPE;

typedef enum
{
    START_RX_MESSAGE_READ = 0,
	FIND_MAGIC,
    READ_STREAM,
    READ_GROUP,
    READ_REQUEST,
    READ_DATA_SIZE,
	READ_DATA,
    CHECK_CRC,
    JUMP_FUNCTION
}UART_READ_STATE;


// RX routines:
void readUartByte(void);
void InitRxMessageParams(void);

// TX routines:
void WriteUartMessage(char* dataBuf, int dataSize);
void SendAckMessage(MSG_GROUPS inGroup, MSG_REQUEST inRequest);
void UART_Write_Text(char* text);
#endif	/* EUSARTAPP_H */


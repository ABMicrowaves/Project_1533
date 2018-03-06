/*******************************************************************************
File name: EusartApp.c                                                      ****
File description:   EUASRT driver application manager.                      ****
MCU:                PIC18F45k22                                             ****
Date modified: 28/01/2018 16:14.                                            ****
Author: RoeeZ (Comm-IT).                                                    ****
****************************************************************************** */

#include "EusartApp.h"

// <editor-fold defaultstate="collapsed" desc="Global verbs">

// Define global message parameters:

static UART_READ_STATE cState = START_RX_MESSAGE_READ;

char rxMsgQueue[MSG_RX_MAX_DATA_SIZE];
char rxMsgData[MSG_RX_MAX_DATA_SIZE];
static uint8_t msgCount = 0;
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="EUSART read packet">

void readUartByte(void)
// Since we read byte by byte from MCC UART driver we need to implement FSM
{    
    UCHAR chRec = NULL, c1 = NULL, c2 = NULL;
    switch(cState)
    {
        case START_RX_MESSAGE_READ:
            
            InitRxMessageParams();
            cState = FIND_MAGIC;
            break;
            
            
        case FIND_MAGIC:
            chRec = EUSART1_Read();
            
            if(chRec == MSG_MAGIC_A)
            {
                cState = READ_DATA;
            }
            break;
            
        case READ_DATA:
            
            rxMsgQueue[msgCount++] = chRec;
            if(chRec == MSG_CARRIAGE_RETURN)
            {
                cState = JUMP_FUNCTION;
            }
            break;
            
        case JUMP_FUNCTION:
            c1 = toupper(rxMsgQueue[0]);
            
            switch(c1)
            {
                case 'Q':
                    
                    break;
                    
                case 'T':
                    break;
            }
            
            //groupsArray[group - 1](request, rxMsgData);
            cState = START_RX_MESSAGE_READ;
            break; 
    }
}

void InitRxMessageParams(void)
{
    msgCount = 0;
    ZeroArray(rxMsgQueue, MSG_RX_MAX_DATA_SIZE);
}

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="EUSART write packet">


void WriteUartMessage(char* dataBuf, int dataSize)
{
    for(int idx = 0; idx < dataSize; idx++)
    {
        EUSART1_Write(dataBuf[idx]);
    }
}

void UART_Write_Text(char* text)
{
  for(int i =0;text[i]!='\0';i++)
  {
    EUSART1_Write(text[i]);  
  }
    
}

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="EUSART send ACK / Simple message">

// Send ACK message
void SendAckMessage(MSG_GROUPS inGroup, MSG_REQUEST inRequest)
{
    // Create TX packet and clear the memory:
    char TxMsg[ACK_MESSAGE_PACKET_SIZE + 1];
    ZeroArray(TxMsg, ACK_MESSAGE_PACKET_SIZE + 1);
    
    // Now fill it:
    TxMsg[MSG_MAGIC_LOCATION] =  MSG_MAGIC_A;
    TxMsg[MSG_GROUP_LOCATION] =  inGroup;
    TxMsg[MSG_REQUEST_LOCATION] =  inRequest;
    TxMsg[MSG_DATA_SIZE_LOCATION] = 0;

    TxMsg[ACK_MESSAGE_PACKET_SIZE] = crc8(TxMsg, ACK_MESSAGE_PACKET_SIZE);
    
    WriteUartMessage(TxMsg, ACK_MESSAGE_PACKET_SIZE + 1);
}
// </editor-fold>
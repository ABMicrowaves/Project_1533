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

MSG_GROUPS group = 0;
MSG_REQUEST request = 0;
char rxMsgQueue[MSG_RX_MAX_DATA_SIZE];
char rxMsgData[MSG_RX_MAX_DATA_SIZE];
static uint8_t msgCount = 0;
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="EUSART read packet">

void readUartByte(void)
// Since we read byte by byte from MCC UART driver we need to implement FSM
{    
    UCHAR chRec = NULL;
    char dest[50];
                    
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
                cState = READ_STREAM;
            }
            break;
            
        case READ_STREAM:
            
            if(eusart1RxCount > 0)
            {
                chRec = EUSART1_Read();
                if(chRec == NULL)
                {
                    return;
                }
                else if(chRec == CHAR_CARRIAGE_RETURN)
                {
                    cState = READ_GROUP;
                }
                else
                {
                    if(chRec != ' ')    // Skip spaces.
                    {
                        rxMsgQueue[msgCount++] = chRec;
                    }
                }
            }
            else
            {
                return;
            }
            break;
            
        case READ_GROUP:
            
            chRec = toupper(rxMsgQueue[0]);
            
            switch(chRec)
            {
                case 'R':
                    
                    group = RX_GROUP;
                    cState = READ_REQUEST;
                    break;
                    
                case 'T':
                    
                    group = TX_GROUP;
                    cState = READ_REQUEST;
                    break;
                
                case 'S':

                    group = COMMON_GROUP;
                    cState = READ_REQUEST;
                    break;
                    
                default:
                    sprintf(dest, "NOT O.K \n\r");
                    UART_Write_Text(dest);
                    cState = START_RX_MESSAGE_READ;
                    break;
            }
            break;
        
        case READ_REQUEST:
            
            chRec = toupper(rxMsgQueue[1]);
            
            switch(group)
            {
                case RX_GROUP:
                    
                    if(chRec == 'I' || chRec == 'F' || chRec == 'Q' || chRec == 'X' || chRec == 'C')
                    {
                        if(chRec == 'C')
                        {
                            if(toupper(rxMsgQueue[2]) == 'P' || toupper(rxMsgQueue[2]) == 'R')
                            {
                                request = chRec + toupper(rxMsgQueue[2]) - '0';
                            }
                            else
                            {
                                sprintf(dest, "NOT O.K \n\r");
                                UART_Write_Text(dest);
                                cState = START_RX_MESSAGE_READ;
                                return;
                            }   
                        }
                        else
                        {
                            request = chRec - '0';
                        }
                        
                        cState = READ_DATA;
                        return;
                    }       
                    break;
            
                case TX_GROUP:
                    
                    if(chRec == 'I' || chRec == 'F' || chRec == 'Q' || chRec == 'X' || chRec == 'B')
                    {
                        request = (chRec - '0');
                        cState = READ_DATA;
                        return;
                    }
                    break;
            
                case COMMON_GROUP:
                    
                    if(chRec == 'H')
                    {
                        request = (chRec - '0');
                        cState = READ_DATA;
                        return;
                    }
                    else if(chRec == 'L')
                    {
                        request = (chRec - '0');
                        cState = READ_DATA;
                        return;
                    }
                    else
                    {
                        sprintf(dest, "NOT O.K \n\r");
                        UART_Write_Text(dest);
                        cState = START_RX_MESSAGE_READ;
                        return;
                    } 
                    break;
            }
            
            sprintf(dest, "NOT O.K \n\r");
            UART_Write_Text(dest);
            cState = START_RX_MESSAGE_READ;
            
            break;
            
        case READ_DATA:
            
            cState = JUMP_FUNCTION;
            break;
            
        case JUMP_FUNCTION:
            
            groupsArray[group](request, rxMsgData);
            cState = START_RX_MESSAGE_READ;
            break; 
    }
}

void InitRxMessageParams(void)
{
    group = 0;
    request = 0;
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
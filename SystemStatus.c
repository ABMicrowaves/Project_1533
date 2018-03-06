/*******************************************************************************
File name: SystemStatus.c                                                   ****
File description:   Include MCU run-time and status parameters              ****
                    and functions.                                          ****
MCU:                PIC18F45k22                                             ****
Date modified: 05/02/2018 16:34.                                            ****
Author: RoeeZ (Comm-IT).                                                    ****
****************************************************************************** */

#include "SystemStatus.h"

static uint32_t mcuRunTimeIn5SecTicks = 0;   // Max Time to store = 24 hours


void SetMcuFwVersion(char* data)
{
    for(uint8_t idx = 0; idx < FW_VERSION_MAX_SIZE_BYTE; idx++)
    {
        EepromWrite(idx, data[idx]);
    }
    
    // Now send ACK message via serial:        
    SendAckMessage((MSG_GROUPS)MCU_STATUS_VERSION_MSG, (MSG_REQUEST)STATUS_SET_MCU_FW_VERSION);
}

void GetMcuFwVersion()
{
    // Create TX packet and clear the memory:
    char TxMsg[STATUS_FW_PACKET_SIZE + 1];
    ZeroArray(TxMsg, STATUS_FW_PACKET_SIZE + 1);
    
    // Now fill it:
    TxMsg[MSG_MAGIC_LOCATION] =  MSG_MAGIC_A;
    TxMsg[MSG_GROUP_LOCATION] =  MCU_STATUS_VERSION_MSG;
    TxMsg[MSG_REQUEST_LOCATION] =  STATUS_GET_MCU_FW_VERSION;
    TxMsg[MSG_DATA_SIZE_LOCATION] = FW_VERSION_MAX_SIZE_BYTE;

    // Fill TX array with data:
    for(uint8_t idx = 0; idx < FW_VERSION_MAX_SIZE_BYTE; idx++)
    {
        TxMsg[MSG_DATA_LOCATION + idx] = EepromRead(idx);
    }
    
    TxMsg[STATUS_FW_PACKET_SIZE] = crc8(TxMsg, STATUS_FW_PACKET_SIZE);
    
    WriteUartMessage(TxMsg, STATUS_FW_PACKET_SIZE + 1);
}

void SetCpldFwVersion(char* data)
{
    for(int idx = 0; idx < FW_VERSION_MAX_SIZE_BYTE; idx++)
    {
        EepromWrite(CPLD_FW_ADDR_OFFSET + idx, data[idx]);
    }
    SendAckMessage((MSG_GROUPS)MCU_STATUS_VERSION_MSG, (MSG_REQUEST)STATUS_SET_CPLD_FW_VERSION);
}

void GetCpldFwVersion()
{
    // Create TX packet and clear the memory:
    char TxMsg[STATUS_FW_PACKET_SIZE + 1];
    ZeroArray(TxMsg, STATUS_FW_PACKET_SIZE + 1);
    
    // Now fill it:
    TxMsg[MSG_MAGIC_LOCATION] =  MSG_MAGIC_A;
    TxMsg[MSG_GROUP_LOCATION] =  MCU_STATUS_VERSION_MSG;
    TxMsg[MSG_REQUEST_LOCATION] =  STATUS_GET_CPLD_FW_VERSION;
    TxMsg[MSG_DATA_SIZE_LOCATION] = FW_VERSION_MAX_SIZE_BYTE;

    // Fill TX array with data:
    for(int idx = 0; idx < FW_VERSION_MAX_SIZE_BYTE; idx++)
    {
        TxMsg[MSG_DATA_LOCATION + idx] = EepromRead(CPLD_FW_ADDR_OFFSET + idx);
    }
    
    TxMsg[STATUS_FW_PACKET_SIZE] = crc8(TxMsg, STATUS_FW_PACKET_SIZE);
    
    WriteUartMessage(TxMsg, STATUS_FW_PACKET_SIZE + 1);
}

void SetMcuRunTime()
{
    mcuRunTimeIn5SecTicks++;
    mcuRunTimeIn5SecTicks %= NUM_5SEC_TICS_24_HOURS;
}

void ClearMcuRunTime()
{
    mcuRunTimeIn5SecTicks = 0;
}

void GetMcuRunTime()
{
    // Create TX packet and send it:
    char TxMsg[STATUS_RUN_TIME_PACKET_SIZE + 1];
        
    // Now fill it:
    TxMsg[MSG_MAGIC_LOCATION] =  MSG_MAGIC_A;
    TxMsg[MSG_GROUP_LOCATION] =  MCU_STATUS_VERSION_MSG;
    TxMsg[MSG_REQUEST_LOCATION] =  STATUS_MCU_RUN_TIME;
    TxMsg[MSG_DATA_SIZE_LOCATION] = RUN_TIME_MAX_SIZE_BYTE;

    uint32_t tempRunTime = mcuRunTimeIn5SecTicks;
    
    // Fill TX array with data:
    for(int idx = 0; idx < RUN_TIME_MAX_SIZE_BYTE; idx++)
    {
        TxMsg[MSG_DATA_LOCATION + idx] = tempRunTime % 10;
        tempRunTime /= 10;
    }
    
    TxMsg[STATUS_RUN_TIME_PACKET_SIZE] = crc8(TxMsg, STATUS_RUN_TIME_PACKET_SIZE);
    
    WriteUartMessage(TxMsg, STATUS_RUN_TIME_PACKET_SIZE + 1);
}

void keepAliveSignalUart(void)
{
    SendAckMessage((MSG_GROUPS)CONTROL_MSG, (MSG_REQUEST)CONTROL_KEEP_ALIVE);
}

void SendUartSystemInitMessage(void)
{    
    char dest[50];
    
    sprintf(dest, "*************************** \n\r");
    UART_Write_Text(dest);
    
    sprintf(dest, "FAST LINK SYSTEM \n\r");
    UART_Write_Text(dest);
    
    sprintf(dest, "SW VESRION: 1.001 \n\r");
    UART_Write_Text(dest);
    
    sprintf(dest, "Compile date: %s \n\r", __DATE__);
    UART_Write_Text(dest);
    
    sprintf(dest, "Compile time: %s \n\r", __TIME__);
    UART_Write_Text(dest);
    
    sprintf(dest, "*************************** \n\r");
    UART_Write_Text(dest);
}

void PrintHelpScreen(void)
{    
    char dest[50];
    
    sprintf(dest, "DS <data soure><cr>  \tSet data source (0-1)\r\n");
    UART_Write_Text(dest);
    sprintf(dest, "DP <data polarity><cr>  \tSet data polarity (0-1)\r\n");
    UART_Write_Text(dest);
    sprintf(dest, "DE <setup SOQPSK><cr>  \tSet setup SOQPSK (0-1)\r\n");
    UART_Write_Text(dest);
    sprintf(dest, "RP <power height><cr>  \tSet power height (0-1)\r\n");
    UART_Write_Text(dest);
    sprintf(dest, "RF <power comand><cr>  \tSet power comand (0-1)\r\n");
    UART_Write_Text(dest);
    sprintf(dest, "RA <randomizer><cr>  \tSet with/without randomizer (0-1)\r\n");
    UART_Write_Text(dest);
    sprintf(dest, "FR <frequency><cr>  \tSet frequency (2200.0-2400.0)\r\n");
    UART_Write_Text(dest);
    sprintf(dest, "MO <mode><cr>  \tSet mode (0-3)\r\n");
    UART_Write_Text(dest);
    sprintf(dest, "IC <bitrate><cr>  \tSet birtate (1.00-30.00DBps)\r\n");
    UART_Write_Text(dest);
    sprintf(dest, "ID <internal pattern><cr>  \tSet internal pattern (0-3)\r\n");
    UART_Write_Text(dest);
    sprintf(dest, "VE <cr>  \tdisplay version info\r\n");
    UART_Write_Text(dest);
    sprintf(dest, "VS <major>.<minor> <cr>  \tset the setup file version\r\n");
    UART_Write_Text(dest);
    sprintf(dest, "VP <power level><cr>  \tSet power level (20-40)\r\n");
    UART_Write_Text(dest);
    sprintf(dest, "VL <power high><cr>  \tSet high power level (20-40)\r\n");
    UART_Write_Text(dest);
    sprintf(dest, "VM <negative power level><cr>  \tSet negative power level\r\n");
    UART_Write_Text(dest);
    sprintf(dest, "IC <bitrate><cr>  \tSet birtate (1.00-30.00DBps)\r\n");
    UART_Write_Text(dest);
    sprintf(dest, "ID <internal pattern><cr>  \tSet internal pattern (0-3)\r\n");
    UART_Write_Text(dest);
}
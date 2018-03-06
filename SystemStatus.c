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


typedef union 
{
    struct 
    {
        bool TB;
    }TX_UNIT;
    
    
}SYSTEM;

void SetMcuFwVersion(char* data)
{

}

void GetMcuFwVersion()
{

}

void SetCpldFwVersion(char* data)
{

}

void GetCpldFwVersion()
{
    
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
    
}

void keepAliveSignalUart(void)
{
    //SendAckMessage((MSG_GROUPS)CONTROL_MSG, (MSG_REQUEST)CONTROL_KEEP_ALIVE);
}

void SendUartSystemInitMessage(void)
{    
    char dest[50];
    
    sprintf(dest, "*************************** \n\r");
    UART_Write_Text(dest);
    
    sprintf(dest, "FAST LINK SYSTEM \n\r");
    UART_Write_Text(dest);
    
    sprintf(dest, "SW VESRION: %s \n\r", SYS_VERSION);
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
    
    // TX commands:
    sprintf(dest, "<TX system commands>\n\r");
    UART_Write_Text(dest);
    
    sprintf(dest, "$TI <XXXX><cr>   Init TX system and set frequency (0-9999)[MHz]\r\n");
    UART_Write_Text(dest);
    sprintf(dest, "$TF <XXXX><cr>   Set TX system frequency at (0-9999)[MHz].\r\n");
    UART_Write_Text(dest);
    sprintf(dest, "$TQ <cr>         Get status from TX system.\r\n");
    UART_Write_Text(dest);
    sprintf(dest, "$TB <X><cr>      Turn on[1] / off[0] BIT mode at TX system [Default = 0]\r\n");
    UART_Write_Text(dest);
    sprintf(dest, "$TX <X><cr>      Turn on[1] / off[0] transmission at TX system [Default = 0]\r\n");
    UART_Write_Text(dest);
    
    // RX commands:
    sprintf(dest, "\n\r<RX system commands>\n\r");
    UART_Write_Text(dest);
    sprintf(dest, "$RI <XXXX><cr>   Init RX system and set frequency at XXXX (0-9999)[MHz]\r\n");
    UART_Write_Text(dest);
    sprintf(dest, "$RQ <cr>         Get status from RX system\r\n");
    UART_Write_Text(dest);
    sprintf(dest, "$RB <X><cr>      Turn on[1] / off[0] BIT mode at RX system.\r\n");
    UART_Write_Text(dest);
    sprintf(dest, "$RX <X><cr>      Turn on[1] / off[0] receive at RX system.\r\n");
    UART_Write_Text(dest);
    sprintf(dest, "$RCR <X><cr>     Set Compression range at RX system. High [1] Low [0] [Default = 0]\r\n");
    UART_Write_Text(dest);
    sprintf(dest, "$RCP <X><cr>     Set Compression operation mode at RX system: Automatic[1] Manual[0] [Default = 0]\r\n");
    UART_Write_Text(dest);
    
    // Common system commands:
    sprintf(dest, "\n\r<Common system commands>\n\r");
    UART_Write_Text(dest);
    sprintf(dest, "$SH <cr>         Print system help message.\r\n");
    UART_Write_Text(dest);
    sprintf(dest, "$SBT <XX><cr>    Set UART refresh rate (1-20)[Hz].\r\n");
    UART_Write_Text(dest);
    sprintf(dest, "$SBU <X><cr>     Set UART automatic operation: Automatic[1] Manual[0] [Default = 0]\r\n");
    UART_Write_Text(dest);
    sprintf(dest, "$SQ <X><cr>      Get system status.\r\n");
    UART_Write_Text(dest);
    sprintf(dest, "$SL <cr>         Test system LEDs.\r\n");
    UART_Write_Text(dest);
}

void PrintSystemStatus()
{
    
}
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

}

void ReadSystemStatusFromEprom(void)
{
    uint16_t sysData = ReadIntFromEeprom(EEPROM_SYSTEM_ADDRESS_OFSEET | SYSTEM_INFO_ADDRES[0], 1);
    systemStatus.UnitType = sysData & 0x1;
    sysData = ReadIntFromEeprom(EEPROM_SYSTEM_ADDRESS_OFSEET | SYSTEM_INFO_ADDRES[1], 1);
    systemStatus.UartMode = sysData & 0x1;
    sysData = ReadIntFromEeprom(EEPROM_SYSTEM_ADDRESS_OFSEET | SYSTEM_INFO_ADDRES[2], 2);
    systemStatus.UartRefreshRate = sysData & 0x1F;
}
void SaveSystemStatus(void)
{
    StoreIntInEeprom(systemStatus.UnitType,EEPROM_SYSTEM_ADDRESS_OFSEET | SYSTEM_INFO_ADDRES[0], 1);
    StoreIntInEeprom(systemStatus.UartMode,EEPROM_SYSTEM_ADDRESS_OFSEET | SYSTEM_INFO_ADDRES[1], 1);
    StoreIntInEeprom(systemStatus.UartRefreshRate,EEPROM_SYSTEM_ADDRESS_OFSEET | SYSTEM_INFO_ADDRES[2], 2);
    //uint16_t sysData = ReadIntFromEeprom(EEPROM_SYSTEM_ADDRESS_OFSEET | SYSTEM_INFO_ADDRES[0], 1);
    //systemStatus.UnitType = sysData & 0x1;
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
    sprintf(dest, "$SU <XX><cr>    Set UART refresh rate (1-20)[Hz].\r\n");
    UART_Write_Text(dest);
    sprintf(dest, "$SA <X><cr>     Set UART automatic operation: Automatic[1] Manual[0] [Default = 0]\r\n");
    UART_Write_Text(dest);
    sprintf(dest, "$SQ <X><cr>      Get system status.\r\n");
    UART_Write_Text(dest);
    sprintf(dest, "$SL <cr>         Test system LEDs.\r\n");
    UART_Write_Text(dest);
    sprintf(dest, "$TD <DAC NUM><DAC VALUE><cr>         Set TX DAC <0-3> <0-Vref[4 dig]> \r\n");
    UART_Write_Text(dest);
    sprintf(dest, "$SQ <cr>         Read System Status \r\n");
    UART_Write_Text(dest);
    sprintf(dest, "$ST <cr>         Set Unit Type \r\n");
    UART_Write_Text(dest);
    sprintf(dest, "$SV <cr>         Save System status To EEPROM \r\n");
    UART_Write_Text(dest);
//    sprintf(dest, "$                                    DAC0: bla \r\n");
//    UART_Write_Text(dest);
//    sprintf(dest, "$                                    DAC1: blabla \r\n");
//    UART_Write_Text(dest);
//    sprintf(dest, "$                                    DAC2: blablabla \r\n");
//    UART_Write_Text(dest);
//    sprintf(dest, "$                                    DAC2: blablablabla \r\n");
//    UART_Write_Text(dest);
}

void PrintSystemStatus(void)
{
    char dest[80];
    systemStatus.SwVersion = SYS_VERSION;
    //char dest[50];
    //sprintf(dest, "%d\t",POWER_EN_GetValue());  
    sprintf(dest, "UNIT ID %d\n\r",systemStatus.UnitId); 
    UART_Write_Text(dest);
    sprintf(dest, "SOFTWARE VERSION %s\n\r",systemStatus.SwVersion); 
    UART_Write_Text(dest);
    sprintf(dest, "UNIT TYPE %d\n\r",systemStatus.UnitType); 
    UART_Write_Text(dest);
    sprintf(dest, "PASS COUNTER %d\n\r",systemStatus.PassCounter); 
    UART_Write_Text(dest);
}

void CollectRxStatusParams(void)
{
    rxStatistics.Synt = rxFreq;
    rxStatistics.DeviceTemperature = lastAdcTemp;
    rxStatistics.InputPowerStatus = POWER_EN_GetValue();   
    rxStatistics.Freq = rxFreq; 
    rxStatistics.RSSI = lastAdcFfwrRSSI;
    rxStatistics.Light = LED_LIGHT_EN_GetValue();
    //rxStatistics.UnitId = 123;
    rxStatistics.UnitDc = 1234;
    //rxStatistics.SwVersion = SYS_VERSION;
    //rxStatistics.UnitType = false;
    
    //rxStatistics.AdcValues.ADC0 = 0x7;
}

void CollectTxStatusParams(void)
{
    txStatistics.Synt = txFreq;
    txStatistics.DeviceTemperature = lastAdcTemp;
    txStatistics.InputPowerStatus = POWER_EN_GetValue();   
    txStatistics.Freq = txFreq; 
    txStatistics.RSSI = lastAdcFfwrRSSI;
    txStatistics.Light = LED_LIGHT_EN_GetValue();
    //txStatistics.UnitId = 123;
    txStatistics.UnitDc = 1234;
    //txStatistics.SwVersion = SYS_VERSION;
    //txStatistics.UnitType = true;
    
    txStatistics.AdcValues.ADC0 = 0x7;
}

void PrintRxStatus(void)
{
    char dest[80];
    sprintf(dest, "*******************\n\r"); 
    UART_Write_Text(dest);
    sprintf(dest, "RX SYNTH (PLL) Lock indication 0: not locked 1: locked%d\n\r",rxStatistics.Synt); 
    UART_Write_Text(dest);
    sprintf(dest, "Device Temperature %f\n\r",rxStatistics.DeviceTemperature); 
    UART_Write_Text(dest);
    sprintf(dest, "Input power status 0: OFF 1: ON%d\n\r",rxStatistics.InputPowerStatus); 
    UART_Write_Text(dest);
    sprintf(dest, "RX Frequency in MHz%f\n\r",rxStatistics.Freq); 
    UART_Write_Text(dest);
    sprintf(dest, "RSSI %d\n\r",rxStatistics.RSSI); 
    UART_Write_Text(dest);
    sprintf(dest, "Light 0: OFF 1: ON%d\n\r",rxStatistics.Light); 
    UART_Write_Text(dest);
    //sprintf(dest, "UNIT ID %d\n\r",rxStatistics.UnitId); 
    //UART_Write_Text(dest);
    sprintf(dest, "UNIT DC %d\n\r",rxStatistics.UnitDc); 
    UART_Write_Text(dest);
    //sprintf(dest, "SOFTWARE VERSION %s\n\r",rxStatistics.SwVersion); 
   // UART_Write_Text(dest);
    //sprintf(dest, "UNIT TYPE %d\n\r",rxStatistics.UnitType); 
    //UART_Write_Text(dest);
    sprintf(dest, "*******************\n\r"); 
    UART_Write_Text(dest);
}

void PrintTxStatus(void)
{
    char dest[80];
    sprintf(dest, "*******************\n\r"); 
    UART_Write_Text(dest);
    sprintf(dest, "TX SYNTH (PLL) Lock indication %d\n\r",txStatistics.Synt); 
    UART_Write_Text(dest);
    sprintf(dest, "Device Temperature %f\n\r",txStatistics.DeviceTemperature); 
    UART_Write_Text(dest);
    sprintf(dest, "Input power status 0: OFF 1: ON%d\n\r",txStatistics.InputPowerStatus); 
    UART_Write_Text(dest);
    sprintf(dest, "TX Frequency in MHz%f\n\r",txStatistics.Freq); 
    UART_Write_Text(dest);
    sprintf(dest, "RSSI %d\n\r",txStatistics.RSSI); 
    UART_Write_Text(dest);
    sprintf(dest, "Light 0: OFF 1: ON%d\n\r",txStatistics.Light); 
    UART_Write_Text(dest);
    //sprintf(dest, "UNIT ID %d\n\r",txStatistics.UnitId); 
    //UART_Write_Text(dest);
    sprintf(dest, "UNIT DC %d\n\r",txStatistics.UnitDc); 
    UART_Write_Text(dest);
    //sprintf(dest, "SOFTWARE VERSION %s\n\r",txStatistics.SwVersion); 
    //UART_Write_Text(dest);
    //sprintf(dest, "UNIT TYPE %d\n\r",txStatistics.UnitType); 
    //UART_Write_Text(dest);
    sprintf(dest, "*******************\n\r"); 
    UART_Write_Text(dest);
}


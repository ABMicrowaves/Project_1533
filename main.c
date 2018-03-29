/*******************************************************************************
File name: main.c                                                           ****
File description:   Main entry of the system flow. Impelemt sigle threaded  ****
 *                  system ("BERMETAL")                                     ****
MCU:                PIC18F45k22                                             ****
Date modified: 28/01/2018 16:14.                                            ****
Author: RoeeZ (Comm-IT).                                                    ****
****************************************************************************** */

#include "SytstemSettings.h"
#include "SystemCommon.h"

void main(void)
{
    // First initialize system settings:
    SetMcuSystem();
    
    // Second set application managers:
    InitSystemApplicationManagers();

    // Then send keep alive signal to PC host application:
    SendUartSystemInitMessage();
    
    // Read system status from EEPROM:
    ReadSystemStatusFromEprom();
    // Indicate by Green led that system start OK:
    BlinkOkLeds(OK_START_SYSTEM);
            
    //PrintHelpScreen();
    while (1)
    {    
        readUartByte();
        
        if (TimerOneSecFlag == true)
        {
           //DacTest();   
            SetMcuRunTime();
            TimerOneSecFlag = false; 
        }
        else if (TimerKeepAliveFlag == true)
        {
            keepAliveSignalLed();
            TimerKeepAliveFlag = false; 
        }
        else if (TimertenSecFlag == true)
        {
            SampleAllChannels();
            TimertenSecFlag = false;
        }
        else if (TimerSamplingFlag == true)
        {
            if(true == needToSample)
            {
                SampleSingleChannel();
            }
        }
    }
}

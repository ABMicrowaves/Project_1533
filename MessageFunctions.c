/*******************************************************************************
File name: MessageFunctions.c                                               ****
File description:   Include EUSART P2P groups functions definitions.        ****
MCU:                PIC18F45k22                                             ****
Date modified: 28/01/2018 16:14.                                            ****
Author: RoeeZ (Comm-IT).                                                    ****
****************************************************************************** */

#include "MessageFunctions.h"

void GroupRx(MSG_REQUEST request, char* data)
{
    switch (request)
    {
        case UNIT_MODULE:
            //testLeds();
            break;
            
        case SET_MODULE_FREQUENCY:
            UpdateSynthFreq(RX_TYPE, data);
            break;
            
        case READ_MODULE_STATUS:
            //ResetCpld();
            break;
            
        case SET_MODULE_BIT_MODE:
            break;
            
        case SET_MODULE_OPERATION_MODE:
            break;
        
        case ADC_SAMPLE:
            AdcSingleSample(RX_TYPE, data);
            break;
            
        default:
            break;
    }
}

void GroupTx(MSG_REQUEST request, char* data)
{
    switch (request)
    {
        case UNIT_MODULE:
            //testLeds();
            break;
            
        case SET_MODULE_FREQUENCY:
            
            UpdateSynthFreq(TX_TYPE, data);
            break;
            
        case READ_MODULE_STATUS:
            //ResetCpld();
            break;
            
        case SET_MODULE_BIT_MODE:
            break;
            
        case SET_MODULE_OPERATION_MODE:
            break;
            
        case RX_SET_COMRESSION_MODE:
            break;
            
        case RX_SET_COMRESSION_RANGE:
            break;
        
        case ADC_SAMPLE:
            AdcSingleSample(TX_TYPE, data);
            break;
        
        default:
            break;
    }
}

void GroupCommon(MSG_REQUEST request, char* data)
{
    switch (request)
    {
        case SYSTEM_PRINT_HELP_LIST:
            PrintHelpScreen();
            break;
            
        case SYSTEM_TEST_LED:
            testLeds();
            break;
            
        default:
            break;
    }
}

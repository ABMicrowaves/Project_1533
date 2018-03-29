/*******************************************************************************
File name: MessageFunctions.c                                               ****
File description:   Include EUSART P2P groups functions definitions.        ****
MCU:                PIC18F45k22                                             ****
Date modified: 28/01/2018 16:14.                                            ****
Author: RoeeZ (Comm-IT).                                                    ****
****************************************************************************** */

#include "MessageFunctions.h"
uint32_t retNum =0;
uint16_t numSamples = 0;
uint16_t channelNum = 0;

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
            CollectRxStatusParams();
            PrintRxStatus();
            break;
            
        case SET_MODULE_BIT_MODE:
            break;
            
        case SET_MODULE_OPERATION_MODE:
            break;
        
        case ADC_SAMPLE:
            retNum = GetIntFromUartData(data);
            channelNum  = data[1] - '0';
            numSamples  = retNum % (int)(pow(10,data[0] - 1));
            AdcSingleSample(RX_TYPE, channelNum, numSamples);
            //AdcSingleSample(RX_TYPE, data);
            
            // For testing
            //DacSetValue(data);
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
            CollectTxStatusParams();
            PrintTxStatus();
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
            retNum = GetIntFromUartData(data);
            channelNum  = data[1] - '0';
            numSamples  = retNum % (int)(pow(10,data[0] - 1));
            AdcSingleSample(TX_TYPE, channelNum, numSamples);
            //AdcSingleSample(TX_TYPE, data);
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
            
        case SET_SYSTEM_TYPE:
            set_system_type(data);
            
            break;
            
        case PRINT_SYSTEM_STATUS:
            PrintSystemStatus();
            break;
            
        case SET_UART_REFRASH_RATE:     //SU
            SetUartRefrashRate(data);
            break;
            
        case SET_UART_MODE:             //SA
            SetUartMode(data);
            break;
            
        case SAVE_SYSTEM_STATUS:
            SaveSystemStatus();
            break;

            
        default:
            break;
    }
}

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
        case TX_RX_UNIT_UNIT:
            //testLeds();
            break;
            
        case TX_RX_SET_UNIT_FREQUENCY:
            //ResetMcu();
            break;
            
        case TX_RX_READ_UNIT_STATUS:
            //ResetCpld();
            CollectRxStatusParams();
            PrintRxStatus();
            break;
            
        case TX_RX_SET_BIT_MODE:
            break;
            
        case TX_RX_SET_OPERATION_MODE:
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
        case TX_RX_UNIT_UNIT:
            //testLeds();
            break;
            
        case TX_RX_SET_UNIT_FREQUENCY:
            //ResetMcu();
            break;
            
        case TX_RX_READ_UNIT_STATUS:
            CollectTxStatusParams();
            PrintTxStatus();
            break;
            
        case TX_RX_SET_BIT_MODE:
            break;
            
        case TX_RX_SET_OPERATION_MODE:
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
            

            
        default:
            break;
    }
}

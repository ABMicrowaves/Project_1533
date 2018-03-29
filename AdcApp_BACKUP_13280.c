<<<<<<< HEAD
/*******************************************************************************
File name: AdcApp.c                                                         ****
File description:   A2D driver application manager.                         ****
MCU:                PIC18F45k22                                             ****
Date modified: 28/01/2018 16:14.                                            ****
Author: RoeeZ (Comm-IT).                                                    ****
****************************************************************************** */

#include "AdcApp.h"

// <editor-fold defaultstate="collapsed" desc="Global verbs">

ADC_SAMPLE_MODE adcSampleMode = CIRCULAR;
char channel = 0;
uint16_t count = 0;
uint16_t numSamples = 0;
uint16_t channelNum = 0;

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="ADC application manager init">

void InitAdcApplicationMgr()
{
    adcSampleMode = CIRCULAR;
}

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Set ADC operation mode">


void SetChannelMode(char* data)
{
    adcSampleMode = data[0];
    if (adcSampleMode == SINGLE_CHANNEL)
    {
        channel = data[1];
    }
    //SendAckMessage((MSG_GROUPS)ADC_MSG, (MSG_REQUEST)ADC_CHANNEL_MODE);
}
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="ADC convert">

void AdcSingleSample(MODULE_TYPE cType, char* data)
{
    uint32_t retNum = 0x0;
    
    if(data[0] == '0')
    {
        UART_Write_Text(UART_NOT_OK_MESSAGE);
    }
    else
    {
        retNum = GetIntFromUartData(data);
        channelNum  = (retNum / 0xA) % 0x64;
        numSamples  = retNum % 0xA;
        
        if(channelNum > ADC_NUM_CHANNELS)
        {
            UART_Write_Text(UART_NOT_OK_MESSAGE);
        }
        else
        {
            if(cType == TX_TYPE)
            {
                if(channelNum == 0) UART_Write_Text("SAMPLE CHANNEL NAME");
                if(channelNum == 0x0 || channelNum == 0x1)
                {
                    needToSample = true;
                }
                
                else
                {
                    UART_Write_Text(UART_NOT_OK_MESSAGE);
                }
                
            }
            
            if(cType == RX_TYPE)
            {
                needToSample = true;
            }
            else
            {
                UART_Write_Text(UART_NOT_OK_MESSAGE);
            }
        }
    }
}

bool SampleSingleChannel(void)
{
    char dest[50];
    uint16_t adcRes = 0x0;
    if(numSamples--)
    {
        adc_result_t _adcResult = ADC_GetConversion(channelArr[channelNum]);
        adcRes = (_adcResult/pow(2,ADC_BIT_SIZE))*VDD;
        
        sprintf(dest, "%d \t", adcRes);
        UART_Write_Text(dest);
        __delay_ms(1000);
    }
    else
    {
        needToSample = false;
        UART_Write_Text(UART_OK_MESSAGE);
    }
}
// </editor-fold>
=======
/*******************************************************************************
File name: AdcApp.c                                                         ****
File description:   A2D driver application manager.                         ****
MCU:                PIC18F45k22                                             ****
Date modified: 28/01/2018 16:14.                                            ****
Author: RoeeZ (Comm-IT).                                                    ****
****************************************************************************** */

#include "AdcApp.h"

// <editor-fold defaultstate="collapsed" desc="Global verbs">

ADC_SAMPLE_MODE adcSampleMode = CIRCULAR;
char channel = 0;
uint16_t count = 0;
uint16_t numSamples = 0;
uint16_t channelNum = 0;

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="ADC application manager init">

void InitAdcApplicationMgr()
{
    adcSampleMode = CIRCULAR;
}

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="ADC convert">

void AdcSingleSample(MODULE_TYPE cType, ADC_CHANNEL_INDEX chType, int32_t numSamples)
{
    uint32_t retNum = 0x0;
    
    if(chType == ADC_OFF)
    {
        if(cType == TX_TYPE)  txStatistics.AdcValues.OperState = false;
        else rxStatistics.AdcValues.OperState = false;
    }
    else
    {
        
        if(channelNum > ADC_NUM_CHANNELS)
        {
            UART_Write_Text("NOT OK \n\r");
        }
        else
        {
            if(cType == TX_TYPE)
            {
                if(channelNum == 0)   // Don`t sample.
                {
                    rxStatistics.AdcValues.OperState = false; 
                    return;
                }
                else
                {
                    if(channelNum == 1) UART_Write_Text("TX SAMPLE CHANNEL: TX-ADC_RREV\n\r");
                    else if(channelNum == 2) UART_Write_Text("TX SAMPLE CHANNEL ADC_TEMP\n\r");
                    if(channelNum == 0x1 || channelNum == 0x2)
                    {
                        needToSample = true;
                    }
                    else
                    {
                        UART_Write_Text("NOT OK \n\r");
                    }
                }
            }
            
            if(cType == RX_TYPE)
            {
                if(channelNum == 0)   // Don`t sample.
                {
                    rxStatistics.AdcValues.OperState = false; 
                    return;
                }
                else
                {
                    if(channelNum == 1) UART_Write_Text("RX SAMPLE CHANNEL RX-ADC_FFWR\n\r");
                    else if(channelNum == 2) UART_Write_Text("RX SAMPLE CHANNEL RX-ADC_VG_MON\n\r");
                    if(channelNum == 0x1 || channelNum == 0x2)
                    {
                        needToSample = true;
                    }
                    else
                    {
                    UART_Write_Text("NOT OK \n\r");
                    }
                }
            }
            
        }
    }
}

bool SampleSingleChannel(void)
{
    char dest[50];
    uint16_t adcRes = 0x0;
    if(numSamples > 0)
    {
        adc_result_t _adcResult = ADC_GetConversion(channelArr[channelNum]);
        adcRes = (_adcResult/pow(2,ADC_BIT_SIZE))*VDD;
        if(channelArr[channelNum] == 0x6) lastAdcTemp = adcRes;
        if(channelArr[channelNum] == 0x5) lastAdcFfwrRSSI = adcRes; 
        if(channelArr[channelNum] == 0x4) lastAdcRREV = adcRes;
        if(channelArr[channelNum] == 0x7) lastAdcVgMon = adcRes;
        sprintf(dest, "%d \t", adcRes);
        UART_Write_Text(dest);
        __delay_ms(100);
        numSamples--;
    }
    else
    {
        needToSample = false;
        UART_Write_Text("\n\r OK \n\r");
    }
}

void SampleAllChannels(void)
{
    uint16_t adcRes = 0x0;
    uint8_t i;
    for (i=1;i<=4;i++)
    {
        adc_result_t _adcResult = ADC_GetConversion(channelArr[i]);
        adcRes = (_adcResult/pow(2,ADC_BIT_SIZE))*VDD;
        if(channelArr[i] == 0x6) lastAdcTemp = adcRes;
        if(channelArr[i] == 0x5) lastAdcFfwrRSSI = adcRes; 
        if(channelArr[i] == 0x4) lastAdcRREV = adcRes;
        if(channelArr[i] == 0x7) lastAdcVgMon = adcRes;
    }
}


//void SampleVgMonChannel(void)
//{
//    
//    if(false == rxStatistics.AdcValues.OperState)
//    {
//        return;
//    }
//    else
//    {
//        uint16_t adcRes = 0x0;
//        adc_result_t _adcResult = ADC_GetConversion(channelArr[0x3]);
//        adcRes = (_adcResult/pow(2,ADC_BIT_SIZE))*VDD;
//
//        if(adcRes > VGMON_THRESHOLD)
//        {
//            PA_ON_SetHigh();
//            //PA_ON_SetLow();               /////update on the 1533 
//        }
//        else
//        {
//            PA_ON_SetLow();
//        }
//    }
//    
//}
// </editor-fold>
>>>>>>> Update1533

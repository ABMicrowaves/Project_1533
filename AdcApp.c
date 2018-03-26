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
        UART_Write_Text("NOT OK \n\r");
    }
    else
    {
        retNum = GetIntFromUartData(data);
        channelNum  = data[1] - '0';
        numSamples  = retNum % (int)(pow(10,data[0] - 1));
        
        
        if(channelNum > ADC_NUM_CHANNELS)
        {
            UART_Write_Text("NOT OK \n\r");
        }
        else
        {
            if(cType == TX_TYPE)
            {
                
                if(channelNum == 0) UART_Write_Text("TX SAMPLE CHANNEL: TX-ADC_RREV\n\r");
                else if(channelNum == 1) UART_Write_Text("TX SAMPLE CHANNEL ADC_FFWR\n\r");
                if(channelNum == 0x0 || channelNum == 0x1)
                {
                    needToSample = true;
                }
                else
                {
                    UART_Write_Text("NOT OK \n\r");
                }
                
            }
            
            if(cType == RX_TYPE)
            {
                if(channelNum == 0) UART_Write_Text("RX SAMPLE CHANNEL RX-ADC_FFWR\n\r");
                else if(channelNum == 1) UART_Write_Text("RX SAMPLE CHANNEL RX-ADC_VG_MON\n\r");
                if(channelNum == 0x0 || channelNum == 0x1)
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
        UART_Write_Text("\n\r OK \n\r");
    }
}

void SampleVgMonChannel(void)
{
    
    uint16_t adcRes = 0x0;
    
    adc_result_t _adcResult = ADC_GetConversion(channelArr[0x3]);
    adcRes = (_adcResult/pow(2,ADC_BIT_SIZE))*VDD;

    if(adcRes > VGMON_THRESHOLD)
    {
        PA_ON_SetHigh();
        //PA_ON_SetLow();               /////update on the 1533 
    }
    else
    {
        PA_ON_SetLow();
    }
}
// </editor-fold>

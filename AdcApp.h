/*******************************************************************************
File name: AdcApp.h                                                         ****
File description:   A2D driver application manager.                         ****
MCU:                PIC18F45k22                                             ****
Date modified: 28/01/2018 16:14.                                            ****
Author: RoeeZ (Comm-IT).                                                    ****
*******************************************************************************/

#ifndef ADCAPP_H
#define	ADCAPP_H

#include "SystemCommon.h"

#define ADC_NUM_CHANNELS    (0x04)
#define VDD                 (3340)
#define ADC_BIT_SIZE        (10)
#define V_REF               (3400)
#define VGMON_THRESHOLD     V_REF / 2 // 2.1V

typedef enum
{
	CIRCULAR        = 0x0,
    SINGLE_CHANNEL  = 0x1,
}ADC_SAMPLE_MODE;

const adc_channel_t channelArr[ADC_NUM_CHANNELS]  = 
{
    0x4,     // TX-ADC_RREV
    0x6,     // TX-ADC_TMP
    0x5,     // RX-ADC_FFWR (RSSI)
    0x7,     // RX-ADC_VG_MON
};

volatile bool needToSample = false;    // Indicate if we are in middle of sampling

void AdcSingleSample(MODULE_TYPE cType, char* data);
void SetChannelMode(char* data);
void InitAdcApplicationMgr();
bool SampleSingleChannel(void);
void SampleVgMonChannel(void);

//void AdcConvert();

#endif	/* ADCAPP_H */


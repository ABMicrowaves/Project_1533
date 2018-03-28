/*******************************************************************************
File name: SystemStatus.h                                                   ****
File description:   Include MCU run-time and status parameters              ****
                    and functions.                                          ****
MCU:                PIC18F45k22                                             ****
Date modified: 05/02/2018 16:34.                                            ****
Author: RoeeZ (Comm-IT).                                                    ****
****************************************************************************** */

#ifndef SYSTEMSTATUS_H
#define	SYSTEMSTATUS_H

#include "SystemCommon.h"
#define FW_VERSION_MAX_SIZE_BYTE    (0x4)
#define RUN_TIME_MAX_SIZE_BYTE      (0x4)
#define NUM_5SEC_TICS_24_HOURS      (17280)
#define EEPROM_MCU_FW_ADDRESS       (0)
#define SYS_VERSION "1_002"         // System version:

typedef struct
{
    bool    OperState;              //  0: ADC OFF  1: ADC ON
    uint16_t ADC0;
    uint16_t ADC1;
}ADC_VALUES;

typedef struct
{
    bool        Synt;               //(PLL). Lock indication.
    ADC_VALUES  AdcValues;
    double      DeviceTemperature;  // XX.X (value in Celsius degree).
    bool        InputPowerStatus;   // 1: ON 0: OFF.
    double      Freq;                // XXXX.XX (value in MHz).
    int8_t      RSSI;               // ± XX (value in dBm). 
    double      TEMP;               // XX.X (value in Celsius degree). 
    bool        Light;              // 1: ON 0: OFF
    int8_t      UnitId;             // XXX.
    int16_t     UnitDc;             // YYXX.
    char*       SwVersion;          
    bool        UnitType;           // 1: T 0: R
    int8_t      CompressionPoint;   // [XX] (Value in dbm)
    int32_t     PassCounter;        // PASS / FAIL bit (PASS = number of income good signals reach predefine threshold). 
}RX_STATISTICS;

typedef struct
{
    bool        Synt;               //(PLL). Lock indication.
    ADC_VALUES  AdcValues;
    double      DeviceTemperature;  // XX.X (value in Celsius degree).
    bool        InputPowerStatus;   // 1: ON 0: OFF.
    double      Freq;                // XXXX.XX (value in MHz).
    int8_t      RSSI;               // ± XX (value in dBm). 
    double      TEMP;               // XX.X (value in Celsius degree). 
    bool        Light;              // 1: ON 0: OFF
    int8_t      UnitId;             // XXX.
    int16_t     UnitDc;             // YYXX.
    char*       SwVersion;          
    bool        UnitType;           // 1: T 0: R
    int8_t      CompressionPoint;   // [XX] (Value in dbm)
    int32_t     PassCounter;        // PASS / FAIL bit (PASS = number of income good signals reach predefine threshold). 
}RX_STATISTICS;

typedef struct
{
    bool        Synt;               //(PLL). Lock indication.
    ADC_VALUES  AdcValues;
    double      DeviceTemperature;  // XX.X (value in Celsius degree).
    bool        InputPowerStatus;   // 1: ON 0: OFF.
    double      Freq;                // XXXX.XX (value in MHz).
    int8_t      RSSI;               // ± XX (value in dBm). 
    double      TEMP;               // XX.X (value in Celsius degree). 
    bool        Light;              // 1: ON 0: OFF
    int8_t      UnitId;             // XXX.
    int16_t     UnitDc;             // YYXX.
    char*       SwVersion;          
    bool        UnitType;           // 1: T 0: R
    int8_t      CompressionPoint;   // [XX] (Value in dbm)
    int32_t     PassCounter;        // PASS / FAIL bit (PASS = number of income good signals reach predefine threshold). 
    
    bool        IntMode;            // 1: BIT mode active 0: BIT mode don`t active. 
}TX_STATISTICS;

volatile RX_STATISTICS rxStatistics;
volatile TX_STATISTICS txStatistics;

void SetMcuFwVersion(char* data);
void SetCpldFwVersion(char* data);

void GetMcuFwVersion();
void GetCpldFwVersion();

void SetMcuRunTime();
void GetMcuRunTime();
void ClearMcuRunTime();
void keepAliveSignalUart(void);
void SendUartSystemInitMessage(void);
void PrintHelpScreen(void);
void CollectRxStatusParams(void);
void CollectTxStatusParams(void);
void PrintRxStatus(void);
void PrintTxStatus(void);
#endif	/* SYSTEMSTATUS_H */


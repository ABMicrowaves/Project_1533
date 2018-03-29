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
#define NUM_SYSTEM_STATUS_TO_EPROM_WRITE (3)

typedef struct
{
    bool    OperState;              //  0: ADC OFF  1: ADC ON
    uint16_t ADC0;
    uint16_t ADC1;
}ADC_VALUES;

typedef struct
{
    bool    OperState;              //  0: ADC OFF  1: ADC ON
    uint16_t DAC0;
    uint16_t DAC1;
}DAC_VALUES;

const uint8_t SYSTEM_INFO_ADDRES[NUM_SYSTEM_STATUS_TO_EPROM_WRITE] = 
{
    0x0,        // UNIT_TYPE / system type data address where to store or read from EPROM
    0x1,        //UartMode
    0x2,        //Uart Refresh Rate[1-20]]
};

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
    int16_t     UnitDc;             // YYXX.         
    int8_t      CompressionPoint;   // [XX] (Value in dbm)
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
    int16_t     UnitDc;             // YYXX.
    int8_t      CompressionPoint;   // [XX] (Value in dbm) 
    bool        IntMode;            // 1: BIT mode active 0: BIT mode don`t active. 
}TX_STATISTICS;

typedef struct
{
    int8_t      UnitId;             // XXX.
    char*       SwVersion;          
    bool        UnitType;           // 1: H 0: L
    int32_t     PassCounter;        // PASS / FAIL bit (PASS = number of income good signals reach predefine threshold).
    bool        UartMode;
    uint8_t     UartRefreshRate;
}SYSTEM_STATUS;


volatile RX_STATISTICS rxStatistics;
volatile TX_STATISTICS txStatistics;
volatile SYSTEM_STATUS systemStatus;

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
void PrintSystemStatus(void);
void SaveSystemStatus();
void ReadSystemStatusFromEprom(void);
#endif	/* SYSTEMSTATUS_H */


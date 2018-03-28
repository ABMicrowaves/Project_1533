/*******************************************************************************
File name: GroupsCommon.h                                                   ****
File description:   Include EUSART P2P definition and parameters.           ****
MCU:                PIC18F45k22                                             ****
Date modified: 28/01/2018 16:14.                                            ****
Author: RoeeZ (Comm-IT).                                                    ****
****************************************************************************** */

#ifndef GROUPSCOMMON_H
#define	GROUPSCOMMON_H

typedef enum
{
    RX_GROUP                    = 0x0,
    TX_GROUP                    = 0x1,
    COMMON_GROUP                = 0x2,
}MSG_GROUPS;

typedef enum
{
    // RX + TX system requests
    
    TX_RX_SET_BIT_MODE          = 0x12,
    TX_RX_SET_UNIT_FREQUENCY    = 0x16,
    TX_RX_UNIT_UNIT             = 0x19,
    TX_RX_READ_UNIT_STATUS      = 0x21,
    TX_RX_SET_OPERATION_MODE    = 0x28,
    
    // Only RX requests
    RX_SET_COMRESSION_MODE      = 0x63,
    RX_SET_COMRESSION_RANGE     = 0x65,
    
    // ADC
    ADC_SAMPLE                  = 0x23,        //adc sample command is $rs 1 4                         
    
    // Common system common requests
    SYSTEM_PRINT_HELP_LIST      = 0x18,
    SYSTEM_TEST_LED             = 0x1C,
}MSG_REQUEST;

#endif	/* GROUPSCOMMON_H */


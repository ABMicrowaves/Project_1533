/*******************************************************************************
File name: AdcApp.h                                                         ****
File description:   D2A driver application manager for AD5312 external chip ****
MCU:                PIC18F45k22                                             ****
Date modified: 28/01/2018 16:14.                                            ****
Author: RoeeZ (Comm-IT).                                                    ****
*******************************************************************************/

#include "DacApp.h"


void DacInit(void)
{
    for(int8_t idx = 0; idx < NUM_OF_DACS; idx++)
    {
        uint16_t dacInput = ReadIntFromEeprom(EEPROM_DAC_REGS_ADDRESS_OFSEET | DAC_ADDRES[idx], 2);
        if(dacInput == 0xFFFF)
        {
            SWSPI_send_word(EXT_DAC, DAC_DEFAULT_INIT_VALUES[idx], 1);
            StoreIntInEeprom(DAC_DEFAULT_INIT_VALUES[idx], EEPROM_DAC_REGS_ADDRESS_OFSEET | DAC_ADDRES[idx], 2);
        }
        else
        {
            SWSPI_send_word(EXT_DAC, dacInput, 1);
        }
    }
}

// <editor-fold defaultstate="collapsed" desc="DAC Convert">

void DacSetValue(char* data)
{
    uint32_t retNum = GetIntFromUartData(data);
    uint8_t dacNum  = data[1] - '0';
    uint16_t dacAnalog  = retNum % (int)(pow(10,data[0] - 1));
    uint16_t dacDigital = DacAnalogToDigitalSpi(dacAnalog, dacNum);
    
    // Send DAC value to SPI
    SWSPI_send_word(EXT_DAC, dacDigital, 1);
    
    // Save value in EEPROM
    StoreIntInEeprom(dacDigital, EEPROM_DAC_REGS_ADDRESS_OFSEET | DAC_ADDRES[dacNum], 2);

}

uint16_t DacAnalogToDigitalSpi(uint16_t AnalogValMili, uint8_t dacNum)
{
    uint16_t dacDigital = (int)((AnalogValMili * (pow(2, DAC_BITS) - 1)) / DAC_VSOURCEPLUS_MILI);
    uint16_t dacSpiVal = (int)(dacNum * pow(2,14)) | (int)(DAC_POWER_MODE * pow(2,13)) | (int)(dacDigital * pow(2,2));  
    return dacSpiVal;
}

uint16_t DacReadValue(char* data)
{
    uint16_t readVal;
    uint8_t regNum = 0, byteNum = 0; 
    
    uint8_t dacIndex = data[0];
    uint16_t readVal = ReadIntFromEeprom(EEPROM_DAC_REGS_ADDRESS_OFSEET | DAC_ADDRES[dacIndex], 2);
    
//    for(int byteIdx = 0; byteIdx < DAC_NUM_BYTES_PRESENT_VALUE; byteIdx++)
//    {
//        TxMsg[MSG_DATA_LOCATION + byteIdx] = make8(readVal, byteIdx);
//    }
//    TxMsg[DAC_READ_CONDITION_PACKET_SIZE] = crc8(TxMsg, DAC_READ_CONDITION_PACKET_SIZE);
//    WriteUartMessage("OK \n\r");     
}
// </editor-fold>


/*******************************************************************************
File name: FlashApp.c                                                       ****
File description:   Flash and EEPROM driver application manager.            ****
MCU:                PIC18F45k22                                             ****
Date modified: 29/01/2018 16:14.                                            ****
Author: RoeeZ (Comm-IT).                                                    ****
****************************************************************************** */

#include "FlashApp.h"

// <editor-fold defaultstate="collapsed" desc="EEPROM functions">

uint8_t EepromRead(uint8_t address)
{
    return DATAEE_ReadByte(address);
}

void EepromWrite(uint8_t address, uint8_t data)
{
    DATAEE_WriteByte(address, data);
}

// </editor-fold>
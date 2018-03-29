/*******************************************************************************
File name: FlashApp.h                                                       ****
File description:   Flash driver application manager.                       ****
MCU:                PIC18F45k22                                             ****
Date modified: 29/01/2018 16:14.                                            ****
Author: RoeeZ (Comm-IT).                                                    ****
*******************************************************************************/

#ifndef FLASHAPP_H
#define	FLASHAPP_H

#include <stdint.h>
#include "SystemCommon.h"


// EEPRM Address
#define EEPROM_SYNTH_TX_REGS_ADDRESS_OFSEET     (0)
#define EEPROM_SYNTH_RX_REGS_ADDRESS_OFSEET     (0x20)
#define EEPROM_DAC_REGS_ADDRESS_OFSEET          (0x40)
#define EEPROM_SYSTEM_ADDRESS_OFSEET            (0x50)

// EEPROMM routines:
uint8_t EepromRead(uint8_t address);
void EepromWrite(uint8_t address, uint8_t data);

#endif	/* FLASHAPP_H */


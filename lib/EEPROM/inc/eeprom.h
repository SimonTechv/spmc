#ifndef EEPROM_H
#define EEPROM_H

#include "stdint.h"
#include "pins.h"


/* Global function prototypes (interface) */
void EEPROM_Init();
void EEPROMByteProg(uint16_t address, uint8_t byte);

#endif
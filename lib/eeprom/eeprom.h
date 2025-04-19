#ifndef EEPROM_H
#define EEPROM_H

#include "stdint.h"
#include "pins.h"

/* Min programmable area in flash memory */
#define EEPROM_PAGE_SIZE  32


/* Global function prototypes (interface) */
void EEPROM_Init();
void EEPROMByteProg(uint16_t address, uint8_t byte);
void EEPROMPageProg(uint16_t address, uint8_t *txbuf, uint8_t size);

void EEPROMWrite(uint16_t address, uint8_t *txbuf, uint16_t size);
void EEPROMRead(uint16_t address, uint8_t *rxbuf, uint16_t size);


#endif
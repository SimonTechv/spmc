#include "eeprom.h"
#include "em_cmu.h"
#include "em_i2c.h"
#include "em_gpio.h"
#include "pins.h"

void EEPROM_Init()
{
  __NOP();
}

// void EEPROMPageProg(uint16_t addr, uint8_t *src, uint8_t size)

void EEPROMByteProg(uint16_t address, uint8_t byte)
{
  /* write MSB + LSB + BYTE */
  uint8_t cmd[3] = {0};

  cmd[0] = address >> 8;
  cmd[1] = address & 0xFF;
  cmd[2] = byte;

  /* Configure */
  I2C_TransferSeq_TypeDef t = {0};
  t.flags = I2C_FLAG_WRITE;
  t.addr = EEPROM_ADDR << 1;
  t.buf[0].len = sizeof(cmd);
  t.buf[0].data = &cmd[0];

  /* If EEPROM respond NACK -> RETRY */
  retry:

  I2C_TransferReturn_TypeDef ret = I2C_TransferInit(I2C0, &t);

  while (ret == i2cTransferInProgress) 
  {
    ret = I2C_Transfer(I2C0);

    if (ret == i2cTransferNack)
    {
      goto retry;
    }
  }
}


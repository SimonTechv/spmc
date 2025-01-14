#include "eeprom.h"
#include "em_cmu.h"
#include "em_i2c.h"
#include "em_gpio.h"
#include "pins.h"

/* Internal used functions */
static void EEPROMBusTransfer(I2C_TypeDef *i2c, I2C_TransferSeq_TypeDef *seq);

void EEPROM_Init()
{
  __NOP();
}

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

  /* Perform transfer */
  EEPROMBusTransfer(I2C0, &t);
}


void EEPROMPageProg(uint16_t address, uint8_t *txbuf, uint8_t size)
{
  /* Input checking */
  if (size == 0 || txbuf == 0) return;

  /* Size correction */
  uint16_t temp_prog_size = EEPROM_PAGE_SIZE - (address % EEPROM_PAGE_SIZE);

  /* If programmable size is less than end of page */
  if (size >= temp_prog_size)
  {
    size = temp_prog_size;
  }

  /* write MSB + LSB + BYTE */
  uint8_t cmd[2] = {0};

  cmd[0] = address >> 8;
  cmd[1] = address & 0xFF;

  /* Configure */
  I2C_TransferSeq_TypeDef t = {0};
  t.flags = I2C_FLAG_WRITE_WRITE;
  t.addr = EEPROM_ADDR << 1;

  /* WRITE address */
  t.buf[0].len = sizeof(cmd);
  t.buf[0].data = &cmd[0];

  /* WRITE data */
  t.buf[1].len  = size;
  t.buf[1].data = txbuf;

  /* Perform transfer */
  EEPROMBusTransfer(I2C0, &t);
}

/**
 * @brief Write raw data to any EEPROM address with page alignment
 * 
 * @param address Address in flash memory
 * @param txbuf   Source buffer
 * @param size    Buffer size
 */
void EEPROMWrite(uint16_t address, uint8_t *txbuf, uint16_t size)
{
  /* Input checking */
  if (size == 0 || txbuf == 0) return;

  uint16_t temp_prog_size = EEPROM_PAGE_SIZE - (address % EEPROM_PAGE_SIZE);
  uint16_t temp_prog_addr = address;
  uint16_t end_address    = address + size; 

  /* If programmable size is less than end of page */
  if (size < temp_prog_size)
  {
    temp_prog_size = size;
  }

  /* Perform page by page programming */
  do
  {
    EEPROMPageProg(temp_prog_addr, txbuf, temp_prog_size);

    temp_prog_addr += temp_prog_size;
    txbuf          += temp_prog_size;

    // EOF achieved?
    if ((temp_prog_addr + EEPROM_PAGE_SIZE) > end_address)
    {
      // Last one
      temp_prog_size = end_address - temp_prog_addr;
    }
    else
    {
      // Next one
      temp_prog_size = EEPROM_PAGE_SIZE;
    }
  } while(temp_prog_addr < end_address);

  return;
}


void EEPROMRead(uint16_t address, uint8_t *rxbuf, uint16_t size)
{
  /* set ADDR MSB + LSB */
  uint8_t cmd[2] = {0};

  cmd[0] = address >> 8;
  cmd[1] = address & 0xFF;

  /* Configure ADDR setting */
  I2C_TransferSeq_TypeDef t = {0};
  t.flags = I2C_FLAG_WRITE_READ;
  t.addr = EEPROM_ADDR << 1;
  t.buf[0].len = sizeof(cmd);
  t.buf[0].data = &cmd[0];
  t.buf[1].data = rxbuf;
  t.buf[1].len  = size;

  /* Perform transfer */
  EEPROMBusTransfer(I2C0, &t);
}


static void EEPROMBusTransfer(I2C_TypeDef *i2c, I2C_TransferSeq_TypeDef *seq)
{

  // Acquire I2C bus mutex 
  #warning "Mutex acquire needed"

  /* If EEPROM respond NACK -> RETRY */
  retry:

  I2C_TransferReturn_TypeDef ret = I2C_TransferInit(i2c, seq);

  while (ret == i2cTransferInProgress)
  {
    ret = I2C_Transfer(i2c);

    if (ret == i2cTransferNack)
    {
      goto retry;
    }
  }

  // Release I2C bus mutex 
  #warning "Mutex release needed"
}
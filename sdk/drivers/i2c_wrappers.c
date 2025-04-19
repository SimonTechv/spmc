/**
 * @file i2c_wrappers.c
 * @author anonymous (undefined)
 * @brief Provide beautiful HAL-style wrappers over fucking emlib shitcode
 * @version 0.1
 * @date 2025-04-19
 * 
 * @copyright Copyright (c) 2025
 * 
 */



#include "i2c_wrappers.h"



int32_t LightSensorWriteRegister(uint8_t slave_addr, uint8_t reg_addr, uint16_t value)
{
  /** Split register into transfer array */
  uint8_t reg[2] = 
  {
    (uint8_t)(value >> 8),
    (uint8_t)(value & 0xFF)
  };


  /** Transfer sequence write N data by reg address */
  I2C_TransferSeq_TypeDef t = 
  {
    .addr = slave_addr << 1,       
    .flags = I2C_FLAG_WRITE_WRITE,  
    .buf[0] = 
    {
      .data = &reg_addr,
      .len = sizeof(reg_addr)
    },
    .buf[1] =
    {
      .data = reg,
      .len = sizeof(reg)
    }
  };

  return (I2C_PollingTransfer(&t) == i2cTransferDone) ? (0) : (-1);
}


int32_t LightSensorReadRegister(uint8_t slave_addr, uint8_t reg_addr, uint16_t *value)
{

  uint8_t recv[2] = {0};

  /** Transfer sequence write N data by reg address */
  I2C_TransferSeq_TypeDef t = 
  {
    .addr = slave_addr << 1,       
    .flags = I2C_FLAG_WRITE_READ,  
    .buf[0] = 
    {
      .data = &reg_addr,
      .len = sizeof(reg_addr)
    },
    .buf[1] =
    {
      .data = recv,
      .len = sizeof(recv)
    }
  };

  /** Perform transaction */
  int32_t ret = (I2C_PollingTransfer(&t) == i2cTransferDone) ? (0) : (-1);

  /** Fill uint16_t pointer */
  *value = (recv[0] << 8) | recv[1];

  return ret;
}



I2C_TransferReturn_TypeDef I2C_PollingTransfer(I2C_TransferSeq_TypeDef *t)
{
  uint16_t try_count = 0;

  retry:

  I2C_TransferReturn_TypeDef ret = I2C_TransferInit(I2C0, t);

  while (ret == i2cTransferInProgress)
  {
    ret = I2C_Transfer(I2C0);

    if (ret == i2cTransferNack && try_count < MAX_I2C_RETRY_COUNT)
    {
      try_count++;
      goto retry;
    }
  }

  return ret;
}


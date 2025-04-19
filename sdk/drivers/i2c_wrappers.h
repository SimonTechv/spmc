/**
 * @file i2c_wrappers.h
 * @author anonymous (undefined)
 * @brief Provide beautiful HAL-style wrappers over fucking emlib shitcode
 * @version 0.1
 * @date 2025-04-19
 * 
 * @copyright Copyright (c) 2025
 * 
 */


#ifndef I2C_WRAPPERS_H
#define I2C_WRAPPERS_H


#include <stdint.h>
#include <em_i2c.h>



#define MAX_I2C_RETRY_COUNT 2


/**
 * @brief 
 * 
 * @param slave_addr 
 * @param reg_addr 
 * @param value 
 * @return int32_t (1 = SUCCESS, 0 = ERROR)
 */
int32_t LightSensorWriteRegister(uint8_t slave_addr, uint8_t reg_addr, uint16_t value);


/**
 * @brief 
 * 
 * @param slave_addr 
 * @param reg_addr 
 * @param value 
 * @return int32_t 
 */
int32_t LightSensorReadRegister(uint8_t slave_addr, uint8_t reg_addr, uint16_t *value);


/**
 * @brief Common polling I2C transaction
 * 
 * @param t internal emlib i2c sequence structure
 * @return I2C_TransferReturn_TypeDef (check emlib I2C_TransferReturn_TypeDef enum)
 */
I2C_TransferReturn_TypeDef I2C_PollingTransfer(I2C_TransferSeq_TypeDef *t);


#endif
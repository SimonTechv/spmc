/**
 * @file lsensor.h
 * @author anonymous (undefined)
 * @brief Light sensor OPT3001DNPR polling library
 * @version 0.1
 * @date 2025-04-19
 * 
 * @copyright Copyright (c) 2025
 * 
 */


#ifndef LSENSOR_H
#define LSENSOR_H


#include <stdint.h>

#include <pins.h>


// Internal registers
#define OPT3001_REG_RESULT     0x00
#define OPT3001_REG_CONFIG     0x01
#define OPT3001_REG_LOW_LIMIT  0x02
#define OPT3001_REG_HIGH_LIMIT 0x03
#define OPT3001_REG_MFG_ID     0x7E
#define OPT3001_REG_DEV_ID     0x7F


// Configuration register settings
#define OPT3001_CONFIG_CONTINUOUS 0x06        // Continuous mode
#define OPT3001_CONFIG_CONVERSION_800MS 0x00  // 800ms conversion time
#define OPT3001_CONFIG_RANGE_AUTO 0xC000      // Automatic full-scale range
#define OPT3001_CONFIG_DEFAULT (OPT3001_CONFIG_CONTINUOUS | OPT3001_CONFIG_CONVERSION_800MS | OPT3001_CONFIG_RANGE_AUTO)

// Manufacturer information
#define OPT3001_MFG_ID 0x5449
#define OPT3001_DEV_ID 0x3001


/**
 * @brief Get Manufacturer ID Register
 * 
 * @return uint16_t manufacturer id
 */
uint16_t OPT3001_ReadManufacturerID(void);


/**
 * @brief Get Device ID Register
 * 
 * @return uint16_t device id
 */
uint16_t OPT3001_ReadDeviceID(void);

#endif
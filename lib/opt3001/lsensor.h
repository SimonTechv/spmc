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

// Manufacturer information
#define OPT3001_MFG_ID 0x5449
#define OPT3001_DEV_ID 0x3001

// Shift bits
#define OPT3001_RN_SHIFT       12  // Range Number (RN), bits 15-12
#define OPT3001_CT_SHIFT       11  // Conversion Time (CT), bit 11
#define OPT3001_M_SHIFT        9   // Mode of Operation (M), bits 10-9
#define OPT3001_OVF_SHIFT      8   // Overflow Flag (OVF), bit 8
#define OPT3001_CRF_SHIFT      7   // Conversion Ready Flag (CRF), bit 7
#define OPT3001_FH_SHIFT       6   // Flag High (FH), bit 6
#define OPT3001_FL_SHIFT       5   // Flag Low (FL), bit 5
#define OPT3001_L_SHIFT        4   // Latch (L), bit 4
#define OPT3001_POL_SHIFT      3   // Polarity (POL), bit 3
#define OPT3001_ME_SHIFT       2   // Mask Exponent (ME), bit 2
#define OPT3001_FC_SHIFT       0   // Fault Count (FC), bits 1-0

// Range Number (RN)
#define OPT3001_RN_AUTO        0xC  // Auto range
#define OPT3001_RN_120         0x0  // 120.96 lx
#define OPT3001_RN_241         0x1  // 241.92 lx
#define OPT3001_RN_483         0x2  // 483.84 lx
#define OPT3001_RN_967         0x3  // 967.68 lx
#define OPT3001_RN_1935        0x4  // 1935.36 lx
#define OPT3001_RN_3870        0x5  // 3870.72 lx
#define OPT3001_RN_7741        0x6  // 7741.44 lx
#define OPT3001_RN_15482       0x7  // 15482.88 lx
#define OPT3001_RN_30965       0x8  // 30965.76 lx
#define OPT3001_RN_61931       0x9  // 61931.52 lx
#define OPT3001_RN_123863      0xA  // 123863.04 lx
#define OPT3001_RN_247726      0xB  // 247726.08 lx

// Conversion Time (CT)
#define OPT3001_CT_100MS       0x0  // 100 мс
#define OPT3001_CT_800MS       0x1  // 800 мс

// Mode of Operation (M)
#define OPT3001_M_SHUTDOWN     0x0  // Выключен
#define OPT3001_M_SINGLE       0x1  // Однократное измерение
#define OPT3001_M_CONTINUOUS   0x2  // Непрерывное измерение

// Latch (L)
#define OPT3001_L_LATCH        0x1  // С фиксацией
#define OPT3001_L_TRANSPARENT  0x0  // Прозрачный режим

// Polarity (POL)
#define OPT3001_POL_ACTIVE_HIGH 0x0 // Активный высокий
#define OPT3001_POL_ACTIVE_LOW  0x1 // Активный низкий

// Fault Count (FC)
#define OPT3001_FC_1           0x0  // 1 сбой
#define OPT3001_FC_2           0x1  // 2 сбоя
#define OPT3001_FC_4           0x2  // 4 сбоя
#define OPT3001_FC_8           0x3  // 8 сбоев

// Create configuration register macro
#define OPT3001_CONFIG(RN, CT, M, L, POL, FC) \
    ((uint16_t)(((RN) & 0xF) << OPT3001_RN_SHIFT) | \
     ((CT) & 0x1) << OPT3001_CT_SHIFT | \
     ((M) & 0x3) << OPT3001_M_SHIFT | \
     ((L) & 0x1) << OPT3001_L_SHIFT | \
     ((POL) & 0x1) << OPT3001_POL_SHIFT | \
     ((FC) & 0x3) << OPT3001_FC_SHIFT)


/*

  -- Configuration register macro examples --

  #define OPT3001_CFG_DEFAULT \
      OPT3001_CONFIG(OPT3001_RN_AUTO, OPT3001_CT_800MS, OPT3001_M_CONTINUOUS, \
                     OPT3001_L_LATCH, OPT3001_POL_ACTIVE_HIGH, OPT3001_FC_1)

  #define OPT3001_CFG_SINGLE_SHOT \
      OPT3001_CONFIG(OPT3001_RN_AUTO, OPT3001_CT_100MS, OPT3001_M_SINGLE, \
                     OPT3001_L_LATCH, OPT3001_POL_ACTIVE_HIGH, OPT3001_FC_1)

  #define OPT3001_CFG_LOW_POWER \
      OPT3001_CONFIG(OPT3001_RN_AUTO, OPT3001_CT_100MS, OPT3001_M_CONTINUOUS, \
                     OPT3001_L_LATCH, OPT3001_POL_ACTIVE_HIGH, OPT3001_FC_1)
*/


/**
 * @brief Read Lux value
 * 
 * @return float floating point measured lux value
 */
float OPT3001_ReadLux(void);


/**
 * @brief Initialize opt3001 light sensor
 * 
 * @return int32_t (0 = SUCCESS, -1 = ERROR)
 */
int32_t OPT3001_Init(void);


/**
 * @brief Get Manufacturer ID Register
 * 
 * @return uint16_t manufacturer id
 */
uint16_t OPT3001_ReadManufacturerID(void);


/**
 * @brief Get Device ID Register value
 * 
 * @return uint16_t device id
 */
uint16_t OPT3001_ReadDeviceID(void);


/**
 * @brief Get Config Register value
 * 
 * @return uint16_t current configuration register value
 */
uint16_t OPT3001_ReadConfigReg(void);

#endif
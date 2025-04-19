#include <i2c_wrappers.h>


#include "lsensor.h"


float OPT3001_ReadLux(void) {
  
  uint16_t raw; LightSensorReadRegister(OPT3001_ADDR, OPT3001_REG_RESULT, &raw);

  uint16_t mantissa = raw & 0x0FFF;
  uint8_t exponent = (raw >> 12) & 0x0F;

  return 0.01 * (1 << exponent) * mantissa;
}


void OPT3001_Init(void)
{
  uint16_t reg = OPT3001_CONFIG(OPT3001_RN_AUTO, OPT3001_CT_800MS, OPT3001_M_CONTINUOUS, \
    OPT3001_L_LATCH, OPT3001_POL_ACTIVE_HIGH, OPT3001_FC_1);

  LightSensorWriteRegister(OPT3001_ADDR, OPT3001_REG_CONFIG, reg);
}


uint16_t OPT3001_ReadManufacturerID(void) {

  uint16_t reg = 0;

  LightSensorReadRegister(OPT3001_ADDR, OPT3001_REG_MFG_ID, &reg);

  return reg;
}


uint16_t OPT3001_ReadDeviceID(void) {

  uint16_t reg = 0;

  LightSensorReadRegister(OPT3001_ADDR, OPT3001_REG_DEV_ID, &reg);

  return reg;
}


uint16_t OPT3001_ReadConfigReg(void) {

  uint16_t reg = 0;

  LightSensorReadRegister(OPT3001_ADDR, OPT3001_REG_CONFIG, &reg);

  return reg;
}
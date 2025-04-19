#include <i2c_wrappers.h>


#include "lsensor.h"



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
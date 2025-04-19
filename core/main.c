/**
 * @file main.c
 * @author anonymous (undefined)
 * @brief Entry point of firmware & provide device functionality
 * @version 0.1
 * @date 2025-04-18
 * 
 * @copyright Copyright (c) 2025
 * 
 */


#include <log.h>
#include <em_chip.h>
#include <init.h>
#include <pins.h>
#include <lsensor.h>

#include "main.h"


#ifdef LOG_EN
uint8_t rtt_buff[256];
#endif


/**
 * @brief Application entry point. Running as state-machine manage module functionality.
 * 
 * @return int 
 */
int main(void) {

  CHIP_Init();

# ifdef LOG_EN
  SEGGER_RTT_ConfigUpBuffer(0, NULL, rtt_buff, 256, SEGGER_RTT_MODE_NO_BLOCK_SKIP);
  LOG("Power harvesting module started...\n");
# endif

  ConfigureIO();
  ConfigureI2C();
  LOG("GPIO configured...\n");

  V5_ENA;
  LOG("TPS61040 enabled...\n");

  OPT3001_Init();
  LOG("Light sensor init\n");
  LOG("Light sensor: MAN_ID : 0x%x\n", OPT3001_ReadManufacturerID());
  LOG("Light sensor: DEV_ID : 0x%x\n", OPT3001_ReadDeviceID());

  OPT3001_Init();

  for (;;) {
    for(uint32_t i = 0; i  < 10000000; i++) {}

    float lux = OPT3001_ReadLux();
    LOG("Light sensor: %d,%d lux\n", (int16_t)lux,  (int16_t)((int32_t)(lux * 100.0f) % 100));
  }
}


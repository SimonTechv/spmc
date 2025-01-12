/***************************************************************************//**
 * @file main.c
 * @brief main() function.
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/
#include "stdint.h"

#include "em_device.h"
#include "em_cmu.h"
#include "em_emu.h"
#include "em_gpio.h"
#include "em_chip.h"
#include "em_i2c.h"

#include "main.h"
#include "pins.h"
#include "eeprom.h"

/* Global variables */
I2C_TypeDef I2C0_handle;


int main(void)
{

  CHIP_Init();

  /* Configure peripheral GPIO functions */
  configureIO();
  configureI2C();

  /* Enable DC-DC */
  GPIO_PinOutSet(TPS61040_EN_PORT, TPS61040_EN_PIN);

  for(;;)
  {


  }
}



/**
 * Configure simple driven GPIO lines
 */
void configureIO()
{
  /* Enable GPIO periphery unit */
  CMU_ClockEnable(cmuClock_GPIO, true);

  /* Relay control GPIO */
  GPIO_PinModeSet(REL_PORT, REL_SET_PIN, gpioModePushPull, 0);
  GPIO_PinModeSet(REL_PORT, REL_RESET_PIN, gpioModePushPull, 0);

  /* DC-DC */
  GPIO_PinModeSet(TPS61040_EN_PORT, TPS61040_EN_PIN, gpioModePushPull, 0);
}


/**
 * Configure I2C0 bus
 */
void configureI2C()
{

  I2C_Init_TypeDef I2C0_InitHandle = I2C_INIT_DEFAULT;

  /* Set I2C periphery parameters */
  I2C0_InitHandle.enable                    = 1;
  I2C0_InitHandle.master                    = 1;
  I2C0_InitHandle.freq                      = I2C_FREQ_STANDARD_MAX;
  I2C0_InitHandle.clhr                      = i2cClockHLRStandard;

  /* Enable I2C periphery */
  CMU_ClockEnable(cmuClock_I2C0, true);

  /* Configure I2C0 periphery GPIO lines (external pull & open drain) */
  GPIO_PinModeSet(I2C0_PORT, I2C0_SCL_PIN, gpioModeWiredAndFilter, 1);
  GPIO_PinModeSet(I2C0_PORT, I2C0_SDA_PIN, gpioModeWiredAndFilter, 1);

  /* Perform routing */
  I2C0->ROUTE = I2C_ROUTE_SDAPEN | I2C_ROUTE_SCLPEN;
  I2C0->ROUTE = (I2C0->ROUTE & (~_I2C_ROUTE_LOCATION_MASK)) | I2C_ROUTE_LOCATION_LOC0;

  /* Perform init */
  I2C_Init(&I2C0_handle, &I2C0_InitHandle);
}
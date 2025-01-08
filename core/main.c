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

#include "pins.h"

/**
 * Temporary prototypes
 */
void configureIO(void);


int main(void)
{

  CHIP_Init();

  /* Configure peripheral GPIO functions */
  configureIO();

  GPIO_PinOutSet(REL_PORT, REL_SET_PIN);


  for(;;)
  {

  }
}

/**
 * Configure MCU GPIO pins
 */
void configureIO()
{
  /* Enable GPIO peripheral unit */
  CMU_ClockEnable(cmuClock_GPIO, true);

  /* Relay control GPIO */
  GPIO_PinModeSet(REL_PORT, REL_SET_PIN, gpioModePushPull, 0);
  GPIO_PinModeSet(REL_PORT, REL_RESET_PIN, gpioModePushPull, 0);
}
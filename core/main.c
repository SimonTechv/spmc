#include "stdint.h"

#include "em_chip.h"
#include "em_cmu.h"
#include "em_device.h"
#include "em_emu.h"
#include "em_gpio.h"
#include "em_i2c.h"


#include "eeprom.h"
#include "main.h"
#include "pins.h"

#include "SEGGER_RTT.h"

#include "eefs_filesys.h"


uint8_t rtt_buff[256];

int main(void) {

  CHIP_Init();

  /* Configure RTT buffer */
  int res = SEGGER_RTT_ConfigUpBuffer(0, NULL, rtt_buff, 256, SEGGER_RTT_MODE_NO_BLOCK_SKIP);

  SEGGER_RTT_printf(0, "MCU started...\n", res);

  /* Configure peripheral GPIO functions */
  configureIO();
  configureI2C();

  SEGGER_RTT_printf(0, "GPIO configured...\n", res);

  /* Enable DC-DC */
  GPIO_PinOutSet(TPS61040_EN_PORT, TPS61040_EN_PIN);
  SEGGER_RTT_printf(0, "TPS61040 run...\n", res);
  
  for (;;) {

    for(uint32_t i = 0; i  < 10000000; i++) {}

    SEGGER_RTT_printf(0, "NOP...\n", res);
  }
}

/**
 * Configure simple driven GPIO liPnes
 */
void configureIO()
{
  /* Enable GPIO periphery unit */
  CMU_ClockEnable(cmuClock_GPIO, true);

  /* Relay control GPIO */
  GPIO_PinModeSet(REL_PORT, REL_SET_PIN, gpioModePushPull, 0);
  GPIO_PinModeSet(REL_PORT, REL_RESET_PIN, gpioModePushPull, 0);

  /* DC-DC */
//   GPIO_PinModeSet(TPS61040_EN_PORT, TPS61040_EN_PIN, gpioModePushPull, 0);
}

/**
 * Configure I2C0 bus
 */
void configureI2C() {

  I2C_Init_TypeDef I2C0_InitHandle = I2C_INIT_DEFAULT;

  /* Set I2C periphery parameters */
  I2C0_InitHandle.enable = true;
  I2C0_InitHandle.master = true;
  I2C0_InitHandle.freq = I2C_FREQ_STANDARD_MAX;
  I2C0_InitHandle.clhr = i2cClockHLRStandard;

  /* Enable I2C periphery */
  CMU_ClockEnable(cmuClock_I2C0, true);

  /* Configure I2C0 periphery GPIO lines (external pull & open drain) */
  GPIO_PinModeSet(I2C0_PORT, I2C0_SCL_PIN, gpioModeWiredAndPullUp, 1);
  GPIO_PinModeSet(I2C0_PORT, I2C0_SDA_PIN, gpioModeWiredAndPullUp, 1);

  /* Perform routing */
  I2C0->ROUTE = I2C_ROUTE_SDAPEN | I2C_ROUTE_SCLPEN;
  I2C0->ROUTE =
      (I2C0->ROUTE & (~_I2C_ROUTE_LOCATION_MASK)) | I2C_ROUTE_LOCATION_LOC4;

  /* Perform init */
  I2C_Init(I2C0, &I2C0_InitHandle);
}

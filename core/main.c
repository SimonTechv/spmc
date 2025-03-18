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

#include "eefs_filesys.h"


uint8_t byte_array_dec[64u] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63};


int main(void) {

  CHIP_Init();

  /* Configure peripheral GPIO functions */
  configureIO();
  configureI2C();

  /* Enable DC-DC */
  GPIO_PinOutSet(TPS61040_EN_PORT, TPS61040_EN_PIN);

  uint8_t readbuf[32] = {0};

  /* Init filesystem */
  EEFS_InitFS("/EEPROM", (uint16)0x0000);

  /* Mount filesystem */
  EEFS_Mount("/EERPOM", "/FS0");

  __NOP();

  for (;;) {
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
  GPIO_PinModeSet(TPS61040_EN_PORT, TPS61040_EN_PIN, gpioModePushPull, 0);
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

void ConfigurePeripheryClock(void) {}
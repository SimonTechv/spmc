#ifndef PINS_H
#define PINS_H


#include <em_cmu.h>
#include <em_gpio.h>


/* IIC bus addresses */
#define EEPROM_ADDR         0x50
#define OPT3001_ADDR        0x44
#define TMP102_ADDR         0x48

/* GPIO reg CMU def */
#define GPIO_CMU_CLK        cmuClock_GPIO 

/* DC-DC enable pin */
#define TPS61040_EN_PIN     7
#define TPS61040_EN_PORT    gpioPortB

/* I2C module interface pins */
#define I2C0_CMU_CLK        cmuClock_I2C0
#define I2C0_SDA_PIN        0
#define I2C0_SCL_PIN        1
#define I2C0_PORT           gpioPortC

/* Relay control pins */
#define REL_SET_PIN         14
#define REL_RESET_PIN       8
#define REL_PORT            gpioPortB


#endif
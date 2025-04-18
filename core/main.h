#ifndef MAIN_H
#define MAIN_H


#include <stdint.h>


#define V5_ENA GPIO_PinOutSet(TPS61040_EN_PORT, TPS61040_EN_PIN)
#define V5_DIS GPIO_PinOutClear(TPS61040_EN_PORT, TPS61040_EN_PIN)


#endif
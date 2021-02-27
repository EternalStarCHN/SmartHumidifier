#ifndef __HUMIDIFIERCONTROL_H
#define __HUMIDIFIERCONTROL_H

#include "stm32f1xx_hal.h"
#include "gpio.h"

void Humidifier_On(void);
void Humidifier_Off(void);
void Humidifier_Play(void);

#endif
#ifndef __USERMAIN_H
#define __USERMAIN_H

#include "stm32f1xx_hal.h"
#include "usart.h"
#include "stdio.h"
#include "oled.h"
#include "esp8266.h"
#include "beep.h"
#include "HumidifierControl.h"
#include "sht30_i2c_drv.h"

void Usermain(void);
void UserInit(void);
void OLED_Display(void);

#endif
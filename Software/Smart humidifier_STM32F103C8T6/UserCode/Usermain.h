#ifndef __USERMAIN_H
#define __USERMAIN_H

#include "stm32f1xx_hal.h"
#include "usart.h"
#include "stdio.h"
#include "oled.h"
#include "esp.h"
#include "beep.h"
#include "HumidifierControl.h"
#include "sht30_i2c_drv.h"

enum Hum_Sta{ 
	Hum_Stop = 0, 
	Hum_Run = 1,
	Hum_Int = 2,
	Hum_Auto = 3
};

void Usermain(void);
void UserInit(void);
void OLED_Display(void);
void User_Update(void);

#endif
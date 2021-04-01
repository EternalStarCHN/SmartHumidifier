#ifndef __BEEP_H
#define __BEEP_H

#include "gpio.h"

void BEEP_Yell(void);
void BEEP_Stop(void);
void BEEP_Yell_Times(uint8_t Times,uint8_t On_delay_ms,uint8_t Off_delay_ms);
	
#endif
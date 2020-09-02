#include "esp8266.h"

void Esp8266_StatusConfirm(void)
{
	if(HAL_GPIO_ReadPin(ESP8266_State_GPIO_Port,ESP8266_State_Pin)== RESET)
	{
		OLED_ShowStr(85, 0, "Online ", 1);
	}
	else
	{
		OLED_ShowStr(85, 0, "Offline", 1);		
	}
}
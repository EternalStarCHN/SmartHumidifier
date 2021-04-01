#include "esp8266.h"

extern uint8_t Hum_Sta;

void Esp8266_StatusConfirm(void)
{
	if(HAL_GPIO_ReadPin(ESP8266_STA_GPIO_Port, ESP8266_STA_Pin)== RESET)//检测WIFI连接状态(0：连接;1：断开)
	{
		OLED_ShowString(0, 0, "Online ", 12);
	}
	else
	{
		OLED_ShowString(0, 0, "Offline", 12);		
	}
	if(HAL_GPIO_ReadPin(HUM_STA_GPIO_Port, HUM_STA_Pin)== SET)//检测加湿器工作命令(0：运行;1：停止)
	{
		OLED_ShowString(108, 0, "ON ", 12);
		Hum_Sta = 1;
	}
	else
	{
		OLED_ShowString(108, 0, "OFF", 12);
		Hum_Sta = 0;		
	}
}
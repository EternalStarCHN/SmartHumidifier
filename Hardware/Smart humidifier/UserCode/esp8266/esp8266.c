#include "esp8266.h"

void Esp8266_StatusConfirm(void)
{
	if(HAL_GPIO_ReadPin(ESP8266_State_GPIO_Port,ESP8266_State_Pin)== RESET)//检测WIFI连接状态(0:连接;1：断开)
	{
		OLED_ShowStr(0, 0, "Online ", 1);
	}
	else
	{
		OLED_ShowStr(0, 0, "Offline", 1);		
	}
	if(HAL_GPIO_ReadPin(Humidifier_State_GPIO_Port,Humidifier_State_Pin)== SET)//检测加湿器工作命令(0:停止;1：运行)
	{
		OLED_ShowStr(108, 0, "ON ", 1);
	}
	else
	{
		OLED_ShowStr(108, 0, "OFF", 1);		
	}
}
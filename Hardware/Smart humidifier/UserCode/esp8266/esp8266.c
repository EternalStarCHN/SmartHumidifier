#include "esp8266.h"

uint8_t Esp_Sta = 0;

void Esp8266_StatusConfirm(void)
{
	//检测WIFI连接状态(0：连接;1：断开)
	if( HAL_GPIO_ReadPin(ESP8266_STA_GPIO_Port, ESP8266_STA_Pin) == RESET )
	{
		OLED_ShowString(0, 0, "Online ", 12);
		Esp_Sta = 1;
	}
	else
	{
		OLED_ShowString(0, 0, "Offline", 12);
		Esp_Sta = 0;		
	}
	//检测加湿器工作命令(0：运行;1：停止)
	if( (HAL_GPIO_ReadPin(HUM_STA_GPIO_Port, HUM_STA_Pin) == RESET) )//Esp_Sta && 
	{
		OLED_ShowString(104, 0, "ON ", 12);
	}
	else if((HAL_GPIO_ReadPin(HUM_STA_GPIO_Port, HUM_STA_Pin) == SET) )
	{
		OLED_ShowString(104, 0, "OFF", 12);
	}
	else OLED_ShowString(104, 0, "UNK", 12);
}
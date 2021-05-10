#include "HumidifierControl.h"

uint8_t Hum_Mod = Hum_Run;
uint8_t AntiBur_Flag = 0;
float Humidity_Set = 65;
extern float humidity;

/**
 * @brief    加湿器开
 * @param    无
 * @note   无
*/
void Humidifier_On(void){
	HAL_GPIO_WritePin(HUM_CON_GPIO_Port, HUM_CON_Pin, GPIO_PIN_SET);
}

/**
 * @brief    加湿器关
 * @param    无
 * @note   无
*/
void Humidifier_Off(void){
	HAL_GPIO_WritePin(HUM_CON_GPIO_Port, HUM_CON_Pin, GPIO_PIN_RESET);
}

/**
 * @brief    加湿器运行
 * @param    无
 * @note     停止模式-关闭；开始模式-开启；间歇开启模式-开5s关5s（500ms判断一次是否中途改变状态）；自动模式-湿度低于设定值开启，湿度高于设定值关闭；
*/
void Humidifier_Play(void){
	if( Hum_Mod == 1 )
		Humidifier_On();
	else if( Hum_Mod == 0 )
		Humidifier_Off();
	else if( Hum_Mod == 2){
		if( Hum_Mod == 2 ) Humidifier_On();//开5s
		if( Hum_Mod == 2 ) HAL_Delay(500);
		if( Hum_Mod == 2 ) HAL_Delay(500);
		if( Hum_Mod == 2 ) HAL_Delay(500);
		if( Hum_Mod == 2 ) HAL_Delay(500);
		if( Hum_Mod == 2 ) HAL_Delay(500);
		if( Hum_Mod == 2 ) HAL_Delay(500);
		if( Hum_Mod == 2 ) HAL_Delay(500);
		if( Hum_Mod == 2 ) HAL_Delay(500);
		if( Hum_Mod == 2 ) HAL_Delay(500);
		if( Hum_Mod == 2 ) HAL_Delay(500);		
		if( Hum_Mod == 2 ) Humidifier_Off();//关5s		
		if( Hum_Mod == 2 ) HAL_Delay(500);
		if( Hum_Mod == 2 ) HAL_Delay(500);
		if( Hum_Mod == 2 ) HAL_Delay(500);
		if( Hum_Mod == 2 ) HAL_Delay(500);
		if( Hum_Mod == 2 ) HAL_Delay(500);
		if( Hum_Mod == 2 ) HAL_Delay(500);
		if( Hum_Mod == 2 ) HAL_Delay(500);
		if( Hum_Mod == 2 ) HAL_Delay(500);
		if( Hum_Mod == 2 ) HAL_Delay(500);
		if( Hum_Mod == 2 ) HAL_Delay(500);	
	}
	else if( Hum_Mod == 3){
		if(humidity < Humidity_Set) Humidifier_On();
		else Humidifier_Off();
	}
}
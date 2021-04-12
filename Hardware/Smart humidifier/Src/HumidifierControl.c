#include "HumidifierControl.h"

uint8_t Hum_Mod = Hum_Stop;
uint8_t AntiBur_Flag = 0;
float Humidity_Set = 65;
extern float humidity;

void Humidifier_On(void){
	HAL_GPIO_WritePin(HUM_CON_GPIO_Port, HUM_CON_Pin, GPIO_PIN_SET);
}
void Humidifier_Off(void){
	HAL_GPIO_WritePin(HUM_CON_GPIO_Port, HUM_CON_Pin, GPIO_PIN_RESET);
}
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
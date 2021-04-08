#include "HumidifierControl.h"

uint8_t Hum_Mod = Hum_Stop;
uint8_t AntiBur_Flag = 1;

void Humidifier_On(void){
	HAL_GPIO_WritePin(HUM_CON1_GPIO_Port, HUM_CON1_Pin, GPIO_PIN_SET);
}
void Humidifier_Off(void){
	HAL_GPIO_WritePin(HUM_CON1_GPIO_Port, HUM_CON1_Pin, GPIO_PIN_RESET);
}
void Humidifier_Play(void){
	if( Hum_Mod == 1 )
		Humidifier_On();
	else if( Hum_Mod == 0 )
		Humidifier_Off();
	else {
		Humidifier_On();
		HAL_Delay(500);
		if( Hum_Mod == 2 ) HAL_Delay(500);
		if( Hum_Mod == 2 ) HAL_Delay(500);
		if( Hum_Mod == 2 ) HAL_Delay(500);
		if( Hum_Mod == 2 ){
			Humidifier_Off();
			HAL_Delay(500);	
		}
		if( Hum_Mod == 2 ) HAL_Delay(500);
		if( Hum_Mod == 2 ) HAL_Delay(500);
		if( Hum_Mod == 2 ) HAL_Delay(500);
	}
}
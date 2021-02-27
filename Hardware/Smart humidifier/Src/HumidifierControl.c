#include "HumidifierControl.h"

uint8_t Hum_Sta = 0;

void Humidifier_On(void){
	HAL_GPIO_WritePin(Humidifier_Control_GPIO_Port,Humidifier_Control_Pin,GPIO_PIN_SET);
}
void Humidifier_Off(void){
	HAL_GPIO_WritePin(Humidifier_Control_GPIO_Port,Humidifier_Control_Pin,GPIO_PIN_RESET);
}
void Humidifier_Play(void){
	if( Hum_Sta == 1 )
		Humidifier_On();
	else if( Hum_Sta == 0 )
		Humidifier_Off();
}
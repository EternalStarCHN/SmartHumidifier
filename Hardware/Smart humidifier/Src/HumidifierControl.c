#include "HumidifierControl.h"

void Humidifier_On(void){
	HAL_GPIO_WritePin(Humidifier_Control_GPIO_Port,Humidifier_Control_Pin,GPIO_PIN_SET);
}
void Humidifier_Off(void){
	HAL_GPIO_WritePin(Humidifier_Control_GPIO_Port,Humidifier_Control_Pin,GPIO_PIN_RESET);
}
#include "beep.h"

/**
* @brief    开启蜂鸣器
* @param    无
* @note	    开启蜂鸣器
*/
void BEEP_Yell(void){
	HAL_GPIO_WritePin(BEEP_CON_GPIO_Port,BEEP_CON_Pin,GPIO_PIN_SET);
}

/**
* @brief    关闭蜂鸣器
* @param     
* @note     关闭蜂鸣器
*/
void BEEP_Stop(void){
	HAL_GPIO_WritePin(BEEP_CON_GPIO_Port,BEEP_CON_Pin,GPIO_PIN_RESET);
}

/**
* @brief    间歇开启蜂鸣器
* @param    Times - 开启次数
* @param    On_delay_ms - 开启时间
* @param    Off_delay_ms - 关闭时间
* @note	    间歇开启蜂鸣器
*/
void BEEP_Yell_Times(uint8_t Times,uint8_t On_delay_ms,uint8_t Off_delay_ms){
	uint8_t i = 0;
	for(i = 0;i<Times;i++){
		HAL_GPIO_WritePin(BEEP_CON_GPIO_Port,BEEP_CON_Pin,GPIO_PIN_SET);
		HAL_Delay(On_delay_ms);
		HAL_GPIO_WritePin(BEEP_CON_GPIO_Port,BEEP_CON_Pin,GPIO_PIN_RESET);
		HAL_Delay(Off_delay_ms);
	}
}
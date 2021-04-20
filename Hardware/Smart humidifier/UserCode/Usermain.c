#include "Usermain.h"

extern char TEMP[45];
extern char HUMI[45];
extern unsigned char BMP1[];
extern uint8_t Hum_Mod;
extern uint8_t SHT30Update_Flag;
extern uint8_t AntiBur_Flag;

void Usermain(void)
{ 
	UserInit();
	while(1)
	{	
		if( !AntiBur_Flag ) User_Update();							//如果防烧标志位为0，则正常运行。
		else{																						//如果防烧标志位为1，触发防烧警报。
			OLED_ShowString(12, 0, "Press any key", 12);
			OLED_ShowString(20, 2, "to exit the ", 12);
			OLED_ShowString(15, 4, "anti-burning", 12);	
			OLED_ShowString(42, 6, "state", 12);
			BEEP_Yell_Times(10, (uint8_t)200, (uint8_t)200);
		}
	}
}

/**
 * @brief    加湿器初始化
 * @param    无
 * @note     调整内部参数可调节声音和画面出现的顺序、蜂鸣器时间等
*/
void UserInit(void)
{
    OLED_Init();
		Humidifier_Off();
    SHT30_Reset();
    if(SHT30_Init() == HAL_OK)
    printf("sht30 init ok.\n");
    else
    printf("sht30 init fail.\n");
		BEEP_Yell_Times(3, (uint8_t)100, (uint8_t)100);
		OLED_DrawBMP(0,0,128,8,BMP1);
		HAL_Delay(300);
		OLED_Clear();
}

/**
 * @brief    OLED屏幕显示函数
 * @param    无
 * @note     调整内部参数可调节OLED屏幕显示样式
*/
void OLED_Display(void){
	OLED_ShowString(0, 1, "----------------", 12);
	OLED_ShowString(10, 2, "TEM:", 12);
  OLED_ShowString(5, 3, TEMP, 16);
	OLED_ShowString(45, 3, "`", 16);
  OLED_ShowString(10, 5, "HUM:", 12);
  OLED_ShowString(5, 6, HUMI, 16);
  OLED_ShowString(45, 6, "%", 16);	
  OLED_ShowString(60, 2, "|", 16);
  OLED_ShowString(60, 4, "|", 16);
  OLED_ShowString(60, 6, "|", 16);
  OLED_ShowString(86, 2, "MOD:", 12);
	switch(Hum_Mod){
		case Hum_Stop:
			OLED_ShowString(78, 4, " ", 16);
			OLED_ShowString(110, 4, ">", 16);
			break;
		case Hum_Run:
			OLED_ShowString(78, 4, "<", 16);
			OLED_ShowString(110, 4, ">", 16);
			break;
		case Hum_Int:
			OLED_ShowString(78, 4, "<", 16);
			OLED_ShowString(110, 4, ">", 16);
			break;
		case Hum_Auto:
			OLED_ShowString(78, 4, "<", 16);
			OLED_ShowString(110, 4, " ", 16);
			break;
		default:
			break;
	}	
	OLED_ShowNum(94, 4, Hum_Mod, 1, 16);
}

/**
 * @brief    用户更新函数
 * @param    无
 * @note     用于更新Esp、SHT30、OLED和加湿器状态
*/
void User_Update(void){
	Esp_StatusConfirm();
	if( SHT30Update_Flag ) SHT30_Update();	
	OLED_Display();
	Humidifier_Play();
}

/* printf重定向 */
#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif 
int fputc(int ch,FILE *f)
{
    uint8_t temp[1]={ch};
    HAL_UART_Transmit(&huart1,temp,1,10);        //UartHandle设置
  return ch;
}
PUTCHAR_PROTOTYPE
{
 HAL_UART_Transmit(&huart1,(uint8_t*)&ch,1,10);
 return ch;
}

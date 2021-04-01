#include "Usermain.h"

extern char TEMP[45];
extern char HUMI[45];
extern unsigned char BMP1[];
extern uint8_t Hum_Mod;

void Usermain(void)
{ 
	UserInit();
	while(1)
	{	
		Esp8266_StatusConfirm();
		Humidifier_Play();
        SHT30_Update();
        OLED_Display();
//		Humidifier_On();
//		HAL_Delay(2000);
//		Humidifier_Off();
//		HAL_Delay(2000);
	}
}

void UserInit(void)
{
        OLED_Init();
		OLED_DrawBMP(0,0,128,8,BMP1);
		HAL_Delay(300);
		OLED_Clear();
		Humidifier_Off();
        SHT30_Reset();
        if(SHT30_Init() == HAL_OK)
        printf("sht30 init ok.\n");
        else
        printf("sht30 init fail.\n");
		BEEP_Yell_Times(3, (uint8_t)500, (uint8_t)500);
}

void OLED_Display(void){
    OLED_ShowString(0, 1, "----------------", 12);
    OLED_ShowString(10, 2, "TEM:", 12);
    OLED_ShowString(5, 3, TEMP, 16);
    OLED_ShowString(10, 5, "HUM:", 12);
    OLED_ShowString(5, 6, HUMI, 16);
    OLED_ShowString(60, 2, "|", 16);
    OLED_ShowString(60, 4, "|", 16);
    OLED_ShowString(60, 6, "|", 16);
    OLED_ShowString(86, 2, "MOD:", 12);
	switch(Hum_Mod){
		case 0:
			OLED_ShowString(78, 4, " ", 16);
			OLED_ShowString(110, 4, ">", 16);
			break;
		case 1:
			OLED_ShowString(78, 4, "<", 16);
			OLED_ShowString(110, 4, ">", 16);
			break;
		case 2:
			OLED_ShowString(78, 4, "<", 16);
			OLED_ShowString(110, 4, " ", 16);
			break;
		default:
			break;
	}	
	OLED_ShowNum(94, 4, Hum_Mod, 1, 16);
}

#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif 


/* printf重定向 */
int fputc(int ch,FILE *f)
{
    uint8_t temp[1]={ch};
    HAL_UART_Transmit(&huart1,temp,1,10);        //UartHandle??????
  return ch;
}


PUTCHAR_PROTOTYPE
{
 HAL_UART_Transmit(&huart1,(uint8_t*)&ch,1,10);
 return ch;
}

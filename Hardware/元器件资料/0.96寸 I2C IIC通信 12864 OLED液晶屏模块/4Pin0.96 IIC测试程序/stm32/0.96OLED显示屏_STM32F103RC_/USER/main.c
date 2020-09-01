//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//  文 件 名   : main.c
//  版 本 号   : v2.0
//  作    者   : 
//  生成日期   : 2014-0101
//  最近修改   : 
//  功能描述   : 0.69寸OLED 接口演示例程(STM32F103ZE系列IIC)
//              说明: 
//              ----------------------------------------------------------------
//              GND   电源地
//              VCC   接5V或3.3v电源
//              SCL   接PB13（SCL）
//              SDA   接PB15（SDA） 
//              RES   接PB11 如果是用4针iic接口这个脚可以不接
//              ----------------------------------------------------------------
//All rights reserved
//////////////////////////////////////////////////////////////////////////////////

#include "delay.h"
#include "sys.h"
#include "oled.h"
#include "bmp.h"
 int main(void)
  {	u8 t;
		delay_init();	    	 //延时函数初始化	  
		NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级 	LED_Init();			     //LED端口初始化
	//		delay_ms(8000);
		OLED_Init();			//初始化OLED  
		OLED_Clear()  	; 
	
		t=' ';
	
		OLED_ShowCHinese(54,0,3);//电
		OLED_ShowCHinese(72,0,4);//子
		OLED_ShowCHinese(90,0,5);//科
		OLED_ShowCHinese(108,0,6);//技
	while(1) 
	{		
		OLED_Clear();

		OLED_ShowCHinese(54,0,3);//电
		OLED_ShowCHinese(72,0,4);//子
		OLED_ShowCHinese(90,0,5);//科
		OLED_ShowCHinese(108,0,6);//技
		OLED_ShowString(6,3,"0.96' OLED TEST",16);
		//OLED_ShowString(8,2,"ZHONGJINGYUAN");  
	 //	OLED_ShowString(20,4,"2014/05/01");  
		OLED_ShowString(0,6,"ASCII:",16);  
		OLED_ShowString(63,6,"CODE:",16);  
		OLED_ShowChar(48,6,t,16);//显示ASCII字符	   
		t++;
		if(t>'~')t=' ';
		OLED_ShowNum(103,6,t,3,16);//显示ASCII字符的码值 	
			delay_ms(8000);
		delay_ms(8000);

					delay_ms(8000);
		delay_ms(8000);
		delay_ms(8000);
		OLED_DrawBMP(0,0,128,8,BMP1);  //图片显示(图片显示慎用，生成的字表较大，会占用较多空间，FLASH空间8K以下慎用)
		delay_ms(8000);
					delay_ms(8000);
		delay_ms(8000);
		delay_ms(8000);
		OLED_DrawBMP(0,0,128,8,BMP1);
		delay_ms(8000);
					delay_ms(8000);
		delay_ms(8000);
		delay_ms(8000);
	}	  
	
}
	
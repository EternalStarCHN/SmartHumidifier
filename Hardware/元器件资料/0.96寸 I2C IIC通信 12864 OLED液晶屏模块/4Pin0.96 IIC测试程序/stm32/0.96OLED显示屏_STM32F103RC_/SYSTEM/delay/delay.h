#ifndef __DELAY_H
#define __DELAY_H 			   
#include "sys.h"
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

//V1.3修改说明
//增加了对UCOSII延时的支持.
//如果使用ucosII,delay_init会自动设置SYSTICK的值,使之与ucos的TICKS_PER_SEC对应.
//delay_ms和delay_us也进行了针对ucos的改造.
//delay_us可以在ucos下使用,而且准确度很高,更重要的是没有占用额外的定时器.
//delay_ms在ucos下,可以当成OSTimeDly来用,在未启动ucos时,它采用delay_us实现,从而准确延时
//可以用来初始化外设,在启动了ucos之后delay_ms根据延时的长短,选择OSTimeDly实现或者delay_us实现.

//V1.4修改说明 20110929
//修改了使用ucos,但是ucos未启动的时候,delay_ms中中断无法响应的bug.
//V1.5修改说明 20120902
//在delay_us加入ucos上锁，防止由于ucos打断delay_us的执行，可能导致的延时不准。
////////////////////////////////////////////////////////////////////////////////// 	 
void delay_init(void);
void delay_ms(u16 nms);
void delay_us(u32 nus);

#endif






























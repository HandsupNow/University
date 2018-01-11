/*
 * LED.c
 *
 * Created: 2017/7/5 星期三 下午 2:16:01
 *  Author: Administrator
 */ 


#include "LED.h"

void LED_Init(void)
{
	DDRA =0xff;   //对小灯初始化，PA端口设置为输出模式
}

void LED_ON(unsigned char led)    
{
	PORTA = led;
}

void LED_Run(void)
{
	int i;
	for (i=0;i<=7;i++)
	{
		LED_ON(_BV(i));        //#define _BV(x) 1<<(x) 一个宏定义相当于1左移x位
		_delay_ms(500);         
	}
}
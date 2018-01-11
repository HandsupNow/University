/*
 * light.c
 *
 * Created: 2017/7/6 星期四 下午 2:53:45
 *  Author: Administrator
 */ 

#include "light.h"


void Light_Init(void)
{
	DDRB &= ~_BV(1); //&写0时输出
}

unsigned char Get_Light(void)
{
	if (PINB & _BV(1))   //输入的数据存入PIN寄存器
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
void Light_Test()
{
	if (Get_Light() == 1)
	{
		Bell_ON(1);
		LED_ON(0xff);
	}
	else
	{
		Bell_ON(0);
		LED_ON(0x00);
	}
}

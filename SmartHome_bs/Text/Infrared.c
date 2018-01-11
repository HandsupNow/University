/*
 * Infrared.c
 *
 * Created: 2017/7/6 星期四 下午 5:07:26
 *  Author: Administrator
 */ 

#include "Infrared.h"

void Infrared_Init()
{
	DDRB &=~_BV(4);
}
unsigned char Get_Infrared(void)
{
	if(PINB &_BV(4))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void Infrared_Test()
{
	if (Get_Infrared() ==0x01)
	{
		LED_ON(0xff);
	}
	else
	{
		LED_ON(0x00);
	}
}

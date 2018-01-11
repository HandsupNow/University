/*
 * Vibration.c
 *
 * Created: 2017/7/6 星期四 下午 4:09:52
 *  Author: Administrator
 */ 

#include "Vibration.h"

void Vibration_Init(void)
{
	DDRD &=~(_BV(2));
}

unsigned char Get_Vibration(void)
{
	if(PIND &_BV(2))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void Vibration_Test(void)
{
	Usart_Put(Get_Vibration());
}
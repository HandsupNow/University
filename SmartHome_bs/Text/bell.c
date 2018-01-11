/*
 * bell.c
 *
 * Created: 2017/7/6 星期四 下午 2:09:51
 *  Author: Administrator
 * 对函数的实现
 */ 


#include "bell.h"


void Bell_Init(void)
{
	DDRD |=_BV(3);  //设置为输出模式
	Bell_ON(0);               //关闭蜂鸣器
}

void Bell_ON(unsigned char bell)
{
	if (bell == 0)   //参数为0关闭蜂鸣器
	{
		PORTD &=~(_BV(3));
	}
	else
	{
		PORTD |=_BV(3);
	}
}

void Bell_Test(void)
{
	Bell_ON(1);
	_delay_ms(1000);
	Bell_ON(0);
}
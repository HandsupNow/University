/*
 * Motor.c
 *
 * Created: 2017/7/10 星期一 下午 2:31:18
 *  Author: Administrator
 */ 
#define   F_CPU  8000000UL
#include "Motor.h"

unsigned char table1[4]={0x30,0x60,0xc0,0x90};
unsigned char table2[4]={0x30,0x90,0xc0,0x60};

void Motor_Init(void)
{
	DDRD|=0xf0;  //设置PD高四位为输出模式
}



void Motor_GO(int num)
{
	int i,j;
	
		if (num>0)
		{
			for (j=0;j<num;j++)
			{
				for (i=0;i<4;i++)//产生4次不同的脉冲
				{
					PORTD |=table1[i];//产生脉冲，设置高电平
					_delay_ms(4);
					PORTD &=~table1[i];//产生脉冲，清零高电平
				}
			}
		}else
		{
			num=-num;
			for (j=0;j<num;j++)//产生4次不同的脉冲
			{
				for (i=0;i<4;i++)
				{
					PORTD |=table2[i];//产生脉冲，设置高电平
					_delay_ms(4);
					PORTD &=~table2[i];
				}
			}
		}
}

/*
 * DHT11.c
 *
 * Created: 2017/7/11 15:01:18
 *  Author: Administrator
 */ 
#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "dht11.h"
/******初始化DHT11数据总线******/
void DHT11_Init(void)
{
	DDRB |= _BV(PB0);//PB0配置为输出模式
	PORTB |= _BV(PB0);//PB0输出高电平
}

/****************************************
函数功能：获取DHT11所有数据
*****************************************/
unsigned char DHT11_GetValue(unsigned char* HumH,unsigned char* TempH)
{
	unsigned char temp;//存放校验的数据
	unsigned char i=0;//循环判断高电平持续时间
	DDRB |= _BV(PB0);//PB0配置为输出模式
	PORTB |= _BV(PB0);//PB0输出高电平
	_delay_ms(5);//确保通信数据线为高电平
	PORTB &= ~_BV(PB0);//拉低PB0管脚
	_delay_ms(20);//拉低信号线20ms使得DHT11能检验到起始位
	PORTB |= _BV(PB0);//拉高PB0管脚
	DDRB &= ~_BV(PB0);//配置PB0为输入模式用于检测接下来DHT11的数据
	_delay_us(14);
	while((!(PINB&1<<PB0))&&(i<150))//检测是否有上升沿的产生
	{
		i++;
		_delay_us(1);
	}
	if(i<40) return 1;//说明器件不存在或有问题
	while(PINB&1<<PB0);//检测是否有下降沿的产生
	*HumH = Read_Com();//读取湿度整数部分
	temp = Read_Com();//读取湿度小数部分
	*TempH = Read_Com();//读取温度整数部分
	temp = Read_Com();//读取温度小数部分
	temp = Read_Com();//读取校验
	return 0;//说明器件正确
	
}
//***读取一个字节的数据***/
unsigned char Read_Com(void)
{
	unsigned char value=0;
	unsigned char i=0;//记录时间
	unsigned char j;
	for (j=0;j<8;j++)
	{
		while(!(PINB&1<<PB0));//检测上升沿
		while(PINB&1<<PB0)//检测是否出现下降沿，记录高电平
		{
			i++;
			_delay_us(1);
		}
		if(i<30)//说明传输的数据为0
		value = value<<1;
		else//说明传输的数据位1
		value = (value<<1) |0x01;
		i=0;//初始化i变量
	}
	return value;
	
}
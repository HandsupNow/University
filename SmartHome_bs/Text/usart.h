#ifndef  USART_H
#define  USART_H


#include <avr/io.h>
#include <util/delay.h>

void Usart_Init(void);//串口的初始化
void Usart_Put(char c);//串口发送函数
char Usart_Get(void);//串口接收函数
void Usart_PutString(char *s);//串口发送一串函数
void Usart_Test(void);//串口测试函数
#endif
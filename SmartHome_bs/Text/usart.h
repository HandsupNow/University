#ifndef  USART_H
#define  USART_H


#include <avr/io.h>
#include <util/delay.h>

void Usart_Init(void);//���ڵĳ�ʼ��
void Usart_Put(char c);//���ڷ��ͺ���
char Usart_Get(void);//���ڽ��պ���
void Usart_PutString(char *s);//���ڷ���һ������
void Usart_Test(void);//���ڲ��Ժ���
#endif
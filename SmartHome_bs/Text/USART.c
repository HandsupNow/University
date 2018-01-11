#include "usart.h"
void Usart_Init(void){
	UCSR0A = 0;
	UCSR0B |=_BV(3) |_BV(4);   //�����ͺͽ���
	UCSR0C |=_BV(1) |_BV(2);
	UBRR0H =0;
	UBRR0L =8;
	}//���ڵĳ�ʼ��
void Usart_Put(char c){
	while(!(UCSR0A&(1<<UDRE0)));       //UDREΪ1ʱ��������Ϊ�գ����Խ����µ����� UCSR0A 0010 0000
	UDR0 = c;                   //UDREΪ0���ɽ����µ�����    &   1101 1111
	}//���ڷ��ͺ���
char Usart_Get(void)            //RXCΪ1ʱ����������δ���������ݲ��ܽ����µ�����
{
	while(!(UCSR0A & (1<<RXC0)));
	return UDR0;
	}//���ڽ��պ���
	void Usart_PutString(char *s){
		while(*s !='\0')
		{
			Usart_Put(*s++);
			
		}
	}
	void Usart_Test(void)
	{
		Usart_Put(Usart_Get());
	}
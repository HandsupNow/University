#include "usart.h"
void Usart_Init(void){
	UCSR0A = 0;
	UCSR0B |=_BV(3) |_BV(4);   //发起发送和接受
	UCSR0C |=_BV(1) |_BV(2);
	UBRR0H =0;
	UBRR0L =8;
	}//串口的初始化
void Usart_Put(char c){
	while(!(UCSR0A&(1<<UDRE0)));       //UDRE为1时，缓冲器为空，可以接受新的数据 UCSR0A 0010 0000
	UDR0 = c;                   //UDRE为0不可接受新的数据    &   1101 1111
	}//串口发送函数
char Usart_Get(void)            //RXC为1时缓存器中有未读出的数据不能接受新的数据
{
	while(!(UCSR0A & (1<<RXC0)));
	return UDR0;
	}//串口接收函数
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
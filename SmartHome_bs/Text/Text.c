/*
 * Text.c
 *
 * Created: 2017/7/2 星期日 上午 11:15:52
 *  Author: Administrator
 */ 

#define F_CPU 8000000UL


#include <avr/io.h>
#include <util/delay.h>
#include "usart.h"
#include "LED.h"
#include "bell.h"
#include "light.h"
#include "Vibration.h"
#include "Infrared.h"
#include "Motor.h"
#include "dht11.h"


//void test(void);

unsigned char data[13]={0};
unsigned char Send[13]={0xfe,0xfe,0x0d,0,0,0,0,0,0,0,0,0x00,0xff};
void contral(void);
unsigned char H,T;



int main(void)
{
	//char *s="hello world\n";
	unsigned char H,T;
	
	LED_Init();
	Usart_Init();
	Bell_Init();//串口初始化
	Light_Init();
	Vibration_Init();
	Infrared_Init();
	//test();
	Motor_Init();
	//Motor_GO(512);
	//_delay_ms(200);
	//Motor_GO(-512);
	DHT11_Init();
	
	
	
	// Bell_Test();
	// Light_Test();
	
	
	
	
	while(1)
    {
		//LED_ON(0xff);
		contral();
		//Infrared_Test();
      //LED_Run();
	  //Usart_Test();
	  //Vibration_Test();
	 // _delay_ms(100);
	//test();
	//DHT11_GetValue(&H,&T);
	//Usart_Put(H/10+0x30);
	//Usart_Put(H%10+0x30);
	//Usart_Put('H');
	//Usart_Put(T/10+0x30);
	//Usart_Put(T%10+0x30);
	//Usart_Put('C');
	//Usart_Put('\n');
    }
}
void contral(void)
{
	int i;
	if(Usart_Get() == 0xef)
	{
		data[0]= 0xef;
		if (Usart_Get() == 0xef)
		{
			data[1] = 0xef;
			if (Usart_Get()==0x0d)
			{
				data[2] = 0x0D;
				for (i=3;i<13;i++)
				{
					data[i]=Usart_Get();
				}
				Bell_ON(data[3]);
				Motor_GO(data[4]);
				LED_ON(data[5]);
				DHT11_GetValue(&H,&T);
				Send[3] = H;
				Send[4] = T;
				Send[5] = Get_Light();
				Send[6] = Get_Infrared();
				Send[7] = Get_Vibration();
				for (i=0;i<13;i++)
				{
					Usart_Put(Send[i]);
				}
			}
		}
	}
}



/*
 * Infrared.h
 *
 * Created: 2017/7/6 星期四 下午 5:07:35
 *  Author: Administrator
 */ 


#ifndef INFRARED_H_
#define INFRARED_H_
#include "usart.h"
#include <avr/io.h>
#include "LED.h"

void Infrared_Init(void);
unsigned char Get_Infrared(void);
void Infrared_Test(void);





#endif /* INFRARED_H_ */
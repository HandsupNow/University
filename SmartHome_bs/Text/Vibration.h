/*
 * Vibration.h
 *
 * Created: 2017/7/6 星期四 下午 4:09:35
 *  Author: Administrator
 */ 


#ifndef VIBRATION_H_
#define VIBRATION_H_

#include "usart.h"
#include <avr/io.h>
#include "LED.h"



void Vibration_Init(void);
unsigned char Get_Vibration(void);
void Vibration_Test(void);




#endif /* VIBRATION_H_ */
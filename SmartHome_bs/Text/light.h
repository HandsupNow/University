/*
 * light.h
 *
 * Created: 2017/7/6 星期四 下午 2:53:55
 *  Author: Administrator
 */ 


#ifndef LIGHT_H_
#define LIGHT_H_

#include <avr/io.h>
#include <util/delay.h>
#include "bell.h"
#include "LED.h"

void Light_Init(void);
unsigned char Get_Light(void);
void Light_Test(void);





#endif /* LIGHT_H_ */
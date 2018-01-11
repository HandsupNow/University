/*
 * LED.h
 *
 * Created: 2017/7/5 星期三 下午 2:09:57
 *  Author: Administrator
 */ 


#ifndef LED_H_     //预处理命令，定义避免一个函数被多次声明
#define LED_H_


#include <avr/io.h>
#include <util/delay.h>

void LED_Init(void);    //小灯初始化
void LED_ON(unsigned char led);    //打开指定的灯
void LED_Run(void);     //流水灯      




#endif /* LED_H_ */
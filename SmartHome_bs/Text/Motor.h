/*
 * Motor.h
 *
 * Created: 2017/7/10 星期一 下午 2:27:55
 *  Author: Administrator
 */ 


#ifndef MOTOR_H_
#define MOTOR_H_

#include <avr/io.h>
#include <util/delay.h>


void Motor_Init(void);//马达初始化
void Motor_GO(int num);//马达转动
void Motor_Test(void);//马大测试





#endif /* MOTOR_H_ */
/*
 * bell.h
 *
 * Created: 2017/7/6 星期四 下午 2:09:33
 *  Author: Administrator
 * 对函数的声明
 */ 


#ifndef BELL_H_
#define BELL_H_

#include <avr/io.h>  //存放了芯片的寄存器地址
#include <util/delay.h>


void Bell_Init(void);  //蜂鸣器的初始化
void Bell_ON(unsigned char bell);  //蜂鸣器的打开函数
void Bell_Test(void);  //蜂鸣器的测试函数


#endif /* BELL_H_ */
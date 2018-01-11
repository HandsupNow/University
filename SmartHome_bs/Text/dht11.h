/*
 * dht11.h
 *
 * Created: 2017/7/11 星期二 下午 2:55:59
 *  Author: Administrator
 */ 


#ifndef DHT11_H_
#define DHT11_H_

unsigned char DHT11_GetValue(unsigned char* HumH,unsigned char* TempH);
void DHT11_Init(void);
unsigned char Read_Com(void);





#endif /* DHT11_H_ */
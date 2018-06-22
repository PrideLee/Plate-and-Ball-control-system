#ifndef __KEY_H
#define __KEY_H

#include "stm32f4xx.h"

//#define KEY KEY_Scan()

#define KEY1 		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1) //
#define KEY2 		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)	//
#define KEY3 		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3) //
#define KEY4  	GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)	//
#define KEY5 		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5) //
#define KEY6  	GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_6)	//

void KEY_Init(void);
uint8_t KEY_Scan(u8 key);

#endif

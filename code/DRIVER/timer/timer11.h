#ifndef _TIMER11_H
#define _TIMER11_H

#include "stm32f4xx.h"

void TIM11_Init(u16 auto_data,u16 fractional);
void TIM11_on(void);
void TIM11_off(void);
	
#endif

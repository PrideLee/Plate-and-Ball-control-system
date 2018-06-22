#ifndef _TIMER6_H
#define _TIMER6_H

#include "stm32f4xx.h"

void TIM6_Init(u16 auto_data,u16 fractional);
void TIM6_on(void);
void TIM6_off(void);
	
#endif

#ifndef __LED_H
#define __LED_H

#include "stm32f4xx.h"
#include "sys.h"

#define LEDON  0
#define LEDOFF 1

#define LED0 PFout(8)
#define LED1 PFout(9)

void LED_Init(void);
void LED_set(uint8_t Num,uint8_t Set);
#endif

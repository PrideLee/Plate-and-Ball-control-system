#ifndef __USART3_H
#define __USART3_H
#include "stdio.h"	
#include "stm32f4xx_conf.h"
#include "sys.h" 
//////////////////////////////////////////////////////////////////////////////////	 

////////////////////////////////////////////////////////////////////////////////// 

#define USART_REC_LEN3  			200  	//定义最大接收字节数 200
#define EN_USART3_RX 			1		//使能（1）/禁止（0）串口1接收
	  	
extern u8  USART_RX_BUF3[USART_REC_LEN3]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART_RX_STA3;         		//接收状态标记	
//如果想串口中断接收，请不要注释以下宏定义
void uart3_init(u32 bound);
void printf_3_(uint8_t *date,uint8_t S);
#endif



#ifndef __USART3_H
#define __USART3_H
#include "stdio.h"	
#include "stm32f4xx_conf.h"
#include "sys.h" 
//////////////////////////////////////////////////////////////////////////////////	 

////////////////////////////////////////////////////////////////////////////////// 

#define USART_REC_LEN3  			200  	//�����������ֽ��� 200
#define EN_USART3_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����
	  	
extern u8  USART_RX_BUF3[USART_REC_LEN3]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART_RX_STA3;         		//����״̬���	
//����봮���жϽ��գ��벻Ҫע�����º궨��
void uart3_init(u32 bound);
void printf_3_(uint8_t *date,uint8_t S);
#endif



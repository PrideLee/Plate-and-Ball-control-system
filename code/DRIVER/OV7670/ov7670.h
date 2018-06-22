#ifndef _OV7670_H
#define _OV7670_H
#include "sys.h"
#include "sccb.h"
//////////////////////////////////////////////////////////////////////////////////	 
//		OV7670_DATA:    PA0~7
//					 WRST:		PB5
//					 RRST:		PB6
//					OE_CS:		PB7
//					 WREN:		PB8
//					  RCK:		PB9
//					VSYNC:		PB4    		//
//////////////////////////////////////////////////////////////////////////////////
	
#define OV7670_WRST_H  GPIOB->BSRRL = GPIO_Pin_5
#define OV7670_WRST_L  GPIOB->BSRRH = GPIO_Pin_5

#define OV7670_RRST_H  GPIOB->BSRRL = GPIO_Pin_6
#define OV7670_RRST_L  GPIOB->BSRRH = GPIO_Pin_6

#define OV7670_CS_H    GPIOB->BSRRL = GPIO_Pin_7
#define OV7670_CS_L    GPIOB->BSRRH = GPIO_Pin_7

#define OV7670_WREN_H  GPIOB->BSRRL = GPIO_Pin_8
#define OV7670_WREN_L  GPIOB->BSRRH = GPIO_Pin_8

#define OV7670_RCK_H	 GPIOB->BSRRL = GPIO_Pin_9
#define OV7670_RCK_L	 GPIOB->BSRRH = GPIO_Pin_9

#define OV7670_DATA   GPIOA->IDR&0x00FF  					//数据输入端口
/////////////////////////////////+++++++++++++++++++++++++++++++++++++++++++++////////									
	//  屏蔽中断：EXTI->IMR&=~(1<<4);    Line8上的中断
	//  打开中断：EXTI->IMR|=1<<4;   
#define EXTI_Line_4_ON   EXTI->IMR|=1<<4     //EXTI->IMR|=0X00000100
#define EXTI_Line_4_OFF  EXTI->IMR&=~(1<<4)  //EXTI->IMR&=0XFFFFFEFF
							 
//////////////////////////////////////////////////////////////////////////////////
							 
							extern uint8_t Part;//灰度阈值
							 
u8   OV7670_Init(void);		  	   		 

void GPIO_Config(void);
uint8_t Show_FIFO_DATA(void);
void GetCoordinatData(void);

void OV7670_Light_Mode(u8 mode);
void OV7670_Color_Saturation(u8 sat);
void OV7670_Brightness(u8 bright);
void OV7670_Contrast(u8 contrast);
void OV7670_Special_Effects(u8 eft);
void OV7670_Window_Set(u16 sx,u16 sy,u16 width,u16 height);


#endif






















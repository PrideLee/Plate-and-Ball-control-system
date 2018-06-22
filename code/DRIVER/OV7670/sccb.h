#ifndef __SCCB_H
#define __SCCB_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
// SCCB:    SDA: PB0  	SCL:PB1 	    							    							  
//////////////////////////////////////////////////////////////////////////////////

#define SCCB_SDA_IN()  {GPIOC->MODER&=0XFFFFFFFC;GPIOC->PUPDR&=0XFFFFFFFC;GPIOC->PUPDR|=0X00000001;}
#define SCCB_SDA_OUT() {GPIOC->MODER&=0XFFFFFFFC;GPIOC->MODER|=0X00000001;GPIOC->PUPDR&=0XFFFFFFFC;}

//IO操作函数	 
#define SCCB_SCL    		PCout(1)	 	//SCL
#define SCCB_SDA    		PCout(0) 		//SDA	 

#define SCCB_READ_SDA    	PCin(0)  		//输入SDA    
#define SCCB_ID   			0X42  			//OV7670的ID

///////////////////////////////////////////
void SCCB_Init(void);
void SCCB_Start(void);
void SCCB_Stop(void);
void SCCB_No_Ack(void);
u8 SCCB_WR_Byte(u8 dat);
u8 SCCB_RD_Byte(void);
u8 SCCB_WR_Reg(u8 reg,u8 data);
u8 SCCB_RD_Reg(u8 reg);
#endif














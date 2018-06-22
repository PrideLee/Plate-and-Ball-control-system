#ifndef __TARGET_H
#define __TARGET_H

#include "stm32f4xx.h"

void Set_Centre( uint16_t X , uint16_t  Y , uint16_t Colour );
void Set_L_Up( uint16_t  X , uint16_t  Y , uint16_t Colour );
void Set_L_Dw( uint16_t  X , uint16_t  Y , uint16_t Colour );
void Set_R_Up( uint16_t  X , uint16_t  Y , uint16_t Colour );
void Set_R_Dw( uint16_t  X , uint16_t  Y , uint16_t Colour );

void Set_Target( uint16_t X , uint16_t  Y , uint8_t  Width , uint16_t Colour );
uint8_t Show_target(void);

void Target_Data_Init(void);

void Coordinate_Init(void);

uint8_t Chack_Target(void);

struct Target_
	{
		uint16_t X,Y;
		uint16_t exp_x,exp_y;
		
		uint16_t top;
		uint16_t l;
		uint16_t r;
		uint16_t btm;
		
		uint16_t history_top;
		uint16_t history_l;
		uint16_t history_r;
		uint16_t history_btm;
	};

struct Region
{
	uint16_t R1x,R1y;
	uint16_t R2x,R2y;
	uint16_t R3x,R3y;
	uint16_t R4x,R4y;
	uint16_t R5x,R5y;
	uint16_t R6x,R6y;
	uint16_t R7x,R7y;
	uint16_t R8x,R8y;
	uint16_t R9x,R9y;
	uint8_t r;
};
	

#endif

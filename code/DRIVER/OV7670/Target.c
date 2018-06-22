#include "Target.h"
#include "lcd.h"

extern struct Target_ target;
struct Region REG;

	/* 中心点 */
void Set_Centre( uint16_t  X , uint16_t  Y , uint16_t Colour)
{
	uint16_t x,y;

	for(x= X-2;x<= X+2;x++)
		for(y= Y-2;y<= Y+2;y++)
			{
				LCD_Color_DrawPoint(x,y,Colour);
			}
}			
	/* 左上 */
void Set_L_Up( uint16_t  X , uint16_t  Y , uint16_t Colour )
{
	uint16_t x,y;

	for(x= X;x> X-10;x--)
		for(y= Y;y> Y-3;y--)
			{
				LCD_Color_DrawPoint(x,y,Colour);
			}
	
	for(x= X;x> X-3;x--)
		for(y= Y-3;y> Y-10;y--)
			{
				LCD_Color_DrawPoint(x,y,Colour);
			}
			
}
	/* 左下 */
void Set_L_Dw( uint16_t  X , uint16_t  Y , uint16_t Colour )
{
	uint16_t x,y;

	for(x= X;x< X+10;x++)
		for(y= Y;y> Y-3;y--)
			{
				LCD_Color_DrawPoint(x,y,Colour);
			}
	
	for(x= X;x< X+3;x++)
		for(y= Y-3;y> Y-10;y--)
			{
				LCD_Color_DrawPoint(x,y,Colour);
			}
}
	/* 右上 */
void Set_R_Up( uint16_t  X , uint16_t  Y , uint16_t Colour )
{
	uint16_t x,y;

	for(x= X;x> X-10;x--)
		for(y= Y;y< Y+3;y++)
			{
				LCD_Color_DrawPoint(x,y,Colour);
			}
	
	for(x= X;x> X-3;x--)
		for(y= Y+3;y< Y+10;y++)
			{
				LCD_Color_DrawPoint(x,y,Colour);
			}
}
	/* 右下 */
void Set_R_Dw( uint16_t  X , uint16_t  Y , uint16_t Colour )
{
	uint16_t x,y;

	for(x= X;x< X+10;x++)
		for(y= Y;y< Y+3;y++)
			{
				LCD_Color_DrawPoint(x,y,Colour);
			}
	
	for(x= X;x< X+3;x++)
		for(y= Y+3;y< Y+10;y++)
			{
				LCD_Color_DrawPoint(x,y,Colour);
			}
}

/*
  设置中心框 
	

*/
void Set_Target( uint16_t X , uint16_t  Y , uint8_t  Width , uint16_t Colour )
{
	 Set_Centre( X , Y , Colour );
   Set_L_Up( X+Width , Y+Width , Colour );
   Set_L_Dw( X-Width , Y+Width , Colour );
   Set_R_Up( X+Width , Y-Width , Colour );
   Set_R_Dw( X-Width , Y-Width , Colour );
}

void Target_Data_Init(void)
{
	
	target.history_r=0xffff;
	target.history_btm=0xffff;
	target.history_l=0;
	target.history_top=0;
	
}


uint8_t Show_target(void)
{
	uint16_t x=0,y=0;
	uint8_t i=0;
		x=((target.btm+target.top)/2);
		y=((target.l+target.r)/2);
	
				if((x>0&&x<320)&&(y>0&&y<240))
				{
					target.X=x;
					target.Y=y;
						Set_Centre(x,y,RED);
						Set_L_Up((target.top),(target.l),RED);
						Set_L_Dw((target.btm),(target.l),RED);
						Set_R_Up((target.top),(target.r),RED);
						Set_R_Dw((target.btm),(target.r),RED);
					i=1;
				}
				return i;
}

uint8_t Chack_Target(void)
{
	if((target.X>=55&&target.X<=265)&&(target.Y>=15&&target.Y<=225))
		return 1;
	else return 0;
}

//
//    ( y , x )   
//
//
void Coordinate_Init(void)
{
	REG.R1y = 190;   REG.R1x = 230; 	     REG.R2y = 120;   REG.R2x = 230;	     REG.R3y = 50;   REG.R3x = 230;

	REG.R4y = 190;   REG.R4x = 160;      	 REG.R5y = 120;   REG.R5x = 160;	     REG.R6y = 50;   REG.R6x = 160;

	REG.R7y = 190;   REG.R7x =  90;	       REG.R8y = 120;   REG.R8x =  90;	     REG.R9y = 50;   REG.R9x =  90;	

}

//uint8_t Getcoordinate=0; //是否得到坐标
//uint8_t Show_target(void)
//{
//	uint16_t x=0,y=0;
//	uint8_t i=0;
//		x=((target.btm+target.top)/2);
//		y=((target.l+target.r)/2);
//	
//				if((x>5&&x<315)&&(y>5&&y<235))
//				{
//					//存取坐标
//						target.X=x;
//						target.Y=y;
//					//捕获坐标
//						Set_Centre(x,y,RED);
//						Set_L_Up((target.top),(target.l),RED);
//						Set_L_Dw((target.btm),(target.l),RED);
//						Set_R_Up((target.top),(target.r),RED);
//						Set_R_Dw((target.btm),(target.r),RED);
//					Getcoordinate=1;
//					i=1;
//				}
//				else 
//				{
//					Getcoordinate=0;
//						target.X=0;
//						target.Y=0;
//					i=0;
//				}
//				return i;
//}



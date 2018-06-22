/*
	KEY_Init();配置
	查询用KEY_Scan();
*/

#include "KEY.h"
#include "GPIO.h"
#include "delay.h"

/* 
	功能：KEY配置
	输入：无
	输出：无
*/
void KEY_Init(void)
{
	GPIO_GeneralInInit(PE,GPIO_Pin_1,1);
	GPIO_GeneralInInit(PE,GPIO_Pin_2,1);
	GPIO_GeneralInInit(PE,GPIO_Pin_3,1);
	GPIO_GeneralInInit(PE,GPIO_Pin_4,1);
	GPIO_GeneralInInit(PE,GPIO_Pin_5,1);
	GPIO_GeneralInInit(PE,GPIO_Pin_6,1);
}

/* 
	功能：查询按键是否被按下
	输入： key ：查询那个按键？
	输出：按下：1
					否：0
*/
uint8_t KEY_Scan(u8 key)
{	 
	uint8_t ON_flag=0;
	switch(key)
	{
		case 1:if(KEY1==0)ON_flag=1;break;
		case 2:if(KEY2==0)ON_flag=1;break;
		case 3:if(KEY3==0)ON_flag=1;break;
		case 4:if(KEY4==0)ON_flag=1;break;
		case 5:if(KEY5==0)ON_flag=1;break;
		case 6:if(KEY6==0)ON_flag=1;break;
		default : ON_flag=0;return 0;
	}
	
	if(ON_flag)
	{
		delay_ms(10);
		switch(key)
		{
			case 1:if(KEY1==0)while(KEY1==0){delay_ms(20);} ;return 1;
			case 2:if(KEY2==0)while(KEY2==0){delay_ms(20);} ;return 1;
			case 3:if(KEY3==0)while(KEY3==0){delay_ms(20);} ;return 1;
			case 4:if(KEY4==0)while(KEY4==0){delay_ms(20);} ;return 1;
			case 5:if(KEY5==0)while(KEY5==0){delay_ms(20);} ;return 1;
			case 6:if(KEY6==0)while(KEY6==0){delay_ms(20);} ;return 1;
			default : ON_flag=0;return 0;
		}
	}
	else return 0;
	
}

#include "stm32f4xx.h" 

#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "usart3.h"	

#include "FreeRTOS.h"
#include "task.h"

#include "APP.h"
#include "APPinit.h"
#include "BEED.h" 
#include "LED.h"
#include "KEY.h"
#include "ServoPWMOut.h"
#include "lcd.h"
#include "Timer.h"

#include "Function.h"
/************************************************/

void _Test_(void);//（此函数用于硬件测试，不经过FreeRTOS）


uint8_t Debug=1;//默认开启调试输出
uint8_t tasknum=0;

uint8_t use_freertos=1;//在输出中用
/************************************************/

int main()
{
	uint8_t i=1;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	
	delay_init(168);
	uart_init(115200);
	uart3_init(9600);
	
	LED_Init();
	BEED_Init(1);
	KEY_Init();
	
	PWMOut_TIM12(2000,840,1000);
	Timer20msInit();//FreeRTOS系统定时      
	
	LCD_Init();
	LCD_DisplayOn();
	LCD_Clear(BLACK);
	LCD_AUTOScan_Dir(L2R_U2D);
	LCD_DisplayString_color(50,50,12,"This is my OV7670 test!",WHITE,BLACK);
	LCD_Display_Dir(0);
	
////////////////////////////////////
taskENTER_CRITICAL();           //进入临界区
	if(OV7670_Init()){ LED1=0;LED0=0; }
taskEXIT_CRITICAL();            //退出临界区
	
	Coordinate_Init();//坐标初始化
		
	OV7670_Light_Mode(3);//白平衡设置//0:自动//1:太阳sunny//2,阴天cloudy//3,办公室office//4,家里home
	OV7670_Color_Saturation(4);//色度 0/-2  1/-1  2/0  3/1  4/2
	OV7670_Brightness(2);//亮度 0/-2  1/-1  2/0  3/1  4/2
	OV7670_Contrast(4);//对比度 0/-2  1/-1  2/0  3/1  4/2
	OV7670_Special_Effects(0);//0:普通模式//1,负片//2,黑白//3,偏红色//4,偏绿色//5,偏蓝色//6,复古	 

	printf("OV7670 OK\n");
	printf_3_("OK\n",3);
	LCD_DisplayString(10,10,12,"Ready");
	
	while(i)//是否开启调试
	{
		if(KEY_Scan(1))
		{
			LCD_DisplayString(80,10,12,"Debug");
			i=0;
			BEED_1(50);
			Debug=1;
		}
		if(KEY_Scan(2))
		{
			i=0;
			BEED_1(50);
			Debug=0;
		}
	}
	
	LCD_Display_Dir(0);
	LCD_AUTOScan_Dir(L2R_U2D);
	
	AllAppInit();
	
	vTaskStartScheduler();          //开启任务调度
	
	while(1)
	{
		;
	}
}


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

void _Test_(void);//���˺�������Ӳ�����ԣ�������FreeRTOS��


uint8_t Debug=1;//Ĭ�Ͽ����������
uint8_t tasknum=0;

uint8_t use_freertos=1;//���������
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
	Timer20msInit();//FreeRTOSϵͳ��ʱ      
	
	LCD_Init();
	LCD_DisplayOn();
	LCD_Clear(BLACK);
	LCD_AUTOScan_Dir(L2R_U2D);
	LCD_DisplayString_color(50,50,12,"This is my OV7670 test!",WHITE,BLACK);
	LCD_Display_Dir(0);
	
////////////////////////////////////
taskENTER_CRITICAL();           //�����ٽ���
	if(OV7670_Init()){ LED1=0;LED0=0; }
taskEXIT_CRITICAL();            //�˳��ٽ���
	
	Coordinate_Init();//�����ʼ��
		
	OV7670_Light_Mode(3);//��ƽ������//0:�Զ�//1:̫��sunny//2,����cloudy//3,�칫��office//4,����home
	OV7670_Color_Saturation(4);//ɫ�� 0/-2  1/-1  2/0  3/1  4/2
	OV7670_Brightness(2);//���� 0/-2  1/-1  2/0  3/1  4/2
	OV7670_Contrast(4);//�Աȶ� 0/-2  1/-1  2/0  3/1  4/2
	OV7670_Special_Effects(0);//0:��ͨģʽ//1,��Ƭ//2,�ڰ�//3,ƫ��ɫ//4,ƫ��ɫ//5,ƫ��ɫ//6,����	 

	printf("OV7670 OK\n");
	printf_3_("OK\n",3);
	LCD_DisplayString(10,10,12,"Ready");
	
	while(i)//�Ƿ�������
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
	
	vTaskStartScheduler();          //�����������
	
	while(1)
	{
		;
	}
}


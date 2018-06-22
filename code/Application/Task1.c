#include "Task1.h"
#include "math.h"

#include "Function.h"

#include "delay.h"
#include "usart.h"
#include "LED.h"
#include "KEY.h"
#include "BEED.h" 
#include "Timer.h"
#include "lcd.h"
#include "PID.h"

#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "croutine.h"
#include "event_groups.h"
#include "list.h"
#include "semphr.h"

/*
	任务1
*/
//任务优先级
#define Task1task_PRIO		10
//任务堆栈大小	
#define Task1task_STK_SIZE 		250
//任务句柄
TaskHandle_t Task1task_Handler;
//任务函数
void Task1task(void *pvParameters);

void CreatTask1(void)
{
	xTaskCreate((TaskFunction_t )Task1task,            	//任务函数
							(const char*    )"Task1task",           //任务名称
							(uint16_t       )Task1task_STK_SIZE,    //任务堆栈大小
							(void*          )NULL,                //传递给任务函数的参数
							(UBaseType_t    )Task1task_PRIO,       	//任务优先级
							(TaskHandle_t*  )&Task1task_Handler);   //任务句柄  

}

/*****************************************************************************/
//                        任务1
/*****************************************************************************/

/************************************************/
//                 数据
/************************************************/
extern float My_Sqrt(float x)  ;
extern struct Target_ target;
extern SemaphoreHandle_t TIMER_BinarySemaphore;	//二值信号量句柄

uint8_t XON=1,YON=1;//轴开关
extern float XIerror;
extern float YIerror;

void Task1task(void *pvParameters)
{

	uint8_t i=1;
	uint8_t j=0;
	float X_UK=0,Y_UK=0;
	BaseType_t err=pdFALSE;
	

	while(1)
	{
		TIM6Close();
		
		taskENTER_CRITICAL();           //进入临界区
		
		X_UK=0;
		Y_UK=0;
		XIerror=0;
		YIerror=0;
		
		Set_MotoDeg(1000,1);//关动力
		Set_MotoDeg(1000,2);
		
		LCD_Display_Dir(0);
		LCD_AUTOScan_Dir(L2R_U2D);
		LCD_Fill_onecolor(0,0,240,320,WHITE);
		LCD_DisplayString(90,50,12,"Task 1");
		LCD_DisplayString(50,100,12,"KEY3");
		LCD_DisplayString(50,150,12,"STOP");
		taskEXIT_CRITICAL();            //退出临界区
		
		if(Get_KEY(3))
		{
			LCD_Fill_onecolor(0,0,240,320,WHITE);
			LCD_Display_Dir(1);
			LCD_AUTOScan_Dir(L2R_U2D);
			j=1;
			i=1;
		  EXTI_Line_4_ON;
		}
		
		while(j)
		{
			err=xSemaphoreTake(TIMER_BinarySemaphore,portMAX_DELAY);	//获取信号量
			if(err==pdTRUE)
			{
				i++;
				if(i==4)
				{
					GetCoordinatData();//每80ms读取一次数据
					i=0;
				}
				if(Chack_Target())//目标在范围内
				{
				
					//每20ms运算一次
					if(XON)
					X_UK = X_PID(target.X,target.exp_x);
					if(YON)
					Y_UK = Y_PID(target.Y,target.exp_y);
					
					moto(X_UK,Y_UK);
					
					if(Debug)OUTPUT ();
					
					if(Get_KEY(3))
					{	
						j=0;
						EXTI_Line_4_OFF;
						TIM6Close();
					}
				}
				else 
				{
					;
//					moto(0,0);
				}
			}
		}
		
		
	}
}


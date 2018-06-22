#include "Task2.h"
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
	任务2
*/
//任务优先级
#define Task2task_PRIO		10
//任务堆栈大小	
#define Task2task_STK_SIZE 		250
//任务句柄
TaskHandle_t Task2task_Handler;
//任务函数
void Task2task(void *pvParameters);

void CreatTask2(void)
{
	xTaskCreate((TaskFunction_t )Task2task,            	//任务函数
							(const char*    )"Task2task",           //任务名称
							(uint16_t       )Task2task_STK_SIZE,    //任务堆栈大小
							(void*          )NULL,                //传递给任务函数的参数
							(UBaseType_t    )Task2task_PRIO,       	//任务优先级
							(TaskHandle_t*  )&Task2task_Handler);   //任务句柄  

}
	
/*****************************************************************************/
//                        任务2
/*****************************************************************************/
extern float My_Sqrt(float x)  ;
extern SemaphoreHandle_t TIMER_BinarySemaphore;	//二值信号量句柄

void Task2task(void *pvParameters)
{
	BaseType_t err=pdFALSE;
	
	while(1)
	{
		
	}
}


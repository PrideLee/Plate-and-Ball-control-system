#include "APPinit.h"
#include "usart.h"
#include "LED.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
/*
*****************************************************************************************************
																	任务宏定义
*****************************************************************************************************
*/

/*
	LED闪烁，表示系统正在运行
*/
//任务优先级
#define LEDtask_PRIO		6
//任务堆栈大小	
#define LEDtask_STK_SIZE 		500
//任务句柄
TaskHandle_t LEDtask_Handler;
//任务函数
void LEDtask(void *pvParameters);

/*
*****************************************************************************************************
																  函数
*****************************************************************************************************
*/

uint8_t LEDAppinit(void)
{
	uint8_t i=1;
	
	xTaskCreate((TaskFunction_t )LEDtask,            	//任务函数
							(const char*    )"LEDtask",           //任务名称
							(uint16_t       )LEDtask_STK_SIZE,    //任务堆栈大小
							(void*          )NULL,                //传递给任务函数的参数
							(UBaseType_t    )LEDtask_PRIO,       	//任务优先级
							(TaskHandle_t*  )&LEDtask_Handler);   //任务句柄              
	
	return i;
}

/*
	描述：LED显示系统正在运行
*/
void LEDtask(void *pvParameters)
{
	while(1)
	{
		LED0=~LED0;
		vTaskDelay(1000);
	}
}



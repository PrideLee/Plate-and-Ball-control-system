#include "Task3.h"
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
#include "APP.h"

#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "croutine.h"
#include "event_groups.h"
#include "list.h"
#include "semphr.h"

void outputinit(void);

/*
	����3
*/
//�������ȼ�
#define Task3task_PRIO		10
//�����ջ��С	
#define Task3task_STK_SIZE 		250
//������
TaskHandle_t Task3task_Handler;
//������
void Task3task(void *pvParameters);

void CreatTask3(void)
{
	xTaskCreate((TaskFunction_t )Task3task,            	//������
							(const char*    )"Task3task",           //��������
							(uint16_t       )Task3task_STK_SIZE,    //�����ջ��С
							(void*          )NULL,                //���ݸ��������Ĳ���
							(UBaseType_t    )Task3task_PRIO,       	//�������ȼ�
							(TaskHandle_t*  )&Task3task_Handler);   //������  

}

/*****************************************************************************/
//                        ����3
/*****************************************************************************/
extern SemaphoreHandle_t TIMER_BinarySemaphore;	//��ֵ�ź������

void Task3task(void *pvParameters)
{
	BaseType_t err=pdFALSE;
	
	while(1)
	{
		
	}
}

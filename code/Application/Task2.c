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
	����2
*/
//�������ȼ�
#define Task2task_PRIO		10
//�����ջ��С	
#define Task2task_STK_SIZE 		250
//������
TaskHandle_t Task2task_Handler;
//������
void Task2task(void *pvParameters);

void CreatTask2(void)
{
	xTaskCreate((TaskFunction_t )Task2task,            	//������
							(const char*    )"Task2task",           //��������
							(uint16_t       )Task2task_STK_SIZE,    //�����ջ��С
							(void*          )NULL,                //���ݸ��������Ĳ���
							(UBaseType_t    )Task2task_PRIO,       	//�������ȼ�
							(TaskHandle_t*  )&Task2task_Handler);   //������  

}
	
/*****************************************************************************/
//                        ����2
/*****************************************************************************/
extern float My_Sqrt(float x)  ;
extern SemaphoreHandle_t TIMER_BinarySemaphore;	//��ֵ�ź������

void Task2task(void *pvParameters)
{
	BaseType_t err=pdFALSE;
	
	while(1)
	{
		
	}
}


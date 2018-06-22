#include "Task4.h"

#include "Function.h"

#include "usart.h"
#include "LED.h"
#include "KEY.h"
#include "BEED.h" 

#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "croutine.h"
#include "event_groups.h"
#include "list.h"
#include "semphr.h"

#include "PID.h"

/*
	����4
*/
//�������ȼ�
#define Task4task_PRIO		10
//�����ջ��С	
#define Task4task_STK_SIZE 		250
//������
TaskHandle_t Task4task_Handler;
//������
void Task4task(void *pvParameters);

void CreatTask4(void)
{
	xTaskCreate((TaskFunction_t )Task4task,            	//������
							(const char*    )"Task4task",           //��������
							(uint16_t       )Task4task_STK_SIZE,    //�����ջ��С
							(void*          )NULL,                //���ݸ��������Ĳ���
							(UBaseType_t    )Task4task_PRIO,       	//�������ȼ�
							(TaskHandle_t*  )&Task4task_Handler);   //������  

}

/*****************************************************************************/
//                        ����4
/*****************************************************************************/
extern SemaphoreHandle_t TIMER_BinarySemaphore;	//��ֵ�ź������

void Task4task(void *pvParameters)
{
	BaseType_t err=pdFALSE;
	while(1)
	{
		
	}
}


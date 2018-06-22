#include "APPinit.h"
#include "usart.h"
#include "LED.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
/*
*****************************************************************************************************
																	����궨��
*****************************************************************************************************
*/

/*
	LED��˸����ʾϵͳ��������
*/
//�������ȼ�
#define LEDtask_PRIO		6
//�����ջ��С	
#define LEDtask_STK_SIZE 		500
//������
TaskHandle_t LEDtask_Handler;
//������
void LEDtask(void *pvParameters);

/*
*****************************************************************************************************
																  ����
*****************************************************************************************************
*/

uint8_t LEDAppinit(void)
{
	uint8_t i=1;
	
	xTaskCreate((TaskFunction_t )LEDtask,            	//������
							(const char*    )"LEDtask",           //��������
							(uint16_t       )LEDtask_STK_SIZE,    //�����ջ��С
							(void*          )NULL,                //���ݸ��������Ĳ���
							(UBaseType_t    )LEDtask_PRIO,       	//�������ȼ�
							(TaskHandle_t*  )&LEDtask_Handler);   //������              
	
	return i;
}

/*
	������LED��ʾϵͳ��������
*/
void LEDtask(void *pvParameters)
{
	while(1)
	{
		LED0=~LED0;
		vTaskDelay(1000);
	}
}



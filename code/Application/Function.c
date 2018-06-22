/*
	��Ӧ�������ܼ�ͷ�ļ�
*/

#include "Function.h"
#include "semphr.h"
#include "timers.h"
#include "queue.h"
#include "croutine.h"
#include "event_groups.h"
#include "list.h"
#include "lcd.h"

#include "ServoPWMOut.h"
//*************************************************************************

//*************************************************************************



/*
	������������Ƿ񱻰���
	���룺NUM  ����Ǹ�����
	��������·���1  ���򷵻�0
	˵����
*/

//�������ź������   ��APP.c�ж���
extern SemaphoreHandle_t KEY1_CountSemaphore;//�������ź���
extern SemaphoreHandle_t KEY2_CountSemaphore;
extern SemaphoreHandle_t KEY3_CountSemaphore;
extern SemaphoreHandle_t KEY4_CountSemaphore;
//extern SemaphoreHandle_t KEY5_CountSemaphore;
//extern SemaphoreHandle_t KEY6_CountSemaphore;

extern SemaphoreHandle_t BEEP_CountSemaphore;
extern SemaphoreHandle_t LED_CountSemaphore;

uint8_t Get_KEY(uint8_t NUM)
{
	uint8_t i=0;
	
	switch(NUM)
	{
		case 1:	if(xSemaphoreTake(KEY1_CountSemaphore,2)) i=1 ;
						break;
		
	  case 2: if(xSemaphoreTake(KEY2_CountSemaphore,2)) i=1 ;
						break;
			
		case 3:	if(xSemaphoreTake(KEY3_CountSemaphore,2)) i=1 ;
						break;
		
		case 4:	if(xSemaphoreTake(KEY4_CountSemaphore,2)) i=1 ;
						break;
		
//		case 5:	if(xSemaphoreTake(KEY5_CountSemaphore,2)) i=1 ;
//						break;
//		
//		case 6:	if(xSemaphoreTake(KEY6_CountSemaphore,2)) i=1 ;
//						break;
	}
	return i;
}

void beep(void)
{
 xSemaphoreGive(BEEP_CountSemaphore);
}

void led1(void)
{
 xSemaphoreGive(LED_CountSemaphore);
}

/*
	���������ڵ���ٶ�
	���룺speed���ٶ�ֵ       num��������
	��������·���1  ���򷵻�0
	˵����speed ��� 20000
*/
void Set_MotoDeg(uint16_t speed, uint8_t num)
{
	if(speed>2000)speed=2000;
  SetTIM12Compare (speed, num);
}

/*
	
*/





extern uint8_t VSYNC_Flag;
extern struct Target_ target;
extern uint8_t Getcoordinate; //�Ƿ�õ�����

void OUTput(uint8_t a)
{
	uint8_t q=0x03,p=0xfc,H,L;
	uint16_t now_X=0,now_Y=0;
	uint16_t exp_X=0,exp_Y=0;
	
		now_X=target.X;
		now_Y=target.Y;
	
	exp_X=target.exp_x;
	exp_Y=target.exp_y;
	
		if(a)
	{
   printf_1_(&q,1);printf_1_(&p,1);//֡ͷ
	
		H=now_X>>8;
		L=now_X;
		printf_1_(&L,1);//
		printf_1_(&H,1);//
		
		H=now_Y>>8;
		L=now_Y;
		printf_1_(&L,1);//
		printf_1_(&H,1);//
		
		
		H=exp_X>>8;
		L=exp_X;
		printf_1_(&L,1);//
		printf_1_(&H,1);//
		
		H=exp_Y>>8;
		L=exp_Y;
		printf_1_(&L,1);//
		printf_1_(&H,1);//
	
   printf_1_(&p,1);printf_1_(&q,1);//֡β
  }
  else
	{
	printf("%d %d\n",now_X,now_Y);
	printf("%d %d\n",exp_X,exp_Y);
	}
}

extern SemaphoreHandle_t USART_OUT_BinarySemaphore;//��APP.C
void OUTPUT ()
{
	xSemaphoreGive(USART_OUT_BinarySemaphore);	//�ͷŶ�ֵ�ź���
}




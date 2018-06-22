#include "stm32f4xx.h"
#include "timer11.h"
#include "usart.h"//����

void TIM11_Init(u16 auto_data,u16 fractional)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM11,ENABLE);      //ʹ��TIM6ʱ��
	
  TIM_TimeBaseInitStructure.TIM_Period = auto_data; 	     //�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=fractional;      //��ʱ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM11,&TIM_TimeBaseInitStructure);//��ʼ��TIM2
	
	TIM_ITConfig(TIM11,TIM_IT_Update,ENABLE); //����ʱ��6�����ж�
	TIM_Cmd(TIM11,ENABLE);                    //ʹ�ܶ�ʱ��6
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM1_TRG_COM_TIM11_IRQn     ; //��ʱ��6�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x06; //��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;  //�����ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void TIM11_on(void)
{
	TIM_Cmd(TIM11,ENABLE);
}
void TIM11_off(void)
{
	TIM_Cmd(TIM11,DISABLE);
}


//��ʱ��6�жϷ�����
void TIM1_TRG_COM_TIM11_IRQHandler(void)
{
	uint8_t k=0;
	if(TIM_GetITStatus(TIM11,TIM_IT_Update)==SET) //����ж�
	{
		k=~k;
	}
	TIM_ClearITPendingBit(TIM11,TIM_IT_Update);  //����жϱ�־λ
}

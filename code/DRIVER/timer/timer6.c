#include "stm32f4xx.h"
#include "timer6.h"
#include "usart.h"//����

void TIM6_Init(u16 auto_data,u16 fractional)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);      //ʹ��TIM6ʱ��
	
  TIM_TimeBaseInitStructure.TIM_Period = auto_data; 	     //�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=fractional;      //��ʱ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM6,&TIM_TimeBaseInitStructure);//��ʼ��TIM2
	
	TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE); //����ʱ��6�����ж�
	TIM_Cmd(TIM6,DISABLE);                    //ʹ�ܶ�ʱ��6
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM6_DAC_IRQn; //��ʱ��6�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x05; //��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;  //�����ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void TIM6_on(void)
{
	TIM_Cmd(TIM6,ENABLE);
}
void TIM6_off(void)
{
	TIM_Cmd(TIM6,DISABLE);
}


//��ʱ��6�жϷ�����
void TIM6_DAC_IRQHandler(void)
{
	uint8_t k=0;
	if(TIM_GetITStatus(TIM6,TIM_IT_Update)==SET) //����ж�
	{
		k=~k;
	}
	TIM_ClearITPendingBit(TIM6,TIM_IT_Update);  //����жϱ�־λ
}

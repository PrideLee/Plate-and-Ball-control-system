#include "stm32f4xx.h"
#include "timer11.h"
#include "usart.h"//串口

void TIM11_Init(u16 auto_data,u16 fractional)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM11,ENABLE);      //使能TIM6时钟
	
  TIM_TimeBaseInitStructure.TIM_Period = auto_data; 	     //自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=fractional;      //定时器分频
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM11,&TIM_TimeBaseInitStructure);//初始化TIM2
	
	TIM_ITConfig(TIM11,TIM_IT_Update,ENABLE); //允许定时器6更新中断
	TIM_Cmd(TIM11,ENABLE);                    //使能定时器6
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM1_TRG_COM_TIM11_IRQn     ; //定时器6中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x06; //抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;  //子优先级2
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


//定时器6中断服务函数
void TIM1_TRG_COM_TIM11_IRQHandler(void)
{
	uint8_t k=0;
	if(TIM_GetITStatus(TIM11,TIM_IT_Update)==SET) //溢出中断
	{
		k=~k;
	}
	TIM_ClearITPendingBit(TIM11,TIM_IT_Update);  //清除中断标志位
}

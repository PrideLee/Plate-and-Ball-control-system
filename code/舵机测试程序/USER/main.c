#include "stm32f4xx.h"
#include "usart.h"
#include "delay.h"
#include "ServoPWMOut.h"
#include "LED.h"

void Set_MotoDeg(uint16_t speed, uint8_t num);
void SetTIM12Compare_ (uint16_t Data, uint8_t Channel);

int main(void)
{
	u32 t=8500,j=0,i=0;
	uart_init(115200);
	delay_init(168);
	PWMOut_TIM12(48000,7,15000);
	LED_Init();
	
	LED0=0;
	
  while(1)
	{
		if(t==8500)    { j=1; }
		if(t==21500) { j=0; }
		
		if(j) t+=10;
		else t-=10;
		
		Set_MotoDeg(t,1);
		Set_MotoDeg(t,2);
		
		printf("%d\n",t);
		delay_ms(5);
		
		i++;
		if(i==10)
		{
			LED0=~LED0;
			LED1=~LED1;
			i=0;
		}
		
	}
}

void Set_MotoDeg(uint16_t speed, uint8_t num)
{
	if(speed>2500)speed=2500;
  SetTIM12Compare_ (speed, num);
}


void SetTIM12Compare_ (uint16_t Data, uint8_t Channel)
{
	if(Channel==1)TIM_SetCompare1 (TIM12,Data);
	else  if(Channel==2)TIM_SetCompare2 (TIM12,Data);
}


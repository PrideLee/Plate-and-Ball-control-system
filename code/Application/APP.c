#include "APP.h"
#include "usart.h"
#include "usart3.h"	
#include "delay.h"

#include "LED.h"
#include "KEY.h"
#include "BEED.h" 
#include "lcd.h"
#include "Timer.h"

#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "croutine.h"
#include "event_groups.h"
#include "list.h"
#include "semphr.h"

#include "Function.h"

extern uint8_t tasknum;
uint8_t START=0;

extern TaskHandle_t Task1task_Handler;
extern TaskHandle_t Task2task_Handler;
extern TaskHandle_t Task3task_Handler;
extern TaskHandle_t Task4task_Handler;

/*
*****************************************************************************************************
																	任务宏定义
*****************************************************************************************************
*/

SemaphoreHandle_t USART_IN_BinarySemaphore;
SemaphoreHandle_t USART_OUT_BinarySemaphore;

///*
//	LED0闪烁，表示系统正在运行
//*/
//任务优先级
#define LEDtask_PRIO		10
//任务堆栈大小	
#define LEDtask_STK_SIZE 		50
//任务句柄
TaskHandle_t LEDtask_Handler;
//任务函数
void LEDtask(void *pvParameters);

//计数型信号量句柄
SemaphoreHandle_t KEY1_CountSemaphore;//计数型信号量
SemaphoreHandle_t KEY2_CountSemaphore;
SemaphoreHandle_t KEY3_CountSemaphore;
SemaphoreHandle_t KEY4_CountSemaphore;
//SemaphoreHandle_t KEY5_CountSemaphore;
//SemaphoreHandle_t KEY6_CountSemaphore;

SemaphoreHandle_t BEEP_CountSemaphore;

SemaphoreHandle_t LED_CountSemaphore;

/*
	输入
*/
//任务优先级
#define DataINtask_PRIO		9
//任务堆栈大小	
#define DataINtask_STK_SIZE 		500
//任务句柄
TaskHandle_t DataINtask_Handler;
//任务函数
void DataINtask(void *pvParameters);

/*
	输出
*/
//任务优先级
#define DataOUTtask_PRIO		9
//任务堆栈大小	
#define DataOUTtask_STK_SIZE 		500
//任务句柄
TaskHandle_t DataOUTtask_Handler;
//任务函数
void DataOUTtask(void *pvParameters);

/*
	KEY检测任务
*/
//任务优先级
#define KEYtask_PRIO		10
//任务堆栈大小	
#define KEYtask_STK_SIZE 		500
//任务句柄
TaskHandle_t KEYtask_Handler;
//任务函数
void KEYtask(void *pvParameters);

/*
	ENDtask
*/
//任务优先级
#define ENDtask_PRIO		11
//任务堆栈大小	
#define ENDtask_STK_SIZE 		500
//任务句柄
TaskHandle_t ENDtask_Handler;
//任务函数
void ENDtask(void *pvParameters);

/*
	BEEP
*/
//任务优先级
#define BEEPtask_PRIO		10
//任务堆栈大小	
#define BEEPtask_STK_SIZE 		100
//任务句柄
TaskHandle_t BEEPtask_Handler;
//任务函数
void BEEPtask(void *pvParameters);

/*
	LED1
*/
//任务优先级
#define LED1task_PRIO		10
//任务堆栈大小	
#define LED1task_STK_SIZE 		100
//任务句柄
TaskHandle_t LED1task_Handler;
//任务函数
void LED1task(void *pvParameters);

/*
	开始任务
*/
//任务优先级
#define Starttask_PRIO		11
//任务堆栈大小	
#define Starttask_STK_SIZE 		500
//任务句柄
TaskHandle_t Starttask_Handler;
//任务函数
void Starttask(void *pvParameters);


/*
*****************************************************************************************************
																  函数
*****************************************************************************************************
*/

uint8_t AllAppInit(void)
{
	uint8_t i=1;
	
	//创建计数型信号量
	KEY1_CountSemaphore=xSemaphoreCreateCounting(200,0);	
	KEY2_CountSemaphore=xSemaphoreCreateCounting(200,0);	
	KEY3_CountSemaphore=xSemaphoreCreateCounting(200,0);	
	KEY4_CountSemaphore=xSemaphoreCreateCounting(200,0);	
//	KEY5_CountSemaphore=xSemaphoreCreateCounting(200,0);	
//	KEY6_CountSemaphore=xSemaphoreCreateCounting(200,0);	
	
	BEEP_CountSemaphore=xSemaphoreCreateCounting(200,0);	
	LED_CountSemaphore=xSemaphoreCreateCounting(200,0);	
	
	USART_IN_BinarySemaphore=xSemaphoreCreateBinary();	
	USART_OUT_BinarySemaphore=xSemaphoreCreateBinary();
	
	if(KEY1_CountSemaphore==NULL||KEY2_CountSemaphore==NULL||KEY3_CountSemaphore==NULL||KEY4_CountSemaphore==NULL||BEEP_CountSemaphore==NULL||LED_CountSemaphore==NULL) //||KEY5_CountSemaphore==NULL||KEY6_CountSemaphore==NULL
	{
		printf("计数信号量创建失败\n");
		i=0;
	}
	
	xTaskCreate((TaskFunction_t )DataINtask,            	//任务函数
							(const char*    )"DataINtask",           //任务名称
							(uint16_t       )DataINtask_STK_SIZE,    //任务堆栈大小
							(void*          )NULL,                //传递给任务函数的参数
							(UBaseType_t    )DataINtask_PRIO,       	//任务优先级
							(TaskHandle_t*  )&DataINtask_Handler);   //任务句柄  
							
	xTaskCreate((TaskFunction_t )DataOUTtask,            	//任务函数
							(const char*    )"DataOUTtask",           //任务名称
							(uint16_t       )DataOUTtask_STK_SIZE,    //任务堆栈大小
							(void*          )NULL,                //传递给任务函数的参数
							(UBaseType_t    )DataOUTtask_PRIO,       	//任务优先级
							(TaskHandle_t*  )&DataOUTtask_Handler);   //任务句柄  
	
	xTaskCreate((TaskFunction_t )KEYtask,            	//任务函数
							(const char*    )"KEYtask",           //任务名称
							(uint16_t       )KEYtask_STK_SIZE,    //任务堆栈大小
							(void*          )NULL,                //传递给任务函数的参数
							(UBaseType_t    )KEYtask_PRIO,       	//任务优先级
							(TaskHandle_t*  )&KEYtask_Handler);   //任务句柄     
							
	xTaskCreate((TaskFunction_t )BEEPtask,            	//任务函数
							(const char*    )"BEEPtask",           //任务名称
							(uint16_t       )BEEPtask_STK_SIZE,    //任务堆栈大小
							(void*          )NULL,                //传递给任务函数的参数
							(UBaseType_t    )BEEPtask_PRIO,       	//任务优先级
							(TaskHandle_t*  )&BEEPtask_Handler);   //任务句柄     						

	xTaskCreate((TaskFunction_t )ENDtask,            	//任务函数
							(const char*    )"ENDtask",           //任务名称
							(uint16_t       )ENDtask_STK_SIZE,    //任务堆栈大小
							(void*          )NULL,                //传递给任务函数的参数
							(UBaseType_t    )ENDtask_PRIO,       	//任务优先级
							(TaskHandle_t*  )&ENDtask_Handler);   //任务句柄     										

  xTaskCreate((TaskFunction_t )LEDtask,            	//任务函数
							(const char*    )"LEDtask",           //任务名称
							(uint16_t       )LEDtask_STK_SIZE,    //任务堆栈大小
							(void*          )NULL,                //传递给任务函数的参数
							(UBaseType_t    )LEDtask_PRIO,       	//任务优先级
							(TaskHandle_t*  )&LEDtask_Handler);   //任务句柄   	
	xTaskCreate((TaskFunction_t )LED1task,            	//任务函数
							(const char*    )"LED1task",           //任务名称
							(uint16_t       )LED1task_STK_SIZE,    //任务堆栈大小
							(void*          )NULL,                //传递给任务函数的参数
							(UBaseType_t    )LED1task_PRIO,       	//任务优先级
							(TaskHandle_t*  )&LED1task_Handler);   //任务句柄   

	xTaskCreate((TaskFunction_t )Starttask,            	//任务函数
							(const char*    )"Starttask",           //任务名称
							(uint16_t       )Starttask_STK_SIZE,    //任务堆栈大小
							(void*          )NULL,                //传递给任务函数的参数
							(UBaseType_t    )Starttask_PRIO,       	//任务优先级
							(TaskHandle_t*  )&Starttask_Handler);   //任务句柄     
	
	CreatTask1();
	CreatTask2();
	CreatTask3();
	CreatTask4();
	
							
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

/*
	描述：检测按键
*/
void KEYtask(void *pvParameters)
{
	BaseType_t err;
	while(1)
	{
		if(KEY_Scan(1))           	//扫描按键
		{err=xSemaphoreGive(KEY1_CountSemaphore); beep();} //释放计数型信号量
		
		if(KEY_Scan(2))           	//扫描按键
		{err=xSemaphoreGive(KEY2_CountSemaphore); beep();} //释放计数型信号量
		
		if(KEY_Scan(3))           	//扫描按键
		{err=xSemaphoreGive(KEY3_CountSemaphore); beep();} //释放计数型信号量
		
		if(KEY_Scan(4))           	//扫描按键
		{err=xSemaphoreGive(KEY4_CountSemaphore); beep();} //释放计数型信号量
				
//	  if(KEY_Scan(5))           	//扫描按键
//		{err=xSemaphoreGive(KEY5_CountSemaphore); beep();} //释放计数型信号量
//		
//		if(KEY_Scan(6))           	//扫描按键
//		{err=xSemaphoreGive(KEY6_CountSemaphore); beep();} //释放计数型信号量
		
		vTaskDelay(20);     //延时20ms，也就是20个时钟节拍	
	}
}
/*
	描述BEEP一下
*/
void BEEPtask(void *pvParameters)
{
	while(1)
	{
		xSemaphoreTake(BEEP_CountSemaphore,portMAX_DELAY);
		BEED_1(50);
	}
}

/*
	描述LED1闪一下
*/
void LED1task(void *pvParameters)
{
	while(1)
	{
		xSemaphoreTake(LED_CountSemaphore,portMAX_DELAY);
		LED1=0;
		delay_ms(50);
		LED1=1;
	}
}

void ENDtask(void *pvParameters)
{
	while(1)
	{
		xSemaphoreTake(KEY4_CountSemaphore,portMAX_DELAY);
		taskENTER_CRITICAL();           //进入临界区
		
		led1();
		if(tasknum)
		switch(tasknum)
		{
			case 1: vTaskSuspend(Task1task_Handler); break;
			case 2: vTaskSuspend(Task2task_Handler); break;
			case 3: vTaskSuspend(Task3task_Handler); break;
			case 4: vTaskSuspend(Task4task_Handler); break;
//			case 5: vTaskResume(Task5task_Handler); break;
		}
		tasknum=0;
		if(!START)vTaskResume(Starttask_Handler);	//恢复任务
		START=1;
		
		LCD_Fill_onecolor(0,0,240,320,WHITE);
		LCD_DisplayString(90,50,12,"Start ");
		
		taskEXIT_CRITICAL();            //退出临界区
		delay_ms(100);
	}
}

/*
	串口数据接收处理
*/

extern uint8_t Part;//灰度阈值
extern uint8_t XON,YON;//轴开关
extern float IE;
extern float X_P,X_I,X_D;      //PID参数 
extern float Y_P,Y_I,Y_D;      //PID参数 
extern struct Region REG;
extern struct Target_ target;
void DataINtask(void *pvParameters)
{
	uint8_t H,L;
	float P,I,D;
	BaseType_t err=pdFALSE;
	while(1)
	{
		err=xSemaphoreTake(USART_IN_BinarySemaphore,portMAX_DELAY);	//获取信号量
		if(err==pdTRUE)
		{
			if((USART_RX_STA&0x8000)!=0)//接收到了数据
			{
				USART_RX_STA=0;	
				
				//  Y方向的PID
				if(USART_RX_BUF[0]=='X'&&USART_RX_BUF[1]=='P'&&USART_RX_BUF[5]=='I'&&USART_RX_BUF[10]=='D')//调PID
				{
					//调节
					if(USART_RX_BUF[2]-48==0&&USART_RX_BUF[3]-48==0&&USART_RX_BUF[4]-48==0&&USART_RX_BUF[6]-48==0&&USART_RX_BUF[7]-48==0&&USART_RX_BUF[8]-48==0&&USART_RX_BUF[9]-48==0&&USART_RX_BUF[11]-48==0&&USART_RX_BUF[12]-48==0&&USART_RX_BUF[13]-48==0&&USART_RX_BUF[14]-48==0)
						printf("nowXP=%.1f  I=%.4f  D=%.5f\n",X_P,X_I,X_D);
					else
					{
						P=(USART_RX_BUF[2]-48)*100 +(USART_RX_BUF[3]-48)*10 +(USART_RX_BUF[4]-48);
						I=(float)(USART_RX_BUF[6]-48) +(float)(USART_RX_BUF[7]-48)/10 +(float)(USART_RX_BUF[8]-48)/100 +(float)(USART_RX_BUF[9]-48)/1000;
						D=(float)(USART_RX_BUF[11]-48)*10+(float)(USART_RX_BUF[12]-48)+(float)(USART_RX_BUF[13]-48)/10+(float)(USART_RX_BUF[14]-48)/100+(float)(USART_RX_BUF[15]-48)/1000;
						X_P=P;
						X_I=I;
						X_D=D;
						printf("XP=%.1f  I=%.4f  D=%.5f\n",X_P,X_I,X_D);
					}
					//输出
				}
				//  Y方向的PID
				if(USART_RX_BUF[0]=='Y'&&USART_RX_BUF[1]=='P'&&USART_RX_BUF[5]=='I'&&USART_RX_BUF[10]=='D')//调PID
				{
					//调节
					if(USART_RX_BUF[2]-48==0&&USART_RX_BUF[3]-48==0&&USART_RX_BUF[4]-48==0&&USART_RX_BUF[6]-48==0&&USART_RX_BUF[7]-48==0&&USART_RX_BUF[8]-48==0&&USART_RX_BUF[9]-48==0&&USART_RX_BUF[11]-48==0&&USART_RX_BUF[12]-48==0&&USART_RX_BUF[13]-48==0&&USART_RX_BUF[14]-48==0)
						printf("nowYP=%.1f  I=%.4f  D=%.5f\n",Y_P,Y_I,Y_D);
					else
					{
						P=(USART_RX_BUF[2]-48)*100 +(USART_RX_BUF[3]-48)*10 +(USART_RX_BUF[4]-48);
						I=(float)(USART_RX_BUF[6]-48) +(float)(USART_RX_BUF[7]-48)/10 +(float)(USART_RX_BUF[8]-48)/100 +(float)(USART_RX_BUF[9]-48)/1000;
						D=(float)(USART_RX_BUF[11]-48)*10+(float)(USART_RX_BUF[12]-48)+(float)(USART_RX_BUF[13]-48)/10+(float)(USART_RX_BUF[14]-48)/100+(float)(USART_RX_BUF[15]-48)/1000;
						Y_P=P;
						Y_I=I;
						Y_D=D;
						printf("YP=%.1f  I=%.4f  D=%.5f\n",Y_P,Y_I,Y_D);
					}
					//输出
				}
				
			}
				
////////////  串口3  /////////////	
			if((USART_RX_STA3&0x8000)!=0)//接收到了数据
			{
				USART_RX_STA3=0;
				
				if(USART_RX_BUF3[0]=='R')// 目标
				{
					if((USART_RX_BUF3[1]-48==0))
					{
						H=REG.r+48;
						printf_3_(&H,1);
						printf_3_("\n",1);
						beep();
					}
					else
					{
						//调节
						REG.r=(USART_RX_BUF3[1]-48);
						//输出
						printf_3_(&USART_RX_BUF3[1],1);
						printf_3_("\n",1);
						switch(REG.r)
						{
							case 1: target.exp_x=REG.R1x;  target.exp_y=REG.R1y; break;
							case 2: target.exp_x=REG.R2x;  target.exp_y=REG.R2y; break;
							case 3: target.exp_x=REG.R3x;  target.exp_y=REG.R3y; break;
							case 4: target.exp_x=REG.R4x;  target.exp_y=REG.R4y; break;
							case 5: target.exp_x=REG.R5x;  target.exp_y=REG.R5y; break;
							case 6: target.exp_x=REG.R6x;  target.exp_y=REG.R6y; break;
							case 7: target.exp_x=REG.R7x;  target.exp_y=REG.R7y; break;
							case 8: target.exp_x=REG.R8x;  target.exp_y=REG.R8y; break;
							case 9: target.exp_x=REG.R9x;  target.exp_y=REG.R9y; break;
						}
						beep();
					}
				}
				
				if(USART_RX_BUF3[0]=='P')// 二值化阈值
				{
					if((USART_RX_BUF3[1]-48==0)&&(USART_RX_BUF3[2]-48==0))
					{
						H=Part/10+48;
						L=Part%10+48;
						printf_3_(&H,1);
						printf_3_(&L,1);
						printf_3_("\n",1);
						beep();
					}
					else
					{
						//调节
						Part=(USART_RX_BUF3[1]-48)*10+(USART_RX_BUF3[2]-48);
						//输出
						printf_3_(&USART_RX_BUF3[1],1);
						printf_3_(&USART_RX_BUF3[2],1);
						printf_3_("\n",1);
						beep();
					}
				}
				
				if(USART_RX_BUF3[0]=='I'&&USART_RX_BUF3[1]=='E')// 积分开关
				{
					if(USART_RX_BUF3[2]-48==2)
					{
						H=IE+48;
						printf_3_(&H,1);
						printf_3_("\n",1);
						beep();
					}
					else
					{
						//调节
						IE=USART_RX_BUF3[2]-48;
						//输出
						printf_3_(&USART_RX_BUF3[2],1);
						printf_3_("\n",1);
						beep();
					}
				}
				
				if(USART_RX_BUF3[0]=='X'&&USART_RX_BUF3[1]=='O'&&USART_RX_BUF3[2]=='N')// 轴开关
				{
					if((USART_RX_BUF3[3]-48==2))
					{
						H=XON+48;
						printf_3_(&H,1);
						printf_3_("\n",1);
						beep();
					}
					else
					{
						//调节
						XON=(USART_RX_BUF3[3]-48);
						//输出
						printf_3_(&USART_RX_BUF3[3],1);
						printf_3_("\n",1);
						beep();
					}
				}
				
				if(USART_RX_BUF3[0]=='Y'&&USART_RX_BUF3[1]=='O'&&USART_RX_BUF3[2]=='N')// 轴开关
				{
					if((USART_RX_BUF3[3]-48==2))
					{
						H=YON+48;
						printf_3_(&H,1);
						printf_3_("\n",1);
						beep();
					}
					else
					{
						//调节
						YON=(USART_RX_BUF3[3]-48);
						//输出
						printf_3_(&USART_RX_BUF3[3],1);
						printf_3_("\n",1);
						beep();
					}
				}
				 
//				XP 000 I 0.000 D 00.00
				if(USART_RX_BUF3[0]=='X'&&USART_RX_BUF3[1]=='P'&&USART_RX_BUF3[5]=='I'&&USART_RX_BUF3[10]=='D')//调PID
				{
					//调节
						P=(USART_RX_BUF3[2]-48)*100 +(USART_RX_BUF3[3]-48)*10 +(USART_RX_BUF3[4]-48);
						I=(float)(USART_RX_BUF3[6]-48) +(float)(USART_RX_BUF3[7]-48)/10 +(float)(USART_RX_BUF3[8]-48)/100 +(float)(USART_RX_BUF3[9]-48)/1000;
						D=(float)(USART_RX_BUF3[11]-48)*10+(float)(USART_RX_BUF3[12]-48)+(float)(USART_RX_BUF3[13]-48)/10+(float)(USART_RX_BUF3[14]-48)/100+(float)(USART_RX_BUF3[15]-48)/1000;
						X_P=P;
						X_I=I;
						X_D=D;
						beep();
					//输出
				}
				
//				YP 000 I 0.000 D 00.00
				if(USART_RX_BUF3[0]=='Y'&&USART_RX_BUF3[1]=='P'&&USART_RX_BUF3[5]=='I'&&USART_RX_BUF3[10]=='D')//调PID
				{
					//调节
						P=(USART_RX_BUF3[2]-48)*100 +(USART_RX_BUF3[3]-48)*10 +(USART_RX_BUF3[4]-48);
						I=(float)(USART_RX_BUF3[6]-48) +(float)(USART_RX_BUF3[7]-48)/10 +(float)(USART_RX_BUF3[8]-48)/100 +(float)(USART_RX_BUF3[9]-48)/1000;
						D=(float)(USART_RX_BUF3[11]-48)*10+(float)(USART_RX_BUF3[12]-48)+(float)(USART_RX_BUF3[13]-48)/10+(float)(USART_RX_BUF3[14]-48)/100+(float)(USART_RX_BUF3[15]-48)/1000;
						Y_P=P;
						Y_I=I;
						Y_D=D;
						beep();
					//输出
				}
				
			}
		}
	}
}

void DataOUTtask(void *pvParameters)
{
	BaseType_t err=pdFALSE;
	while(1)
	{
		err=xSemaphoreTake(USART_OUT_BinarySemaphore,portMAX_DELAY);	//获取信号量
		if(err==pdTRUE)
		{
			OUTput(1);
		}
	}
}


/****************************************************************************************************************************/
//                                            开始任务
/****************************************************************************************************************************/


/*
	描述：开始任务
*/
void Starttask(void *pvParameters)
{
	uint8_t i=1,changshow=0;
	uint8_t task_num=1;
		LED0=0;
		LED1=0;
	while(1)
	{
		taskENTER_CRITICAL();           //进入临界区
		//关动力
		Set_MotoDeg(1000,1);
		Set_MotoDeg(1000,2);
		
		vTaskSuspend(Task1task_Handler);//挂起任务
		vTaskSuspend(Task2task_Handler);
		vTaskSuspend(Task3task_Handler);
		vTaskSuspend(Task4task_Handler);
		
		TIM6Close();//关定时器
		
		//清数据
		tasknum=0;
		START=1;
		ClearTaskDATA();
		
		LCD_Fill_onecolor(0,0,240,320,WHITE);
		LCD_Fill_onecolor(90,50,200,62,WHITE);
		LCD_DisplayString(90,50,12,"Start ");
		
		LCD_DisplayString(30,100,12,"Select Task ");
		LCD_DisplayNum(120,100,task_num,1,12,0);
		taskEXIT_CRITICAL();            //退出临界区
		
		delay_ms(100);
		
		i=1;
		
		while(i)
		{
			delay_ms(50);
			if(Get_KEY(1))
			{
				led1();
				task_num++;
				if(task_num==5)task_num=1;
				changshow=1;
			}
			if(changshow)
			{
				changshow=0;
				taskENTER_CRITICAL();           //进入临界区
				LCD_Fill_onecolor(120,100,130,120,WHITE);
				LCD_DisplayNum(120,100,task_num,1,12,0);
				taskEXIT_CRITICAL();            //退出临界区
			}
			if(Get_KEY(3))
			{
				led1();
				taskENTER_CRITICAL();           //进入临界区
				tasknum=task_num;
				
				LCD_Fill_onecolor(90,50,200,62,WHITE);
				switch(task_num)
				{
					case 1:LCD_DisplayString(90,50,12,"Task 1");break;
					case 2:LCD_DisplayString(90,50,12,"Task 2");break;
					case 3:LCD_DisplayString(90,50,12,"Task 3");break;
					case 4:LCD_DisplayString(90,50,12,"Task 4");break;
				}
				
				//在此开启任务
				switch(task_num)
				{
					case 1: vTaskResume(Task1task_Handler); break;
					case 2: vTaskResume(Task2task_Handler); break;
					case 3: vTaskResume(Task3task_Handler); break;
					case 4: vTaskResume(Task4task_Handler); break;
//					case 5: vTaskResume(Task5task_Handler); break;
				}
				
				TIM6Open();
				START=0;
				//挂起本身
				vTaskSuspend(Starttask_Handler);
				i=0;
				taskEXIT_CRITICAL();            //退出临界区
			}
		}
	}
}


extern float XIerror;
extern float YIerror;
void ClearTaskDATA(void)
{
	XIerror=0;
	YIerror=0;
}

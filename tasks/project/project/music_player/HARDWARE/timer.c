#include "sys.h"
#include "timer.h"
#include "oled.h"
void TIM5_Int_Init(u16 arr, u16 psc)
{
	TIM_TimeBaseInitTypeDef Timer_Initstructure;
	NVIC_InitTypeDef NVIC_Initstrucure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);
	
	Timer_Initstructure.TIM_ClockDivision=0;
	Timer_Initstructure.TIM_CounterMode=TIM_CounterMode_Up;
	Timer_Initstructure.TIM_Period=arr;
	Timer_Initstructure.TIM_Prescaler=psc;
	TIM_TimeBaseInit(TIM5,&Timer_Initstructure);
	
	TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE);
	NVIC_Initstrucure.NVIC_IRQChannel=TIM5_IRQn;
	NVIC_Initstrucure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Initstrucure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_Initstrucure.NVIC_IRQChannelSubPriority=3;
	NVIC_Init(&NVIC_Initstrucure);
	
	TIM_Cmd(TIM5,ENABLE);
}
void TIM5_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM5,TIM_IT_Update)!=RESET)
	{
		
		OLED_clear(YELLOW);
		/*
		OLED_Char_display(0,0,WHITE,BLACK,'A');
		OLED_Char_display(0,16,WHITE,BLACK,'B');
		OLED_String_Display(0,32,WHITE,BLACK,"ABCDE");
		OLED_Font_Display(0,48,YELLOW,RED,"ÖÐ¹ú");
		*/
		OLED_clear(RED);
		TIM_ClearITPendingBit(TIM5,TIM_IT_Update);
	}
}
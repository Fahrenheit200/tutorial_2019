#include "sys.h"
#include "pwm.h"

void TIM3_PWM_Init(u16 arr, u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM3_Initstructure;
	GPIO_InitTypeDef GPIO_Initstructure;
	TIM_OCInitTypeDef TIM3_OC1_Initstructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	TIM3_Initstructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM3_Initstructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM3_Initstructure.TIM_Period=arr;
	TIM3_Initstructure.TIM_Prescaler=psc;
	TIM_TimeBaseInit(TIM3,&TIM3_Initstructure);
	
	GPIO_Initstructure.GPIO_Mode=GPIO_Mode_AF_PP;   //PWM模式一定要复用功能
	GPIO_Initstructure.GPIO_Pin=GPIO_Pin_6;
	GPIO_Initstructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Initstructure);
	
	TIM3_OC1_Initstructure.TIM_OCMode=TIM_OCMode_PWM2;
	TIM3_OC1_Initstructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM3_OC1_Initstructure.TIM_Pulse=0;
	TIM3_OC1_Initstructure.TIM_OCPolarity=TIM_OCMode_PWM2;
	TIM_OC1Init(TIM3,&TIM3_OC1_Initstructure);
	
	TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM3,ENABLE);
	TIM_Cmd(TIM3, ENABLE);
}
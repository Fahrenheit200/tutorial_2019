#include "sys.h"
#include "key.h"
#include "delay.h"
#include "buzzer.h"
#include "GUI.h"
#include "note.h"

static u8 k=0;
char pause_flag=0;
char Forward_flag=0;
char Backward_flag=0;

void KEY_Init()
{
	GPIO_InitTypeDef GPIO_Initstructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_Initstructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Initstructure.GPIO_Pin=GPIO_Pin_5|GPIO_Pin_4|GPIO_Pin_2;
	GPIO_Init(GPIOA,&GPIO_Initstructure);

	GPIO_Initstructure.GPIO_Pin=GPIO_Pin_1;
	GPIO_Init(GPIOB,&GPIO_Initstructure);
	
	GPIO_Initstructure.GPIO_Pin=GPIO_Pin_0;
	GPIO_Init(GPIOC,&GPIO_Initstructure);
}

void EXTIX_Init()
{
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	KEY_Init();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource4);
	EXTI_InitStructure.EXTI_Line=EXTI_Line4;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//下降沿触发
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource5);
	EXTI_InitStructure.EXTI_Line=EXTI_Line5;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//下降沿触发
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource2);
	EXTI_InitStructure.EXTI_Line=EXTI_Line2;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//下降沿触发
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource0);
	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//下降沿触发
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource1);
	EXTI_InitStructure.EXTI_Line=EXTI_Line1;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//下降沿触发
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	
	
	
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;			//子优先级0
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				
  	NVIC_Init(&NVIC_InitStructure); 
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;			
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;	//抢占优先级0， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;			//子优先级0
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				
  	NVIC_Init(&NVIC_InitStructure); 

	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;			
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;	//抢占优先级1， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;			//子优先级0
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								
  	NVIC_Init(&NVIC_InitStructure); 
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;	//抢占优先级0， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;			//子优先级1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								
  	NVIC_Init(&NVIC_InitStructure); 
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;			
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;	//抢占优先级， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;			//子优先级2
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					
  	NVIC_Init(&NVIC_InitStructure); 
}

/***********暂停&播放***********/
void EXTI4_IRQHandler(void)
{
	u8 i,j;
	delay_ms(10);
	if(RESET != EXTI_GetITStatus(EXTI_Line4))
	{
		if(KEY_PAUSE==0&&pause_flag==0)
		{
			for(i=0; i<100; i++)
			{
				if(KEY_PAUSE==0)
					i=0;
			}
			TIM_Cmd(TIM3,DISABLE);
			pause_flag=1;
		}else if(KEY_PAUSE==0&&pause_flag==1)
		{
			for(j=0; j<100; j++)
			{
				if(KEY_PAUSE==0) j=0;
			}
			TIM_Cmd(TIM3,ENABLE);
			pause_flag=0;
		}
		EXTI_ClearITPendingBit(EXTI_Line4);
	}
}


/***********开始播放***********/
void EXTI9_5_IRQHandler(void)
{
	
	delay_ms(10);
	
	if(RESET != EXTI_GetITStatus(EXTI_Line5))
	{
		if(KEY_START==0)
		{
			while(1)
			{
				TIM_Cmd(TIM3,ENABLE);
				GUI_process(songs[k].name);
				playmusic(k);
				k++;
			}
		}
		
		EXTI_ClearITPendingBit(EXTI_Line5);
	}
	
	
}

/***********下一首***********/
void EXTI2_IRQHandler(void)
{
	u8 i;
	delay_ms(10);
	if(RESET != EXTI_GetITStatus(EXTI_Line2))
	{
		if(KEY_NEXT==0)
		{
			for(i=0;i<100;++i)
			{
				if(KEY_NEXT==0)
					i=0;
			}
			next_flag=1;	
		}
		EXTI_ClearITPendingBit(EXTI_Line2);
	}
}

/***********快进***********/
void EXTI0_IRQHandler(void)
{
	u8 i;
	delay_ms(10);
	if(RESET != EXTI_GetITStatus(EXTI_Line0))
	{
		if(KEY_FAST_FORWARD==0)
		{
			for(i=0;i<100;++i)
			{
				if(KEY_FAST_FORWARD==0)
					i=0;
			}
			//FAST_SPEED=10;			//快退键摁下
			Forward_flag=1;
		}
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}

/***********快退***********/
void EXTI1_IRQHandler(void)
{
	u8 i;
	delay_ms(10);
	if(RESET != EXTI_GetITStatus(EXTI_Line1))
	{
		if(KEY_FAST_BACKWARD==0)
		{
			for(i=0;i<100;++i)
			{
				if(KEY_FAST_BACKWARD==0)
					i=0;
			}
			//FAST_SPEED=-10;    
			Backward_flag=1;
		}
		EXTI_ClearITPendingBit(EXTI_Line1);
	}
}

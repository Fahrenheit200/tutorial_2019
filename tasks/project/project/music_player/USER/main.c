#include "sys.h"
#include "delay.h"
#include "buzzer.h"
#include "pwm.h"
#include "oled.h"
#include "usart.h"
#include "timer.h"
#include "key.h"
#include "GUI.h"
void SWJ_BAN();
int main()
{
	u8 i,j;
	uart_init(9600);
	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	TIM3_PWM_Init(11461,8);
	SWJ_BAN();
	KEY_Init();
	EXTIX_Init();
	OLED_GPIO_Conf();
	OLED_Init();
	MENU_FST();
	
	while(1)
	{
		
	}

}

void SWJ_BAN()
{
	//����AFIO ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	// �ı�ָ���ܽŵ�ӳ�� GPIO_Remap_SWJ_Disable SWJ ��ȫ���ã�JTAG+SW-DP��
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);
	// �ı�ָ���ܽŵ�ӳ�� GPIO_Remap_SWJ_JTAGDisable ��JTAG-DP ���� + SW-DP ʹ��
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
}
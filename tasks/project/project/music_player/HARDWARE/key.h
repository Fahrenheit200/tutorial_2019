#ifndef KEY_H
#define KEY_H
#include "sys.h"

#define KEY_START GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)
#define KEY_PAUSE GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)
#define KEY_NEXT GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2)
#define KEY_FAST_FORWARD GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_0)
#define KEY_FAST_BACKWARD GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)

extern char pause_flag;      //��ͣ��־
extern char next_flag;       //��һ�ױ�־
extern char Forward_flag;    //�����־
extern char Backward_flag;   //���˱�־
void KEY_Init();
void EXTIX_Init();

#endif
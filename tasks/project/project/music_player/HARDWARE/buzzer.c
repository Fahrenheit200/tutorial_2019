#include "sys.h"
#include "buzzer.h"
#include "delay.h"
#include "note.h"
#include "oled.h"
#include "key.h"
char next_flag=0;
u8 outregion =0;

/*�����������̶�Ƶ������*/
void BuzzerSound(u16 Freq)
{
	unsigned long val;
	if((Freq<=8000000/65536)||(Freq > 20000))    //����Ƶ�ʷ�Χ
	{
		TIM_Cmd(TIM3,DISABLE);  //�ر�ʱ��
		outregion=1;     //��ǳ���Ƶ�ʷ�Χ
	}
	else 
	{
		if(outregion==1){     //��ǰһ��Ƶ�ʳ�����Χ
			TIM_Cmd(TIM3,ENABLE);//����ʱ��
			outregion=0;   //�����־
		}
		val = (8000000/Freq)-1;       //pwmƵ��Ӧ����ʵ������Ƶ��
		TIM3->ARR=val;                   //����PWMƵ��
		TIM_SetCompare1(TIM3, val/100);  //����
	}
}
/*��������*/
void playmusic(u8 n)
{
	int i=0;
	while(i<songs_length[n])
	{
		/****��ͣ*****/
		if(pause_flag==1)
		{
			while(1)
			{
				if(pause_flag==0) break;  //�ȴ���ͣ����
			}
		}
		
		/***���*****/
		if(Backward_flag==1)
		{
			i-=10;
			Backward_flag=0;
		}
		
		/***����*****/
		if(Forward_flag==1)
		{
			i+=10;
			Forward_flag=0;
		}
		
		/******����******/
		BuzzerSound((music[n]+i)->mName);
		delay_ms((music[n]+i)->mTime);
		
		/*******������*******/
		PutPixels(10,125,118,128,WHITE);
		cursor(10+i*105/songs_length[n],127);  //���
		PutPixels(10,127,10+i*105/songs_length[n],134,WHITE);  //������ɫΪ��
		PutPixels(13+i*105/songs_length[n],127,118,134,GRAY2); //���ǰ��ɫΪGRAY2
		++i;
		
		/*******��һ��********/
		if(next_flag==1)
		{
			next_flag=0;
			return;
		}
	}
	TIM_Cmd(TIM3,DISABLE);
}














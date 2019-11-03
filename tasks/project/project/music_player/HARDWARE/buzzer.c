#include "sys.h"
#include "buzzer.h"
#include "delay.h"
#include "note.h"
#include "oled.h"
#include "key.h"
char next_flag=0;
u8 outregion =0;

/*蜂鸣器发出固定频率声音*/
void BuzzerSound(u16 Freq)
{
	unsigned long val;
	if((Freq<=8000000/65536)||(Freq > 20000))    //设置频率范围
	{
		TIM_Cmd(TIM3,DISABLE);  //关闭时钟
		outregion=1;     //标记超出频率范围
	}
	else 
	{
		if(outregion==1){     //若前一次频率超出范围
			TIM_Cmd(TIM3,ENABLE);//开启时钟
			outregion=0;   //清除标志
		}
		val = (8000000/Freq)-1;       //pwm频谱应等于实际声音频率
		TIM3->ARR=val;                   //更改PWM频率
		TIM_SetCompare1(TIM3, val/100);  //音量
	}
}
/*播放音乐*/
void playmusic(u8 n)
{
	int i=0;
	while(i<songs_length[n])
	{
		/****暂停*****/
		if(pause_flag==1)
		{
			while(1)
			{
				if(pause_flag==0) break;  //等待暂停结束
			}
		}
		
		/***快进*****/
		if(Backward_flag==1)
		{
			i-=10;
			Backward_flag=0;
		}
		
		/***快退*****/
		if(Forward_flag==1)
		{
			i+=10;
			Forward_flag=0;
		}
		
		/******发声******/
		BuzzerSound((music[n]+i)->mName);
		delay_ms((music[n]+i)->mTime);
		
		/*******进度条*******/
		PutPixels(10,125,118,128,WHITE);
		cursor(10+i*105/songs_length[n],127);  //光标
		PutPixels(10,127,10+i*105/songs_length[n],134,WHITE);  //光标后颜色为白
		PutPixels(13+i*105/songs_length[n],127,118,134,GRAY2); //光标前颜色为GRAY2
		++i;
		
		/*******下一首********/
		if(next_flag==1)
		{
			next_flag=0;
			return;
		}
	}
	TIM_Cmd(TIM3,DISABLE);
}














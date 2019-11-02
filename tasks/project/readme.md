# 单片机项目说明

------
**作者：**刘佳豪
**日期**：2019-11-2
**版本**：1.0

##一、完成情况总览

> * 在单片机储存10首音乐，并可以通过蜂鸣器播放
> * OLED简易交互界面，可以显示歌单以及当前播放音乐
> * 使用按键功能：①播放音乐；②暂停当前音乐；③继续播放；④播放下一首或者上一首
> * 串口上位机通信

##二、项目结构总览
```
#include <avr/pgmspace.h>  //存flash不存动态内存

//OLED模块
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 4

#音符:低中高音全都有
...
const int control_start_and_stop=2; 
const int control_back=5;
const int control_next=3;
const int music_port=8; //蜂鸣器播放

int stop_time=0,x=0;    //暂停，继续播
int buttonState=0;      //按键状态
char current='0';       //选曲
volatile bool State=false;     //外部中断

char datas='9';     //上位机
bool flag=false;      //上位机

void change()       //暂停，继续播放
void music()        //播放音乐,同时在OLED显示

void setup()            //初始化
void loop()
{
    ...
    //读取按键信息
    buttonState=digitalRead();
    ...
    
    //获取上位机发送的指令
    if (Serial.available()>0)
    ...
    
    
}
```

##三、音乐的播放实现以及OLED的显示
###1.音乐播放
```
const static int PROGMEM tune[] //数组用以存储音符
const static float PROGMEM duration[]
//数组用以存储对应音符需要播放的时间
void tone(pin, frequency, duration)//arduino自带播放函数，当然自己写也可以,官网有可替代tone函数的代码
```
###2.OLED的显示
```
static const unsigned char PROGMEM str[]
//用以存储歌曲名字的字模
```


# 单片机题project
- **作者**：李金东
- **修订**：李金东
- **日期**：2019-11-02
- **版本**：1.1.0
- **摘要**：这是大projec的readme

本次大project我完成的功能有
- 通过蜂鸣器播放音乐
- OLED交互界面
- 按键或矩阵键盘交互
- 显示音乐动态频谱
- 上位机通信
- 下载音乐
- 大数相加


本次大project的前5个任务我用的时51单片机实现。为了降低难度我用的是增强版的stc12c5a60s2，该单片机有60kb的flash程序内存，有1024＋256kb的ram，运行速度比stc89c52快一些。但是大数相加的任务虽然我一开始也想用51进行了尝试，但最终还是失败了，所以在最后我不得不用了arduino来实现。下面我就分点仔细地说明我是怎么实现每个模块并且把它嵌在一起的。

## 原理解释

### 通过蜂鸣器播放音乐
简谱的生成方式用了一个叫musicEncoder的软件，简谱的存储方式在此做出详细的说明

曲谱存贮格式 unsigned char code MusicName{音高，音长，音高，音长...., 0,0};	末尾:0,0 表示结束(Important)  
音高由三位数字组成：  
个位是表示 1~7 这七个音符  
十位是表示音符所在的音区:1-低音，2-中音，3-高音;  
百位表示这个音符是否要升半音: 0-不升，1-升半音。  
 
音长最多由三位数字组成： 
个位表示音符的时值，其对应关系是： 
数值(n):  |0 |1 |2 |3 | 4 | 5 | 6  
几分音符: |1 |2 |4 |8 |16 |32 |64 音符=2^n  
十位表示音符的演奏效果(0-2):  0-普通，1-连音，2-顿音  
百位是符点位: 0-无符点，1-有符点  

例如，我的播放器第一首音乐为小星星，它的存储格式为  
```cpp
unsigned char code music[192]={{ 0x15,0x02, 0x15,0x02, 0x19,0x02, 0x19,0x02, 0x1A,0x02,
                                 0x1A,0x02, 0x19,0x01, 0x18,0x02, 0x18,0x02, 0x17,0x02,
                                 0x17,0x02, 0x16,0x02, 0x16,0x02, 0x15,0x01, 0x19,0x02,
                                 0x19,0x02, 0x18,0x02, 0x18,0x02, 0x17,0x02, 0x17,0x02,
                                 0x16,0x01, 0x19,0x02, 0x19,0x02, 0x18,0x02, 0x18,0x02,
                                 0x17,0x02, 0x17,0x02, 0x16,0x01, 0x15,0x02, 0x15,0x02,
                              	 0x19,0x02, 0x19,0x02, 0x1A,0x02, 0x1A,0x02, 0x19,0x01,
                               	 0x18,0x02, 0x18,0x02, 0x17,0x02, 0x17,0x02, 0x16,0x02,
                                 0x16,0x02, 0x15,0x01, 0x00,0x00 },
```
控制音乐播放还有一些细节，在此也进行详细地列出  
在程序里面，一拍的时间设置为  
```cpp
float oneClapTime=2.5;
```
n分音符相对于一拍的时间(即oneClapTime)所占的比例
```cpp
float code clapDiv[7]={1.0,0.5,0.25,0.125,0.0625,0.0315,0.015625};
```
在一拍里面，发生的时间比例设置为
```cpp
float soundpercent=0.5;
```
音乐的频率为
```cpp
uint16 code freq[3][7]={{262,293,329,349,392,440,494},
			{523,586,658,697,783,879,987},
			{1045,1171,1316,1393,1563,1755,1971}};
```
每个频率对应的定时器计时为
```cpp
uint16 code reloadTHTL[3][7]={{0xF88B,0xF95B,0xFA14,0xFA66,0xFB03,0xFB8F,0xFC0B},
			      {0xFC43,0xFCAB,0xFD08,0xFD33,0xFD81,0xFDC7,0xFE05},
			      {0xFB21,0xFE55,0xFE84,0xFE99,0xFEC0,0xFEE3,0xFF02}};
```
以上就是控制音乐播放所用到的全部的基本的信息，这些是控制播放的前提  
播放地原理很简单 就是不停地将蜂鸣器以一定频率把IO口拉高拉低，我用的是定时器0进行控制。中断函数非常简单，如下
```cpp
void beeTimer0()interrupt 1{
	TH0=T0RH; TL0=T0RL;
	if(stopTrig==1) return;
	if(jumpTrig==1) return;
	cnt++;
	if(soundEnable==1) BUZZ=~BUZZ;
	else BUZZ=1;
}
```
如果stop信号触发了，那么就要停止音乐播放，进入interrupt函数之后直接返回什么都不干  
如果jumpTrig信号触发了，相当于触发了快进或者快退  
cnt作为全局变量用来计数，记录一共进入了多少次中断函数，设进入的次数为n，定时器的周期为T，那么n*T就是经过的时间，所以cnt相当于是用来记录时间用的  
如果soundEnable==1 那么要继续发生就将蜂鸣器IO口反向实现生成一定频率的方波  
如果外部某些状况使soundEnable==0 就停止发声，直接return  
控制音乐播放的基本原理就讲到这里了  

### OLED交互界面
我用的是0.96的OLED，与单片机通信的协议为IIC协议。  
开机后，显示的内容为Welcome to my music界面  
在此延时大约2s后开始播放存储的第一首音乐  
播放模式默认为单曲循环，但是没有选择播放模式的功能，若要改变播放模式只能通过改代码来实现  
播放界面为有  
Song:00 00是歌曲的index 前面跟着的是一个音乐符号  
音乐的名字 长度不超过14 中间无空格 以匈牙利命名法命名  
上一首 停止 下一首 的图标符号 若按下停止键，停止图标会换成继续符号  
进度条控制 正常播放时，音乐进度控制条均匀地增加 若停止播放时，音乐进度条会停止变化  
与电脑进行串口通信期间，音乐会停止播放并且界面变成提示正在进行串口通信Communicating的界面  
进度条是通过监测播放音乐时的index相对于整个musicLength的变化来进行更新的  
播放停止时进度条会停止前进 下一首上一首会清空进度条 加快变慢进度条也会相应地加快变慢  
但这里有个BUG 或许是整个project里面唯一的一个bug了 就是快进快退时 进度条会停留在原来的位置无法再次更新，由于时间关系没有修复这个BUG，请求不要扣太多分吧hhhh

### 按键或矩阵键盘交互
我设置了一共有8个功能按键，所用到的功能分别为  
上一首 停止 下一首 进入/退出 UART与电脑进行通信模式  
快退 快进 音乐播放速度变慢 播放速度变快  
按键使用了一个中断，每隔10ms就监测一次按键状态并记录  
如果该次监测到的按键状态不同于上一次的按键状态，则触发功能做出相应的改变  
关于按键的变量声明如下
```cpp
//key in
sbit stop_KeyIn=P1^2;//停止播放
sbit next_KeyIn=P1^3;//下一首
sbit prev_KeyIn=P1^1;//上一首
sbit back_KeyIn=P1^0;//快退
sbit fore_KeyIn=P1^4;//快进
sbit fast_KeyIn=P3^1;//加速
sbit slow_KeyIn=P3^0;//变慢
sbit uart_KeyIn=P3^0;//uart
```
keyIn管脚作为这8个引脚的输入
```cpp
//last key state
bit stop_10msAgo=1;
bit prev_10msAgo=1;
bit next_10msAgo=1;
bit back_10msAgo=1;
bit fore_10msAgo=1;
bit fast_10msAgo=1;
bit slow_10msAgo=1;
bit uart_10msAgo=1;
```
10msAgo这个位用来存储10ms之前监测到的按键状态 按键状态只有低和高
```cpp
//switch song state
bit abortTrig;
bit jumpTrig;
uint8 trigMode;
uint8 musicMode;
//broadcast state
bit stopTrig;
bit isStopSignShow;
bit soundEnable;
```
这些作为全局变量用来存储按键的触发与否和触发的模式  
监测按键的中断函数在下面给出
```cpp
void buttonTimer1()interrupt 3{
	//10ms
	TH1=0x88;
	TL1=0x00;

	stop_KeyIn=1;
	next_KeyIn=1;
	prev_KeyIn=1;
	back_KeyIn=1;
	fore_KeyIn=1;
	fast_KeyIn=1;
	slow_KeyIn=1;
//与10ms前的信号进行比较 如果当前的按键状态和10ms前按键状态不同，则相应地发出触发信号
	if(stop_10msAgo==1&&stop_KeyIn==0){
		if(stopTrig==0){
			stopTrig=1;
			//showContinue();
		}
		else{
			stopTrig=0;
			//showStop();
		}
	}
	if(next_10msAgo==1&&next_KeyIn==0){
		abortTrig=1;
		trigMode=CHANGE_NEXT;
	}
	if(prev_10msAgo==1&&prev_KeyIn==0){
		abortTrig=1;
		trigMode=CHANGE_PRE;
	}
	if(back_10msAgo==1&&back_KeyIn==0){
		jumpTrig=1;
		trigMode=JUMP_BACK;
	}
	if(fore_10msAgo==1&&fore_KeyIn==0){
		jumpTrig=1;
		trigMode=JUMP_FORE;
	}
	if(fast_10msAgo==1&&fast_KeyIn==0){
		oneClapTime+=0.2;
	}
	if(slow_10msAgo==1&&slow_KeyIn==0){
		oneClapTime-=0.2;
	}
	stop_10msAgo=stop_KeyIn;
	prev_10msAgo=prev_KeyIn;
	next_10msAgo=next_KeyIn;
	back_10msAgo=back_KeyIn;
	fore_10msAgo=fore_KeyIn;
	fast_10msAgo=fore_KeyIn;
	slow_10msAgo=fore_KeyIn;
//存储此次监测到的按键信号，覆盖10ms之前的按键信号
}
```
至于按键触发了之后会相应地做出怎样地变化后面再说

### 显示音乐动态频谱
频谱的实现我用了另外一个单片机 通过接收蜂鸣器控制频率的IO的高低电平信息，来控制另外一个0.96寸的OLED进行频谱的显示  
频谱控制的算法用了快速傅里叶变换  
参考了网上音乐频谱实现的例程，大部分都用了adc转换加上快速傅里叶变换  
但我想了想如果只是蜂鸣器的话无非是不同频率的方波信号，是离散的0101而不是连续的模拟量，这样我就用不着adc了我就直接用一个普通的管脚，用一个定时中断，以一定频率监测蜂鸣器的io口是0还是1就行了，每获取64个数据之后就进行快速傅里叶变换即可
由于控制蜂鸣器的频率最高也不超过2k，所以采样频率并不用太快，我设置成4khz就算了  
进行傅里叶变换之后，每一个频率分量对应的复数幅值就是这个在这个频率幅值，按比例地在oled显示的时候用一根长柱来表示即可  
64个点，就有64个频率分量，但是快速傅里叶变换得出来的结果是对称的，取前面的32个即可  
于是便可以将0.96寸的即128乘64的oled划分成横坐标为32(每四列为一个住)，纵坐标为8 (8个位一页，方便控制显示) 的频谱图，将傅里叶变换得到的32个频率分量的幅值就可以按比例地映射到这32个柱子上
我看网上还有些代码使用了自动增益控制。但我看了看无非就是做一个判断防止幅值过高上冲到顶  
我感觉如果比例调地刚刚好，自动增益控制就可有可无，所以就没有做这一步

### 上位机通信和下载音乐
实现上位机通信时，单片机通过uart协议和电脑进行通信。在电脑实现的上位机程序使用了pyserial和pysimpleui  
电脑上位机程序能实现的功能:
- 设置好com口和波特率与单片机成功进行串口连接后，即弹出框框显示当前单片机存储的音乐总数量。
- 读取某个index的音乐的信息
- 下载音乐到某个index位置
- 如果在这个index位置内原来就有旧的音乐，那么新下载的音乐就会覆盖旧的音乐

进行上位机通信之前，必须按下 进入/退出UART与电脑进行通信模式 按键，并等待其出现Communicating界面，才能进行上位机通信  
结束上位机通信继续播放音乐时，要在电脑上电机关闭串口按键，之后再在单片机按下 进入/退出UART与电脑进行通信模式 按键 才能继续播放音乐  
音乐存放的位置不像大多数人都直接写成code变量存储在程序中，我的音乐存放位置时at24c256 eeprom里面  
该eeprom有32kb的内存，足够存放音乐。为了使从上位机下载下来的音乐能够断电保存，必须存储在eeprom内（或者sd卡 但在这里就不考虑了hhhhh）  
存储在eeprom里就麻烦多了，不能像之前一样直接访问unsign char code music[][]一样访问  
每播一首歌之前必须要先把要播放的歌曲序号从eeprom相应的存储空间内获取到buff[]里面，然后播放音乐时就从buff[]里面一个一个index移动播放下一个音调  
音乐在eeprom里面存储遵循着一定的格式。我用的是atc256的eeprom，有256/8即36kb的存储空间。每64字节为一页，一共有512页。每首音乐事先规定占用3页的空间，即192字节。这192字节的前16位是音乐的基本信息，前14位是音乐的名字，15位是名字的长度(0-14)，16位是音乐的长度。每次从eeprom里面获取音乐时，就将这192字节一次性全部获取即可。

### 大数相加
大数相加要用到sd卡，sd卡用的使spi通信，stc12c5a60s2内置有spi模块，我用了spi内置模块进行对sd卡读取的尝试，照着datasheet里面的配置我就一步步地配置各个寄存器，写好底层函数，但是实在不知道为什么写好程序之后无论向sd卡发送什么的消息返回来的都是0xff。。并没有成功debug了很久之后还是无法实现对sd卡的初始化。于是所以我又用了模拟spi通信的办法进行尝试，通过手动拉低拉高时钟来进行byte的传输，但还是没有成功，debug了很久之后最终还是放弃了，决定使用arduino进行实现

arduino实现就简单很多了，所有sd卡初始化的工作全部交给arduino自带的库，自己实现大数相加就行。arduino是无法存储10000个数的，必须分批地进行读取和写入。我每次从sd卡里面取100位进行相加，结果先按照最低为在前的方式存储到d.txt里面，计算完之后，再将d.txt里面的数字逆序存储到c.txt里面，再将d.txt删除，就完成了这个逆序再逆序的过程。

## 代码分析
下面具体地分析我的代码
上传上来的文件有10个文件夹 在此一一说明它们是用来干嘛的
arduino-sd-bigNumberAdd 进行大数相加
fft-spectrum 上传到单片机B 从单片机A的蜂鸣器IO口进行采样 控制oled B来进行频谱显示
music-button-oled 上传到单片机A 该代码是历史版本 没有嵌入uart上位机通信
spi-sd-doNotUseSPIReg 用51单片机 不用stc12c5a60s2内置SPI模块对sd卡进行读取的尝试（失败）
spi-sd-UseSPIReg 用51单片机 用stc12c5a60s2内置SPI模块对sd卡进行读取的尝试（失败）
uart 上传到单片机A 该代码是历史版本 只能单纯地进行上位机通信
uart-music-button-oled 上传到单片机A 最终版本 嵌入了音乐播放 键盘控制 oled A显示播放信息 和uart上位机通信
uart-readTotalSong 用于debug 读取eeprom里面写入地所有音乐 用串口助手进行接收
uart-writeBasicSong 初始化程序 往eeprom里面写入最基本的6首歌

主要介绍
uart-music-button-oled文件夹里面的程序
该文件夹有9个文件
- delay.c 实现软件delay函数 每个程序通过extern来调用
- eeprom.c 进行写入eeprom的基本操作 依赖IIC.c里面的函数 eeprom.c 里面有以下函数
```cpp
uint8 eepromReadByte(uint16 addr);
bit eepromWriteByte(uint16 addr,uint8 dat);
bit eepromWritePage(uint16 addr,uint8 *dat,uint8 len);
bit eepromReadPage(uint16 addr,uint8 *dat,uint8 len);
```
- IIC.c 实现了最基本的IIC传输协议所需要的最基本的函数 是实现控制oled和eeprom的最基本最底层的函数
```cpp
void I2CStart();
void I2CStop();
bit I2CWrite(unsigned char dat);
unsigned char I2CReadNAK();
unsigned char I2CReadACK();
```
- music_data.c 里面是控制音乐播放所需要的所有信息 在原理解释中已经给出具体的介绍
```cpp
oled_data.c 进行oled显示所要显示的内容 比如
uint8 code s1[]="Welcome to my";
uint8 code s2[]="[MUSIC]";
uint8 code u1[]="Communicating";
uint8 code u2[]="UARTing";
uint8 code smallChar[];
uint8 code bigChar[]
```
- oled_show.c 把要在oled显示的控制代码封装成一个个函数 每个函数里面调用oledctrl.c里面的函数进行具体的显示 例如
```cpp
void showName();
void showBasicPic();
void showSongNumber();
void showBeginPic();
void clearName();
void showStopSign();
void showContinue();
void showBeatLine();
void clearBeatLine();
void showUart();
void oledInit();
```
- oledctrl.c 进行oled最基本操作的所有函数 包括
```cpp
void oldeWrite(unsigned dat, unsigned cmd);
void writeI2CCom(uint8 cmd);
void writeI2CDat(uint8 dat);
void oledClear();
void oledSetPos(uint8 x, uint8 y);
void oledSmallChar(uint8 x,uint8 y,uint8 chr);
void oledBigChar(uint8 x,uint8 y,uint8 chr);
void oledDrawPic(uint8 x0,uint8 y0,
				 uint8 x1,uint8 y1,uint8 BMP[]);
```
- togethor_main.c 最重要的文件 包含了main文件 嵌入了所有功能  
由于readMe写到这里的时候已经11:22分了，所以只能简要地写写  
最主要的代码是main函数 playMusic()函数 uart串口中断函数  
```cpp
void main(){
	EA=1;
	TMOD=0x11;
	//初始化
	oledInit();
	beeInit();
	buttonInit();
	oledClear();
	readTotalSong();
	
	showBeginPic();
	delay50ms(500);
	whichSong=0;
	musicMode=THE_SAME;
	//主循环
	while(1){
		//如果当前处于串口通信状态
		if(uartTrig==1){
			if(isUartSignShow==0){
				oledClear();
				showUart();
				isUartSignShow=1;
				configUART(9600);
			}
			continue;
		}
		//显示oled
		oledClear();
		showBasicPic();

		//从eeprom里面获取music
		getMusicData();
		showSongNumber();
		showName();

		//播放音乐
		playMusic();

		//换歌
		changeSong();
		delay50ms(200);
	}
}
```
playMusic()函数 无力再写注释了 playMusic在干的事情整体就是 在musicBuff[]里面index不断地移向下一个，读取下一个节拍的信息
遇到各种不同的按键触发采取不同的行为来应付
```cpp
void playMusic(){
	uint8 t;
	float beatCnt=0,soundCnt=0;
	uint8 buffIndex=16;
	bit endTrig=0;
	
	uint8 note,beat;
	uint8 noteNum,noteLevel;
	uint8 beatNum,beatDot;
	
	isStopSignShow=1;
	soundEnable=0;
	stopTrig=0;
	cnt=0;
	clearBeatLine();

	modBeat=musicBuff[15]/32.0;
	for(t=0;t<16;t++) lineShowIndex[t]=modBeat*(float)(t+1)+0.5;
	nowLine=0;
	
	while(1){
		if(abortTrig==1) break;
		if(endTrig==1) break;
		if(stopTrig==1){
			if(isStopSignShow==1){
				isStopSignShow=0;
				showContinue();
			}
			continue;
		}
		else{
			if(isStopSignShow==0){
				isStopSignShow=1;
				showStop();
			}
		}
		if(jumpTrig==1){
			if(trigMode==JUMP_BACK){
				if(buffIndex<26) buffIndex=16;
				else buffIndex-=10;
			}
			if(trigMode==JUMP_FORE) buffIndex=buffIndex+10;
			jumpTrig=0;
			trigMode=0;
			
			cnt=0;
			soundEnable=0;
			beatCnt=0;
			soundCnt=0;
			continue;
		}
		if(soundEnable==1&&cnt>soundCnt) soundEnable=0;
		if(cnt>=beatCnt){
			//another note and beat,reset cnt
			cnt=0;
			//get note and beat
			note=musicBuff[buffIndex];
			beat=musicBuff[buffIndex+1];
			buffIndex+=2;
			//reach the end
			if(note==0x00&&beat==0x00){
				endTrig=1;
				T0RH=0Xff; T0RL=0X00;
				continue;
			}
			//translate note and beat
			noteNum=note%10-1; noteLevel=note/10-1;
			beatNum=beat%10;   beatDot=beat/100;
			//set the beatCnt and soundCnt
			if(beatDot==0) beatCnt=(oneClapTime*clapDiv[beat])*freq[noteLevel][noteNum];
					  else beatCnt=(oneClapTime*clapDiv[beatNum]*1.5)*freq[noteLevel][noteNum];
			soundCnt=beatCnt*soundpercent;
			//reload the timer
			T0RH=reloadTHTL[noteLevel][noteNum]>>8;
			T0RL=reloadTHTL[noteLevel][noteNum];
			soundEnable=1;
			
			if((buffIndex-16)/2==lineShowIndex[nowLine]){
				nowLine++;
				showBeatLine();
			}
		}
	}
	soundEnable=0;
	nowLine=0;
}
```
串口中断函数 遇到接收到的不同的信息 进行不同的处理  
从上位机里面的接收到的命令有  
- 0xfa 说明要下载音乐状态
- 0xfc 说明要进行读取音乐状态
- 0xfd 说明要读取所有音乐的数目 该数目存储在地址为0x1111的内存里面
- 0x99 说明要结束串口通信 并进行disableUart操作 该信号的触发由上位机来发出 必须有这一个信号否则无法结束串口通信

原因是我监测按键用的是T1计时器，但是串口中断用的也是T1计时器，每次进入串口中断时要按下相应的功能按键 才能enableUART将T1计时器改成串口通信模式 每次结束串口通信 要通过上位机发送0x99命令 才能disableUART使T1计时器重新用来监测键盘

``cpp
void InterruptUART()interrupt 4{
	uint8 i,tmp;
	uint8 cache;
	if(RI==1){
		RI=0;
		cache=SBUF;
		if(cache==0x99) disableUart();
		if(cache==0xfa) getState=GET_0XFA;
		if(cache==0xfc) getState=GET_0XFC;
		if(cache==0xfd) getState=GET_TOT; 
		switch(getState){
			case GET_0XFA:
				getState=GET_WRITE_INDEX;
				for(i=0;i<192;i++) buff[i]=0;
				buffIndex=0;
				break;
			case GET_WRITE_INDEX:
				writeIndex=cache;
				getState=GET_DATA;
				break;
			case GET_DATA:
				if(cache==0xff){
					copy2EEProm();
					tot+=1;
					while(eepromWriteByte(0x1111,tot)==0);
					getState=FINISH;
					break;
				}
				buff[buffIndex]=cache;
				buffIndex++;
				break;
			case GET_0XFC:
				getState=GET_INDEX;
				break;
			case GET_INDEX:
				if(cache==0xff){
					getState=FINISH;
					SBUF=0x01;
					sendstate=1;
					buffIndex=0;
					len=0;
					getFromEEProm();
					break;
				}
				readIndex=cache;
				break;
			case GET_TOT:
				tmp=0xee;
				while(tmp==0xee)
				tmp=eepromReadByte(0x1111);
				SBUF=tmp;
				getState=FINISH;
				break;
		}
	}
	if(TI==1){
		TI=0;
		if(sendstate==1){
			cache=buff[buffIndex];
			if(buffIndex==15) len=cache;
			if((len==0||buffIndex<len+16)&&buffIndex<192){
				SBUF=cache;
				buffIndex++;
			}
			else
			sendstate=0;
		}
	}
}
```
到这里就结束了 没时间再写多了要赶紧push了哈哈哈哈哈哈

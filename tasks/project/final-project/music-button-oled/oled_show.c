typedef unsigned char uint8;
typedef unsigned int uint16;

extern uint8 code s1[];
extern uint8 code s2[];
extern uint8 code smallChar[];
extern uint8 code bigChar[];
extern uint8 code musicSign[];
extern uint8 code processLine[];
extern uint8 code emptyLine[];
extern uint8 code preSign[];
extern uint8 code nextSign[];
extern uint8 code stopSign[];
extern uint8 code continueSign[];
extern uint8 musicBuff[];
extern uint8 whichSong;

extern void oledSmallChar(uint8 x,uint8 y,uint8 chr);
extern void oledBigChar(uint8 x,uint8 y,uint8 chr);
extern void oledDrawPic(uint8 x0,uint8 y0,
				 uint8 x1,uint8 y1,uint8 BMP[]); 

void showName();
void showBasicPic();
void showSongNumber();
void showBeginPic();
void clearName();
void showStopSign();
void showContinue();
void showBeatLine();
void clearBeatLine();

float modBeat;
unsigned char beatLineIndex;
unsigned char nowLine;
unsigned char lineShowIndex[16];

void showBeatLine(){
	oledDrawPic(beatLineIndex,7,beatLineIndex+8,7,processLine);
	beatLineIndex+=8;
}
void clearBeatLine(){
	unsigned char t;
	beatLineIndex=0;
	for(t=0;t<128;t=t+8)
	oledDrawPic(t,7,t+8,7,emptyLine);
}
void showStop(){
	oledDrawPic(56,6,64,6,stopSign);
}
void showContinue(){
	oledDrawPic(56,6,64,6,continueSign);
}
void showName(){
	uint16 t;
	uint16 index;
	for(t=0,index=0;musicBuff[t]!=0&&t<14;t++,index+=8)
	oledBigChar(index,3,musicBuff[t]);
}
void showBasicPic(){
	oledDrawPic(0,0,16,1,musicSign);
	oledBigChar(16,0,'S');
	oledBigChar(24,0,'o');
	oledBigChar(32,0,'n');
	oledBigChar(40,0,'g');
	oledBigChar(48,0,':');
	oledBigChar(56,0,'0');
	oledBigChar(64,0,'1');
	oledSmallChar(24,6,'p');
	oledSmallChar(30,6,'r');
	oledSmallChar(36,6,'e');
	oledDrawPic(48,6,56,6,preSign);
	oledDrawPic(56,6,64,6,stopSign);
	oledDrawPic(64,6,72,6,nextSign);
	oledSmallChar(76,6,'n');
	oledSmallChar(82,6,'e');
	oledSmallChar(88,6,'x');
	oledSmallChar(94,6,'t');
}
void showSongNumber(){
	uint8 lowNum=whichSong%10;
	uint8 highNum=whichSong/10;
	oledBigChar(56,0,highNum+'0');
	oledBigChar(64,0,lowNum+'0');
}
void showBeginPic(){
	uint8 t;
	uint8 xIndex;
	xIndex=12;
	for(t=0;t<13;t++){
		oledBigChar(xIndex,1,s1[t]);
		xIndex+=8;
	}
	xIndex=36;
	for(t=0;t<7;t++){
		oledBigChar(xIndex,4,s2[t]);
		xIndex+=8;
	}
	oledDrawPic(16,4,32,5,musicSign);
	oledDrawPic(96,4,112,5,musicSign);
}
void clearName(){
	uint16 t;
	for(t=0;t<15;t++)
	oledBigChar(t*8,3,' ');
}

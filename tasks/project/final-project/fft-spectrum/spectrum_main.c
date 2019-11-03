#include "STC12C5A60S2.H" 
#include "intrins.h"
typedef unsigned char uint8;
typedef unsigned int uint16;

extern void oledInit();
extern void oledClear();
extern void spectrumShow();

extern uint8 isLightUp[16][8];
extern void fastFourier();
extern void clearDat();
extern void pushDat(uint8 index,uint8 s);

uint8 scnt=0;
bit cacheDat;
sbit detect=P3^2;

void detectInit();
//void configUART(unsigned int baud);
void main(){
	uint8 i,j;
	EA=1;
	for(i=0;i<32;i++)
	for(j=0;j<8;j++)
	isLightUp[i][j]=0;
	detectInit();
	oledInit();
	oledClear();
	//configUART(9600);
	
	while(1){
		if(scnt>=64){
			scnt=0;
			fastFourier();
			spectrumShow();
			clearDat();
		}
	}
}
/*
void configUART(unsigned int baud){
	SCON=0x50;
	TMOD&=0X0F;
	TMOD|=0X20;
	TH1=256-(11059200/12/32)/baud;
	TL1=TH1;
	ET1=0;
	ES=1;
	TR1=1;
}
*/
void detectInit(){
	TMOD=0x01;
	
	TH0=0xff;
	TL0=0x48;
	ET0=1;
	TR0=1;
}
void detectInterrupt()interrupt 1{
	TH0=0xff;
	TL0=0x80;
	detect=1;
	if(detect==1) cacheDat=0x01;
	else cacheDat=0x00;
	
	if(scnt<64){
		pushDat(scnt,cacheDat);
		scnt++;
	}
}
/*
void InterruptUART()interrupt 4{
	uint8 tmp;
	if(RI==1){
		RI=0;
		tmp=SBUF;
		SBUF=0x01;
	}
	if(TI==1){
		TI=0;
		if(scnt<=64)
		SBUF=cacheDat;
		else
		SBUF=0xff;
	}
}
*/

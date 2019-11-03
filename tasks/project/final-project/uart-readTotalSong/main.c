#include "STC12C5A60S2.H"
typedef unsigned char uint8;	//0~255
typedef unsigned int uint16;	//0~65525

extern bit eepromWriteByte(uint16 addr,uint8 dat);
extern uint8 eepromReadByte(uint16 addr);
extern void eepromWritePage(uint16 addr,uint8 *dat,uint8 len);
extern void eepromReadPage(uint16 addr,uint8 *dat,uint8 len);

uint16 cnt=0;
uint8 tmp;
uint16 addr=0;

void configUART(unsigned int baud);
void main(){
	EA=1;
	configUART(9600);
	while(1){
	}
}								
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
void InterruptUART()interrupt 4{
	if(RI==1){
		RI=0;
		tmp=SBUF;
		SBUF=tmp;
	}
	if(TI==1){
		TI=0;
		if(cnt<1920){
			tmp=0xee;
			while(tmp==0xee){
				tmp=eepromReadByte(addr);
			}
			SBUF=tmp;
			addr++;
			cnt++;
		}
		if(cnt==1920){
			tmp=0xee;
			while(tmp==0xee){
				tmp=eepromReadByte(0x1111);
			}
			SBUF=tmp;
			cnt++;
		} 
	}
}

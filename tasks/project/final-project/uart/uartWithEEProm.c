#include "STC12C5A60S2.H"
#define GET_0XFA 0
#define GET_WRITE_INDEX 5
#define GET_DATA 1
#define GET_0XFC 2
#define GET_INDEX 3
#define FINISH 4
#define GET_TOT 6
typedef unsigned char uint8;	//0~255
typedef unsigned int uint16;	//0~65525
extern bit eepromWriteByte(uint16 addr,uint8 dat);
extern uint8 eepromReadByte(uint16 addr);
extern bit eepromWritePage(uint16 addr,uint8 *dat,uint8 len);
extern bit eepromReadPage(uint16 addr,uint8 *dat,uint8 len);

uint16 code dataStart[20]= {0,192,384,576,768,960,1152,1344,1536,1728,
						   1920,2112,2304,2496,2688,2880,3072,3264,3456,3648};
uint8 getState;
uint8 buff[192];
uint8 buffIndex;
uint8 readIndex;
uint8 writeIndex=6;
uint8 totSong;
uint8 len=0;
bit sendstate=0;
void delay1ms(unsigned int t);
void copy2EEProm();
void getFromEEProm();
void configUART(unsigned int baud);
void main(){
	EA=1;
	
	totSong=0xee;
	while(totSong==0xee)
	totSong=eepromReadByte(0x1111);
	
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
void copy2EEProm(){
	uint8 *ptr;
	uint16 addr;
	addr=dataStart[writeIndex];
	ptr=&buff[0];
	while(eepromWritePage(addr,ptr,64)==0);
	delay1ms(5);
	addr=dataStart[writeIndex]+64;
	ptr=&buff[64];
	while(eepromWritePage(addr,ptr,64)==0);
	delay1ms(5);
	addr=dataStart[writeIndex]+128;
	ptr=&buff[128];
	while(eepromWritePage(addr,ptr,64)==0);
	delay1ms(5);
}
void getFromEEProm(){
	//uint8 *ptr;
	uint8 tmp;
	uint8 i;
	uint16 addr;
	addr=dataStart[readIndex];
	for(i=0;i<192;i++){
		tmp=0xee;
		while(tmp==0xee) tmp=eepromReadByte(addr);
		buff[i]=tmp;
		addr++;
	}
	/*
	ptr=&buff[0];
	while(eepromReadPage(addr,ptr,64)==0);
	delay1ms(5);
	addr=dataStart[readIndex]+64;
	ptr=&buff[64];
	while(eepromReadPage(addr,ptr,64)==0);
	delay1ms(5);
	addr=dataStart[readIndex]+128;
	ptr=&buff[128];
	while(eepromReadPage(addr,ptr,64)==0);
	delay1ms(5);
	*/
}
void InterruptUART()interrupt 4{
	uint8 i,tmp;
	uint8 cache;
	if(RI==1){
		RI=0;
		cache=SBUF;
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
					totSong+=1;
					while(eepromWriteByte(0x1111,totSong)==0);
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
void delay1ms(unsigned int t)
{
	unsigned char i;
	while (t--)
	for (i=0;i<123;i++);
}

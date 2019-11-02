#include "STC12C5A60S2.H"
typedef unsigned char uint8;	//0~255
typedef unsigned int uint16;	//0~65525

extern bit eepromWriteByte(uint16 addr,uint8 dat);
extern uint8 eepromReadByte(uint16 addr);
extern bit eepromWritePage(uint16 addr,uint8 *dat,uint8 len);
extern bit eepromReadPage(uint16 addr,uint8 *dat,uint8 len);

extern unsigned char code musicCode[6][192];
extern unsigned char musicLength[6];
extern unsigned char code nameLength[6];
extern unsigned char *nameCode[6];

uint8 code zero[64]={0};
uint16 code nameStart[20]= {0,192,384,576,768,960,1152,1344,1536,1728,
						    1920,2112,2304,2496,2688,2880,3072,3264,3456,3648};
						    
uint16 code musicStart[20][3]={{16,64,128},{208,256,320},{400,448,512},{592,640,704},
							   {784,832,896},{976,1024,1088},{1168,1216,1280},{1360,1408,1472},
							   {1552,1600,1664},{1744,1792,1856},{1936,1984,2048},{2128,2176,2240},
							   {2320,2368,2432},{2512,2560,2624},{2704,2752,2816},{2896,2944,3008},
							   {3088,3136,3200},{3280,3328,3392},{3472,3520,3584},{3664,3712,3776}};
uint16 addr;
uint8 *ptr;
bit flag=0;
void configUART(unsigned int baud);
void delay1ms(unsigned int t);
void main(){
	uint16 i;
	uint16 len;
	EA=1; 
	configUART(9600);
	addr=0;
	for(i=0;i<60;i++){
		addr=64*i;
		while(eepromWritePage(addr,zero,64)==0);
		delay1ms(10);
	}
	
	for(i=0;i<6;i++){
		addr=nameStart[i];
		while(eepromWritePage(addr,nameCode[i],nameLength[i])==0);
		len=musicLength[i];
		delay1ms(10);
		while(eepromWriteByte(addr+14,nameLength[i])==0);
		while(eepromWriteByte(addr+15,musicLength[i])==0);
		//-------------------------------------------round 1
		addr=musicStart[i][0];
		ptr=&musicCode[i][0];
		if(len>=48){
			while(eepromWritePage(addr,ptr,48)==0);
			len=len-48;
		}
		else{
			while(eepromWritePage(addr,ptr,len)==0);
			continue;
		}
		delay1ms(10);
		//-------------------------------------------round 2
		addr=musicStart[i][1];
		ptr=&musicCode[i][48];
		if(len>=64){
			while(eepromWritePage(addr,ptr,64)==0);
			len=len-64;
		}
		else{
			while(eepromWritePage(addr,ptr,len)==0);
			continue;
		}
		delay1ms(10);
		//-------------------------------------------round 3
		addr=musicStart[i][2];
		ptr=&musicCode[i][112];
		if(len>=64){
			while(eepromWritePage(addr,ptr,64)==0);
			len=len-64;
		}
		else{
			while(eepromWritePage(addr,ptr,len)==0);
			continue;
		}
		delay1ms(10);
	}
	
	while(eepromWriteByte(0x1111,0x06)==0){
		delay1ms(10);
	}
	flag=1;
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
void delay1ms(unsigned int t)
{
	unsigned char i;
	while (t--)
	for (i=0;i<123;i++);
}
void InterruptUART()interrupt 4{
	if(RI==1){
		RI=0;
		if(flag==1)
		SBUF=0xff;
		else
		SBUF=0xee;
	}
	if(TI==1){
		TI=0;
	}
}


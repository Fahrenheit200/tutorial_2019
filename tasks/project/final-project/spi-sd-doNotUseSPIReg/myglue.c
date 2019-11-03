#include "reg51.h"
#define error 1
sbit CS  =P1^3;//CS
sbit SDI =P1^6;//MISO
sbit SDO =P1^5;//MOSI
sbit SCK =P1^7;//SCK
typedef unsigned char 	uint8;
typedef unsigned int 	uint16;
typedef unsigned long 	uint32;

void delay5us();
void WriteByte(uint8 thisByte);
void SendCmd(uint8 first,uint8 a1,uint8 a2,uint8 a3,uint8 a4,uint8 crc);
void disableCS();
void enableCS();
uint8 ReadByte();
uint8 WaitOneByteRespond();
uint8 AllInit();
uint8 WaitForReady();
uint8 WriteSector(uint32 SectorNumber,uint8 *Buffer);
uint8 ReadSector(uint32 SectorNumber,uint8 *Buffer);
void disableCS(){
	CS=1;
}
void enableCS(){
	CS=0;
}
void delay5us(){
	uint8 a=0;
	for(a=0;a<40;a++);
}
void WriteByte(uint8 thisByte){
	uint8 i;
	for (i=0;i<8;i++)
	{
		SCK=0;
		if(thisByte&0x80) SDO=1;
		else SDO=0;
		SCK=1;
		delay5us();
		thisByte=thisByte<<1;
	}
}
uint8 ReadByte(){
	uint8 ret,i;
	ret=0xff;
	for (i=0;i<8;i++)
	{
		SCK=0;
		delay5us();
		SCK=1;
		ret=ret<<1;
		if(SDI) ret++;	
	}
	return ret;
}
void SendCmd(uint8 first,uint8 a1,uint8 a2,uint8 a3,uint8 a4,uint8 crc){
	SDO=1;
	CS=0;
	WriteByte(0xff);
	WriteByte(first+64);
	WriteByte(a1);
	WriteByte(a2);
	WriteByte(a3);
	WriteByte(a4);
	WriteByte(crc);
	WriteByte(0xff);
}
uint8 WaitOneByteRespond(){
	uint8 TIMES=100,i;
	uint8 tmp=0xff;
	for(i=0;i<TIMES;i++){
		tmp=ReadByte();
		if(tmp!=0xff)
		return tmp;
	}
	return tmp;
}
uint8 AllInit(){
	uint8 i,TIMES,reply;
	
	CS=1;
	for(i=0;i<10;i++)
	WriteByte(0xff);
	CS=0;
	
	SendCmd(0,0,0,0,0,0x95);//cmd 0
	TIMES=100;
	reply=0xff;
	for(i=0;i<TIMES;i++){
		reply=WaitOneByteRespond();
		if(reply==0x01) break;
	}
	while(!TI); TI=0;
	SBUF=0xbb;
	while(!TI); TI=0;
	SBUF=reply;
	
	if(reply!=0x01) return error;
	
	
	SendCmd(8,0,0,0x01,0xaa,0x87);//cmd 8
	TIMES=100;
	reply=0xff;
	for(i=0;i<TIMES;i++){
		reply=WaitOneByteRespond();
		if(reply!=0xff) break;
	}
	while(!TI); TI=0;
	SBUF=0xcc;
	while(!TI); TI=0;
	SBUF=reply;
	
	/* 
	SendCmd(55,0,0,0,0,0xff);//cmd 55 41
	SendCmd(41,0,0,0,0,0xff);
	TIMES=100;
	reply=0xff;
	for(i=0;i<TIMES;i++){
		reply=WaitOneByteRespond();
		if(reply!=0xff) break;
	}
	while(!TI); TI=0;
	SBUF=0xcc;
	while(!TI); TI=0;
	SBUF=reply;
	if(reply==0){
		SendCmd(55,0,0,0,0,0xff);//cmd 55 41
		SendCmd(41,0,0,0,0,0xff);
		TIMES=100;
		reply=0xff;
		for(i=0;i<TIMES;i++){
			reply=WaitOneByteRespond();
			if(reply==0x00) break;
		}
	}
	else{
		SendCmd(1,0,0,0,0,0xff);//cmd 1
		TIMES=100;
		reply=0xff;
		for(i=0;i<TIMES;i++){
			reply=WaitOneByteRespond();
			if(reply==0x00) break;
		}
	}
	while(!TI); TI=0;
	SBUF=0xdd;
	while(!TI); TI=0;
	SBUF=reply;
	//if(reply!=0) return error;
	*/ 
	if(reply==0x01){
		ReadByte(); ReadByte();	ReadByte();	ReadByte();
		SendCmd(55,0,0,0,0,0xff);//cmd 55 41
		SendCmd(41,0,0,0,0,0xff);
		TIMES=100;
		reply=0xff;
		for(i=0;i<TIMES;i++){
			reply=WaitOneByteRespond();
			if(reply!=0xff) break;
		}
	}
	else{
		SendCmd(55,0,0,0,0,0xff);//cmd 55 41
		SendCmd(41,0,0,0,0,0xff);
		TIMES=100;
		reply=0xff;
		for(i=0;i<TIMES;i++){
			reply=WaitOneByteRespond();
			if(reply!=0xff) break;
		}
	}
	while(!TI); TI=0;
	SBUF=0xdd;
	while(!TI); TI=0;
	SBUF=reply;
	
	
	
	SendCmd(1,0,0,0,0,0xff);//cmd 1
	TIMES=100;
	reply=0xff;
	for(i=0;i<TIMES;i++){
		reply=WaitOneByteRespond();
		if(reply==0x00) break;
	}
	while(!TI); TI=0;
	SBUF=0xee;
	while(!TI); TI=0;
	SBUF=reply;
	//if(reply!=0x00) return error;
	

	
	SendCmd(16,0,0,0x02,0x00,0xff);//cmd 16
	TIMES=100;
	reply=0xff;
	for(i=0;i<TIMES;i++){
		reply=WaitOneByteRespond();
		if(reply==0x00) break;
	}
	while(!TI); TI=0;
	SBUF=0x99;
	while(!TI); TI=0;
	SBUF=reply;
	if(reply!=0x00) return error;
	
	CS=0;
	return 0;
}
uint8 WaitForReady(){
	uint8 i,TIMES,reply;
	TIMES=100;
	for(i=0;i<TIMES;i++){
		reply=ReadByte();
		if(reply!=0xff)
		return reply;
	}
	return 0xff;
}
uint8 WriteSector(uint32 SectorNumber,uint8 *Buffer){
	uint8 i,TIMES,reply;
   	uint8 a1,a2,a3,a4;
   	
   	SectorNumber=SectorNumber<<9;
   	a4=SectorNumber;
   	a3=SectorNumber>>8;
   	a2=SectorNumber>>16;
   	a1=SectorNumber>>24;
   	SendCmd(24,a1,a2,a3,a4,0xff);
   	
   	TIMES=100;
   	reply=0xff;
   	for(i=0;i<TIMES;i++){
   		reply=WaitOneByteRespond();
   		if(reply==0x00) break;
   	}
   	if(reply!=0x00) return error;
   	WriteByte(0xfe);
   	
   	for(i=0;i<512;i++)
   	WriteByte(*Buffer++);
   	
   	WriteByte(0xff);
   	WriteByte(0xff);
   	
   	WaitOneByteRespond();
   	WriteByte(0xff);
   	CS=1;
   	return 0;
}
uint8 ReadSector(uint32 SectorNumber,uint8 *Buffer){
   	uint8 i,TIMES,reply;
	uint8 a1,a2,a3,a4;
   
   	SectorNumber=SectorNumber<<9;
   	a4=SectorNumber;
   	a3=SectorNumber>>8;
   	a2=SectorNumber>>16;
   	a1=SectorNumber>>24;
   	SendCmd(17,a1,a2,a3,a4,0xff);
   
   	TIMES=100;
   	reply=0xff;
   	for(i=0;i<TIMES;i++){
   		reply=WaitOneByteRespond();
   		if(reply==0x00) break;
   	}
   	if(reply!=0x00) return error;
   	
   	TIMES=100;
   	reply=0xff;
   	for(i=0;i<TIMES;i++){
   		reply=WaitOneByteRespond();
   		if(reply==0xfe) break;
   	}
   	if(reply!=0xfe) return error;
   	
   	for(i=0;i<512;i++)
	*Buffer++=ReadByte();
	
	WriteByte(0xff);
	WriteByte(0xff);
   	CS=1;
   	return 0;
}

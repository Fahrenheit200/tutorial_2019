#include<reg52.h>
#include "intrins.h"
typedef unsigned char uint8;
typedef unsigned int uint16;

extern void I2CStart();
extern void I2CStop();
extern bit I2CWrite(unsigned char dat);
extern unsigned char I2CReadNAK();
extern unsigned char I2CReadACK();

uint8 eepromReadByte(uint16 addr){
	uint8 dat;
	I2CStart();
	if(I2CWrite(0XA0)==0){
		I2CStop(); return 0xee;
	}
	if(I2CWrite(addr>>8)==0){
		I2CStop(); return 0xee;
	}
	if(I2CWrite(addr%256)==0){
		I2CStop(); return 0xee;
	}
	
	I2CStart();
	if(I2CWrite(0XA1)==0){
		I2CStop(); return 0;
	}
	dat=I2CReadNAK();
	I2CStop();
	return dat;
}
bit eepromWriteByte(uint16 addr,uint8 dat){
	I2CStart();
	if(I2CWrite(0XA0)==0){
		I2CStop(); return 0;
	}
	if(I2CWrite(addr>>8)==0){
		I2CStop(); return 0;
	}
	if(I2CWrite(addr%256)==0){
		I2CStop(); return 0;
	}
	if(I2CWrite(dat)==0){
		I2CStop(); return 0;
	}
	I2CStop();
	return 1;
}
void eepromWritePage(uint16 addr,uint8 *dat,uint8 len){
	uint8 i;
	if(len>=64||len==0) return;
	I2CStart();
	I2CWrite(0XA0);
	I2CWrite(addr>>8);
	I2CWrite(addr%256);
	
	for(i=0;i<len;i++)
	I2CWrite(dat[i]);
	I2CStop();
}
void eepromReadPage(uint16 addr,uint8 *dat,uint8 len){
	uint8 i;
	if(len>=64||len==0) return;
	I2CStart();
	I2CWrite(0XA0);
	I2CWrite(addr>>8);
	I2CWrite(addr%256);
	
	I2CStart();
	I2CWrite(0XA1);
	for(i=0;i<len-1;i++)
	dat[i]=I2CReadACK();
	dat[len-1]=I2CReadNAK();
	I2CStop();
}

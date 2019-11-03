#include<reg52.h>
#include "intrins.h"
#define EEPromDelay() {_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();}
typedef unsigned char uint8;
typedef unsigned int uint16;

extern void I2CStart();
extern void I2CStop();
extern bit I2CWrite(unsigned char dat);
extern unsigned char I2CReadNAK();
extern unsigned char I2CReadACK();

uint8 eepromReadByte(uint16 addr);
bit eepromWriteByte(uint16 addr,uint8 dat);
bit eepromWritePage(uint16 addr,uint8 *dat,uint8 len);
bit eepromReadPage(uint16 addr,uint8 *dat,uint8 len);

uint8 eepromReadByte(uint16 addr){
	uint8 dat;
	I2CStart();
	if(I2CWrite(0XA0)==0){
		I2CStop(); return 0xee;
	}
	//EEPromDelay();
	if(I2CWrite(addr>>8)==0){
		I2CStop(); return 0xee;
	}
	//EEPromDelay();
	if(I2CWrite(addr%256)==0){
		I2CStop(); return 0xee;
	}
	//EEPromDelay();
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
bit eepromWritePage(uint16 addr,uint8 *dat,uint8 len){
	uint8 i;
	if(len>64||len==0) return 0;
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
	
	for(i=0;i<len;i++)
	I2CWrite(dat[i]);
	I2CStop();
	return 1;
}
bit eepromReadPage(uint16 addr,uint8 *dat,uint8 len){
	uint8 i;
	if(len>64||len==0) return 0;
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
	
	I2CStart();
	if(I2CWrite(0XA1)==0){
		I2CStop(); return 0;
	}
	for(i=0;i<len-1;i++)
	dat[i]=I2CReadACK();
	dat[len-1]=I2CReadNAK();
	I2CStop();
	return 1;
}

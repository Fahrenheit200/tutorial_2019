#include "STC12C5A60S2.H" 
#include "intrins.h"
#include "math.h"
#define DAT_NUM 32
typedef unsigned char uint8;
typedef unsigned int uint16;

extern float getDat(uint8 t); 
extern void oledDrawPic(uint8 x0,uint8 y0,
				 uint8 x1,uint8 y1,uint8 BMP[]); 
uint8 code base[]=
{0xe0,0xe0,0xe0,0x00};
uint8 code square[]=
{0xEE,0xEE,0xEE,0x00};
uint8 code empty[]=
{0x00,0x00,0x00,0x00};

uint8 isLightUp[32][8];
float biggest(float a,float b);
void showBaseLine(){
	uint8 i,colIndex=0;
	for(i=0;i<32;i++,colIndex+=4)
	oledDrawPic(colIndex,0,colIndex+4,0,base);
} 
void spectrumShow(){
	uint8 i,j;
	uint8 tmp;
	uint8 colIndex=0;
	uint8 col=0;
	showBaseLine();
	for(i=0;i<32;i+=1){
		tmp=getDat(i)/2;
		if(tmp>8) tmp=8;
		for(j=1;j<=tmp;j++)
		if(isLightUp[col][j]==0){
			oledDrawPic(colIndex,j,colIndex+4,j,square);
			isLightUp[col][j]=1;
		}
		for(j=tmp+1;j<8;j++)
		if(isLightUp[col][j]==1){
			oledDrawPic(colIndex,j,colIndex+4,j,empty);
			isLightUp[col][j]=0;
		}
		col++;
		colIndex+=4;
	}
}
float biggest(float a,float b){
	uint8 A; 
	if(a>b) A=a;
	else A=b;
	return A;
}

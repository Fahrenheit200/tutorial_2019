#include "STC12C5A60S2.H"
#include "intrins.h"

#define OLED_CMD  0
#define OLED_DATA 1
#define X_WIDTH 128
#define Y_WIDTH 64
typedef unsigned char uint8;
typedef unsigned int uint16;

extern void I2CStart();
extern void I2CStop();
extern bit I2CWrite(uint8 dat);
extern void delay50ms(uint16 t);
extern void delay1ms(uint16 t);

void oledInit();
void oldeWrite(unsigned dat, unsigned cmd);
void writeI2CCom(uint8 cmd);
void writeI2CDat(uint8 dat);
void oledClear();
void oledSetPos(uint8 x, uint8 y);
void oledDrawPic(uint8 x0,uint8 y0,
				 uint8 x1,uint8 y1,uint8 BMP[]);
				 
void oledInit()
{
	oldeWrite(0xAE, OLED_CMD);//display off
	oldeWrite(0x00, OLED_CMD);//set low column address
	oldeWrite(0x10, OLED_CMD);//set high column address
	oldeWrite(0x40, OLED_CMD);//set start line address  
	oldeWrite(0xB0, OLED_CMD);//set page address
	oldeWrite(0x81, OLED_CMD);//contract control
	oldeWrite(0xFF, OLED_CMD);//128   
	oldeWrite(0xA1, OLED_CMD);//set segment remap 
	oldeWrite(0xA6, OLED_CMD);//normal / reverse
	oldeWrite(0xA8, OLED_CMD);//set multiplex ratio(1 to 64)
	oldeWrite(0x3F, OLED_CMD);//1/32 duty
	oldeWrite(0xC8, OLED_CMD);//Com scan direction
	oldeWrite(0xD3, OLED_CMD);//set display offset
	oldeWrite(0x00, OLED_CMD);//

	oldeWrite(0xD5, OLED_CMD);//set osc division
	oldeWrite(0x80, OLED_CMD);//

	oldeWrite(0xD8, OLED_CMD);//set area color mode off
	oldeWrite(0x05, OLED_CMD);//

	oldeWrite(0xD9, OLED_CMD);//Set Pre-Charge Period
	oldeWrite(0xF1, OLED_CMD);//

	oldeWrite(0xDA, OLED_CMD);//set com pin configuartion
	oldeWrite(0x12, OLED_CMD);//

	oldeWrite(0xDB, OLED_CMD);//set Vcomh
	oldeWrite(0x30, OLED_CMD);//

	oldeWrite(0x8D, OLED_CMD);//set charge pump enable
	oldeWrite(0x14, OLED_CMD);//

	oldeWrite(0xAF, OLED_CMD);//turn on oled panel
}
void oldeWrite(unsigned dat, unsigned cmd)
{
	if (cmd) writeI2CDat(dat);
	else  writeI2CCom(dat);
}
void writeI2CCom(uint8 cmd)
{
	I2CStart();
	I2CWrite(0x78);
	I2CWrite(0x00);
	I2CWrite(cmd);
	I2CStop();
}
void writeI2CDat(uint8 dat)
{
	I2CStart();
	I2CWrite(0x78);
	I2CWrite(0x40);
	I2CWrite(dat);
	I2CStop();
}
/*
void oledDisplayOn()
{
	oldeWrite(0X8D, OLED_CMD);//SET DCDC
	oldeWrite(0X14, OLED_CMD);//DCDC ON
	oldeWrite(0XAF, OLED_CMD);//DISPLAY ON
}    
void oledDisplayOff()
{
	oldeWrite(0X8D, OLED_CMD);//SET DCDC
	oldeWrite(0X10, OLED_CMD);//DCDC OFF
	oldeWrite(0XAE, OLED_CMD);//DISPLAY OFF
}
*/
void oledClear()
{
	uint8 i, n;
	for (i = 0; i < 8; i++)
	{
		oldeWrite(0xb0 + i, OLED_CMD);
		oldeWrite(0x00, OLED_CMD);
		oldeWrite(0x10, OLED_CMD);   
		for (n = 0; n < 128; n++)
		oldeWrite(0, OLED_DATA);
	}
}
void oledSetPos(uint8 x, uint8 y)
{
	oldeWrite(0xb0+y, OLED_CMD);
	oldeWrite(((x&0xf0)>>4)|0x10,OLED_CMD);//high 4 bits
	oldeWrite((x&0x0f),OLED_CMD);//low 4 bits
}
void oledDrawPic(uint8 x0,uint8 y0,
				 uint8 x1,uint8 y1,uint8 BMP[])
{
	uint16 i = 0;
	uint8 x, y;
	for (y=y0;y<=y1;y++)
	{
		oledSetPos(x0,y);
		for (x =x0;x<x1;x++)
		oldeWrite(BMP[i++], OLED_DATA);
	}
}


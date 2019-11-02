#include "oled.h"
#include "sys.h"
#include "delay.h"
#include "font.h"
#include "usart.h"

void OLED_GPIO_Conf()
{
	GPIO_InitTypeDef GPIO_Initstructure;
	RCC_APB2PeriphClockCmd(TFT_RCC, ENABLE);
	GPIO_Initstructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Initstructure.GPIO_Pin=SDA|SCL|DC|RST|CS;
	GPIO_Initstructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_Initstructure);
}

void SPI_Write_Data(u8 data)
{
	u8 i=0;
	for(i=0;i<8;i++)
	{
		if(data&0x80) SDA_H;
		else SDA_L;
		SCL_L;
		SCL_H;
		data<<=1;
	}
}

void OLED_Write_Cmd(u8 cmd)
{
	CS_L;
	DC_L;
	SPI_Write_Data(cmd);
	CS_H;
}
void OLED_Write_Data(u8 data)
{
	CS_L;
	DC_H;
	SPI_Write_Data(data);
	CS_H;
}
void OLED_Write_16Bits(u16 data)
{
	CS_L;
	DC_H;
	SPI_Write_Data(data>>8);
	SPI_Write_Data(data);
	CS_H;
}
void ReSet()
{
	RST_L;
	delay_ms(1000);
	RST_H;
	delay_ms(1000);
}
void OLED_Init()
{
	ReSet();
	OLED_Write_Cmd(0x11);//Sleep exit 
	delay_ms (120);
		
	OLED_Write_Cmd(0xB1);   //turn off sleep mode
	OLED_Write_Data(0x01);    
	OLED_Write_Data(0x2C); 	
	OLED_Write_Data(0x2D); 
	
	OLED_Write_Cmd(0xB2); 	//SET the frame frequency of the ldle mode	
	OLED_Write_Data(0x01); 	
	OLED_Write_Data(0x2C); 	
	OLED_Write_Data(0x2D); 	

	OLED_Write_Cmd(0xB3); 	//Set the frame frequency of the Partial mode/ full colors	
	OLED_Write_Data(0x01); 
	OLED_Write_Data(0x2C); 
	OLED_Write_Data(0x2D); 
	OLED_Write_Data(0x01); 
	OLED_Write_Data(0x2C); 
	OLED_Write_Data(0x2D); 
	
	OLED_Write_Cmd(0xB4); //Column inversion 
	OLED_Write_Data(0x07); 
	
	// Power Sequence
	OLED_Write_Cmd(0xC0); 
	OLED_Write_Data(0xA2); 
	OLED_Write_Data(0x02); 
	OLED_Write_Data(0x84); 
	OLED_Write_Cmd(0xC1); 
	OLED_Write_Data(0xC5); 

	OLED_Write_Cmd(0xC2); 
	OLED_Write_Data(0x0A); 
	OLED_Write_Data(0x00); 

	OLED_Write_Cmd(0xC3); 
	OLED_Write_Data(0x8A); 
	OLED_Write_Data(0x2A); 
	OLED_Write_Cmd(0xC4); 
	OLED_Write_Data(0x8A); 
	OLED_Write_Data(0xEE); 
	
	OLED_Write_Cmd(0xC5); //VCOM 
	OLED_Write_Data(0x0E); 
	
	OLED_Write_Cmd(0x36); //MX, MY, RGB mode 
	OLED_Write_Data(0xC0);
	//ST7735R Gamma Sequence
	OLED_Write_Cmd(0xe0); 
	OLED_Write_Data(0x0f); 
	OLED_Write_Data(0x1a); 
	OLED_Write_Data(0x0f); 
	OLED_Write_Data(0x18); 
	OLED_Write_Data(0x2f); 
	OLED_Write_Data(0x28); 
	OLED_Write_Data(0x20); 
	OLED_Write_Data(0x22); 
	OLED_Write_Data(0x1f); 
	OLED_Write_Data(0x1b); 
	OLED_Write_Data(0x23); 
	OLED_Write_Data(0x37); 
	OLED_Write_Data(0x00); 	
	OLED_Write_Data(0x07); 
	OLED_Write_Data(0x02); 
	OLED_Write_Data(0x10); 

	OLED_Write_Cmd(0xe1); 
	OLED_Write_Data(0x0f); 
	OLED_Write_Data(0x1b); 
	OLED_Write_Data(0x0f); 
	OLED_Write_Data(0x17); 
	OLED_Write_Data(0x33); 
	OLED_Write_Data(0x2c); 
	OLED_Write_Data(0x29); 
	OLED_Write_Data(0x2e); 
	OLED_Write_Data(0x30); 
	OLED_Write_Data(0x30); 
	OLED_Write_Data(0x39); 
	OLED_Write_Data(0x3f); 
	OLED_Write_Data(0x00); 
	OLED_Write_Data(0x07); 
	OLED_Write_Data(0x03); 
	OLED_Write_Data(0x10);  
	
	OLED_Write_Cmd(0x09);
	delay_ms(100);
	OLED_Write_Data(0x60);
	OLED_Write_Data(0x61);
	OLED_Write_Data(0x00);
	OLED_Write_Data(0x00);
	
	OLED_Write_Cmd(0x2a);
	OLED_Write_Data(0x00);
	OLED_Write_Data(0x00+2);
	OLED_Write_Data(0x00);
	OLED_Write_Data(0x80+2);

	OLED_Write_Cmd(0x2b);
	OLED_Write_Data(0x00);
	OLED_Write_Data(0x00+3);
	OLED_Write_Data(0x00);
	OLED_Write_Data(0x80+3);
	
	OLED_Write_Cmd(0xF0); //Enable test command  
	OLED_Write_Data(0x01); 
	OLED_Write_Cmd(0xF6); //Disable ram power save mode 
	OLED_Write_Data(0x00); 
	
	OLED_Write_Cmd(0x3A); //65k mode 
	OLED_Write_Data(0x05); 
	
	
	OLED_Write_Cmd(0x29);//Display on
}
void setRegion(u8 x_start, u8 y_start, u8 x_end, u8 y_end)
{
	OLED_Write_Cmd(0X2A);
	OLED_Write_Data(0X00);
	OLED_Write_Data(x_start);
	OLED_Write_Data(0X00);
	OLED_Write_Data(x_end);
	
	OLED_Write_Cmd(0X2B);
	OLED_Write_Data(0X00);
	OLED_Write_Data(y_start);
	OLED_Write_Data(0X00);
	OLED_Write_Data(y_end);
	
	OLED_Write_Cmd(0x2c);
}
void PutPixel(u8 x_start, u8 y_start, u16 color)
{
	setRegion(x_start, y_start, x_start+1, y_start+1);
	OLED_Write_16Bits(color);
}

void PutPixels(u8 x_start, u8 y_start, u8 x_end, u8 y_end,u16 color)
{
	u8 i,j;
	setRegion(x_start, y_start, x_end, y_end);
	for(i=0;i<=(x_end-x_start);i++)
		for(j=0;j<=(y_end-y_start);j++)
			OLED_Write_16Bits(color);
}
	
void OLED_clear(u16 color)
{
	u8 i=0;
	u8 j=0;
	setRegion(0,0,127,159);
	for(i=0; i<128; i++)
	{
		for(j=0; j<160; ++j)
		{
			OLED_Write_16Bits(color);
		}
	}
}
void OLED_Char_display(u16 x, u16 y, u16 fcolor, u16 bcolor,u8 s)
{
	u8 i, j;
	u16 k;
	uint32_t num;
	num=sizeof(ASCII)/sizeof(ASCII[0]);
	setRegion(x,y,x+8-1,y+16-1);
	for(k=0;k<num;k++)
	{
		if(s==ASCII[k].Index)
		{
			for(i=0;i<16;i++)
			{
				printf("%d\n",ASCII[k].Msk[i]);
				for(j=0;j<8;j++)
				{
					if(ASCII[k].Msk[i]&(0x80>>j))	OLED_Write_16Bits(fcolor);
					else{
						if(fcolor!=bcolor) OLED_Write_16Bits(bcolor);
					}
				}
			}
		}
	}
	
}

void OLED_String_Display(u16 x, u16 y, u16 fcolor, u16 bcolor,u8 *s)
{
	u8 i, j;
	u16 k,num;
	num=sizeof(ASCII)/sizeof(ASCII[0]);      //根据索引在字库中寻找对应，需要遍历数组
	printf("%d",num);
	while(*s)
	{
		OLED_Char_display(x,y,fcolor,bcolor,*s);
		s+=1;
		x+=8;
		if(x>=128)
		{
			x-=128;
			y+=16;
		}
	}
}
void OLED_Font_Display(u16 x, u16 y, u16 fcolor, u16 bcolor,u8 *s)
{
	u8 i,j,k;
	u16 num = sizeof(FONT)/sizeof(FONT[0]);
	while(*s)
	{
		for(k=0;k<num;++k)
		{
			if(*s==FONT[k].Index[0] && *(s+1)==FONT[k].Index[1])
			{
				setRegion(x,y,x+16-1,y+16-1);
				for(i=0;i<16*2;++i)
				{
					for(j=0;j<8;++j)
					{
						if(FONT[k].Msk[i] & (0x80>>j))  OLED_Write_16Bits(fcolor);
						else OLED_Write_16Bits(bcolor);
					}
				}
				s+=2;
				x+=16;
			}
			
	
		}
	}
}

void cursor(u16 x, u16 y)
{
	u8 i,j;
	setRegion(x,y,x+3,y+7);
	for(i=0;i<=3;i++)
	{
		for(j=0;j<=7;j++)
		{
			OLED_Write_16Bits(WHITE);
		}
	}
}






















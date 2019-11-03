#ifndef OLED_H
#define OLED_H
#include "sys.h"

#define GPIO_TFT GPIOA
#define TFT_RCC RCC_APB2Periph_GPIOA
#define SDA GPIO_Pin_11
#define SCL GPIO_Pin_12
#define CS GPIO_Pin_13
#define RST GPIO_Pin_14
#define DC GPIO_Pin_15

#define SDA_H GPIO_SetBits(GPIO_TFT,SDA)
#define SDA_L GPIO_ResetBits(GPIO_TFT,SDA)
#define SCL_H GPIO_SetBits(GPIO_TFT,SCL)
#define SCL_L GPIO_ResetBits(GPIO_TFT,SCL)
#define CS_H GPIO_SetBits(GPIO_TFT,CS)
#define CS_L GPIO_ResetBits(GPIO_TFT,CS)
#define RST_H GPIO_SetBits(GPIO_TFT,RST)
#define RST_L GPIO_ResetBits(GPIO_TFT,RST)
#define DC_H    GPIO_SetBits(GPIO_TFT,DC)
#define DC_L    GPIO_ResetBits(GPIO_TFT,DC)

#define RED 0XF800
#define GREEN 0X07E0
#define BLUE 0x001f
#define WHITE 0xffff
#define BLACK 0x0000
#define YELLOW 0xFFE0
#define GRAY0 0xef7d
#define GRAY1 0x8410
#define GRAY2 0x4208

void OLED_Init();
void OLED_GPIO_Conf();
void setRegion(u8 x_start, u8 y_start, u8 x_end, u8 y_end);
void OLED_clear(u16 color);
void OLED_Char_display(u16 x, u16 y, u16 fcolor, u16 bcolor,u8 s);
void OLED_Write_16Bits(u16 data);
void OLED_String_Display(u16 x, u16 y, u16 fcolor, u16 bcolor,u8 *s);
void OLED_Font_Display(u16 x, u16 y, u16 fcolor, u16 bcolor,u8 *s);
void PutPixels(u8 x_start, u8 y_start, u8 x_end, u8 y_end,u16 color);
void cursor(u16 x, u16 y);
#endif
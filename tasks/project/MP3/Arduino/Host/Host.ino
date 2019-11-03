#define DL1 147
#define DL2 165
#define DL3 175
#define DL4 196
#define DL5 221
#define DL6 248
#define DL7 278

#define D0 262
#define D1 294
#define D2 330
#define D3 350
#define D4 393
#define D5 441
#define D6 495
#define D7 556

#define DH1 589
#define DH2 661
#define DH3 740
#define DH4 786
#define DH5 882
#define DH6 990
#define DH7 1112

#include <avr/pgmspace.h>
//导入OLED显示屏的“ Adafruit_SSD1306.h ”
#include<Adafruit_SSD1306.h>


//OLED尺寸为128x64，在这里分别设置OLED显示屏的宽度和高度
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_DC A1
#define OLED_CS A2
#define OLED_CLK 10
#define OLED_MOSI 9
#define OLED_RESET A0
Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

static const unsigned char char1[4][32] PROGMEM={
  {0xFF,0xFF,0x80,0x03,0xFE,0xFF,0xFE,0xFF,0xFE,0xFF,0xFE,0xFF,0xEE,0xFF,0xEE,0x07,
  0xEE,0xFF,0xEE,0xFF,0xEE,0xFF,0xEE,0xFF,0xEE,0xFF,0xEE,0xFF,0x00,0x01,0xFF,0xFF},/*"正",0*/

  {0xFD,0xFF,0xFD,0xFF,0xFB,0xFF,0x00,0x01,0xF7,0xFF,0xF7,0xBF,0xEF,0xBF,0xCF,0xBF,
  0xA8,0x03,0x6F,0xBF,0xEF,0xBF,0xEF,0xBF,0xEF,0xBF,0xEF,0xBF,0xE0,0x01,0xEF,0xFF},/*"在",1*/

  {0xDF,0x87,0xD8,0x3F,0xDD,0xB7,0xDE,0xAF,0x04,0x03,0xDE,0xAF,0xDD,0xB7,0xD3,0xF9,
  0xCC,0x07,0x1D,0xB7,0xDD,0xB7,0xDC,0x07,0xDD,0xB7,0xDD,0xB7,0x5C,0x07,0xBD,0xF7},/*"播",2*/

  {0xDF,0xBF,0xEF,0xBF,0xFF,0xBF,0x01,0x7F,0xDF,0x01,0xDE,0xF7,0xC1,0x77,0xDB,0x77,
  0xDB,0x77,0xDB,0xAF,0xDB,0xAF,0xDB,0xDF,0xBB,0xAF,0xAB,0x77,0x76,0xFB,0xFD,0xFD},/*"放",3*/
};

static const unsigned char char2[2][32] PROGMEM={
  {0xEF,0xF3,0x01,0x0F,0xDF,0x7F,0xB7,0x7F,0x81,0x01,0xF7,0x77,0xF1,0x77,0x06,0xF7,
  0xB5,0xF7,0xE0,0x07,0xEF,0xEF,0xEF,0xEF,0xE0,0x0F,0xEF,0xEF,0xEF,0xEF,0xE0,0x0F},/*"暂",0*/

  {0xEF,0x7F,0xEF,0xBF,0xE8,0x03,0xDF,0xFF,0xDC,0x07,0x9D,0xF7,0x9C,0x07,0x5F,0xFF,
  0xD0,0x01,0xD7,0xFD,0xDC,0x07,0xDF,0xBF,0xDF,0xBF,0xDF,0xBF,0xDE,0xBF,0xDF,0x7F},/*"停",1*/
};

static const unsigned char char3[3][32] PROGMEM={
  {0xFF,0xFF,0x00,0x01,0xFD,0xFF,0xFD,0xFF,0xFD,0xFF,0xFD,0xFF,0xFD,0xBF,0xFD,0xDF,
  0xFD,0xEF,0xFD,0xF7,0xFD,0xF7,0xFD,0xFF,0xFD,0xFF,0xFD,0xFF,0xFD,0xFF,0xFD,0xFF},/*"下",0*/

  {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x01,
  0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},/*"一",1*/

  {0xEF,0xEF,0xF7,0xDF,0x00,0x01,0xFD,0xFF,0xFB,0xFF,0xC0,0x07,0xDF,0xF7,0xDF,0xF7,
  0xC0,0x07,0xDF,0xF7,0xDF,0xF7,0xC0,0x07,0xDF,0xF7,0xDF,0xF7,0xC0,0x07,0xDF,0xF7},/*"首",2*/
};

static const unsigned char char4[3][32] PROGMEM={
  {0xFD,0xFF,0xFD,0xFF,0xFD,0xFF,0xFD,0xFF,0xFD,0xFF,0xFD,0xFF,0xFC,0x07,0xFD,0xFF,
  0xFD,0xFF,0xFD,0xFF,0xFD,0xFF,0xFD,0xFF,0xFD,0xFF,0xFD,0xFF,0x00,0x01,0xFF,0xFF},/*"上",0*/

  {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x01,
  0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},/*"一",1*/

  {0xEF,0xEF,0xF7,0xDF,0x00,0x01,0xFD,0xFF,0xFB,0xFF,0xC0,0x07,0xDF,0xF7,0xDF,0xF7,
  0xC0,0x07,0xDF,0xF7,0xDF,0xF7,0xC0,0x07,0xDF,0xF7,0xDF,0xF7,0xC0,0x07,0xDF,0xF7},/*"首",2*/
};

static const unsigned char char5[2][32] PROGMEM={
  {0xEF,0xBF,0xEF,0xBF,0xEF,0xBF,0xEC,0x07,0xE7,0xB7,0xAB,0xB7,0xAF,0xB7,0xAF,0xB7,
  0x68,0x01,0xEF,0xBF,0xEF,0x5F,0xEF,0x5F,0xEE,0xEF,0xEE,0xEF,0xED,0xF7,0xEB,0xF9},/*"快",0*/

  {0xFF,0x6F,0xDF,0x6F,0xEF,0x6F,0xEC,0x03,0xFF,0x6F,0xFF,0x6F,0x0F,0x6F,0xE8,0x01,
  0xEF,0x6F,0xEF,0x6F,0xEE,0xEF,0xEE,0xEF,0xED,0xEF,0xD7,0xFF,0xB8,0x01,0xFF,0xFF},/*"进",1*/
};

static const unsigned char char6[2][32] PROGMEM={
  {0xEF,0xBF,0xEF,0xBF,0xEF,0xBF,0xEC,0x07,0xE7,0xB7,0xAB,0xB7,0xAF,0xB7,0xAF,0xB7,
  0x68,0x01,0xEF,0xBF,0xEF,0x5F,0xEF,0x5F,0xEE,0xEF,0xEE,0xEF,0xED,0xF7,0xEB,0xF9},/*"快",0*/

  {0xFC,0x07,0xDD,0xF7,0xED,0xF7,0xEC,0x07,0xFD,0xF7,0xFD,0xF7,0x0C,0x07,0xED,0xBB,
  0xED,0xD7,0xED,0xEF,0xED,0x77,0xEC,0xFB,0xED,0xFB,0xD7,0xFF,0xB8,0x01,0xFF,0xFF},/*"退",1*/
};

static const unsigned char char7[2][32] PROGMEM={
  {0xFF,0xFF,0xC0,0x07,0xDF,0xF7,0xDF,0xF7,0xDF,0xF7,0xC0,0x07,0xDF,0xF7,0xDF,0xF7,
  0xDF,0xF7,0xC0,0x07,0xDF,0xF7,0xDF,0xF7,0xDF,0xF7,0xDF,0xF7,0xC0,0x07,0xDF,0xF7},/*"目",0*/

  {0xFF,0xFF,0xC0,0x0F,0xFF,0xEF,0xFF,0xEF,0xE0,0x0F,0xFF,0xEF,0xFF,0xEF,0x00,0x01,
  0xFE,0xFF,0xDE,0xF7,0xEE,0x6F,0xFA,0x9F,0xF6,0xDF,0xCE,0xE7,0x3A,0xF9,0xFD,0xFF},/*"录",1*/
};

static const unsigned char char8[6][32] PROGMEM={
  {0xFF,0xFF,0xC0,0x0F,0xFF,0xEF,0xFF,0xEF,0xFF,0xEF,0xDF,0xEF,0xDF,0xEF,0xC0,0x0F,
  0xDF,0xFF,0xDF,0xFF,0xDF,0xFF,0xDF,0xFB,0xDF,0xFB,0xDF,0xFB,0xE0,0x03,0xFF,0xFF},/*"已",0*/

  {0xFF,0xBF,0xDF,0xBF,0xE8,0x01,0xEF,0x7F,0xFF,0x5F,0xFE,0xDF,0x0C,0x03,0xEF,0xDF,
  0xEF,0xDF,0xEF,0xDF,0xE8,0x01,0xEF,0xDF,0xEF,0xDF,0xD7,0xDF,0xB8,0x01,0xFF,0xFF},/*"连",1*/

  {0xEF,0x7F,0xEF,0xBF,0xEC,0x03,0xEF,0xFF,0x02,0xF7,0xEF,0x6F,0xE8,0x01,0xEF,0xBF,
  0xE7,0xBF,0xC8,0x01,0x2F,0x77,0xEE,0xF7,0xEF,0x6F,0xEF,0x9F,0xAE,0x67,0xD9,0xFB},/*"接",2*/

  {0xFD,0xFF,0xFD,0xFF,0xFD,0xFF,0xFD,0xFF,0xFD,0xFF,0xFD,0xFF,0xFC,0x07,0xFD,0xFF,
  0xFD,0xFF,0xFD,0xFF,0xFD,0xFF,0xFD,0xFF,0xFD,0xFF,0xFD,0xFF,0x00,0x01,0xFF,0xFF},/*"上",3*/

  {0xF7,0x7F,0xF7,0xBF,0xF7,0xBF,0xEF,0xFF,0xE8,0x03,0xCF,0xFF,0xCF,0xF7,0xAD,0xF7,
  0x6D,0xF7,0xEE,0xEF,0xEE,0xEF,0xEE,0xEF,0xEE,0xDF,0xEF,0xDF,0xE0,0x01,0xEF,0xFF},/*"位",4*/

  {0xEF,0xFF,0xEE,0x0F,0xEE,0xEF,0xEE,0xEF,0x02,0xEF,0xEE,0xEF,0xCE,0xEF,0xC6,0xEF,
  0xAA,0xEF,0xAA,0xEF,0x6E,0xEF,0xEE,0xED,0xEE,0xED,0xED,0xED,0xED,0xF1,0xEB,0xFF},/*"机",5*/
};

static const unsigned char char9[3][32] PROGMEM={
  {0xFF,0xFF,0xC0,0x0F,0xFF,0xEF,0xFF,0xEF,0xFF,0xEF,0xDF,0xEF,0xDF,0xEF,0xC0,0x0F,
  0xDF,0xFF,0xDF,0xFF,0xDF,0xFF,0xDF,0xFB,0xDF,0xFB,0xDF,0xFB,0xE0,0x03,0xFF,0xFF},/*"已",0*/

  {0xFF,0xFF,0x00,0x01,0xFD,0xFF,0xFD,0xFF,0xFD,0xFF,0xFD,0xFF,0xFD,0xBF,0xFD,0xDF,
  0xFD,0xEF,0xFD,0xF7,0xFD,0xF7,0xFD,0xFF,0xFD,0xFF,0xFD,0xFF,0xFD,0xFF,0xFD,0xFF},/*"下",1*/

  {0xF7,0xDF,0xF7,0xD7,0x80,0xDB,0xF7,0xDF,0x00,0x01,0xEF,0xDF,0xEF,0xDB,0x00,0xDB,
  0xDF,0xDB,0xB7,0xD7,0x80,0xD7,0xF7,0xEF,0xF0,0xED,0x07,0xD5,0xF7,0xB9,0xF7,0x7D},/*"载",2*/
};

static const unsigned char char10[6][32] PROGMEM={
  {0xEF,0xFF,0xEF,0xFF,0xEF,0xFF,0xE0,0x03,0xEF,0xFF,0xDF,0xFF,0xDF,0xFF,0xC0,0x07,
  0xFF,0xF7,0xFF,0xF7,0xFF,0xF7,0x00,0x37,0xFF,0xF7,0xFF,0xF7,0xFF,0xAF,0xFF,0xDF},/*"与",0*/

  {0xFD,0xFF,0xFD,0xFF,0xFD,0xFF,0xFD,0xFF,0xFD,0xFF,0xFD,0xFF,0xFC,0x07,0xFD,0xFF,
  0xFD,0xFF,0xFD,0xFF,0xFD,0xFF,0xFD,0xFF,0xFD,0xFF,0xFD,0xFF,0x00,0x01,0xFF,0xFF},/*"上",1*/

  {0xF7,0x7F,0xF7,0xBF,0xF7,0xBF,0xEF,0xFF,0xE8,0x03,0xCF,0xFF,0xCF,0xF7,0xAD,0xF7,
  0x6D,0xF7,0xEE,0xEF,0xEE,0xEF,0xEE,0xEF,0xEE,0xDF,0xEF,0xDF,0xE0,0x01,0xEF,0xFF},/*"位",2*/

  {0xEF,0xFF,0xEE,0x0F,0xEE,0xEF,0xEE,0xEF,0x02,0xEF,0xEE,0xEF,0xCE,0xEF,0xC6,0xEF,
  0xAA,0xEF,0xAA,0xEF,0x6E,0xEF,0xEE,0xED,0xEE,0xED,0xED,0xED,0xED,0xF1,0xEB,0xFF},/*"机",3*/

  {0xFB,0xFF,0xFB,0xFB,0xAA,0x87,0xB1,0xBF,0xBB,0xBF,0x80,0xBF,0xBB,0x81,0xB1,0xB7,
  0xAA,0xB7,0x9A,0xB7,0xBB,0xB7,0xBB,0xB7,0xBF,0xB7,0x80,0x77,0xFF,0x77,0xFE,0xF7},/*"断",4*/

  {0xFF,0xFF,0x80,0x03,0xF7,0xDF,0xF7,0xDF,0xF7,0xDF,0xF7,0xDF,0xF7,0xDF,0x00,0x01,
  0xF7,0xDF,0xF7,0xDF,0xF7,0xDF,0xF7,0xDF,0xEF,0xDF,0xEF,0xDF,0xDF,0xDF,0xBF,0xDF},/*"开",5*/
};

//内置曲目的音符部分
const uint16_t tune[10][120] PROGMEM=
{
  {//HLW：葫芦娃
    62, 
    D1, D1, D3,
    D1, D1, D3,
    D6, D6, D6, D5, D6,
    D5, D1, D3, 
    DH1, D6, D6, D5, D6,
    D5, D1, D2,
    D7, D7, D5, D3,
    D5,
    DH1, D6, D6, D5, D5, D6, D6,
    D5, D1, D3, 
    DH1, D6, D6, D5, D5, D6, D6,
    D5, D1, D2,
    D3, D1, DL6,
    D1,
    D3, D5, D6, 
    D3, D5, D6, 
    DH1, D0, D7, D5,
    D6},
  {//HLS：欢乐颂
    62,
    D2,D2,D3,D4,
    D4,D3,D2,D1,
    D0,D0,D1,D2,
    D2,D1,D1,
    D2,D2,D3,D4,
    D4,D3,D2,D1,
    D0,D0,D1,D2,
    D1,D0,D0,
    D1,D1,D2,D0,
    D1,D2,D3,D2,D0,
    D1,D2,D3,D2,D1,
    D0,D1,DL4,
    D2,D2,D3,D4,
    D4,D3,D2,D1,
    D0,D0,D1,D2,
    D1,D0,D0},
  {//Deja Vu：逮虾虎
    49,
    D1,D3,D3,
    D1,D3,D3,D3,D3,D2,D2,
    D5,D4,D3,D2,D3,
    D3,D3,D4,D3,D4,D4,D5,D5,D4,
    D1,D3,D3,
    D1,D3,D3,D3,D3,D2,D2,
    D5,D4,D3,D2,D3,
    D3,D3,D4,D3,D4,D4,D5,D5,D4,D5},
  {//TKZC:天空之城
    115,
    D6,D7,DH1,D7,DH1,DH3,D7,
    D3,D3,D6,D5,D6,DH1,D5,
    D3,D4,D3,D4,DH1,D3,
    DH1,DH1,DH1,D7,D4,D4,D7,D7,
    D6,D7,DH1,D7,DH1,DH3,D7,
    D3,D3,D6,D5,D6,DH1,D5,
    D2,D3,D4,DH1,D7,DH1,DH2,DH2,DH3,DH1,
    DH1,D7,D6,D6,D7,D5,D6,
    DH1,DH2,DH3,DH2,DH3,DH5,DH2,
    D5,D5,DH1,D7,DH1,DH3,DH3,
    D6,D7,DH1,D7,DH1,DH2,DH1,D5,D5,
    DH4,DH3,DH2,DH1,DH3,
    DH3,DH6,DH6,DH5,DH5,DH3,DH2,DH1,
    DH1,DH2,DH1,DH2,DH5,DH3,
    DH3,DH6,DH6,DH5,DH5,DH3,DH2,DH1,
    DH1,DH2,DH1,DH2,D7,D6},
  {//Tiger：两只老虎
    32,
    D2,D3,D4,D2,
    D2,D3,D4,D2,
    D4,D4,D6,
    D4,D5,D6,
    D6,D7,D6,D5,D4,D2,
    D6,D7,D6,D5,D4,D2,
    D3,DL6,D2,
    D3,DL6,D2},
  {//HBD：生日歌
    25,
    D5,D5,D6,D5,DH1,D7,
    D5,D5,D6,D5,DH2,DH1,
    D5,D5,DH5,DH3,DH1,D7,D6,
    DH4,DH4,DH3,DH1,DH2,DH1,
    },
  {//SDG：圣诞歌
    82,
    D5,DH1,DH1,DH2,DH1,D7,D6,D6,
    D6,DH2,DH2,DH3,DH2,DH1,D7,D5,
    D5,DH3,DH3,DH4,DH3,DH2,DH1,D6,
    D5,D5,D6,DH2,D7,DH1,
    D5,DH1,DH1,DH2,DH1,D7,D6,D6,
    D6,DH2,DH2,DH3,DH2,DH1,D7,D5,
    D5,DH3,DH3,DH4,DH3,DH2,DH1,D6,
    D5,D5,D6,DH2,D7,DH1,
    D5,DH1,DH1,DH1,D7,
    D7,DH1,D7,D6,D5,
    DH2,DH3,DH2,DH1,DH5,D5,
    D5,D5,D6,DH2,D7,DH1},
  {//XDD：铃儿响叮当
    51,
    D7,D7,D7,
    D7,D7,D7,
    D7,DH2,D5,D6,D7,
    DH1,DH1,DH1,DH1,DH1,D7,D7,
    D7,D7,D7,D6,D6,D5,D6,DH2,
    D7,D7,D7,
    D7,D7,D7,
    D7,DH2,D5,D6,D7,
    DH1,DH1,DH1,DH1,DH1,D7,D7,
    D7,D7,DH2,DH2,DH1,D6,D5},
  {//DDM：叮当猫
    57,
    DL4,DL7,DL7,D2,D5,D2,D4,
    D4,D5,D4,D2,D3,D2,D1,
    DL5,D1,D1,D3,D6,D6,D5,D4,
    D3,D3,D2,DL5,DL6,DL7,D1,
    DL4,DL7,DL7,D2,D5,D2,D4,
    D4,D5,D4,D2,D3,D2,D1,
    DL5,D1,D1,D3,D6,D6,D5,D4,
    D3,D3,D2,DL6,D1,DL7},
  {//CR：超人
    31,
    D3,D4,D5,D5,D5,D7,D7,D6,
    D2,D2,D7,D7,D7,D6,D6,D5,
    D5,D4,D3,D5,
    D5,D4,D2,D5,
    D5,D5,D6,D3,D5,D5,D4}
};

//内置曲目的节拍，即音符持续时间
const float duration[10][120] PROGMEM=
{
  {//HLW：葫芦娃
    1, 1, 1 + 1,
    0.5, 1, 2.5,
    1, 1, 0.5, 0.5, 1,
    0.5, 1, 2.5,
    0.5, 0.5, 0.5, 0.5, 1 + 1,
    0.5, 1, 2.5,
    1 + 1, 0.5, 0.5, 1,
    1 + 1 + 1 + 1,
    1, 0.5 + 0.25, 0.25, 0.5 + 0.25, 0.25, 0.5 + 0.25, 0.75,
    1, 0.5, 2,
    1, 0.5 + 0.25, 0.25, 0.5 + 0.25, 0.25, 0.5 + 0.25, 0.75,
    1, 0.5, 2,
    2.5, 0.5, 1,
    1 + 1 + 1 + 1,
    0.5, 1, 2.5,
    0.5, 1, 2.5,
    1 + 1, 0.5, 0.5, 1,
    1 + 1 + 1 + 1},
  {//HLS：欢乐颂
    1,1,1,1,
    1,1,1,1,
    1,1,1,1,
    1+0.5,0.5,1+1,
    1,1,1,1,
    1,1,1,1,
    1,1,1,1,
    1+0.5,0.5,1+1,
    1,1,1,1,
    1,0.5,0.5,1,1,
    1,0.5,0.5,1,1,
    1,1,2,
    1,1,1,1,
    1,1,1,1,
    1,1,1,1,
    1+0.5,0.5,1+1},
  {//Deja Vu：逮虾虎
    0.4,0.4,0.8,
    0.4,0.4,0.8,0.4,0.8,0.4,0.8,
    0.4,0.4,0.4,0.4,0.8,
    0.4,0.4,0.4,0.4,0.4,0.8,0.4,0.4,1.6,
    0.4,0.4,0.8,
    0.4,0.4,0.8,0.4,0.8,0.4,0.8,
    0.4,0.4,0.4,0.4,0.8,
    0.4,0.4,0.4,0.4,0.4,0.8,0.4,0.4,2,2.4},
  {//TKZC:天空之城
    0.5,0.5,1.5,0.5,1,1,3,
    0.5,0.5,1.5,0.5,1,1,3,
    1,1.5,0.5,1,1,2.5,
    0.5,0.5,0.5,1.5,0.5,1,1,3,
    0.5,0.5,1.5,0.5,1,1,3,
    0.5,0.5,1.5,0.5,1,1,3,
    0.5,0.5,1,0.5,1,1.5,0.5,1,0.5,2,
    0.5,0.5,0.5,0.5,1,1,3,
    0.5,0.5,1.5,0.5,1,1,3,
    0.5,0.5,1.5,0.5,1,1,4,
    0.5,0.5,1,1,0.5,0.5,1.5,0.5,2,
    1,1,1,1,3,
    1,1.5,0.5,1.5,0.5,0.5,0.5,2,
    1,1,0.5,1.5,1,3,
    1,1.5,0.5,1.5,0.5,0.5,0.5,2,
    1,1,0.5,1.5,1,4},
  {//Tiger：两只老虎
    1,1,1,1,
    1,1,1,1,
    1,1,2,
    1,1,2,
    0.5,0.5,0.5,0.5,1,1,
    0.5,0.5,0.5,0.5,1,1,
    1,1,2,
    1,1,2},
  {//HBD：生日歌
    0.5,0.5,1,1,1,2,
    0.5,0.5,1,1,1,2,
    0.5,0.5,1,1,1,1,2,
    0.5,0.5,1,1,1,2},
  {//SDG：圣诞歌
    1,1,0.5,0.5,0.5,0.5,1,1,
    1,1,0.5,0.5,0.5,0.5,1,1,
    1,1,0.5,0.5,0.5,0.5,1,1,
    0.5,0.5,1,1,1,2,
    1,1,0.5,0.5,0.5,0.5,1,1,
    1,1,0.5,0.5,0.5,0.5,1,1,
    1,1,0.5,0.5,0.5,0.5,1,1,
    0.5,0.5,1,1,1,2,
    1,1,1,1,2,
    1,1,1,1,2,
    1,1,1,1,1,1,
    0.5,0.5,1,1,1,3},
  {//XDD：铃儿响叮当
    0.5,0.5,1,
    0.5,0.5,1,
    0.5,0.5,0.75,0.25,2,
    0.5,0.5,0.75,0.25,0.5,0.5,0.5,
    0.25,0.25,0.5,0.5,0.5,0.5,1,1,
    0.5,0.5,1,
    0.5,0.5,1,
    0.5,0.5,0.75,0.25,2,
    0.5,0.5,0.75,0.25,0.5,0.5,0.5,
    0.25,0.25,0.5,0.5,0.5,0.5,2},
  {//DDM：叮当猫
    0.75,0.25,0.75,0.25,0.75,0.25,1,
    0.75,0.25,0.75,0.25,0.75,0.25,1,
    0.75,0.25,0.75,0.25,0.75,0.25,0.75,0.25,
    1,0.75,0.25,0.75,0.75,0.5,4,
    0.75,0.25,0.75,0.25,0.75,0.25,1,
    0.75,0.25,0.75,0.25,0.75,0.25,1,
    0.75,0.25,0.75,0.25,0.75,0.25,0.75,0.25,
    1,0.75,0.25,1,1,4},
  {//CR：超人
    0.5,0.5,1,1,1,0.5,1,2.5,
    0.5,0.5,1,1,1,0.5,1,1.5,
    1,0.5,1,1.5,
    1,0.5,1,2.5,
    0.5,0.5,1,1,0.5,1,4.5},
};

//内置曲目的名称
const String song_name[10]={
  "HLW","HLS","Deja Vu","TKZC","Tiger","HBD","SDG","XDD","DDM","ATM"
};

int next=2;//2号端口用于检测是否切到下一首
int pause=3;//3号端口用于检测是否暂停
int last=4;//4号端口用于检测是否切到上一首
int forward=5;//5号端口用于输入快进指令
int back=6;//6号端口用于输入快退指令
int menu=7;//7号端口用于切到菜单
int tonePin = 8; //蜂鸣器的pin

int i,          //当前播放的歌曲序号
    len,        //歌曲长度
    flag1,      //标记暂停状态
    flag2,      //标记目录状态
    flag3,      //标记与上位机通信状态
    space,      //歌曲播放速度
    if_next,    //下一首信号标记
    if_pause,   //暂停信号标记
    if_last,    //上一首信号标记
    if_forward, //快进信号标记
    if_back,    //快退信号标记
    if_menu,    //目录信号标记
    song_num,   //当前储存的歌曲总数
    name_len;   //记录当前歌曲名的长度
int tu[15];
float du[15];
char comdata[10] = "";
int ret=0;
  
void setup()
{
  //设置端口
  pinMode(tonePin, OUTPUT); //设置蜂鸣器的pin为输出模式
  pinMode(next,INPUT);
  pinMode(pause,INPUT);
  pinMode(last,INPUT);
  pinMode(forward,INPUT);
  pinMode(back,INPUT);
  pinMode(menu,OUTPUT);

  Serial.begin(9600);
  
  song_num=10;
  i=0;
  len=pgm_read_word_near(&tune[i][0]);
  flag1=0;
  space=200;

  for(int ii=0;ii<15;ii++){
    tu[ii]=0;
    du[ii]=0;
  }

  //设置显示屏
  display.begin(SSD1306_SWITCHCAPVCC);
//  if(!){
//      Serial.println(F("SSD1306 allocation failed"));
//  }
  display.clearDisplay(); //清除OLED屏幕的显示
}

void loop()
{
  //显示进度条、曲目名称、状态栏
  display.clearDisplay();
  display.drawLine(0,56,127,56,WHITE);
  display.fillCircle(0,56,2,WHITE);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  name_len=song_name[i].length();
  display.setCursor((10.5-name_len)*128/21,24);
  display.println(song_name[i]);
  draw_ing();
  display.display();

  //以下是播放的代码
  for (int x = 0; x < len; x++) //循环的次数为当前歌曲的长度
  {
    //更新进度条、曲目名称、状态栏
    len=pgm_read_word_near(&tune[i][0]);
    display.clearDisplay();
    display.drawLine(0,56,127,56,WHITE);
    display.fillCircle((x+1)*128/len,56,2,WHITE);
    display.setTextSize(2);
    display.setTextColor(WHITE);
    name_len=song_name[i].length();
    display.setCursor((10.5-name_len)*128/21,24);
    display.println(song_name[i]);

    
    tone(tonePin, pgm_read_word_near(&tune[i][x+1])); //依次播放tune数组元素，即每个音符
    //Serial.println(pgm_read_word_near(&tune[i][x+1]));
    delay(space*pgm_read_float_near(&duration[i][x])); //每个音符持续的时间，即节拍duration，调整时间的越大，曲子速度越慢，越小曲子速度越快
    noTone(tonePin);//停止当前音符，进入下一音符
    //正常速度是400
    space=400;

    //判定用户是否按下“上一首”按钮
    if_last=digitalRead(last);
    if(if_last==HIGH)//上一首
    {
      display.clearDisplay();
      i=i-1;
      if(i<0)
        i=i+song_num;
      x=-1;
      display.drawLine(0,56,127,56,WHITE);
      display.fillCircle((x+1)*128/len,56,2,WHITE);
      draw_last();
      display.setTextSize(2);
      display.setTextColor(WHITE);
      name_len=song_name[i].length();
      display.setCursor((10.5-name_len)*128/21,24);
      display.println(song_name[i]);
      display.display();
      delay(500);
    }

    //判定用户是否按下“下一首”按钮
    if_next=digitalRead(next);
    if(if_next==HIGH)//下一首
    {
      display.clearDisplay();
//      Serial.print("[next]");
      i=i+1;
      if(i>=song_num)
        i=i-song_num;
      x=-1;
      display.drawLine(0,56,127,56,WHITE);
      display.fillCircle((x+1)*128/len,56,2,WHITE);
      draw_next();
      display.setTextSize(2);
      display.setTextColor(WHITE);
      name_len=song_name[i].length();
      display.setCursor((10.5-name_len)*128/21,24);
      display.println(song_name[i]);
      display.display();
      delay(500);
    }

    //判定用户是否按下“暂停”按钮
    if_pause=digitalRead(pause);
    if(if_pause==HIGH)//暂停
    {
      flag1=1;
//      Serial.print("[pause]");
      delay(500);
    }
    
    while(flag1==1)
    {
      delay(100);
      draw_stop();
      display.display();
      //判定用户是否再次按下“暂停”按钮，恢复播放
      if_pause=digitalRead(pause);
      if(if_pause==HIGH)//重新开始
      {
        flag1=0;
      }
    }
    
    //歌曲目录模块
    int UD=0;
    int song1,song2;
    song1=i;
    song2=i+1;
    if(song2>9)
      song2=song2-song_num;

    //判定用户是否按下“目录”按钮
    if_menu=digitalRead(menu);
    if(if_menu==HIGH)
    {
      flag2=1;
//      Serial.print("[menu]");
      delay(500);
    }

    while(flag2==1)
    {
      delay(100);

      if(UD==0){
        display.clearDisplay();
        draw_menu();
        output_name_2(song1,24);
        output_name_1(song2,40);
        display.display();
      }
      else{
        display.clearDisplay();
        draw_menu();
        output_name_1(song1,24);
        output_name_2(song2,40);
        display.display();
      }

      //目录模式下，按“上一首”按钮可将光标上移
      if_last=digitalRead(last);
      if(if_last==HIGH)//光标上移
      {
        if(UD==1){
          UD=0;
        }
        else{
          song2=song1;
          song1=song1-1;
          if(song1<0)
            song1=song1+song_num;
          delay(300);  
        }
        
      }

      //目录模式下，按“下一首”按钮可将光标下移
      if_next=digitalRead(next);
      if(if_next==HIGH)//光标下移
      {
        if(UD==0){
          UD=1;
        }
        else{
          song1=song2;
          song2=song2+1;
          if(song2>9)
            song2=song2-song_num;
          delay(300);  
        } 
      }

      //目录模式下，按“暂停”按钮可将MP3连接到上位机
      if_pause=digitalRead(pause);
      if(if_pause==HIGH)//连接上位机
      {
        flag3=1;
        display.clearDisplay();
        draw_com();
        display.display();
        Serial.println("begin");
        delay(500);
      }
      
      while(flag3==1){//上位机操作
        //听取上位机指令
        ans();
        //连接到上位机后，按“暂停”按钮可回到目录
        if_pause=digitalRead(pause);
        if(if_pause==HIGH){
          flag3=0;
          delay(500);
          Serial.println("end");
        }

        //连接到上位机后，按“目录”按钮可回听上位机传输过来的音乐
        if_menu=digitalRead(menu);
        if(if_menu==HIGH){
          for(int ii=0;ii<tu[0];ii++){
            display.clearDisplay();
            display.drawLine(0,56,127,56,WHITE);
            display.fillCircle((ii+1)*128/tu[0],56,2,WHITE);
            display.setTextSize(2);
            display.setTextColor(WHITE);
            display.setCursor((10.5-ret)*128/21,24);
            display.println(comdata);
            draw_ing();
            display.display();
            tone(tonePin,tu[ii+1]);
            delay(400*du[ii]);
            noTone(tonePin);
            delay(10);
          }
          display.clearDisplay();
          draw_com();
          display.display();
        }
        if(flag3==0){
          display.clearDisplay();
          draw_disconnect();
          display.display();
          delay(1000);
        }
      }
      
      //目录模式下，再次按“目录”按钮可回到正常播放
      if_menu=digitalRead(menu);
      if(if_menu==HIGH)//重新开始
      {
        flag2=0;
        if(i!=song1+UD){
          i=song1+UD;
          if(i>9)
            i=i-song_num;
          x=-1;
        }
      }
    }
    
    //将光标所指的歌曲设定为将要播放的歌曲
    if_forward=digitalRead(forward);
    if_back=digitalRead(back);
    if(if_forward==HIGH)
    {
      space=100;
      draw_forward();
    }
    else if(if_back==HIGH)
    {
      x=x-2;
      if(x<0)
        x=-2;
      space=100;
      draw_back();
    }
    else
    {
      draw_ing();
    }
    display.display();
  }
  
  display.clearDisplay();
  display.drawLine(0,56,127,56,WHITE);
  display.fillCircle(128,56,2,WHITE);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  name_len=song_name[i].length();
  display.setCursor((10.5-name_len)*128/21,24);
  display.println(song_name[i]);
  draw_ing();
  display.display();
  delay(500);
}

//////////////////////////////////////////////////////////////////////////

//状态栏：显示“正在播放”
void draw_ing() {
  display.drawBitmap(32, 0, char1[0], 16, 16, BLACK, WHITE); 
  display.drawBitmap(48, 0, char1[1], 16, 16, BLACK, WHITE); 
  display.drawBitmap(64, 0, char1[2], 16, 16, BLACK, WHITE); 
  display.drawBitmap(80, 0, char1[3], 16, 16, BLACK, WHITE); 
}

//状态栏：显示“暂停”
void draw_stop() {
  display.drawBitmap(48, 0, char2[0], 16, 16, BLACK, WHITE); 
  display.drawBitmap(64, 0, char2[1], 16, 16, BLACK, WHITE); 
}

//状态栏：显示“下一首”
void draw_next() {
  display.drawBitmap(40, 0, char3[0], 16, 16, BLACK, WHITE); 
  display.drawBitmap(56, 0, char3[1], 16, 16, BLACK, WHITE); 
  display.drawBitmap(72, 0, char3[2], 16, 16, BLACK, WHITE); 
}

//状态栏：显示“上一首”
void draw_last() {
  display.drawBitmap(40, 0, char4[0], 16, 16, BLACK, WHITE); 
  display.drawBitmap(56, 0, char4[1], 16, 16, BLACK, WHITE); 
  display.drawBitmap(72, 0, char4[2], 16, 16, BLACK, WHITE); 
}

//状态栏：显示“快进”
void draw_forward() {
  display.drawBitmap(48, 0, char5[0], 16, 16, BLACK, WHITE); 
  display.drawBitmap(64, 0, char5[1], 16, 16, BLACK, WHITE); 
}

//状态栏：显示“快退”
void draw_back() {
  display.drawBitmap(48, 0, char6[0], 16, 16, BLACK, WHITE); 
  display.drawBitmap(64, 0, char6[1], 16, 16, BLACK, WHITE); 
}

//状态栏：显示“目录”
void draw_menu() {
  display.drawBitmap(48, 0, char7[0], 16, 16, BLACK, WHITE); 
  display.drawBitmap(64, 0, char7[1], 16, 16, BLACK, WHITE); 
}

//状态栏：显示“已连接上位机”
void draw_com() {
  display.drawBitmap(16, 24, char8[0], 16, 16, BLACK, WHITE); 
  display.drawBitmap(32, 24, char8[1], 16, 16, BLACK, WHITE); 
  display.drawBitmap(48, 24, char8[2], 16, 16, BLACK, WHITE); 
  display.drawBitmap(64, 24, char8[3], 16, 16, BLACK, WHITE); 
  display.drawBitmap(80, 24, char8[4], 16, 16, BLACK, WHITE); 
  display.drawBitmap(96, 24, char8[5], 16, 16, BLACK, WHITE); 
}

//状态栏：显示“已下载”
void draw_download() {
  display.drawBitmap(40, 8, char9[0], 16, 16, BLACK, WHITE); 
  display.drawBitmap(56, 8, char9[1], 16, 16, BLACK, WHITE); 
  display.drawBitmap(72, 8, char9[2], 16, 16, BLACK, WHITE); 
}

//状态栏：显示“与上位机断开”
void draw_disconnect() {
    display.drawBitmap(16, 24, char10[0], 16, 16, BLACK, WHITE); 
    display.drawBitmap(32, 24, char10[1], 16, 16, BLACK, WHITE); 
    display.drawBitmap(48, 24, char10[2], 16, 16, BLACK, WHITE); 
    display.drawBitmap(64, 24, char10[3], 16, 16, BLACK, WHITE); 
    display.drawBitmap(80, 24, char10[4], 16, 16, BLACK, WHITE); 
    display.drawBitmap(96, 24, char10[5], 16, 16, BLACK, WHITE); 
}

//输出普通亮度的歌名
void output_name_1(int num,int pos){
  display.setTextSize(2);
  display.setTextColor(WHITE);
  name_len=song_name[num].length();
  display.setCursor((10.5-name_len)*128/21,pos);
  display.println(song_name[num]);
}

//输出高亮的歌名
void output_name_2(int num,int pos){
  display.setTextSize(2);
  display.setTextColor(BLACK,WHITE);
  name_len=song_name[num].length();
  display.setCursor((10.5-name_len)*128/21,pos);
  display.println(song_name[num]);
}

//听取上位机指令的函数
void ans(){
  int var;
  if(Serial.available()>0){
    var=Serial.read();
    //指令1：发送歌单
    if(var==49)
      ans_songname();
    //指令2：传输音乐到MP3
    if(var==50){
      add_song();
      delay(1000);
      for(int ii=0;ii<tu[0];ii++){
        tone(tonePin,tu[ii+1]);
        delay(400*du[ii]);
        noTone(tonePin);
        delay(10);
      }
      delay(1000);
      display.clearDisplay();
      draw_com();
      display.display();
    }
    //指令3：断开连接
    if(var==51){
      flag3=0;
    }
  }
}

//用于向上位机发送歌单的函数
void ans_songname(){
  Serial.println("beginone");
  for(int ans=0;ans<song_num;ans++)
  {
    Serial.println(song_name[ans]);
  }
  Serial.println("endone");
}

//用于接收并储存上位机发送过来的音乐的函数
void add_song(){
  //接收音符
  Serial.println("begintu");
  int ii=0;
  int x=0;
  int tu_store=0;
  float du_store=0;
  int tune_num=0;
  int point=0;
  Serial.println("OK");
  ret=Serial.readBytesUntil('\n', comdata, 10); 
  for(x=0;x<ret;x++){
    tune_num=tune_num*10+(comdata[x]-'0');
  }
  
  tu[0]=tune_num;

  for(ii=0;ii<tune_num;ii++){
    Serial.println("OK");
    ret=Serial.readBytesUntil('\n', comdata, 10); 
    for(x=0;x<ret;x++){
      tu_store=tu_store*10+(comdata[x]-'0');
    }
    tu[ii+1]=tu_store;
    tu_store=0;
  }
  //接收节拍
  Serial.println("begindu");

  for(ii=0;ii<tune_num;ii++){
    Serial.println("OK");
    ret=Serial.readBytesUntil('\n', comdata, 10); 
    for(x=0;x<ret;x++){
      du_store=du_store*10+(comdata[x]-'0');
    }
    du[ii]=du_store;
    point=0;
    du_store=0;
  }
  //接收音乐名称
  Serial.println("beginname");
  ret=Serial.readBytesUntil('\n', comdata, 10); 
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor((10.5-ret)*128/21,32);
  display.println(comdata);
  draw_download();
  display.display();
  //结束接收
  Serial.println("endtwo");


}

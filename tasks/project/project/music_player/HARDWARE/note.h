#ifndef __NOTE_H
#define __NOTE_H
#include "sys.h"

/********************F*********************/
//定义低音音名F (单位是Hz)
#define F_L1 349
#define F_L2 392
#define F_L3 440
#define F_L4 466
#define F_L5 523
#define F_L6 587
#define F_L7 659

//定义中音音名F
#define F_M1 698
#define F_M2 784
#define F_M3 880
#define F_M4 932
#define F_M5 1047
#define F_M6 1175
#define F_M7 1319
	
//定义高音音名F
#define F_H1 1397
#define F_H2 1568
#define F_H3 1760
#define F_H4 1865

/********************C*********************/
//定义低音
#define C_L1 262
#define C_L2 294
#define C_L3 330
#define C_L4 349
#define C_L5 392
#define C_L6 440
#define C_L7 494

//定义中音
#define C_M1 523
#define C_M2 587
#define C_M3 659
#define C_M4 698
#define C_M5 784
#define C_M6 880 
#define C_M7 988

//定义高音
#define C_H1 1047
#define C_H2 1175
#define C_H3 1319
#define C_H4 1397
#define C_H5 1568
#define C_H6 1760
#define C_H7 1976

/********************E*********************/
//定义低音
#define E_L1 330
#define E_L2 370
#define E_L3 415
#define E_L4 440
#define E_L5 494
#define E_L6 554
#define E_L7 622

//定义中音
#define E_M1 659
#define E_M2 740
#define E_M3 831
#define E_M4 880
#define E_M5 988
#define E_M6 1109
#define E_M7 1245

//定义高音
#define E_H1 1318



//定义时值单位,决定演奏的速度 ms为单位 2000为佳
#define TT 2500    
//extern u16 TT;

typedef struct
{
	short mName; //音名
	short mTime; //时值，全音符，二分音符，四分音符
}tNote;

typedef struct
{
	u8 *name;
	u8 index;
	tNote *music;
}song_msg;


extern tNote *music[];
extern song_msg songs[];
extern u16 songs_length[];

#endif












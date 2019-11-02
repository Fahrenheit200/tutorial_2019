#include "reg51.H"
#include "integer.h"
#include "diskio.h"
#include "tff.h"
typedef unsigned char uint8;
typedef unsigned int uint16;
void delay50ms(uint16 t);
void configUART(unsigned int baud);
void main(){
    FATFS fs;            // Work area (file system object) for logical drive
    FIL fsrc, fdst;      // file objects
    BYTE buffer[8];   	 // file copy buffer
    FRESULT res;         // FatFs function common result code
    UINT br, bw;         // File R/W count

	EA=1;
	configUART(9600);
	
	delay50ms(20);
    // Register a work area for logical drive 0
    SBUF=0xff;
    
    
    res = f_mount(0, &fs);
	
    // Open source file
    res = f_open(&fsrc, "a.txt", FA_OPEN_EXISTING | FA_READ);
    //if (res) die(res);
	
    // Create destination file
    res = f_open(&fdst, "b.txt", FA_CREATE_ALWAYS | FA_WRITE);
    //if (res) die(res);
	
    // Copy source to destination
    for (;;) {
        res = f_read(&fsrc, buffer, sizeof(buffer), &br);
        SBUF=res;
        if (res || br == 0) break;   // error or eof
        
        res = f_write(&fdst, buffer, br, &bw);
        SBUF=res;
        if (res || bw < br) break;   // error or disk full
    }
	
    // Close all files
    f_close(&fsrc);
    f_close(&fdst);

    // Unregister a work area before discard it
    f_mount(0, 0);
    while(1){
	}
}
void delay50ms(uint16 t)
{
	uint16 i;
	for(;t>0;t--)
	for(i=6245;i>0;i--);
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

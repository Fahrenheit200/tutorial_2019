#include "reg51.H" 
#include "diskio.h"
#include "integer.h"

/*------------------------------------------------------------*/
/*define sd card CMD control info*/
#define CMD_GO_IDLE_STATE         0
#define CMD_SEND_OP_COND          1
#define CMD_SEND_CSD              9
#define CMD_SEND_CID              10
#define CMD_STOP_TRANSMISSION     12
#define CMD_SEND_STATUS           13
#define CMD_SET_BLOCKLEN          16
#define CMD_READ_SINGLE_BLOCK     17
#define CMD_READ_MULTIPLE_BLOCK   18
#define CMD_WRITE_SINGLE_BLOCK    24
#define CMD_WRITE_MULTIPLE_BLOCK  25
#define CMD_PROGRAM_CSD           27
#define CMD_SET_WRITE_PROT        28
#define CMD_CLR_WRITE_PROT        29
#define CMD_SEND_WRITE_PROT       30
#define CMD_TAG_SECTOR_START      32
#define CMD_TAG_SECTOR_END        33
#define CMD_UNTAG_SECTOR          34
#define CMD_TAG_ERASE_GROUP_START 35
#define CMD_TAG_ERASE_GROUP_END   36
#define CMD_UNTAG_ERASE_GROUP     37
#define CMD_ERASE                 38
#define CMD_LOCK_UNLOCK           42
#define CMD_APP_CMD               55
#define CMD_READ_OCR              58
#define CMD_CRC_ON_OFF            59
#define ACMD_SEND_OP_COND         41
#define SD_TIME_OUT				  1
#define SD_ERROR				  2
#define IDLE_STATE				  0x01 
/*------------------------------------------------------------*/
/*card type*/
xdata WORD CardType;	/* MMC=0,SDCard v1=1,SDCard v2=2*/
/*------------------------------------------------------------*/
/*Auxiliary and SPI status register*/
sfr AUXR = 		0x8e; 	//Auxiliary register
sfr SPSTAT = 	0xcd; 	//SPI status register
#define SPIF 	0x80 	//SPSTAT.7
#define WCOL 	0x40 	//SPSTAT.6
/*------------------------------------------------------------*/
/*SPI control register*/
sfr SPCTL = 	0xce;		//SPI control register
#define SSIG 	0x80 	//SPCTL.7
#define SPEN 	0x40	//SPCTL.6
#define DORD 	0x20	//SPCTL.5
#define MSTR 	0x10 	//SPCTL.4
#define CPOL 	0x08 	//SPCTL.3
#define CPHA 	0x04 	//SPCTL.2
#define SPDHH 	0x00 	//CPU_CLK/4
#define SPDH 	0x01 	//CPU_CLK/16
#define SPDL 	0x02 	//CPU_CLK/64
#define SPDLL 	0x03 	//CPU_CLK/128
/*------------------------------------------------------------*/
/*other necessary control*/
sfr SPDAT = 	0xcf; 	//SPI data register
sbit SPISS = 	P1 ^ 3; 	//SPI slave select, connect to slave' SS(P1.4) pin
sfr IE2 = 		0xAF; 	//interrupt enable register 2
#define ESPI 	0x02 	//IE2.1
/*------------------------------------------------------------*/
/*frequency type*/
//enum SPI_FREQUENCIES { kHz93_75, kHz187_5, kHz750, MHz3 };
/*------------------------------------------------------------*/
/*necessary structure union definition*/
typedef union
{
	BYTE Index[6];
	struct
	{
		BYTE Command;
		ULONG Argument;
		BYTE Cksum;
	} CA;
} CommandStructure;

typedef union
{
	BYTE b[4];
	ULONG ul;
} b_ul;
/*------------------------------------------------------------*/
/*basic SPI function declare*/
BYTE SPI_Byte(BYTE ThisByte);
void SPI_EnableCS();
void SPI_DisableCS();
void SPI_Init(BYTE freq);
/*------------------------------------------------------------*/
/*futher SPI function declare*/
BYTE SD_ReadSector(ULONG SectorNumber, BYTE *Buffer);
BYTE SD_WriteSector(ULONG SectorNumber, BYTE *Buffer);
BYTE SD_WaitForReady();
BYTE SD_Command(BYTE ThisCommand, ULONG ThisArgument);
BYTE SD_Init();
BYTE SD_GetR1();
WORD SD_GetR2();
void Delay(WORD MilSec);
/*basic SPI function definition*/
BYTE SPI_Byte(BYTE ThisByte)
{
	BYTE tmp;
	SPDAT = ThisByte;
	while ((SPSTAT&SPIF == 0));
	SPSTAT = SPIF | WCOL;
	tmp = SPDAT;
	if(tmp!=0xff){
		while(!TI); TI=0;
		SBUF=tmp;
	}

	return tmp;
}
void SPI_EnableCS()
{
	SPISS = 0;				//SPI slave enable
}
void SPI_DisableCS()
{
	SPISS = 1;				//SPI slave disable
}
void SPI_Init(BYTE freq)
{
	SPDAT = 0; 										//initial SPI data
	SPSTAT = SPIF | WCOL; 							//clear SPI status
	SPCTL = SPEN | MSTR | SSIG | CPOL | CPHA; 		//master mode
	switch (freq)             						// sets frequency...
	{
	case 3:
		SPCTL = SPCTL | SPDHH;
		break;
	case 2:
		SPCTL = SPCTL | SPDH;
		break;
	case 1:
		SPCTL = SPCTL | SPDL;
		break;
	case 0:
		SPCTL = SPCTL | SPDLL;
		break;
	default:
		SPCTL = SPCTL | SPDH;
		break;
	}
}
/*------------------------------------------------------------*/
/*futher SPI function definition*/
BYTE SD_GetR1()
{
	BYTE i, j;

	for (i = 0; i < 8; i++)
	{                        /* response will be after 1-8 0xffs.. */
		j = SPI_Byte(0xff);
		if (j != 0xff)         /* if it isn't 0xff, it is a response */
		{
			return(j);
		}

	}
	return(j);
}
WORD SD_GetR2()
{
	idata WORD R2;

	R2 = ((SD_GetR1()) << 8) & 0xff00;
	R2 |= SPI_Byte(0xff);
	return(R2);
}
void Delay(WORD MilSec)
{
	UINT i;
	while (MilSec--)
		for (i = 0; i < 123; i++);
}
BYTE SD_ReadSector(ULONG SectorNumber, BYTE *Buffer)
{
	BYTE c, i;
	WORD count;

	/* send block-read command... */
	SD_Command(CMD_READ_SINGLE_BLOCK, SectorNumber << 9);
	c = SD_GetR1();
	i = SD_GetR1();
	count = 0xFFFF;

	/* wait for data token... */
	while ((i == 0xff) && --count)
		i = SD_GetR1();

	/* handle time out... */
	if (c || i != 0xFE)
		return(1);

	/* read the sector... */
	//for( count=0; count<SD_DATA_SIZE; count++)         
	for (count = 0; count < 512; count++)
		*Buffer++ = SPI_Byte(0xFF);

	/* ignore the checksum... */
	SPI_Byte(0xFF);
	SPI_Byte(0xFF);

	/* release the CS line... */
	SPI_DisableCS();

	return(0);
}
BYTE SD_WriteSector(ULONG SectorNumber, BYTE *Buffer)
{
	BYTE i;
	WORD count;

	/* send block-write command... */
	SD_Command(CMD_WRITE_SINGLE_BLOCK, SectorNumber << 9);
	i = SD_GetR1();

	/* send start block token... */
	SPI_Byte(0xFE);

	/* write the sector... */
	for (count = 0; count < 512; count++)
	{
		SPI_Byte(*Buffer++);
	}
	/* ignore the checksum (dummy write)... */
	SPI_Byte(0xFF);
	SPI_Byte(0xFF);

	/* wait for response token... */
	while (SPI_Byte(0xFF) != 0xFF)

		/* these 8 clock cycles are critical for the card */
		/* to finish up whatever it's working on at the */
		/* time... (before CS is released!) */
		SPI_Byte(0xFF);

	/* release the CS line... */
	SPI_DisableCS();
	SPI_Byte(0xFF);
	return(0);
}
BYTE SD_WaitForReady()
{
	BYTE i;
	WORD j;

	SPI_Byte(0xFF);

	j = 500;
	do
	{
		i = SPI_Byte(0xFF);
		Delay(1);
	} while ((i != 0xFF) && --j);

	return(i);
}
BYTE SD_Init()
{
	WORD CardStatus; // R2 value from status inquiry...
	WORD Count;      // local counter
	BYTE res;
	
	// Global CardType - b0:MMC, b1:SDv1, b2:SDv2

	/* initial speed is slow... */
	SPI_Init(2);

	/* disable SPI chip select... */
	SPI_DisableCS();

	/* fill send data with all ones - 80 bits long to   */
	/* establish link with SD card this fulfills the    */
	/* 74 clock cycle requirement...  */
	for (Count = 0; Count < 10; Count++)
		SPI_Byte(0xFF);

	/* enable the card with the CS pin... */
	SPI_EnableCS();

	/* ************************************************ */
	/* SET SD CARD TO SPI MODE - IDLE STATE...          */
	/* ************************************************ */
	Count = 1000;     // one second...
	CardType = 0;
	
	while(!TI); TI=0;
	SBUF=0xaa;
	
	/* wait for card to enter IDLE state... */
	do
	{
		Delay(1);
		SD_Command(CMD_GO_IDLE_STATE, 0);
		res=SD_GetR1();
		while(!TI); TI=0;
		SBUF=res;
	} while ((res != IDLE_STATE) && (--Count));
	
	while(!TI); TI=0;
	SBUF=0xaa;
	
	/* timeout if we never made it to IDLE state... */
	if (!Count)
		return(SD_TIME_OUT);

	/* ************************************************ */
	/* COMPLETE SD CARD INITIALIZATION                  */
	/* FIGURE OUT WHAT TYPE OF CARD IS INSTALLED...     */
	/* ************************************************ */
	Count = 2000;     // two seconds...

					  /* Is card SDSC or MMC? */
	SD_Command(CMD_APP_CMD, 0);
	SD_Command(ACMD_SEND_OP_COND, 0);
	if (SD_GetR1() <= 1)
	{
		CardType = 2;
	}
	else
	{
		CardType = 1;
	}

	/* wait for initialization to finish... */
	do
	{
		Delay(1);
		if (CardType == 2)
		{
			SD_Command(CMD_APP_CMD, 0);
			SD_Command(ACMD_SEND_OP_COND, 0);
		}
		else
		{
			SD_Command(CMD_SEND_OP_COND, 0);
		}
	} while (SD_GetR1() && --Count);

	if (!Count)
		return(SD_TIME_OUT);

	/* ************************************************ */
	/* QUERY CARD STATUS...                             */
	/* ************************************************ */
	SD_Command(CMD_SEND_STATUS, 0);
	CardStatus = SD_GetR2();

	if (CardStatus)
		return(SD_ERROR);

	/* ************************************************ */
	/* SET BLOCK SIZE...                                */
	/* ************************************************ */
	SD_Command(CMD_SET_BLOCKLEN, 512);
	if (SD_GetR1())
	{
		CardType = 0;
		return(SD_ERROR);
	}

	/* ************************************************ */
	/* SWITCH TO HIGHEST SPI SPEED...                   */
	/* ************************************************ */
	SPI_Init(3);

	/* disable the card with the CS pin... */
	SPI_DisableCS();

	/* return OK... */
	return(0);
}
BYTE SD_Command(BYTE ThisCommand, ULONG ThisArgument)
{
	b_ul Temp;
	BYTE i;

	/* enable the device... */
	SPI_EnableCS();

	/* send buffer clocks to insure no operations are pending... */
	SPI_Byte(0xFF);

	/* send command */
	SPI_Byte(0x40 | ThisCommand);

	/* send argument */
	Temp.ul = ThisArgument;
	for (i = 0; i < 4; i++)
		SPI_Byte(Temp.b[i]);

	/* send CRC */
	SPI_Byte((ThisCommand == CMD_GO_IDLE_STATE) ? 0x95 : 0xFF);

	/* send buffer clocks to insure card has finished all operations... */
	SPI_Byte(0xFF);
	return(0);
}


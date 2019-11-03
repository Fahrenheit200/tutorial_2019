/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2007        */
/*-----------------------------------------------------------------------*/
/* This is a stub disk I/O module that acts as front end of the existing */
/* disk I/O modules and attach it to FatFs module with common interface. */
/*-----------------------------------------------------------------------*/
#include "reg51.h"
#include "diskio.h"
#include "integer.h"
typedef unsigned char 	uint8;
typedef unsigned int 	uint16;
typedef unsigned long 	uint32;
/*-----------------------------------------------------------------------*/
/* Correspondence between physical drive number and physical drive.      */
/* Note that Tiny-FatFs supports only single drive and always            */
/* accesses drive number 0.                                              */

#define ATA		0
#define MMC		1
#define USB		2

extern uint8 AllInit();
extern uint8 WaitForReady();
extern uint8 WriteSector(uint32 SectorNumber,uint8 *Buffer);
extern uint8 ReadSector(uint32 SectorNumber,uint8 *Buffer);
extern void disableCS();
extern void enableCS();
/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
DSTATUS Stat = STA_NOINIT;

DSTATUS disk_initialize(BYTE drv)
{
	BYTE res;
	/* Supports only single drive */
	if (drv != 0)
		return STA_NOINIT;

	/* if initialization succeeds... */

	res = AllInit();
	
	while (!TI); TI = 0;
	SBUF = 0xaa;
	while (!TI); TI = 0;
	SBUF = res;

	if (!res)
	{
		/*Initialize success, Clear STA_NOINIT */
		Stat &= ~STA_NOINIT;
	}

	/* return current status */
	return(Stat);
}



/*-----------------------------------------------------------------------*/
/* Return Disk Status                                                    */

DSTATUS disk_status(BYTE drv)
{
	/* Supports only single drive */
	if (drv != 0)
		return STA_NOINIT;

	/* return current status */
	return(Stat);
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */

DRESULT disk_read(BYTE drv, BYTE *buff, DWORD sector, BYTE count)
{
	/* Supports only single drive and must have a size of 1 sector */
	if (drv || !count || (count > 1))
		return(RES_PARERR);

	/* if we haven't initialized the card yet... */
	if (Stat & STA_NOINIT)
		return(RES_NOTRDY);

	/* Single block read */
	if (ReadSector(sector, buff))
		return(RES_ERROR);

	/* return successful result: OK */
	return(RES_OK);
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */

#if _READONLY == 0
DRESULT disk_write(BYTE drv, const BYTE *buff, DWORD sector, BYTE count)
{
	/* Supports only single drive and must have a size of 1 sector */
	if (drv || !count || (count > 1))
		return(RES_PARERR);

	/* if we haven't initialized the card yet... */
	if (Stat & STA_NOINIT)
		return(RES_NOTRDY);

	/* Single block write */
	if (WriteSector(sector, buff))
		return(RES_ERROR);

	/* return successful result: OK */
	return(RES_OK);
}
#endif /* _READONLY */



/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */

DRESULT disk_ioctl(BYTE drv, BYTE ctrl, void *buff)
{
	DRESULT res;
	BYTE  *ptr = buff;

	/* Supports only single drive */
	if (drv != 0)
		return RES_PARERR;

	/* if we haven't initialized the card yet... */
	if (Stat & STA_NOINIT)
		return RES_NOTRDY;

	res = RES_ERROR;

	switch (ctrl)
	{
		/* Flush dirty buffer if present */
	case CTRL_SYNC:
		enableCS();
		if (WaitForReady() == 0xFF)
			res = RES_OK;
		break;

	default:
		res = RES_PARERR;
		break;
	}

	disableCS();
	return res;
}


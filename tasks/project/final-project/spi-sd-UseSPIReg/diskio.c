/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2007        */
/*-----------------------------------------------------------------------*/
/* This is a stub disk I/O module that acts as front end of the existing */
/* disk I/O modules and attach it to FatFs module with common interface. */
/*-----------------------------------------------------------------------*/
#include "reg51.h"
#include "diskio.h"
#include "integer.h"
/*-----------------------------------------------------------------------*/
/* Correspondence between physical drive number and physical drive.      */
/* Note that Tiny-FatFs supports only single drive and always            */
/* accesses drive number 0.                                              */

#define ATA		0
#define MMC		1
#define USB		2

extern xdata WORD CardType;
extern BYTE SD_ReadSector(ULONG SectorNumber, BYTE *Buffer);
extern BYTE SD_WriteSector(ULONG SectorNumber, BYTE *Buffer);
extern BYTE SD_WaitForReady();
extern void SPI_EnableCS();
extern void SPI_DisableCS();
extern BYTE SD_Init();
extern BYTE SPI_Byte(BYTE ThisByte);

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

	res = SD_Init();
	
	while (!TI); TI = 0;
	SBUF = 0xbb;
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
	if (SD_ReadSector(sector, buff))
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
	if (SD_WriteSector(sector, buff))
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
		SPI_EnableCS();
		if (SD_WaitForReady() == 0xFF)
			res = RES_OK;
		break;

	default:
		res = RES_PARERR;
		break;
	}

	SPI_DisableCS();
	SPI_Byte(0xFF);
	return res;
}


/*
 * FLASH_program.c
 *
 *  Created on: Feb 7, 2024
 *      Author: Youssef Gamal & Mazen Musleh
 */
#include "../Lib/BIT_MATH.h"
#include "../Lib/STD_TYPES.h"
#include "FLASH_interface.h"
#include "FLASH_register.h"
#include "FLASH_config.h"
#include "FLASH_private.h"


/**
 * @brief Erase application area.
 *
 * This function erases the application area by erasing each sector from 1 to 5.
 */
void MFDI_voidEraseAppArea(void)
{
	for(u8 L_u8Iterator = 1; L_u8Iterator < 6; L_u8Iterator++)
	{
		MFDI_voidSectorErase(L_u8Iterator);
	}
}

/**
 * @brief Erase a flash sector.
 *
 * This function erases the specified flash sector.
 *
 * @param A_u8SectorNum The sector number to be erased.
 */
void MFDI_voidSectorErase  (u8 A_u8SectorNum)
{
	if(A_u8SectorNum < 6)
	{
		/* wait the busy flag */
		while(GET_BIT(MFDI -> FLASH_SR, 16) == 1);

		/* check the lick if not unlock */
		if(GET_BIT(MFDI -> FLASH_CR, 31) == 1)
		{
			MFDI -> FLASH_KEYR = MFDI_KEY1;
			MFDI -> FLASH_KEYR = MFDI_KEY2;
		}

		MFDI -> FLASH_CR &= 0xFFFFFF87;
		/* set number of sector */
		MFDI -> FLASH_CR |= A_u8SectorNum << 3;
		/* Set sector Erase */
		SET_BIT(MFDI -> FLASH_CR, 1);
		/* Start Erasing */
		SET_BIT(MFDI -> FLASH_CR, 16);
		/* wait until erasing ends */
		while(GET_BIT(MFDI -> FLASH_SR, 16) == 1);
		/* Set EOP bit */
		SET_BIT(MFDI -> FLASH_SR, 0);
		/* Clear sector erase */
		CLR_BIT(MFDI -> FLASH_CR, 1);
	}
}
/**
 * @brief Write data to flash.
 *
 * This function writes data to flash at the specified address.
 *
 * @param A_u32Address The address where the data will be written.
 * @param A_P16PtrData Pointer to the data array.
 * @param A_u8Len Length of the data array.
 */
void MFDI_voidFlashWrite  (u32 A_u32Address, u16* A_P16PtrData, u8 A_u8Len)
{
	/* wait the busy flag */
	while(GET_BIT(MFDI -> FLASH_SR, 16) == 1);

	/* check the lick if not unlock */
	if(GET_BIT(MFDI -> FLASH_CR, 31) == 1)
	{
		MFDI -> FLASH_KEYR = MFDI_KEY1;
		MFDI -> FLASH_KEYR = MFDI_KEY2;
	}

	/* set Psize --> Half Word */
	MFDI -> FLASH_CR &= 0xFFFFFCFF;
	MFDI -> FLASH_CR |= WRITE_OPERATION << 8;
	/* looping for each element of the array to write */
	for (u8 L_u8Iterator = 0; L_u8Iterator < A_u8Len; L_u8Iterator++)
	{
		/* set PG */
		SET_BIT(MFDI -> FLASH_CR, 0);
		/*
		 * volatile -> in order not to buffer in GPRS */
		*((volatile u16*) A_u32Address) = A_P16PtrData[L_u8Iterator];
		/* +=2 -> in order to increment by Psize (half word) */
		A_u32Address +=2;

		/* wait the busy flag */
		while(GET_BIT(MFDI -> FLASH_SR, 16) == 1);

		/* Set EOP bit */
		SET_BIT(MFDI -> FLASH_SR, 0);

		/* Clear PG */
		CLR_BIT(MFDI -> FLASH_CR, 0);
	}

}

/*
 * FLASH_register.h
 *
 *  Created on: Feb 7, 2024
 *      Author: Youssef Gamal & Mazen Musleh
 */

#ifndef FLASH_FLASH_REGISTER_H_
#define FLASH_FLASH_REGISTER_H_

#define FLASH_BASE_ADDRESS   0x40023C00


typedef struct
{
	u32 FLASH_ACR;
	u32 FLASH_KEYR;
	u32 FLASH_OPTKEYR;
	u32 FLASH_SR;
	u32 FLASH_CR;
	u32 FLASH_OPTCR;
}FDI_t;

#define MFDI     ((volatile FDI_t*)(FLASH_BASE_ADDRESS))
#define MFDI_KEY1  0x45670123
#define MFDI_KEY2  0xCDEF89AB



#endif /* FLASH_FLASH_REGISTER_H_ */

/*
 * FLASH_interface.h
 *
 *  Created on: Feb 7, 2024
 *      Author: Youssef Gamal & Mazen Musleh
 */

#ifndef FLASH_FLASH_INTERFACE_H_
#define FLASH_FLASH_INTERFACE_H_


void MFDI_voidEraseAppArea(void);
void MFDI_voidSectorErase  (u8 A_u8SectorNum);
/* flashing with half word */
void MFDI_voidFlashWrite  (u32 A_u32Address, u16* A_P16PtrData, u8 A_u8Len);


#endif /* FLASH_FLASH_INTERFACE_H_ */

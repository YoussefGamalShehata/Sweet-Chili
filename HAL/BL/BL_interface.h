/*
 * BL_interface.h
 *
 *  Created on: Feb 20, 2024
 *      Author: Youssef Gamal & Mazen Musleh
 */

#ifndef BL_BL_INTERFACE_H_
#define BL_BL_INTERFACE_H_

#define SCB_VTOR	*((volatile u32 *)(0xE000ED08)) /*To Change the Vector Table of the Application*/

typedef void (*AddAsFunc)(void);

void BL_voidJumpToApp(void);
void BL_voidEraseDataBuffer(void);
void BL_voidGetAndParseRecordNew(u8 received_records[],u32 array_size,u32 max_records,u32 max_record_length);

#endif /* BL_BL_INTERFACE_H_ */

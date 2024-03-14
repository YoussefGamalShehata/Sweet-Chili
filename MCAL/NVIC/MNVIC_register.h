/*
 * MNVIC_register.h
 *
 *  Created on: Jan 29, 2024
 *      Author: Hesham Tayel & Amira Magdy
 */

#ifndef MNVIC_MNVIC_REGISTER_H_
#define MNVIC_MNVIC_REGISTER_H_


#define MNVIC_BASE_ADDRESS	0xE000E100

typedef struct
{
	u32 ISER[8];
	u32 RESERVED0[24];
	u32 ICER[8];
	u32 RESERVED1[24];
	u32 ISPR[8];
	u32 RESERVED2[24];
	u32 ICPR[8];
	u32 RESERVED3[24];
	u32 IABR[8];
	u32 RESERVED4[56];
	u8  IPR[240];
	u32 RESERVED5[580];
	u32 STIR;
}NVIC_t;


#define MNVIC_REG		((volatile NVIC_t*)(MNVIC_BASE_ADDRESS))

#define MSCB_AIRCR		(*(volatile u32*)(0xE000ED0C))






#endif /* MNVIC_MNVIC_REGISTER_H_ */

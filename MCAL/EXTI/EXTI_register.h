/*
 * EXTI_register.h
 *
 *  Created on: Jan 30, 2024
 *      Author: Mazen Musleh
 */

#ifndef EXTI_REGISTER_H_
#define EXTI_REGISTER_H_


#define EXTI_BASE_ADDRESS		0x40013C00
#define SYSCFG_BASE_ADDRESS		0x40013800



typedef struct
{
	u32 IMR;
	u32 EMR;
	u32 RTSR;
	u32 FTSR;
	u32 SWIER;
	u32 PR;
}EXTI_t;


#define EXTI	((volatile EXTI_t*)(EXTI_BASE_ADDRESS))

#define SYSCFG_EXTICR1	*((volatile u32*)(SYSCFG_BASE_ADDRESS+8))


#endif /* EXTI_REGISTER_H_ */

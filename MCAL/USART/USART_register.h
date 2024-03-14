/*
 * USART_register.h
 *
 *  Created on: Feb 3, 2024
 *      Author: Ali Samir & Youssef Gamal & Mazen Musleh
 */

#ifndef USART_USART_REGISTER_H_
#define USART_USART_REGISTER_H_

#define USART1_BASE_ADDRESS	0x40011000
#define USART2_BASE_ADDRESS	0x40004400

typedef struct
{
	u32 SR	;
	u32 DR	;
	u32 BRR	;
	u32 CR1	;
	u32 CR2	;
	u32 CR3	;
	u32 GTPR;
}USART_t;

#define USART1	((volatile USART_t*)(USART1_BASE_ADDRESS))
#define USART2	((volatile USART_t*)(USART2_BASE_ADDRESS))

#endif /* USART_USART_REGISTER_H_ */

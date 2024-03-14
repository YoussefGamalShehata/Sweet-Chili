/*
 * MTIM2_5_register.h
 *
 *  Created on: Jan 30, 2024
 *      Author: Youssef Gamal
 */
#ifndef MTIM2_5_MTIM2_5_REGISTER_H_
#define MTIM2_5_MTIM2_5_REGISTER_H_

#define 	TIM2_BASE_ADDRESS			0x40000000
#define 	TIM3_BASE_ADDRESS			0x40000400
#define 	TIM4_BASE_ADDRESS			0x40000800
#define 	TIM5_BASE_ADDRESS			0x40000C00



typedef struct{
	u32		CR1;
	u32		CR2;
	u32		SMCR;
	u32		DIER;
	u32		SR;
	u32		EGR;
	u32		CCMR1;
	u32		CCMR2;
	u32		CCER;
	u32		CNT;
	u32		PSC;
	u32		ARR;
	u32		reserved1;
	u32		CCR1;
	u32		CCR2;
	u32		CCR3;
	u32		CCR4;
	u32		reserved2;
	u32		DCR;
	u32		DMAR;
	u32		OR;
}MTIM2_5_t;





#define 		MTIM2			((volatile MTIM2_5_t *)(TIM2_BASE_ADDRESS))
#define 		MTIM3			((volatile MTIM2_5_t *)(TIM3_BASE_ADDRESS))
#define 		MTIM4			((volatile MTIM2_5_t *)(TIM4_BASE_ADDRESS))
#define 		MTIM5			((volatile MTIM2_5_t *)(TIM5_BASE_ADDRESS))





#endif /* MTIM2_5_MTIM2_5_REGISTER_H_ */

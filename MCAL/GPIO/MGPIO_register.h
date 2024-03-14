/*
 * MGPIO_register.h
 *
 *  Created on: Jan 26, 2024
 *      Author: Ali Samir
 */

#ifndef MGPIO_MGPIO_REGISTER_H_
#define MGPIO_MGPIO_REGISTER_H_


#define GPIOA_BASE_ADDRESS 			0x40020000
#define GPIOB_BASE_ADDRESS 			0x40020400
#define GPIOC_BASE_ADDRESS 			0x40020800



//#define x	*((volatile u32*)(GPIOA_BASE_ADDRESS+0x00))

typedef struct
{
	u32 MODER;
	u32 OTYPER;
	u32 OSPEEDR;
	u32 PUPDR;
	u32 IDR;
	u32 ODR;
	u32 BSRR;
	u32 LCKR;
	u32 AFRL;
	u32 AFRH;
}GPIOx_t;


#define MGPIOA	((volatile GPIOx_t*)(GPIOA_BASE_ADDRESS))
#define MGPIOB	((volatile GPIOx_t*)(GPIOB_BASE_ADDRESS))
#define MGPIOC	((volatile GPIOx_t*)(GPIOC_BASE_ADDRESS))



#endif /* MGPIO_MGPIO_REGISTER_H_ */

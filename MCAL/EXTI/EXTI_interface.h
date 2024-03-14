/*
 * EXTI_interface.h
 *
 *  Created on: Jan 30, 2024
 *      Author: Mazen Musleh
 */

#ifndef EXTI_EXTI_INTERFACE_H_
#define EXTI_EXTI_INTERFACE_H_


void EXTI_voidEnableEXTI(u8 Copy_u8LineNum);

void EXTI_voidDisableEXTI(u8 Copy_u8LineNum);

void EXTI_voidSetTriggerSource(u8 Copy_u8LineNum,u8 Copy_u8TriggerSource);

void EXTI_voidSelectPort(u8 Copy_u8LineNum,u8 Copy_u8PortNum);

void EXTI0_voidSetCallBack(void (*Copy_pvCallBackFunc)(void));


typedef enum
{
	EXTI_LINE0,
	EXTI_LINE1,
	EXTI_LINE2,
	EXTI_LINE3,
	EXTI_LINE4,
	EXTI_LINE5,
	EXTI_LINE6,
	EXTI_LINE7,
	EXTI_LINE8,
	EXTI_LINE9,
	EXTI_LINE10,
	EXTI_LINE11,
	EXTI_LINE12,
	EXTI_LINE13,
	EXTI_LINE14,
	EXTI_LINE15
}EXTI_LINE_NUM_t;

#define EXTI_RISING_EDGE	0
#define EXTI_FALLING_EDGE	1
#define EXTI_ON_CHANGE		2

#define EXTI_PORTA	0
#define EXTI_PORTB	1
#define EXTI_PORTC	2



#endif /* EXTI_EXTI_INTERFACE_H_ */

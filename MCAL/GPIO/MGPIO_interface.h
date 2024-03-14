/*
 * MGPIO_interface.h
 *
 *  Created on: Jan 26, 2024
 *      Author: Ali Samir
 */

#ifndef MGPIO_MGPIO_INTERFACE_H_
#define MGPIO_MGPIO_INTERFACE_H_



#define MGPIO_u8LOW		0
#define MGPIO_u8HIGH	1

/* PORT selection */
#define MGPIOA_u8PORT	0
#define MGPIOB_u8PORT	1
#define MGPIOC_u8PORT	2

/* Mode Selection */
#define MGPIO_u8INPUT		0b00
#define MGPIO_u8OUTPUT		0b01
#define MGPIO_u8ALTFUNC		0b10
#define MGPIO_u8ANALOG		0b11

/* Output options */
#define MGPIO_u8PUSH_PULL	0
#define MGPIO_u8OPENDRAIN	1

/* Output Speed Selection*/
#define MGPIO_u8LOW_SPEED			0b00
#define MGPIO_u8MEDIUM_SPEED		0b01
#define MGPIO_u8HIGH_SPEED			0b10
#define MGPIO_u8VERYHIGH_SPEED		0b11

/* Input options */
#define MGPIO_u8NOPP				0b00
#define MGPIO_u8PULLUP				0b01
#define MGPIO_u8PULLDOWN			0b10

#define MGPIO_u8AF0					0
#define MGPIO_u8AF1					1
#define MGPIO_u8AF2					2
#define MGPIO_u8AF3					3
#define MGPIO_u8AF4					4
#define MGPIO_u8AF5					5
#define MGPIO_u8AF6					6
#define MGPIO_u8AF7					7
#define MGPIO_u8AF8					8
#define MGPIO_u8AF9					9
#define MGPIO_u8AF10				10
#define MGPIO_u8AF11				11
#define MGPIO_u8AF12				12
#define MGPIO_u8AF13				13
#define MGPIO_u8AF14				14
#define MGPIO_u8AF15				15



void MGPIO_voidSetPinMode(u8 Copy_u8Port,u8 Copy_u8Pin,u8 Copy_u8Mode);

void MGPIO_voidSetOutputType(u8 Copy_u8Port,u8 Copy_u8Pin,u8 Copy_u8Type);

void MGPIO_voidSetOutputSpeed(u8 Copy_u8Port,u8 Copy_u8Pin,u8 Copy_u8Speed);

void MGPIO_voidSetPull(u8 Copy_u8Port,u8 Copy_u8Pin,u8 Copy_u8PullType);

u8 MGPIO_u8GetPinValue(u8 Copy_u8Port,u8 Copy_u8Pin);

void MGPIO_voidSetPinValue(u8 Copy_u8Port,u8 Copy_u8Pin,u8 Copy_u8Value);

void MGPIO_voidSetPortValue(u8 Copy_u8Port,u16 Copy_u8Value);

void MGPIO_voidDirectSetReset(u8 Copy_u8Port,u8 Copy_u8Pin,u8 Copy_u8Value);

void MGPIO_voidSetAltFunc(u8 Copy_u8Port,u8 Copy_u8Pin,u8 Copy_u8AltValue);

#endif /* MGPIO_MGPIO_INTERFACE_H_ */

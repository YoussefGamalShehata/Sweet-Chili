/*
 * MNVIC_interface.h
 *
 *  Created on: Jan 29, 2024
 *      Author: Hesham Tayel & Amira Magdy
 */

#ifndef MNVIC_MNVIC_INTERFACE_H_
#define MNVIC_MNVIC_INTERFACE_H_

typedef enum
{
	MNVIC_GROUPMODE_G16S0 = 3,
	MNVIC_GROUPMODE_G8S2 	,
	MNVIC_GROUPMODE_G4S4 	,
	MNVIC_GROUPMODE_G2S8 	,
	MNVIC_GROUPMODE_G0S16
}MNVIC_GROUPMODE_t;



void MNVIC_voidEnableInterrupt(u8 Copy_u8IntPosition);

void MNVIC_voidDisableInterrupt(u8 Copy_u8IntPosition);

void MNVIC_voidSetInterruptGroupMode(MNVIC_GROUPMODE_t Copy_uddGroupMode);

void MNVIC_voidSetInterruptPeriority(u8 Copy_u8IntPosition,u8 Copy_u8Group, u8 Copy_u8SubGroup, MNVIC_GROUPMODE_t Copy_uddGroupMode);

void MNVIC_voidEnableInterruptPending(u8 Copy_u8IntPosition);

void MNVIC_voidDisableInterruptPending(u8 Copy_u8IntPosition);

u8 MNVIC_u8IsInterruptActive(u8 Copy_u8IntPosition);



#endif /* MNVIC_MNVIC_INTERFACE_H_ */

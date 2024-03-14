/*
 * MNVIC_program.c
 *
 *  Created on: Jan 29, 2024
 *      Author: Hesham Tayel & Amira Magdy
 */


#include "../LIB/BIT_MATH.h"
#include "../LIB/STD_TYPES.h"

#include "MNVIC_interface.h"
#include "MNVIC_register.h"
#include "MNVIC_config.h"
#include "MNVIC_private.h"

/**
 * @brief Enables the interrupt at the specified position.
 * 
 * This function enables the interrupt at the given position by setting the corresponding bit in the appropriate register.
 * 
 * @param Copy_u8IntPosition The position of the interrupt to be enabled.
 */
void MNVIC_voidEnableInterrupt(u8 Copy_u8IntPosition)
{					/* REGISTER Number*/					/*BIT*/
	MNVIC_REG->ISER[Copy_u8IntPosition/32] = (1<<(Copy_u8IntPosition%32));
}
/**
 * @brief Disables the interrupt at the specified position.
 * 
 * This function disables the interrupt at the given position by clearing the corresponding bit in the appropriate register.
 * 
 * @param Copy_u8IntPosition The position of the interrupt to be disabled.
 */
void MNVIC_voidDisableInterrupt(u8 Copy_u8IntPosition)
{																/*no of bits*/
	MNVIC_REG->ICER[Copy_u8IntPosition/32] = (1<<(Copy_u8IntPosition%32));
}

/**
 * @brief Sets the interrupt group mode.
 * 
 * This function sets the interrupt group mode by configuring the appropriate bits in the AIRCR register.
 * 
 * @param Copy_uddGroupMode The interrupt group mode to be set.
 */
void MNVIC_voidSetInterruptGroupMode(MNVIC_GROUPMODE_t Copy_uddGroupMode)
{
	/* Enabling VECTKEY => by writing 0x5FA */
	MSCB_AIRCR = MNVIC_VECTKEY;
	MSCB_AIRCR |= MNVIC_VECTKEY | (Copy_uddGroupMode<<8);
}

/**
 * @brief Sets the interrupt priority for the specified interrupt.
 * 
 * This function sets the priority for the specified interrupt based on the provided group mode, group, and sub-group.
 * 
 * @param Copy_u8IntPosition The position of the interrupt.
 * @param Copy_u8Group The priority group.
 * @param Copy_u8SubGroup The priority sub-group.
 * @param Copy_uddGroupMode The interrupt group mode.
 */
void MNVIC_voidSetInterruptPeriority(u8 Copy_u8IntPosition,u8 Copy_u8Group, u8 Copy_u8SubGroup, MNVIC_GROUPMODE_t Copy_uddGroupMode)
{
	u8 Local_u8PriValue=0;
	switch(Copy_uddGroupMode)
	{
	case MNVIC_GROUPMODE_G16S0:	Local_u8PriValue = Copy_u8Group; break;
	case MNVIC_GROUPMODE_G8S2 : Local_u8PriValue = (Copy_u8Group<<1) | Copy_u8SubGroup; break;
	case MNVIC_GROUPMODE_G4S4 : Local_u8PriValue = (Copy_u8Group<<2) | Copy_u8SubGroup; break;
	case MNVIC_GROUPMODE_G2S8 : Local_u8PriValue = (Copy_u8Group<<3) | Copy_u8SubGroup; break;
	case MNVIC_GROUPMODE_G0S16:	Local_u8PriValue = Copy_u8Group; break;
	}
	MNVIC_REG->IPR[Copy_u8IntPosition] = (Local_u8PriValue<<4);						/*no of bytes*/
	//MNVIC_REG->IPR[Copy_u8IntPosition/32] = ((Local_u8PriValue<<4)<<(Copy_u8IntPosition%4));
}

/**
 * @brief Enables interrupt pending for the specified interrupt.
 * 
 * This function enables interrupt pending for the specified interrupt by setting the corresponding bit in the appropriate register.
 * 
 * @param Copy_u8IntPosition The position of the interrupt.
 */
void MNVIC_voidEnableInterruptPending(u8 Copy_u8IntPosition)
{
	MNVIC_REG->ISPR[Copy_u8IntPosition/32] = (1<<(Copy_u8IntPosition%32));
}

/**
 * @brief Disables interrupt pending for the specified interrupt.
 * 
 * This function disables interrupt pending for the specified interrupt by clearing the corresponding bit in the appropriate register.
 * 
 * @param Copy_u8IntPosition The position of the interrupt.
 */
void MNVIC_voidDisableInterruptPending(u8 Copy_u8IntPosition)
{
	MNVIC_REG->ICPR[Copy_u8IntPosition/32] = (1<<(Copy_u8IntPosition%32));
}

/**
 * @brief Checks if the interrupt at the specified position is active.
 * 
 * This function checks whether the interrupt at the specified position is active.
 * 
 * @param Copy_u8IntPosition The position of the interrupt.
 * @return 1 if the interrupt is active, 0 otherwise.
 */
u8 MNVIC_u8IsInterruptActive(u8 Copy_u8IntPosition)
{
	return GET_BIT( MNVIC_REG->IABR[Copy_u8IntPosition/32] , (Copy_u8IntPosition%32));
}

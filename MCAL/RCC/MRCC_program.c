/*
 * MRCC_program.c
 *
 *  Created on: Jan 25, 2024
 *      Author: Amira Magdy
 */
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

#include "MRCC_interface.h"
#include "MRCC_register.h"
#include "MRCC_config.h"
#include "MRCC_private.h"




/**
 * @brief Initialize the system clock according to the configured source (HSI, HSE, or PLL).
 * @note This function should be called at the beginning of the program to set up the system clock.
 * @retval Returns void.
 */
void MRCC_voidInitSystemCLK(void)
{
    #if MRCC_CLKSRC == HSI
        /* Enable HSI */
        SET_BIT(RCC_CR, 0);
        /* Select the HSI for the System */
        CLR_BIT(RCC_CFGR, 0);
        CLR_BIT(RCC_CFGR, 1);
    #elif MRCC_CLKSRC == HSE
        #if MRCC_HSE_SRC == HSE_CRYSTAL
            /* Enable HSE */
            SET_BIT(RCC_CR, 16);
            /* Disable the bypass */
            CLR_BIT(RCC_CR, 18);
            /* Select the HSI for the System */
            SET_BIT(RCC_CFGR, 0);
            CLR_BIT(RCC_CFGR, 1);
        #elif MRCC_HSE_SRC == HSE_BYPASS
            /* Enable HSE */
            SET_BIT(RCC_CR, 16);
            /* Enable the bypass */
            SET_BIT(RCC_CR, 18);
            /* Select the HSI for the System */
            SET_BIT(RCC_CFGR, 0);
            CLR_BIT(RCC_CFGR, 1);
        #endif
    #elif MRCC_CLKSRC == PLL
        /* TO DO: Configure PLL */
    #else
        #error "Invalid Clock Source..."
    #endif
}

/**
 * @brief Enable clock for a specific peripheral.
 * @param Copy_u8BusID: Bus name (AHB1, AHB2, APB1, or APB2).
 * @param Copy_u8PerNum: Peripheral number to enable clock for.
 * @retval Returns void.
 */
void MRCC_voidEnablePeripheralCLK(BusName_t Copy_u8BusID, u8 Copy_u8PerNum)
{
    switch (Copy_u8BusID)
    {
    case AHB1:
        SET_BIT(RCC_AHB1ENR, Copy_u8PerNum);
        break;
    case AHB2:
        SET_BIT(RCC_AHB2ENR, Copy_u8PerNum);
        break;
    case APB1:
        SET_BIT(RCC_APB1ENR, Copy_u8PerNum);
        break;
    case APB2:
        SET_BIT(RCC_APB2ENR, Copy_u8PerNum);
        break;
    }
}

/**
 * @brief Disable clock for a specific peripheral.
 * @param Copy_u8BusID: Bus name (AHB1, AHB2, APB1, or APB2).
 * @param Copy_u8PerNum: Peripheral number to disable clock for.
 * @retval Returns void.
 */
void MRCC_voidDisablePeripheralCLK(BusName_t Copy_u8BusID, u8 Copy_u8PerNum)
{
    switch (Copy_u8BusID)
    {
    case AHB1:
        CLR_BIT(RCC_AHB1ENR, Copy_u8PerNum);
        break;
    case AHB2:
        CLR_BIT(RCC_AHB2ENR, Copy_u8PerNum);
        break;
    case APB1:
        CLR_BIT(RCC_APB1ENR, Copy_u8PerNum);
        break;
    case APB2:
        CLR_BIT(RCC_APB2ENR, Copy_u8PerNum);
        break;
    }
}
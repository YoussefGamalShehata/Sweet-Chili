/*
 * MGPIO_program.c
 *
 *  Created on: Jan 26, 2024
 *      Author: Ali Samir
 */

#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

#include "MGPIO_register.h"
#include "MGPIO_private.h"
#include "MGPIO_config.h"
#include "MGPIO_interface.h"



/**
 * @brief Set the mode of a specific GPIO pin.
 * @param Copy_u8Port: GPIO port number (MGPIOA_u8PORT, MGPIOB_u8PORT, or MGPIOC_u8PORT).
 * @param Copy_u8Pin: GPIO pin number (0 to 15).
 * @param Copy_u8Mode: GPIO pin mode (MGPIO_u8INPUT, MGPIO_u8OUTPUT, MGPIO_u8ALTFUNC, or MGPIO_u8ANALOG).
 * @retval Returns void.
 */
void MGPIO_voidSetPinMode(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Mode)
{
    switch (Copy_u8Port)
    {
    case MGPIOA_u8PORT:
        MGPIOA->MODER &= ~((0b11) << (Copy_u8Pin * 2));
        MGPIOA->MODER |= Copy_u8Mode << (Copy_u8Pin * 2);
        break;
    case MGPIOB_u8PORT:
        MGPIOB->MODER &= ~((0b11) << (Copy_u8Pin * 2));
        MGPIOB->MODER |= Copy_u8Mode << (Copy_u8Pin * 2);
        break;
    case MGPIOC_u8PORT:
        MGPIOC->MODER &= ~((0b11) << (Copy_u8Pin * 2));
        MGPIOC->MODER |= Copy_u8Mode << (Copy_u8Pin * 2);
        break;
    }
}

/**
 * @brief Set the output type of a specific GPIO pin.
 * @param Copy_u8Port: GPIO port number (MGPIOA_u8PORT, MGPIOB_u8PORT, or MGPIOC_u8PORT).
 * @param Copy_u8Pin: GPIO pin number (0 to 15).
 * @param Copy_u8Type: Output type (MGPIO_u8PUSHPULL or MGPIO_u8OPENDRAIN).
 * @retval Returns void.
 */
void MGPIO_voidSetOutputType(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Type)
{
    switch (Copy_u8Port)
    {
    case MGPIOA_u8PORT:
        MGPIOA->OTYPER &= ~(1 << Copy_u8Pin);
        MGPIOA->OTYPER |= (Copy_u8Type << Copy_u8Pin);
        break;
    case MGPIOB_u8PORT:
        MGPIOB->OTYPER &= ~(1 << Copy_u8Pin);
        MGPIOB->OTYPER |= (Copy_u8Type << Copy_u8Pin);
        break;
    case MGPIOC_u8PORT:
        MGPIOC->OTYPER &= ~(1 << Copy_u8Pin);
        MGPIOC->OTYPER |= (Copy_u8Type << Copy_u8Pin);
        break;
    }
}

/**
 * @brief Set the output speed of a specific GPIO pin.
 * @param Copy_u8Port: GPIO port number (MGPIOA_u8PORT, MGPIOB_u8PORT, or MGPIOC_u8PORT).
 * @param Copy_u8Pin: GPIO pin number (0 to 15).
 * @param Copy_u8Speed: Output speed (MGPIO_u8LOW_SPEED, MGPIO_u8MEDIUM_SPEED, or MGPIO_u8HIGH_SPEED).
 * @retval Returns void.
 */
void MGPIO_voidSetOutputSpeed(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Speed)
{
    switch (Copy_u8Port)
    {
    case MGPIOA_u8PORT:
        MGPIOA->OSPEEDR &= ~((0b11) << (Copy_u8Pin * 2));
        MGPIOA->OSPEEDR |= Copy_u8Speed << (Copy_u8Pin * 2);
        break;
    case MGPIOB_u8PORT:
        MGPIOB->OSPEEDR &= ~((0b11) << (Copy_u8Pin * 2));
        MGPIOB->OSPEEDR |= Copy_u8Speed << (Copy_u8Pin * 2);
        break;
    case MGPIOC_u8PORT:
        MGPIOC->OSPEEDR &= ~((0b11) << (Copy_u8Pin * 2));
        MGPIOC->OSPEEDR |= Copy_u8Speed << (Copy_u8Pin * 2);
        break;
    }
}

/**
 * @brief Set the pull-up/pull-down configuration of a specific GPIO pin.
 * @param Copy_u8Port: GPIO port number (MGPIOA_u8PORT, MGPIOB_u8PORT, or MGPIOC_u8PORT).
 * @param Copy_u8Pin: GPIO pin number (0 to 15).
 * @param Copy_u8PullType: Pull-up/pull-down type (MGPIO_u8PULLUP, MGPIO_u8PULLDOWN, or MGPIO_u8NOPULL).
 * @retval Returns void.
 */
void MGPIO_voidSetPull(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8PullType)
{
    switch (Copy_u8Port)
    {
    case MGPIOA_u8PORT:
        MGPIOA->PUPDR &= ~((0b11) << (Copy_u8Pin * 2));
        MGPIOA->PUPDR |= Copy_u8PullType << (Copy_u8Pin * 2);
        break;
    case MGPIOB_u8PORT:
        MGPIOB->PUPDR &= ~((0b11) << (Copy_u8Pin * 2));
        MGPIOB->PUPDR |= Copy_u8PullType << (Copy_u8Pin * 2);
        break;
    case MGPIOC_u8PORT:
        MGPIOC->PUPDR &= ~((0b11) << (Copy_u8Pin * 2));
        MGPIOC->PUPDR |= Copy_u8PullType << (Copy_u8Pin * 2);
        break;
    }
}

/**
 * @brief Get the value of a specific GPIO pin.
 * @param Copy_u8Port: GPIO port number (MGPIOA_u8PORT, MGPIOB_u8PORT, or MGPIOC_u8PORT).
 * @param Copy_u8Pin: GPIO pin number (0 to 15).
 * @retval Returns the value of the specified pin (MGPIO_u8LOW or MGPIO_u8HIGH).
 */
u8 MGPIO_u8GetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin)
{
    u8 Local_u8PinVal;
    switch (Copy_u8Port)
    {
    case MGPIOA_u8PORT:
        Local_u8PinVal = GET_BIT(MGPIOA->IDR, Copy_u8Pin);
        break;
    case MGPIOB_u8PORT:
        Local_u8PinVal = GET_BIT(MGPIOB->IDR, Copy_u8Pin);
        break;
    case MGPIOC_u8PORT:
        Local_u8PinVal = GET_BIT(MGPIOC->IDR, Copy_u8Pin);
        break;
    }
    return Local_u8PinVal;
}

/**
 * @brief Set the value of a specific GPIO pin.
 * @param Copy_u8Port: GPIO port number (MGPIOA_u8PORT, MGPIOB_u8PORT, or MGPIOC_u8PORT).
 * @param Copy_u8Pin: GPIO pin number (0 to 15).
 * @param Copy_u8Value: Value to be set (MGPIO_u8LOW or MGPIO_u8HIGH).
 * @retval Returns void.
 */
void MGPIO_voidSetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Value)
{
    if (Copy_u8Value == MGPIO_u8LOW)
    {
        switch (Copy_u8Port)
        {
        case MGPIOA_u8PORT:
            CLR_BIT(MGPIOA->ODR, Copy_u8Pin);
            break;
        case MGPIOB_u8PORT:
            CLR_BIT(MGPIOB->ODR, Copy_u8Pin);
            break;
        case MGPIOC_u8PORT:
            CLR_BIT(MGPIOC->ODR, Copy_u8Pin);
            break;
        }
    }
    else if (Copy_u8Value == MGPIO_u8HIGH)
    {
        switch (Copy_u8Port)
        {
        case MGPIOA_u8PORT:
            SET_BIT(MGPIOA->ODR, Copy_u8Pin);
            break;
        case MGPIOB_u8PORT:
            SET_BIT(MGPIOB->ODR, Copy_u8Pin);
            break;
        case MGPIOC_u8PORT:
            SET_BIT(MGPIOC->ODR, Copy_u8Pin);
            break;
        }
    }
}

/**
 * @brief Set the value of a specific GPIO port.
 * @param Copy_u8Port: GPIO port number (MGPIOA_u8PORT, MGPIOB_u8PORT, or MGPIOC_u8PORT).
 * @param Copy_u8Value: Value to be set (0 to 65535).
 * @retval Returns void.
 */
void MGPIO_voidSetPortValue(u8 Copy_u8Port, u16 Copy_u8Value)
{
    switch (Copy_u8Port)
    {
    case MGPIOA_u8PORT:
        MGPIOA->ODR = Copy_u8Value;
        break;
    case MGPIOB_u8PORT:
        MGPIOB->ODR = Copy_u8Value;
        break;
    case MGPIOC_u8PORT:
        MGPIOC->ODR = Copy_u8Value;
        break;
    }
}

/**
 * @brief Set or reset a specific GPIO pin directly.
 * @param Copy_u8Port: GPIO port number (MGPIOA_u8PORT, MGPIOB_u8PORT, or MGPIOC_u8PORT).
 * @param Copy_u8Pin: GPIO pin number (0 to 15).
 * @param Copy_u8Value: Value to be set (MGPIO_u8HIGH or MGPIO_u8LOW).
 * @retval Returns void.
 */
void MGPIO_voidDirectSetReset(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Value)
{
    if (Copy_u8Value == MGPIO_u8HIGH)
    {
        switch (Copy_u8Port)
        {
        case MGPIOA_u8PORT:
            MGPIOA->BSRR = 1 << Copy_u8Pin;
            break;
        case MGPIOB_u8PORT:
            MGPIOB->BSRR = 1 << Copy_u8Pin;
            break;
        case MGPIOC_u8PORT:
            MGPIOC->BSRR = 1 << Copy_u8Pin;
            break;
        }
    }
    else if (Copy_u8Value == MGPIO_u8LOW)
    {
        Copy_u8Pin += 16;
        switch (Copy_u8Port)
        {
        case MGPIOA_u8PORT:
            MGPIOA->BSRR = 1 << Copy_u8Pin;
            break;
        case MGPIOB_u8PORT:
            MGPIOB->BSRR = 1 << Copy_u8Pin;
            break;
        case MGPIOC_u8PORT:
            MGPIOC->BSRR = 1 << Copy_u8Pin;
            break;
        }
    }
}

/**
 * @brief Set the alternate function for a specific GPIO pin.
 * @param Copy_u8Port: GPIO port number (MGPIOA_u8PORT, MGPIOB_u8PORT, or MGPIOC_u8PORT).
 * @param Copy_u8Pin: GPIO pin number (0 to 15).
 * @param Copy_u8AltValue: Alternate function value (0 to 15).
 * @retval Returns void.
 */
void MGPIO_voidSetAltFunc(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8AltValue)
{
    if (Copy_u8Pin < 8)
    {
        switch (Copy_u8Port)
        {
        case MGPIOA_u8PORT:
            MGPIOA->AFRL &= ~((0b1111) << (Copy_u8Pin * 4));
            MGPIOA->AFRL |= Copy_u8AltValue << (Copy_u8Pin * 4);
            break;
        case MGPIOB_u8PORT:
            MGPIOB->AFRL &= ~((0b1111) << (Copy_u8Pin * 4));
            MGPIOB->AFRL |= Copy_u8AltValue << (Copy_u8Pin * 4);
            break;
        case MGPIOC_u8PORT:
            MGPIOC->AFRL &= ~((0b1111) << (Copy_u8Pin * 4));
            MGPIOC->AFRL |= Copy_u8AltValue << (Copy_u8Pin * 4);
            break;
        }
    }
    else if (Copy_u8Pin >= 8)
    {
        Copy_u8Pin -= 8;
        switch (Copy_u8Port)
        {
        case MGPIOA_u8PORT:
            MGPIOA->AFRH &= ~((0b1111) << (Copy_u8Pin * 4));
            MGPIOA->AFRH |= Copy_u8AltValue << (Copy_u8Pin * 4);
            break;
        case MGPIOB_u8PORT:
            MGPIOB->AFRH &= ~((0b1111) << (Copy_u8Pin * 4));
            MGPIOB->AFRH |= Copy_u8AltValue << (Copy_u8Pin * 4);
            break;
        case MGPIOC_u8PORT:
            MGPIOC->AFRH &= ~((0b1111) << (Copy_u8Pin * 4));
            MGPIOC->AFRH |= Copy_u8AltValue << (Copy_u8Pin * 4);
            break;
        }
    }
}



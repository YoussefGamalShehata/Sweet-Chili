/*
 * STK_program.c
 *
 *  Created on: Jan 27, 2024
 *      Author: Hesham Tayel
 */
#include "../LIB/BIT_MATH.h"
#include "../LIB/STD_TYPES.h"

#include "STK_register.h"
#include "STK_config.h"
#include "STK_private.h"
#include "STK_interface.h"


static void(*STK_pvCallBackFunc)(void) = NULL;

static u8 Periodic_Flag = 0;


/**
 * @brief Initialize the SysTick timer.
 * @note This function configures the SysTick timer according to the configured clock source.
 * @retval Returns void.
 */
void STK_voidInit(void)
{
#if STK_CLOCK_SOURCE == STK_AHB
    SET_BIT(STK->CTRL, 2);
#elif STK_CLOCK_SOURCE == STK_AHB_DIV_8
    CLR_BIT(STK->CTRL, 2);
#endif
}

/**
 * @brief Start the SysTick timer with a specified load value.
 * @param Copy_u32LoadValue: The value to load into the SysTick timer.
 * @retval Returns void.
 */
void STK_voidStartTimer(u32 Copy_u32LoadValue)
{
    /* Load value into LOAD register */
    STK->LOAD = Copy_u32LoadValue;

    /* Start Timer */
    SET_BIT(STK->CTRL, 0);
}

/**
 * @brief Stop the SysTick timer.
 * @retval Returns void.
 */
void STK_voidStopTimer()
{
    CLR_BIT(STK->CTRL, 0);
}

/**
 * @brief Wait for a specified number of ticks using busy waiting.
 * @param Copy_u32TicksNum: Number of ticks to wait for.
 * @retval Returns void.
 */
void STK_voidSetBusyWait(u32 Copy_u32TicksNum)
{
    /* Reset Timer */
    STK->VAL = 0;

    /* Load value into LOAD register */
    STK->LOAD = Copy_u32TicksNum;

    /* Start Timer */
    SET_BIT(STK->CTRL, 0);

    /* Wait until flag is high */
    while (GET_BIT(STK->CTRL, 16) != 1)
    {
        asm("NOP");
    }

    /* Stop Timer */
    CLR_BIT(STK->CTRL, 0);
}

/**
 * @brief Set an interval for a single SysTick interrupt.
 * @param Copy_u32TicksNum: Number of ticks before the interrupt occurs.
 * @param Copy_pvCallBackFunc: Pointer to the callback function to be called upon interrupt.
 * @retval Returns void.
 */
void STK_voidSetInterval_Single(u32 Copy_u32TicksNum, void (*Copy_pvCallBackFunc)(void))
{
    /* Set Callback */
    STK_pvCallBackFunc = Copy_pvCallBackFunc;

    /* Enable Interrupt */
    SET_BIT(STK->CTRL, 1);

    /* Clear the SW flag */
    Periodic_Flag = 0;

    /* Reset Timer */
    STK->VAL = 0;

    /* Load value into LOAD register */
    STK->LOAD = Copy_u32TicksNum;

    /* Start Timer */
    SET_BIT(STK->CTRL, 0);
}

/**
 * @brief Set an interval for periodic SysTick interrupts.
 * @param Copy_u32TicksNum: Number of ticks before each interrupt occurrence.
 * @param Copy_pvCallBackFunc: Pointer to the callback function to be called upon interrupt.
 * @retval Returns void.
 */
void STK_voidSetInterval_Periodic(u32 Copy_u32TicksNum, void (*Copy_pvCallBackFunc)(void))
{
    CLR_BIT(STK->CTRL, 0);

    /* Set Callback */
    STK_pvCallBackFunc = Copy_pvCallBackFunc;

    /* Enable Interrupt */
    SET_BIT(STK->CTRL, 1);

    /* Set the SW flag */
    Periodic_Flag = 1;

    /* Reset Timer */
    STK->VAL = 0;

    /* Load value into LOAD register */
    STK->LOAD = Copy_u32TicksNum;

    /* Start Timer */
    SET_BIT(STK->CTRL, 0);
}

/**
 * @brief Get the elapsed time since the last SysTick timer start.
 * @retval Returns the elapsed time in ticks.
 */
u32 STK_u32GetElapsedTime(void)
{
    return ((STK->LOAD) - (STK->VAL));
}

/**
 * @brief Get the remaining time before the next SysTick timer interrupt.
 * @retval Returns the remaining time in ticks.
 */
u32 STK_u32GetRemainingTime(void)
{
    return STK->VAL;
}

/**
 * @brief SysTick interrupt handler function.
 * @note This function is called automatically upon SysTick interrupt.
 * @retval Returns void.
 */
void SysTick_Handler(void)
{
    if (STK_pvCallBackFunc != NULL)
    {
        STK_pvCallBackFunc();
    }
    /* Clear SysTick Flag */
    GET_BIT(STK->CTRL, 16);

    /* Check if it comes from single */
    if (Periodic_Flag == 0)
    {
        /* Stop Timer */
        CLR_BIT(STK->CTRL, 0);
    }
}
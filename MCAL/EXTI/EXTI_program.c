/*
 * EXTI_program.c
 *
 *  Created on: Jan 30, 2024
 *      Author: Mazen Musleh
 */

#include "../LIB/BIT_MATH.h"
#include "../LIB/STD_TYPES.h"

#include "EXTI_register.h"
#include "EXTI_config.h"
#include "EXTI_private.h"
#include "EXTI_interface.h"

/* Private function pointer for EXTI0 callback */
static void (*EXTI0_pvCallBackFunc)(void) = NULL;

/**
 * @brief Enable EXTI for a specified line.
 * @param Copy_u8LineNum: EXTI line number to enable.
 * @retval Returns void.
 */
void EXTI_voidEnableEXTI(u8 Copy_u8LineNum)
{
    SET_BIT(EXTI->IMR, Copy_u8LineNum);
}

/**
 * @brief Disable EXTI for a specified line.
 * @param Copy_u8LineNum: EXTI line number to disable.
 * @retval Returns void.
 */
void EXTI_voidDisableEXTI(u8 Copy_u8LineNum)
{
    CLR_BIT(EXTI->IMR, Copy_u8LineNum);
}

/**
 * @brief Set the trigger source for a specified EXTI line.
 * @param Copy_u8LineNum: EXTI line number to configure.
 * @param Copy_u8TriggerSource: Trigger source for the EXTI line (RISING_EDGE, FALLING_EDGE, or ON_CHANGE).
 * @retval Returns void.
 */
void EXTI_voidSetTriggerSource(u8 Copy_u8LineNum, u8 Copy_u8TriggerSource)
{
    switch (Copy_u8TriggerSource)
    {
    case EXTI_RISING_EDGE:
        SET_BIT(EXTI->RTSR, Copy_u8LineNum);
        CLR_BIT(EXTI->FTSR, Copy_u8LineNum);
        break;
    case EXTI_FALLING_EDGE:
        SET_BIT(EXTI->FTSR, Copy_u8LineNum);
        CLR_BIT(EXTI->RTSR, Copy_u8LineNum);
        break;
    case EXTI_ON_CHANGE:
        SET_BIT(EXTI->RTSR, Copy_u8LineNum);
        SET_BIT(EXTI->FTSR, Copy_u8LineNum);
        break;
    }
}

/**
 * @brief Select the port for a specified EXTI line.
 * @param Copy_u8LineNum: EXTI line number to configure.
 * @param Copy_u8PortNum: Port number to select (0 to 15).
 * @retval Returns void.
 */
void EXTI_voidSelectPort(u8 Copy_u8LineNum, u8 Copy_u8PortNum)
{
    /* TO DO... */
    /* for EXTI0,1,2,3 */
    SYSCFG_EXTICR1 &= ~(0x0000000F << (Copy_u8LineNum * 4));
    SYSCFG_EXTICR1 |= (Copy_u8PortNum << (Copy_u8LineNum * 4));
}

/**
 * @brief Set the callback function for EXTI0.
 * @param Copy_pvCallBackFunc: Pointer to the callback function.
 * @retval Returns void.
 */
void EXTI0_voidSetCallBack(void (*Copy_pvCallBackFunc)(void))
{
    EXTI0_pvCallBackFunc = Copy_pvCallBackFunc;
}

/**
 * @brief EXTI0 interrupt handler.
 * @retval Returns void.
 */
void EXTI0_IRQHandler(void)
{
    if (EXTI0_pvCallBackFunc != NULL)
    {
        EXTI0_pvCallBackFunc();
    }
    SET_BIT(EXTI->PR, 0);
}
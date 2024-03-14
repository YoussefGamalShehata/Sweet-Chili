/*
 * ENCODER_program.c
 *
 *  Created on: Feb 20, 2024
 *      Author: Mazen Musleh
 */
#include "../LIB/BIT_MATH.h"
#include "../LIB/STD_TYPES.h"

#include "../MRCC/MRCC_interface.h"
#include "../MNVIC/MNVIC_interface.h"
#include "../EXTI/EXTI_interface.h"
#include "../MGPIO/MGPIO_interface.h"
#include "../STK/STK_interface.h"
#include "../STK/STK_register.h"
#include "../USART/USART_interface.h"

#include "ENCODER_interface.h"



volatile u32 pulse_count=0;
volatile u16 counter=0;
volatile u32 speed=0;
volatile u32 totaldistance=0;
volatile u32 distance=0;



/**
 * @brief This function initializes the encoder module.
 * @retval Returns void.
 */
void ENCODER_voidInit(void)
{
    /* Set pin mode for encoder input */
    MGPIO_voidSetPinMode(MGPIOA_u8PORT, 0, MGPIO_u8INPUT);

    /* Set pin mode for LED output */
    MGPIO_voidSetPinMode(MGPIOA_u8PORT, 8, MGPIO_u8OUTPUT);
    MGPIO_voidSetPull(MGPIOA_u8PORT, 8, MGPIO_u8NOPP);

    /* Set pin mode for another pin */
    MGPIO_voidSetPinMode(MGPIOA_u8PORT, 12, MGPIO_u8OUTPUT);
    MGPIO_voidSetPull(MGPIOA_u8PORT, 12, MGPIO_u8NOPP);

    /* Initialize SysTick timer */
    STK_voidInit();
    STK_voidSetInterval_Periodic(2000000UL, STK_isr);

    /* Enable interrupt for encoder */
    MNVIC_voidEnableInterrupt(6);

    /* Enable EXTI for pin 0 */
    EXTI_voidEnableEXTI(EXTI_LINE0);
    EXTI0_voidSetCallBack(encoder_isr);
    EXTI_voidSelectPort(EXTI_LINE0, EXTI_PORTA);
    EXTI_voidSetTriggerSource(EXTI_LINE0, EXTI_RISING_EDGE);
}

/**
 * @brief Interrupt service routine for SysTick timer.
 * @retval Returns void.
 */
void STK_isr(void)
{
    /* Update speed and reset pulse count */
    speed = distance;
    totaldistance += distance;
    pulse_count = 0;
}

/**
 * @brief Interrupt service routine for encoder input.
 * @retval Returns void.
 */
void encoder_isr(void)
{
    /* Increment pulse count */
    pulse_count++;

    /* Get distance */
    distance = ENCODER_u64GetDistance();

    /* Toggle LED */
    if (MGPIO_u8GetPinValue(MGPIOA_u8PORT, 8) == 1)
    {
        MGPIO_voidSetPinValue(MGPIOA_u8PORT, 8, 0);
    }
    else
    {
        MGPIO_voidSetPinValue(MGPIOA_u8PORT, 8, 1);
    }
}

/**
 * @brief Get distance calculated from pulse count.
 * @retval Returns the calculated distance.
 */
u32 ENCODER_u64GetDistance(void)
{
    return ((pulse_count / ENCODER_PULSES_PER_REVOLUTION) * WHEEL_CIRCUMFERENCE_MM);
}

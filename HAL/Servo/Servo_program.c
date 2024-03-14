/*
 * Servo_program.c
 *
 *  Created on: Feb 23, 2024
 *      Author: Youssef Gamal
 */
#include"../LIB/STD_TYPES.h"
#include"../LIB/BIT_MATH.h"
#include"../MGPIO/MGPIO_interface.h"
#include"../MTIM2_5/MTIM2_5_interface.h"
#include"../MTIM2_5/MTIM2_5_register.h"
#include"../MRCC/MRCC_interface.h"


/**
 * @brief Initialize the timer for servo control.
 * @note This function configures Timer 2 to generate PWM signals for servo control.
 * @retval Returns void.
 */
void TIMER_voidServoTimerInit(void)
{
    // Configure GPIO pin for alternate function mode
    MGPIO_voidSetPinMode(MGPIOA_u8PORT, 5, MGPIO_u8ALTFUNC);
    MGPIO_voidSetOutputType(MGPIOA_u8PORT, 5, MGPIO_u8PUSH_PULL);
    MGPIO_voidSetPull(MGPIOA_u8PORT, 5, MGPIO_u8NOPP);
    MGPIO_voidSetAltFunc(MGPIOA_u8PORT, 5, MGPIO_u8AF1);

    // Reset Timer 2 control register 1
    MTIM2->CR1 = 0;

    // Configure Timer 2 for servo control
    MTIM2->PSC = 16 - 1;            // Set the prescaler
    MTIM2->ARR = 20000 - 1;          // Set the period

    // Configure channel 1 for PWM output
    MTIM2->CCMR1 &= ~((3 << 4) | (1 << 3));  // Clear bits 4:3 (OC1M) and bit 3 (OC1PE)
    MTIM2->CCMR1 |= (6 << 4);                 // PWM mode 1
    MTIM2->CCMR1 |= (1 << 3);                 // Enable OC1 preload

    // Enable capture/compare CH1 output
    MTIM2->CCER |= (1 << 0);                  // CC1E bit (bit 0) set to 1

    // Start the timer
    MTIM2->CR1 |= (1 << 0);                   // CEN bit (bit 0) set to 1
}

/**
 * @brief Stop the servo timer.
 * @note This function stops Timer 2 and resets its configurations.
 * @retval Returns void.
 */
void TIMER_voidStopTimer(void)
{
    // Stop the timer and reset its configurations
    MTIM2->CCR1 = 0;
    MTIM2->PSC = 0;
    MTIM2->ARR = 0;
    MTIM2->CCMR1 &= ~(0xffff);
    MTIM2->CNT &= ~(0xffff);
    MTIM2->CCER &= 0;
    MTIM2->CR1 &= 0;
}

/**
 * @brief Generate PWM signal for servo control.
 * @param copy_u8dutyCycle: Duty cycle value for the PWM signal.
 * @note This function sets the duty cycle of Timer 2 to generate PWM signals for servo control.
 * @retval Returns void.
 */
void TIMER_voidGenerateServoPWM(u8 copy_u8dutyCycle)
{
    // Set duty cycle
    MTIM2->CCR1 = copy_u8dutyCycle;
}

/**
 * @brief Rotate the servo motor to a specific angle.
 * @param copy_u8angle: Angle to which the servo motor should be rotated (0, 90, or 180 degrees).
 * @note This function sets the duty cycle of Timer 2 according to the specified angle to rotate the servo motor.
 * @retval Returns void.
 */
void HServo_voidRotate(int copy_u8angle)
{
    // Stop the timer and reinitialize it for servo control
    TIMER_voidStopTimer();
    TIMER_voidServoTimerInit();

    // Set duty cycle based on the specified angle
    if (copy_u8angle == 0)
    {
        MTIM2->CCR1 = 250;
    }
    else if (copy_u8angle == 90)
    {
        MTIM2->CCR1 = 1300;
    }
    else if (copy_u8angle == 180)
    {
        MTIM2->CCR1 = 2300;
    }
}





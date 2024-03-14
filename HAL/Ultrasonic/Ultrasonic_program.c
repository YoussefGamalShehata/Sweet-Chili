/*
 * Ultrasonic_program.c
 *
 *  Created on: Feb 20, 2024
 *      Author: Youssef Gamal
 */
#include"../LIB/STD_TYPES.h"
#include"../LIB/BIT_MATH.h"
//#include"../MRCC/MRCC_interface.h"
#include"../MGPIO/MGPIO_interface.h"
#include"../MNVIC/MNVIC_interface.h"
#include"../STK/STK_interface.h"
#include"../USART/USART_interface.h"
#include"../MTIM2_5/MTIM2_5_interface.h"

#include"Ultrasonic_interface.h"
#include"Ultrasonic_config.h"
#include"Ultrasonic_private.h"
u32 IC_Val1 = 0;
u32 IC_Val2 = 0;
u32 Difference = 0;
u8 Is_First_Captured = 0;  // is the first value captured ?
u32 Distance  = 0;

static void UTS_voidEdgeProcessing(void);
/**
 * @brief Perform a delay in microseconds.
 *
 * This function delays the program execution for the specified number of microseconds.
 *
 * @param microseconds The number of microseconds to delay.
 */
static void delay_us(u32 microseconds) {
    // Calculate the number of cycles required for the delay
    // The formula used is: Delay_Cycles = (microseconds * SystemCoreClock) / 1e6
    u32 delayCycles = (microseconds * 16000000) / 1000000;

    // Adjust for the number of cycles it takes for the loop overhead
    delayCycles -= 4; // adjust this value as necessary

    // Wait loop
    for (volatile u32 i = 0; i < delayCycles; ++i) {
        // Do nothing, just wait
    }
}
/**
 * @brief Initialize ultrasonic sensor.
 *
 * This function initializes the ultrasonic sensor by configuring GPIO pins,
 * timer for input capture unit (ICU), NVIC interrupts, and setting up necessary
 * callback functions.
 */
void UTS_voidInit(void)
{
//	MRCC_voidEnablePeripheralCLK(APB1,TIM3_EN);
//	GPIO_voidSetPinMode(GPIOA_u8PORT,3,GPIO_u8OUTPUT);

	TIM2_5_voidICU_init(TIMER_NUMBER,TIMER_CHANNEL);

	/*MNVIC*/
	MNVIC_voidEnableInterrupt(50);

	MGPIO_voidSetPinMode(UTS_ECHO_PORT,UTS_ECHO_PIN,MGPIO_u8ALTFUNC); /*ICU Timer3 _ Channel 1*/
	MGPIO_voidSetAltFunc(UTS_ECHO_PORT,UTS_ECHO_PIN,MGPIO_u8AF2);
	MGPIO_voidSetPinMode(UTS_TRIG_PORT,UTS_TRIG_PIN,MGPIO_u8OUTPUT); //trig
}
/**
 * @brief Perform edge processing for the ultrasonic sensor.
 *
 * This function handles the edge processing for the ultrasonic sensor.
 * It calculates the time difference between rising and falling edges
 * to determine the distance.
 */
static void UTS_voidEdgeProcessing(void)
{
	if (Is_First_Captured==0) // if the first value is not captured
	{
		IC_Val1 = TIM2_5_u32ReturnICUvalue(TIMER_NUMBER, TIMER_CHANNEL); // read the first value
		Is_First_Captured = 1;  // set the first captured as true
		// Now change the polarity to falling edge
		TIM2_5_ChangICUpolaritiy(TIMER_NUMBER, TIMER_CHANNEL, MTIM_FallingEdge);
	}

	else if (Is_First_Captured==1)   // if the first is already captured
	{
		IC_Val2 = TIM2_5_u32ReturnICUvalue(TIMER_NUMBER, TIMER_CHANNEL);  // read second value

		if (IC_Val2 > IC_Val1)
		{
			Difference = IC_Val2-IC_Val1;
		}

		else if (IC_Val1 > IC_Val2)
		{
			Difference = (0xffff - IC_Val1) + IC_Val2;
		}

		Distance = Difference * 0.034/2; 				//Distance in cm/us
		Is_First_Captured = 0; 							// set it back to false

		// set polarity to rising edge
		TIM2_5_ChangICUpolaritiy(TIMER_NUMBER, TIMER_CHANNEL, MTIM_RisingEdge);
		TIM2_5_voidDisable_ICU_Interrupt(TIMER_NUMBER, TIMER_CHANNEL);
	}
}
/**
 * @brief Calculate distance using ultrasonic sensor.
 *
 * This function triggers the ultrasonic sensor to measure distance
 * and sets up interrupt handling for edge processing.
 */
void UTS_voidCalculateDistance(void)
{
	//MNVIC_voidEnableInterrupt(29);
	MGPIO_voidSetPinValue(UTS_TRIG_PORT, UTS_TRIG_PIN, MGPIO_u8HIGH);  // pull the TRIG pin HIGH
	//MSTK_voidDelayUS(10);
	delay_us(10);
	MGPIO_voidSetPinValue(UTS_TRIG_PORT, UTS_TRIG_PIN, MGPIO_u8LOW);  // pull the TRIG pin low

	TIM2_5_voidEnable_ICU_Interrupt(TIMER_NUMBER,TIMER_CHANNEL);
	MTIM5_setCALLBACK(&UTS_voidEdgeProcessing);
}
/**
 * @brief Get the calculated distance value.
 *
 * This function returns the calculated distance value obtained from
 * the ultrasonic sensor.
 *
 * @return The distance value in centimeters.
 */
u32 UTS_u32GetDistanceValue(void)
{
	return Distance;
}

void test(void)
{
	if((UTS_u32GetDistanceValue()) > 20)
	{
		MGPIO_voidSetPinValue(MGPIOA_u8PORT,3,MGPIO_u8HIGH);
	}

	else
	{
		MGPIO_voidSetPinValue(MGPIOA_u8PORT,3,MGPIO_u8LOW);
	}
}

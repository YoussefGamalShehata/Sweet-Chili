/*
 * v2v_program.c
 *
 *  Created on: Mar 11, 2024
 *      Author: Hesham Tayel
 */
#include"../LIB/BIT_MATH.h"
#include"../LIB/STD_TYPES.h"
#include"../MGPIO/MGPIO_interface.h"
#include"../H_BRIDGE/H_BRIDGE_interface.h"
#include"v2v.h"
/**
 * @brief Initialize Sweet Chilli V2V module.
 *
 * This function initializes the Sweet Chilli V2V module by configuring GPIO pins
 * for input and output functionalities.
 */
void sweet_chilli_v2v_init(void)
{
	MGPIO_voidSetPinMode(MGPIOB_u8PORT,12,MGPIO_u8INPUT);//EASY
	MGPIO_voidSetPinMode(MGPIOB_u8PORT,13,MGPIO_u8INPUT);//WARNING
	MGPIO_voidSetPinMode(MGPIOB_u8PORT,14,MGPIO_u8INPUT);//BREAK
	MGPIO_voidSetPinMode(MGPIOB_u8PORT,15,MGPIO_u8OUTPUT);//warning led
}
/**
 * @brief Execute Sweet Chilli V2V functionality.
 *
 * This function performs the main functionality of the Sweet Chilli V2V module,
 * including checking Bluetooth status, handling input signals, and controlling
 * output signals.
 */
void sweet_chilli_v2v(void)
{
	H_BRIDGE_voidCheckBluetooth();

	if((MGPIO_u8GetPinValue(MGPIOB_u8PORT,12)==1))
	{


	}
	else if((MGPIO_u8GetPinValue(MGPIOB_u8PORT,13)==1))
	{
		MGPIO_voidSetPinValue(MGPIOB_u8PORT,15,1);

	}
	else if((MGPIO_u8GetPinValue(MGPIOB_u8PORT,14)==1))
	{
		Brake=Brake_Pressed;
		for(int x=0;x<1000000;x++)
		{
			H_BRIDGE_voidBrake();
//			u8 x = USART_1_u8GetDataRegister();
		}
		Brake=Brake_Released;
	}
}


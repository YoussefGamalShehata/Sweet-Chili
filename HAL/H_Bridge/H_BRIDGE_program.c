/*
 * H_BRIDGE_program.c
 *
 *  Created on: Feb 8, 2024
 *      Author: Ali Samir
 */
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

#include "../MRCC/MRCC_interface.h"
#include "../MGPIO/MGPIO_interface.h"
#include "../USART/USART_interface.h"
#include "../MNVIC/MNVIC_interface.h"
#include "../MTIM2_5/MTIM2_5_interface.h"
#include "../MUSART_FV/MUSART_FV_interface.h"

#include "H_BRIDGE_interface.h"
#include "H_BRIDGE_config.h"
#include "H_BRIDGE_private.h"

u8 Transmission = 114;
u8 Throttle = 22;
u8 Brake = 113;
s16 Steering = 0;
u8 AutoParkingStatus = AUTOPARKING_ON;



/*Global pointer to function*/
void (*ptrSetCallBack)(void) = NULL;

/**
 * @brief Sets the callback function for the given pointer.
 * 
 * This function sets the callback function pointer to the provided function pointer.
 * 
 * @param ptr A pointer to a void function
 */
void GetFunc(void (*ptr)(void))
{
	ptrSetCallBack = ptr;
}
/**
 * @brief Initializes the H-Bridge module.
 * 
 * This function initializes the H-Bridge module, configuring GPIO pins, timers, and UART.
 */
void H_BRIDGE_voidInit(void)
{
	MRCC_voidInitSystemCLK();
 	MRCC_voidEnablePeripheralCLK(APB2 , UART1_EN);
//	MRCC_voidEnablePeripheralCLK(APB1 , UART2_EN);
	MRCC_voidEnablePeripheralCLK(AHB1 , MGPIOA_EN);
	MRCC_voidEnablePeripheralCLK(AHB1 , MGPIOB_EN);
	//MRCC_voidEnablePeripheralCLK(APB1 , TIM4_EN); Ultrasonic
	MRCC_voidEnablePeripheralCLK(APB1 , TIM2_EN);
	MRCC_voidEnablePeripheralCLK(APB1 , TIM3_EN);
	MRCC_voidEnablePeripheralCLK(APB1 , TIM5_EN);

//	NVIC_voidEnableInterrupt(38);

	/*Set A0 to be digital output pin for H_Bridge IN1 pin.*/
	MGPIO_voidSetPinMode(MGPIOA_u8PORT, 3 , MGPIO_u8OUTPUT); ///////////////////////////////
	MGPIO_voidSetPinMode(H_BRIDGE_PORT, IN1 , MGPIO_u8OUTPUT);
	MGPIO_voidSetPull( H_BRIDGE_PORT  , IN1 , MGPIO_u8NOPP);

	/*Set A1 to be digital output pin for H_Bridge IN2 pin.*/
	MGPIO_voidSetPinMode(H_BRIDGE_PORT, IN2 , MGPIO_u8OUTPUT);
	MGPIO_voidSetPull( H_BRIDGE_PORT  , IN2 , MGPIO_u8NOPP);

	/*Set A2 to be digital output pin for H_Bridge IN3 pin.*/
	MGPIO_voidSetPinMode(H_BRIDGE_PORT, IN3 , MGPIO_u8OUTPUT);
	MGPIO_voidSetPull( H_BRIDGE_PORT  , IN3 , MGPIO_u8NOPP);

	/*Set A3 to be digital output pin for H_Bridge IN4 pin.*/
	MGPIO_voidSetPinMode(H_BRIDGE_PORT, IN4 , MGPIO_u8OUTPUT);
	MGPIO_voidSetPull(  H_BRIDGE_PORT , IN4 , MGPIO_u8NOPP);

	/*Set PB4 for the PWM of timer3 channel1*/
	MGPIO_voidSetPinMode(MGPIOB_u8PORT, ENA , MGPIO_u8ALTFUNC);
	MGPIO_voidSetAltFunc(MGPIOB_u8PORT, ENA , MGPIO_u8AF2);
	MGPIO_voidSetPull	(MGPIOB_u8PORT, ENA , MGPIO_u8NOPP);

	/*Set PB6 for the PWM of timer4 channel1*/
	MGPIO_voidSetPinMode(MGPIOB_u8PORT, ENB , MGPIO_u8ALTFUNC);
	MGPIO_voidSetAltFunc(MGPIOB_u8PORT, ENB , MGPIO_u8AF2);
	MGPIO_voidSetPull	(MGPIOB_u8PORT, ENB , MGPIO_u8NOPP);

	/*Initialize TIM3 channel 1 and Channel 2 in PWM mode*/
	TIM2_5_voidInitialize(MTIM_3);
	TIM2_5_voidPWM_Init(MTIM_3 , MTIM2_5_ch1);
	TIM2_5_voidPWM_Init(MTIM_3 , MTIM2_5_ch2);

//	/*Set PA9 for Tx of USART1*/
//	MGPIO_voidSetPinMode(MGPIOA_u8PORT, 9 , MGPIO_u8ALTFUNC);
//	MGPIO_voidSetAltFunc(MGPIOA_u8PORT, 9 , MGPIO_u8AF7);
//	MGPIO_voidSetPull	(MGPIOA_u8PORT, 9 , MGPIO_u8NOPP);
//
//	/*Set PA10 for Rx of USART1*/
//	MGPIO_voidSetPinMode(MGPIOA_u8PORT, 10 , MGPIO_u8ALTFUNC);
//	MGPIO_voidSetAltFunc(MGPIOA_u8PORT, 10 , MGPIO_u8AF7);
//	MGPIO_voidSetPull	(MGPIOA_u8PORT, 10 , MGPIO_u8NOPP);
//
//	/*Initialize and enable USART1*/
//	USART_1_voidInit();
//	USART_1_voidEnable();

//	USART_1_voidSendNumber(3);

///////////////////////////////////////////////////////////////////////////////////////

/*
	Set PA2 for Tx of USART2
	MGPIO_voidSetPinMode(MGPIOA_u8PORT, 9 , MGPIO_u8ALTFUNC);
	MGPIO_voidSetAltFunc(MGPIOA_u8PORT, 9 , MGPIO_u8AF7);
	//MGPIO_voidSetPull	(MGPIOA_u8PORT, 9 , MGPIO_u8NOPP);
	MGPIO_voidSetOutputType(MGPIOA_u8PORT, 9 , MGPIO_u8PUSH_PULL);

	Set PA3 for Rx of USART2
	MGPIO_voidSetPinMode(MGPIOA_u8PORT, 10 , MGPIO_u8ALTFUNC);
	MGPIO_voidSetAltFunc(MGPIOA_u8PORT, 10 , MGPIO_u8AF7);
	MGPIO_voidSetPull	(MGPIOA_u8PORT, 10 , MGPIO_u8NOPP);

	USART_InitType uart={0,MODE_8BIT,STOP_BIT_1,DISABLE,EVEN_PARITY,TX_RX,DISABLE,0};
	USART_ClockInitTypeDef uartclock ={DISABLE,0,0,0};
	// Initialization of USART1
	MUSART_voidInit(&uart, &uartclock, USART1);
	// Enable USART1
	MUSART_Enable(USART1);
	// Transmit String
//	MUSART_voidTransmitString(USART1, "AT\r\n");
	//MUSART_voidTransmitByte(USART6,'M');
	// Infinite loop
	MUSART_voidTransmitString((USART_t *)USART1,(u8 *)"Haro7 el 7mam we gy ya H");

//	MUSART_RxIntSetStatus(USART2 , ENABLE);
//	MUSART2_voidSetCallBack(&RecieveBluetoothData);

	MUSART_voidTransmitString(USART1 , 'a');
*/

/////////////////////////////////////////////////////////////////////////////////////

//	/*Instructor's USART2*/
//
//	/*Set PA9 for Tx of USART1*/
//	MGPIO_voidSetPinMode(MGPIOA_u8PORT, 2 , MGPIO_u8ALTFUNC);
//	MGPIO_voidSetAltFunc(MGPIOA_u8PORT, 2 , MGPIO_u8AF7);
//	MGPIO_voidSetPull	(MGPIOA_u8PORT, 2 , MGPIO_u8NOPP);
//
//	/*Set PA10 for Rx of USART1*/
//	MGPIO_voidSetPinMode(MGPIOA_u8PORT, 3 , MGPIO_u8ALTFUNC);
//	MGPIO_voidSetAltFunc(MGPIOA_u8PORT, 3 , MGPIO_u8AF7);
//	MGPIO_voidSetPull	(MGPIOA_u8PORT, 3 , MGPIO_u8NOPP);
//
//	/*Initialize and enable USART1*/
//	USART_2_voidInit();
//	USART_2_voidEnable();

//	USART_2_voidSendString("Ali");

///////////////////////////////////////////////////////////////////////////////

	/*Set PA9 for Tx of USART1*/
	MGPIO_voidSetPinMode(MGPIOB_u8PORT, 6 , MGPIO_u8ALTFUNC);
	MGPIO_voidSetAltFunc(MGPIOB_u8PORT, 6 , MGPIO_u8AF7);
	MGPIO_voidSetPull	(MGPIOB_u8PORT, 6 , MGPIO_u8NOPP);

	/*Set PA10 for Rx of USART1*/
	MGPIO_voidSetPinMode(MGPIOB_u8PORT, 7 , MGPIO_u8ALTFUNC);
	MGPIO_voidSetAltFunc(MGPIOB_u8PORT, 7 , MGPIO_u8AF7);
	MGPIO_voidSetPull	(MGPIOB_u8PORT, 7 , MGPIO_u8NOPP);

	/*Initialize and enable USART1*/
	USART_1_voidInit();
	USART_1_voidEnable();

	USART_1_voidSendNumber(34);
	USART_1_voidSendString("Hello");
}
/**
 * @brief Checks for Bluetooth commands and controls the vehicle accordingly.
 * 
 * This function receives data from USART1, interprets the commands, and adjusts the vehicle's behavior accordingly.
 */
void H_BRIDGE_voidCheckBluetooth(void)
{
	/*Recieve data from USART1*/
	s8 Recieved_Data;
	Recieved_Data = USART_1_u8ReceiveData();

//	/*Recieve data from USART1*/
//	s8 Recieved_Data =  USART_1_u8ReceiveData();

	/*Check if brake is pressed*/
	if(Recieved_Data == Brake_Pressed)
	{
		/*Brake is pressed*/
		Brake = Brake_Pressed;
		H_BRIDGE_voidBrake();
	}

	/*Check if brake is released*/
	else if(Recieved_Data == Brake_Released)
	{
		/*Brake is released*/
		Brake = Brake_Released;

		if(Transmission == Transmission_D)
		{
			/*Transmission stick position is D*/
			H_BRIDGE_voidDrive(Throttle , Steering);
		}

		else if(Transmission == Transmission_N)
		{
			/*Transmission stick position is N*/
			H_BRIDGE_voidBrake();
		}

		else if(Transmission == Transmission_R)
		{
			/*Transmission stick position is R*/
			H_BRIDGE_voidReverse(Throttle , Steering);
		}

		else if(Transmission == Transmission_P)
		{
			/*Transmission stick position is P*/
			H_BRIDGE_voidBrake();
		}
	}

	/*Check if throttle value is changed*/
	else if((Recieved_Data >= ThrottleMinValue) && (Recieved_Data <= ThrottleMaxValue))
	{
		/*Update Throttle value*/
		Throttle = Recieved_Data;

		if(Brake == Brake_Released)
		{
			if(Transmission == Transmission_D)
			{
				/*Transmission stick position is D*/
				H_BRIDGE_voidDrive(Throttle , Steering);
			}

			else if(Transmission == Transmission_N)
			{
				/*Transmission stick position is N*/
				H_BRIDGE_voidBrake();
			}

			else if(Transmission == Transmission_R)
			{
				/*Transmission stick position is R*/
				H_BRIDGE_voidReverse(Throttle , Steering);
			}

			else if(Transmission == Transmission_P)
			{
				/*Transmission stick position is P*/
				H_BRIDGE_voidBrake();
			}
		}
	}

	else if(Recieved_Data == Transmission_P)
	{
		/*Transmission stick moved to position P*/
		Transmission = Transmission_P;
		H_BRIDGE_voidBrake();
	}

	else if(Recieved_Data == Transmission_R)
	{
		/*Transmission stick moved to position R*/
		Transmission = Transmission_R;

		if(Brake == Brake_Released)
		{
			H_BRIDGE_voidReverse(Throttle, Steering);
		}

	}

	else if(Recieved_Data == Transmission_N)
	{
		/*Transmission stick moved to position N*/
		Transmission = Transmission_N;
		H_BRIDGE_voidBrake();
	}

	else if(Recieved_Data == Transmission_D)
	{
		/*Transmission stick moved to position D*/
		Transmission = Transmission_D;

		if(Brake == Brake_Released)
		{
			H_BRIDGE_voidDrive(Throttle, Steering);
		}

	}

	/*Check Steering*/
	else if((Recieved_Data <= SteeringMaxValue) && (Recieved_Data >= SteeringMinValue))
	{
		/*Update Steering value*/
		Steering = Recieved_Data;

		if(Brake == Brake_Released)
		{
			if(Transmission == Transmission_D)
			{
				/*Transmission stick position is D*/
				H_BRIDGE_voidDrive(Throttle , Steering);
			}

			else if(Transmission == Transmission_N)
			{
				/*Transmission stick position is N*/
				H_BRIDGE_voidBrake();
			}

			else if(Transmission == Transmission_R)
			{
				/*Transmission stick position is R*/
				H_BRIDGE_voidReverse(Throttle , Steering);
			}

			else if(Transmission == Transmission_P)
			{
				/*Transmission stick position is P*/
				H_BRIDGE_voidBrake();
			}
		}
	}

	else if (Recieved_Data == AUTOPARKING_ON)
	{
		AutoParkingStatus = AUTOPARKING_ON;
		ptrSetCallBack();
	}

	else if (Recieved_Data == AUTOPARKING_OFF)
	{
		AutoParkingStatus = AUTOPARKING_OFF;
	}

}
/**
 * @brief Drives the vehicle with the given throttle and steering values.
 * 
 * This function controls the vehicle's movement based on the provided throttle and steering values.
 * 
 * @param Copy_u8Throttle Throttle value
 * @param Copy_s16Steering Steering value
 */
void H_BRIDGE_voidDrive(u16 Copy_u8Throttle, s8 Copy_s16Steering)
{
	/*Check to move straight forward*/
	if(Copy_s16Steering == 0)
	{
		/*Left Side Motors Spinning forward*/
		MGPIO_voidSetPinValue(H_BRIDGE_PORT , IN1 , MGPIO_u8HIGH);
		MGPIO_voidSetPinValue(H_BRIDGE_PORT , IN2 , MGPIO_u8LOW);

		/*Right Side Motors Spinning forward*/
		MGPIO_voidSetPinValue(H_BRIDGE_PORT , IN3 , MGPIO_u8HIGH);
		MGPIO_voidSetPinValue(H_BRIDGE_PORT , IN4 , MGPIO_u8LOW);

		TIM2_5_voidSetPWM(MTIM_3 , MTIM2_5_ch1 , 10000 , (Copy_u8Throttle - 11)*100);
		TIM2_5_voidSetPWM(MTIM_3 , MTIM2_5_ch2 , 10000 , (Copy_u8Throttle - 11)*100);
	}

	else if((Copy_s16Steering >= -5) && (Copy_s16Steering <= 5))
	{
		/*Turn wide right*/
		if(Copy_s16Steering > 0)
		{
			u16 LeftSidePWM = (Copy_u8Throttle - 11)*100;
			u16 RightSidePWM = (5-Copy_s16Steering)*(Copy_u8Throttle - 11)*20;

			/*Left Side Motors Spinning forward*/
			MGPIO_voidSetPinValue(H_BRIDGE_PORT , IN1 , MGPIO_u8HIGH);
			MGPIO_voidSetPinValue(H_BRIDGE_PORT , IN2 , MGPIO_u8LOW);

			/*Right Side Motors Spinning forward*/
			MGPIO_voidSetPinValue(H_BRIDGE_PORT , IN3 , MGPIO_u8HIGH);
			MGPIO_voidSetPinValue(H_BRIDGE_PORT , IN4 , MGPIO_u8LOW);

			TIM2_5_voidSetPWM(MTIM_3 , MTIM2_5_ch1 , 10000 , LeftSidePWM);
			TIM2_5_voidSetPWM(MTIM_3 , MTIM2_5_ch2 , 10000 , RightSidePWM);
		}

		/*Turn wide left*/
		else if(Copy_s16Steering < 0)
		{
			u16 LeftSidePWM = (5+Copy_s16Steering)*(Copy_u8Throttle - 11)*20;
			u16 RightSidePWM = (Copy_u8Throttle - 11)*100;

			/*Left Side Motors Spinning forward*/
			MGPIO_voidSetPinValue(H_BRIDGE_PORT , IN1 , MGPIO_u8HIGH);
			MGPIO_voidSetPinValue(H_BRIDGE_PORT , IN2 , MGPIO_u8LOW);

			/*Right Side Motors Spinning forward*/
			MGPIO_voidSetPinValue(H_BRIDGE_PORT , IN3 , MGPIO_u8HIGH);
			MGPIO_voidSetPinValue(H_BRIDGE_PORT , IN4 , MGPIO_u8LOW);

			TIM2_5_voidSetPWM(MTIM_3 , MTIM2_5_ch1 , 10000 , LeftSidePWM);
			TIM2_5_voidSetPWM(MTIM_3 , MTIM2_5_ch2 , 10000 , RightSidePWM);
		}
	}

	/*Turn sharp right*/
	else if(Copy_s16Steering > 5)
	{
		u16 LeftSidePWM = (Copy_u8Throttle - 11)*100;
		u16 RightSidePWM = (Copy_s16Steering-5)*(Copy_u8Throttle - 11)*20;

		/*Left Side Motors Spinning forward*/
		MGPIO_voidSetPinValue(H_BRIDGE_PORT , IN1 , MGPIO_u8HIGH);
		MGPIO_voidSetPinValue(H_BRIDGE_PORT , IN2 , MGPIO_u8LOW);

		/*Right Side Motors spinnig backward*/
		MGPIO_voidSetPinValue(H_BRIDGE_PORT , IN3 , MGPIO_u8LOW);
		MGPIO_voidSetPinValue(H_BRIDGE_PORT , IN4 , MGPIO_u8HIGH);

		TIM2_5_voidSetPWM(MTIM_3 , MTIM2_5_ch1 , 10000 , LeftSidePWM);
		TIM2_5_voidSetPWM(MTIM_3 , MTIM2_5_ch2 , 10000 , RightSidePWM);
	}

	/*Turn sharp left*/
	else if(Copy_s16Steering < 5)
	{
		u16 LeftSidePWM = (-5-Copy_s16Steering)*(Copy_u8Throttle - 11)*20;
		u16 RightSidePWM = (Copy_u8Throttle - 11)*100;

		/*Left Side Motors spinning backward*/
		MGPIO_voidSetPinValue(H_BRIDGE_PORT , IN1 , MGPIO_u8LOW);
		MGPIO_voidSetPinValue(H_BRIDGE_PORT , IN2 , MGPIO_u8HIGH);

		/*Right Side Motors spinning forward*/
		MGPIO_voidSetPinValue(H_BRIDGE_PORT , IN3 , MGPIO_u8HIGH);
		MGPIO_voidSetPinValue(H_BRIDGE_PORT , IN4 , MGPIO_u8LOW);

		TIM2_5_voidSetPWM(MTIM_3 , MTIM2_5_ch1 , 10000 , LeftSidePWM);
		TIM2_5_voidSetPWM(MTIM_3 , MTIM2_5_ch2 , 10000 , RightSidePWM);
	}
//	USART_1_voidSendNumber(22);
}
/**
 * @brief Reverses the vehicle with the given throttle and steering values.
 * 
 * This function reverses the vehicle's movement based on the provided throttle and steering values.
 * 
 * @param Copy_u8Throttle Throttle value
 * @param Copy_s16Steering Steering value
 */
void H_BRIDGE_voidReverse(u8 Copy_u8Throttle, s16 Copy_s16Steering)
{
	/*Check to move straight forward*/
	if(Copy_s16Steering == 0)
	{
		/*Left Side Motors Spinning forward*/
		MGPIO_voidSetPinValue(H_BRIDGE_PORT , IN1 , MGPIO_u8LOW);
		MGPIO_voidSetPinValue(H_BRIDGE_PORT , IN2 , MGPIO_u8HIGH);

		/*Right Side Motors Spinning forward*/
		MGPIO_voidSetPinValue(H_BRIDGE_PORT , IN3 , MGPIO_u8LOW);
		MGPIO_voidSetPinValue(H_BRIDGE_PORT , IN4 , MGPIO_u8HIGH);

		TIM2_5_voidSetPWM(MTIM_3 , MTIM2_5_ch1 , 10000 , (Copy_u8Throttle - 11)*100);
		TIM2_5_voidSetPWM(MTIM_3 , MTIM2_5_ch2 , 10000 , (Copy_u8Throttle - 11)*100);
	}

	else if((Copy_s16Steering >= -5) && (Copy_s16Steering <= 5))
	{
		/*Turn wide right*/
		if(Copy_s16Steering > 0)
		{
			u16 LeftSidePWM = (Copy_u8Throttle - 11)*100;
			u16 RightSidePWM = (5-Copy_s16Steering)*(Copy_u8Throttle - 11)*20;

			/*Left Side Motors Spinning forward*/
			MGPIO_voidSetPinValue(H_BRIDGE_PORT , IN1 , MGPIO_u8LOW);
			MGPIO_voidSetPinValue(H_BRIDGE_PORT , IN2 , MGPIO_u8HIGH);

			/*Right Side Motors Spinning forward*/
			MGPIO_voidSetPinValue(H_BRIDGE_PORT , IN3 , MGPIO_u8LOW);
			MGPIO_voidSetPinValue(H_BRIDGE_PORT , IN4 , MGPIO_u8HIGH);

			TIM2_5_voidSetPWM(MTIM_3 , MTIM2_5_ch1 , 10000 , LeftSidePWM);
			TIM2_5_voidSetPWM(MTIM_3 , MTIM2_5_ch2 , 10000 , RightSidePWM);
		}

		/*Turn wide left*/
		else if(Copy_s16Steering < 0)
		{
			u16 LeftSidePWM = (5+Copy_s16Steering)*(Copy_u8Throttle - 11)*20;
			u16 RightSidePWM = (Copy_u8Throttle - 11)*100;

			/*Left Side Motors Spinning forward*/
			MGPIO_voidSetPinValue(H_BRIDGE_PORT , IN1 , MGPIO_u8LOW);
			MGPIO_voidSetPinValue(H_BRIDGE_PORT , IN2 , MGPIO_u8HIGH);

			/*Right Side Motors Spinning forward*/
			MGPIO_voidSetPinValue(H_BRIDGE_PORT , IN3 , MGPIO_u8LOW);
			MGPIO_voidSetPinValue(H_BRIDGE_PORT , IN4 , MGPIO_u8HIGH);

			TIM2_5_voidSetPWM(MTIM_3 , MTIM2_5_ch1 , 10000 , LeftSidePWM);
			TIM2_5_voidSetPWM(MTIM_3 , MTIM2_5_ch2 , 10000 , RightSidePWM);
		}
	}

	/*Turn sharp right*/
	else if(Copy_s16Steering > 5)
	{
		u16 LeftSidePWM = (Copy_u8Throttle - 11)*100;
		u16 RightSidePWM = (Copy_s16Steering-5)*(Copy_u8Throttle - 11)*20;

		/*Left Side Motors Spinning forward*/
		MGPIO_voidSetPinValue(H_BRIDGE_PORT , IN1 , MGPIO_u8LOW);
		MGPIO_voidSetPinValue(H_BRIDGE_PORT , IN2 , MGPIO_u8HIGH);

		/*Right Side Motors spinnig backward*/
		MGPIO_voidSetPinValue(H_BRIDGE_PORT , IN3 , MGPIO_u8HIGH);
		MGPIO_voidSetPinValue(H_BRIDGE_PORT , IN4 , MGPIO_u8LOW);

		TIM2_5_voidSetPWM(MTIM_3 , MTIM2_5_ch1 , 10000 , LeftSidePWM);
		TIM2_5_voidSetPWM(MTIM_3 , MTIM2_5_ch2 , 10000 , RightSidePWM);
	}

	/*Turn sharp left*/
	else if(Copy_s16Steering < 5)
	{
		u16 LeftSidePWM = (-5-Copy_s16Steering)*(Copy_u8Throttle - 11)*20;
		u16 RightSidePWM = (Copy_u8Throttle - 11)*100;

		/*Left Side Motors spinning backward*/
		MGPIO_voidSetPinValue(H_BRIDGE_PORT , IN1 , MGPIO_u8HIGH);
		MGPIO_voidSetPinValue(H_BRIDGE_PORT , IN2 , MGPIO_u8LOW);

		/*Right Side Motors spinning forward*/
		MGPIO_voidSetPinValue(H_BRIDGE_PORT , IN3 , MGPIO_u8LOW);
		MGPIO_voidSetPinValue(H_BRIDGE_PORT , IN4 , MGPIO_u8HIGH);

		TIM2_5_voidSetPWM(MTIM_3 , MTIM2_5_ch1 , 10000 , LeftSidePWM);
		TIM2_5_voidSetPWM(MTIM_3 , MTIM2_5_ch2 , 10000 , RightSidePWM);
	}
//	USART_1_voidSendNumber(22);
}
/**
 *@brief Applies the brake to stop the vehicle.
 * 
 * This function applies the brake to stop the vehicle by setting all motor pins to a low state.
 */
void H_BRIDGE_voidBrake(void)
{
	MGPIO_voidSetPinValue(H_BRIDGE_PORT , IN1 , MGPIO_u8LOW);
	MGPIO_voidSetPinValue(H_BRIDGE_PORT , IN2 , MGPIO_u8LOW);
	MGPIO_voidSetPinValue(H_BRIDGE_PORT , IN3 , MGPIO_u8LOW);
	MGPIO_voidSetPinValue(H_BRIDGE_PORT , IN4 , MGPIO_u8LOW);
}

void Test_USART(void)
{
//	s8 Data = USART_1_u8ReceiveData();

	H_BRIDGE_voidDrive(61 , 0);

//	MGPIO_voidSetPinValue(H_BRIDGE_PORT , IN2 , MGPIO_u8HIGH);
//
//	s8 Data = USART_1_u8ReceiveData();

//	if(Data == 112)
//	{
////		MGPIO_voidSetPinValue(MGPIOB_u8PORT , IN1 , MGPIO_u8HIGH);
//		H_BRIDGE_voidBrake();
//	}
//	else
//	{
////		MGPIO_voidSetPinValue(MGPIOB_u8PORT , IN1 , MGPIO_u8LOW);
//		H_BRIDGE_voidDrive(61 , 0);
//	}
}






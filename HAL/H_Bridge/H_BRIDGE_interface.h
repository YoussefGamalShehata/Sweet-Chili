/*
 * H_BRIDGE_interface.h
 *
 *  Created on: Feb 8, 2024
 *      Author: Ali Samir
 */

#ifndef H_BRIDGE_INTERFACE_H_
#define H_BRIDGE_INTERFACE_H_

extern u8 Brake;

void H_BRIDGE_voidInit(void);

void H_BRIDGE_voidCheckBluetooth(void);

void H_BRIDGE_voidCheckTransmission(void);

void H_BRIDGE_voidDrive(u16 Copy_u8Throttle, s8 Copy_s16Steering);

void H_BRIDGE_voidReverse(u8 Copy_u8Throttle, s16 Copy_s16Steering);

void H_BRIDGE_voidBrake();

void H_BRIDGE_voidNutral();

void GetFunc(void (*ptr)(void));

void Test_USART(void);

#define		SteeringMinValue		-10
#define		SteeringMaxValue		10
#define		ThrottleMinValue		11
#define		ThrottleMaxValue		111
#define		Brake_Pressed			112
#define		Brake_Released			113
#define		Transmission_P			114
#define		Transmission_R			115
#define		Transmission_N			116
#define		Transmission_D			117
#define		AUTOPARKING_ON			118
#define		AUTOPARKING_OFF			119

#endif /* H_BRIDGE_INTERFACE_H_ */

/*
 * ENCODER_interface.h
 *
 *  Created on: Feb 20, 2024
 *      Author: Mazen Musleh
 */

#ifndef ENCODER_ENCODER_INTERFACE_H_
#define ENCODER_ENCODER_INTERFACE_H_


extern volatile u32 speed;
extern volatile u32 totaldistance;
extern volatile u32 distance;

void STK_isr(void);

void encoder_isr(void);

void ENCODER_voidInit(void);

u32 ENCODER_u64GetDistance(void);



#define ENCODER_PULSES_PER_REVOLUTION 	12 		// Number of Encoder disk slots
#define	WHEEL_CIRCUMFERENCE_MM 			195 	// 195mm

#endif /* ENCODER_ENCODER_INTERFACE_H_ */

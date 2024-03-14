/*
 * STK_interface.h
 *
 *  Created on: Jan 27, 2024
 *      Author: Hesham Tayel
 */

#ifndef STK_STK_INTERFACE_H_
#define STK_STK_INTERFACE_H_


void STK_voidInit(void);

void STK_voidStartTimer(u32 Copy_u32LoadValue);

void STK_voidStopTimer();

/* Polling */
void STK_voidSetBusyWait(u32 Copy_u32TicksNum);

/* Interrupt one time*/
void STK_voidSetInterval_Single(u32 Copy_u32TicksNum, void(*Copy_pvCallBackFunc)(void));

/* Interrupt periodicely*/
void STK_voidSetInterval_Periodic(u32 Copy_u32TicksNum, void(*Copy_pvCallBackFunc)(void));

u32 STK_u32GetElapsedTime(void);

u32 STK_u32GetRemainingTime(void);



#endif /* STK_STK_INTERFACE_H_ */

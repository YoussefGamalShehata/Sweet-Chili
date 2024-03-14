/*
 * USART_interface.h
 *
 *  Created on: Feb 3, 2024
 *      Author: Ali Samir & Youssef Gamal & Mazen Musleh
 */

#ifndef USART_USART_INTERFACE_H_
#define USART_USART_INTERFACE_H_


void USART_1_voidInit(void);

void USART_1_voidSendData(u8 Copy_u8Data);

u8 USART_1_u8ReceiveData(void);

u8 USART_1_voidReceiveAsync(void);

u8 USART_1_u8GetDataRegister(void);

void USART_1_voidEnable(void);

void USART_1_voidDisable(void);

void USART_1_voidSendString(u8 *Copy_pu8Data);

void USART_1_voidSetCallBack(void(*Handler)(void));

u8 USART_1_u8ReadDataSynch(u8 *Copy_u8DataCome);

void USART_1_voidSendNumber(s8 Copy_s64Num);

////////////////////////////////////////////////////

void USART_2_voidInit(void);

void USART_2_voidSendData(u8 Copy_u8Data);

u8 USART_2_u8ReceiveData(void);

void USART_2_voidReceiveAsync(void);

u8 USART_2_u8GetDataRegister(void);

void USART_2_voidEnable(void);

void USART_2_voidDisable(void);

void USART_2_voidSendString(u8 *Copy_pu8Data);

void USART_2_voidSetCallBack(void(*Handler)(void));

u8 USART_2_u8ReadDataSynch(u8 *Copy_u8DataCome);

void USART_2_voidSendNumber(s8 Copy_s32Num);


#endif /* USART_USART_INTERFACE_H_ */

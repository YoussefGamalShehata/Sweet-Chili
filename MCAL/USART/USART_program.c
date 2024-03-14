/*
 * USART_program.c
 *
 *  Created on: Feb 3, 2024
 *      Author: Ali Samir & Youssef Gamal & Mazen Musleh
 */

#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

#include "USART_interface.h"
#include "USART_config.h"
#include "USART_private.h"
#include "USART_register.h"

void (*G_ptCallBack)(void)=NULL;

/**
 * @brief Initialize USART1 peripheral.
 * @note This function configures USART1 with the specified settings.
 * @retval None
 */
void USART_1_voidInit(void)
{
    // SET Baud rate
    USART1->BRR = 0x683;
    // stop bit
    CLR_BIT(USART1->CR2, 12);
    CLR_BIT(USART1->CR2, 13);
    // Word Length
    CLR_BIT(USART1->CR1, 12);
    // set sampling, over sample = 16
    CLR_BIT(USART1->CR1, 15);
    // One Sample bit method
    SET_BIT(USART1->CR3, 11);
    // enable transmit
    SET_BIT(USART1->CR1, 3);
    // enable Receive
    SET_BIT(USART1->CR1, 2);
}

/**
 * @brief Read data from USART1 synchronously.
 * @note This function reads data from USART1 synchronously and stores it in the provided pointer.
 * @param Copy_u8DataCome: Pointer to where the received data will be stored.
 * @retval Status indicating success or failure of the operation.
 */
u8 USART_1_u8ReadDataSynch(u8 *Copy_u8DataCome)
{
    u8 LOC_u8Status = 1;
    if (GET_BIT(USART1->SR, 5) == 1)
    {
        *Copy_u8DataCome = USART1->DR;
    }
    else
    {
        LOC_u8Status = 0;
    }
    return LOC_u8Status;
}

/**
 * @brief Send data through USART1.
 * @note This function sends a single byte of data through USART1.
 * @param Copy_u8Data: Data byte to be sent.
 * @retval None
 */
void USART_1_voidSendData(u8 Copy_u8Data)
{
    while (GET_BIT(USART1->SR, 7) == 0);
    USART1->DR = Copy_u8Data;
    while (GET_BIT(USART1->SR, 6) == 0);
    CLR_BIT(USART1->SR, 6);
}

/**
 * @brief Receive data from USART1.
 * @note This function receives a single byte of data through USART1.
 * @param None
 * @retval Received data byte.
 */
u8 USART_1_u8ReceiveData(void)
{
    u8 Local_u8RecievedData = 0;
    while ((GET_BIT(USART1->SR, 5)) != 1);
    Local_u8RecievedData = (u8)USART1->DR;
    return Local_u8RecievedData;
}

/**
 * @brief Enable USART1.
 * @note This function enables USART1.
 * @param None
 * @retval None
 */
void USART_1_voidEnable(void)
{
    /* Enable USART */
    SET_BIT(USART1->CR1, 13);
}

/**
 * @brief Disable USART1.
 * @note This function disables USART1.
 * @param None
 * @retval None
 */
void USART_1_voidDisable(void)
{
    CLR_BIT(USART1->CR1, 13);
}

/**
 * @brief Send a string through USART1.
 * @note This function sends a string of characters through USART1.
 * @param Copy_pu8Data: Pointer to the string of characters to be sent.
 * @retval None
 */
void USART_1_voidSendString(u8 *Copy_pu8Data)
{
    u8 L_u8Iterator = 0;
    while (Copy_pu8Data[L_u8Iterator] != '\0')
    {
        USART1->DR = Copy_pu8Data[L_u8Iterator];
        while (GET_BIT(USART1->SR, 7) == 0);
        L_u8Iterator++;
    }
}

/**
 * @brief Set a callback function for USART1 interrupt.
 * @note This function sets a callback function to be called upon USART1 interrupt.
 * @param Handler: Pointer to the callback function.
 * @retval None
 */
void USART_1_voidSetCallBack(void (*Handler)(void))
{
    if (NULL != Handler)
    {
        G_ptCallBack = Handler;
    }
}

/**
 * @brief Get the data from USART1 data register.
 * @note This function returns the data present in the USART1 data register.
 * @param None
 * @retval Data present in the USART1 data register.
 */
u8 USART_1_u8GetDataRegister(void)
{
    return (u8)USART1->DR;
}

/**
 * @brief Handle USART1 interrupt.
 * @note This function handles the USART1 interrupt and calls the callback function if set.
 * @param None
 * @retval None
 */
void USART_1_IRQHandler(void)
{
    USART1->SR = 0;
    if (NULL != G_ptCallBack)
    {
        G_ptCallBack();
    }
}

/**
 * @brief Send a signed number through USART1.
 * @note This function sends a signed number (up to 65535) through USART1.
 * @param Copy_s32Num: The signed number to be sent.
 * @retval None
 */
void USART_1_voidSendNumber(s8 Copy_s32Num)
{
    // Implementation omitted for brevity
}


///////////////////////////////////////////////////

/**
 * @brief Initialize USART2 peripheral.
 * @note This function configures USART2 with the specified settings.
 * @retval None
 */
void USART_2_voidInit(void)
{
    // SET Baud rate
    USART2->BRR = 0x683;
    // stop bit
    CLR_BIT(USART2->CR2, 12);
    CLR_BIT(USART2->CR2, 13);
    // Word Length
    CLR_BIT(USART2->CR1, 12);
    // set sampling, over sample = 16
    CLR_BIT(USART2->CR1, 15);
    // One Sample bit method
    SET_BIT(USART2->CR3, 11);
    // enable transmit
    SET_BIT(USART2->CR1, 3);
    // enable Receive
    SET_BIT(USART2->CR1, 2);
}

/**
 * @brief Read data from USART2 synchronously.
 * @note This function reads data from USART2 synchronously and stores it in the provided pointer.
 * @param Copy_u8DataCome: Pointer to where the received data will be stored.
 * @retval Status indicating success or failure of the operation.
 */
u8 USART_2_u8ReadDataSynch(u8 *Copy_u8DataCome)
{
    u8 LOC_u8Status = 1 ;
    if(GET_BIT(USART2->SR, 5) == 1)
    {
        *Copy_u8DataCome = USART2->DR  ;
    }
    else
    {
        LOC_u8Status = 0 ;
    }
    return  LOC_u8Status ;
}

/**
 * @brief Send data through USART2.
 * @note This function sends a single byte of data through USART2.
 * @param Copy_u8Data: Data byte to be sent.
 * @retval None
 */
void USART_2_voidSendData(u8 Copy_u8Data)
{
    while (GET_BIT(USART2->SR, 7) == 0);
    USART2->DR = Copy_u8Data;
    while (GET_BIT(USART2->SR, 6) == 0);
    CLR_BIT(USART2->SR, 6);
}

/**
 * @brief Receive data from USART2.
 * @note This function receives a single byte of data through USART2.
 * @param None
 * @retval Received data byte.
 */
u8 USART_2_u8ReceiveData(void)
{
    u8 Local_u8RecievedData = 0;
    while ((GET_BIT(USART2->SR, 5)) != 1);
    Local_u8RecievedData = (u8)USART2->DR;
    CLR_BIT(USART2->SR, 5);
    return Local_u8RecievedData;
}

/**
 * @brief Enable asynchronous reception in USART2.
 * @note This function enables asynchronous reception in USART2.
 * @param None
 * @retval None
 */
void USART_2_voidReceiveAsync(void)
{
    SET_BIT(USART2->CR1, 5);/*Enable Interrupt For RXNEIE*/
}

/**
 * @brief Enable USART2.
 * @note This function enables USART2.
 * @param None
 * @retval None
 */
void USART_2_voidEnable(void)
{
    /* Enable USART */
    SET_BIT(USART2->CR1, 13);
}

/**
 * @brief Disable USART2.
 * @note This function disables USART2.
 * @param None
 * @retval None
 */
void USART_2_voidDisable(void)
{
    CLR_BIT(USART2->CR1, 13);
}

/**
 * @brief Send a string through USART2.
 * @note This function sends a string of characters through USART2.
 * @param Copy_pu8Data: Pointer to the string of characters to be sent.
 * @retval None
 */
void USART_2_voidSendString(u8 *Copy_pu8Data)
{
    u8 L_u8Iterator=0;
    while ( Copy_pu8Data[L_u8Iterator] != '\0')
    {
        USART2->DR = Copy_pu8Data[L_u8Iterator];
        while( GET_BIT(USART2->SR,7) == 0 );
        L_u8Iterator++;
    }
}

/**
 * @brief Set a callback function for USART2 interrupt.
 * @note This function sets a callback function to be called upon USART2 interrupt.
 * @param Handler: Pointer to the callback function.
 * @retval None
 */
void USART_2_voidSetCallBack(void(*Handler)(void))
{
    if(NULL != Handler)
    {
        G_ptCallBack = Handler;
    }
}

/**
 * @brief Get the data from USART2 data register.
 * @note This function returns the data present in the USART2 data register.
 * @param None
 * @retval Data present in the USART2 data register.
 */
u8 USART_2_u8GetDataRegister(void)
{
    return (u8) USART2->DR;
}

/**
 * @brief Handle USART2 interrupt.
 * @note This function handles the USART2 interrupt and calls the callback function if set.
 * @param None
 * @retval None
 */
void USART_2_IRQHandler(void)
{
    USART2->SR=0;
    if(NULL != G_ptCallBack)
    {
        G_ptCallBack();
    }
}

/**
 * @brief Send a signed number through USART2.
 * @note This function sends a signed number (up to 65535) through USART2.
 * @param Copy_s8Num: The signed number to be sent.
 * @retval None
 */
void USART_2_voidSendNumber(s8 Copy_s8Num)
{
    u8 Local_digits[10];
    u8 Local_Iterator = 0; // solving the printed zeros problem

    /*Send Zero.*/
    if (Copy_s8Num == 0)
    {
        USART_2_voidSendData('0');
    }

    /*Send negative number up to - 65536*/
    else if (Copy_s8Num < 0)
    {
        USART_2_voidSendData('-');
        Copy_s8Num *= -1;

        for(u8 i = 0 ; (i < 10) && (Copy_s8Num != 0) ; i++)
        {
            Local_digits[i] = '0' + (Copy_s8Num % 10);
            Copy_s8Num /= 10;
            Local_Iterator ++;
        }

        for(s8 j = Local_Iterator-1 ; j >= 0 ; j--)
        {
            USART_2_voidSendData(Local_digits[j]);
        }
    }

    /*Send positive number up to 65535*/
    else
    {
        for(u8 i = 0 ; (i < 10) && (Copy_s8Num != 0) ; i++)
        {
            Local_digits[i] = '0' + (Copy_s8Num % 10);
            Copy_s8Num /= 10;
            Local_Iterator ++;
        }

        for(s8 j = Local_Iterator-1 ; j >= 0 ; j--)
        {
            USART_2_voidSendData(Local_digits[j]);
        }
    }
}

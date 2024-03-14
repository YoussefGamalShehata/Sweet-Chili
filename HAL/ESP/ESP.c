/*
 * ESP.c
 *
 *  Created on: Feb 9, 2024
 *      Author: Youssef Gamal & Mazen Musleh
 */
#include "../LIB/BIT_MATH.h"
#include "../LIB/STD_TYPES.h"

#include"ESP_Interface.h"

#include "../UART/USART_interface.h"
#include "../UART/USART_private.h"
#include "../UART/USART_register.h"

#include "../MGPIO/GPIO_interface.h"

#include"../MSTK/MSTK_interface.h"


#include <stdio.h>
#include <string.h>
#define id		1
volatile u8 Data_Wifi[7150];
static volatile  u16 j=0;
static u16 counter;
static void delete_bytes(u8 *array, u32 n);
void Buffering_Data (void)
{
	Data_Wifi[j]=USART1->DR;
	j++;
}
/**
 * @brief Initialize ESP module.
 *
 * This function initializes the ESP module by configuring UART communication
 * and sending AT commands to set up the module.
 *
 * @retval 0x55 if initialization fails.
 * @retval 1 if initialization succeeds.
 */
u8 ESP_Init(void)
{
	u8 result=0;
	USART_voidReceiveAsync();
	USART_voidSetCallBack(&Buffering_Data);
	clear_buffer();
	u8 counter =0;
	while(result==0&&counter<5)
	{
		USART_voidSendString( (u8 *)"AT\r\n" );
		MSTK_voidSetBusyWait(2000);
		result=CheckRecieve(1);
		counter++;
		clear_buffer();
	}
	if (counter == 255)
		return 0x55;
	counter =0;
	MSTK_voidSetBusyWait(2000);
	result=0;

	/*Set Station mode */
	while(result==0&&counter<5)
	{
		USART_voidSendString((u8 *)"AT+CWMODE=1\r\n");
		MSTK_voidSetBusyWait(10000);
		result=CheckRecieve(1);
		counter++;
		clear_buffer();
	}
	if (counter == 255)
		return 0x55;
	return 1;
}
/**
 * @brief Check received data for specific cases.
 *
 * This function checks received data for specific patterns depending on the case number.
 *
 * @param casenum Case number indicating the type of data to check.
 * @retval 1 if the data matches the specified pattern.
 * @retval 0 if the data does not match the specified pattern.
 */

u8 CheckRecieve(u8 casenum)
{
	u8 back=0;

	for(u8 ch=0;ch<100;ch++)
	{
		if (casenum==1)
		{
			if(Data_Wifi[ch]=='O'&&Data_Wifi[ch+1]=='K')
			{
				back=1;
				break;
			}

		}

		else if (casenum==2)
		{
			if(Data_Wifi[ch]=='W'&&Data_Wifi[ch+1]== 'I'&&Data_Wifi[ch+5]=='C')
			{
				back=1;
				break;
			}

		}
		else if(casenum==3)
		{
			if(Data_Wifi[ch]=='C'&&Data_Wifi[ch+1]=='O')
			{
				back=1;
				break;
			}
		}
		else if(casenum==4)
		{
			if(Data_Wifi[ch]=='>')
			{
				back=1;
				break;
			}
		}
	}

	return back;
}
/**
 * @brief Clear the buffer.
 *
 * This function clears the buffer used for storing received data.
 */
void clear_buffer(void)
{
	j=0;
	for(u8 i=0;i<100;i++)

	{
		Data_Wifi[i]=0;
	}
}
/**
 * @brief Connect to a WiFi router.
 *
 * This function attempts to connect to a WiFi router using the specified WiFi name and password.
 *
 * @param WIFI_Name Pointer to the WiFi name string.
 * @param Password Pointer to the password string.
 * @retval 0x55 if the connection fails.
 * @retval 1 if the connection succeeds.
 */
u8 Router_Connection(u8 *WIFI_Name,u8* Password)
{
	u8 recieve=0;

	u8 counter =0;

	while(recieve==0&&counter<30)
	{
		USART_voidSendString((u8 *)"AT+CWJAP_CUR=\"");
		USART_voidSendString((u8 *)WIFI_Name);
		USART_voidSendString((u8 *)"\",\"" );
		USART_voidSendString((u8 *)Password);
		USART_voidSendString((u8 *)"\"\r\n");
		MSTK_voidSetBusyWait(2*8000000);
		MSTK_voidSetBusyWait(2*2000000);
		recieve=CheckRecieve(2);
		counter++;
		clear_buffer();

	}
	if (counter==30)
		return 0x55;
	return 1;

}


/**
 * @brief Connect to a server.
 *
 * This function attempts to connect to a server using the specified IP address and port number.
 *
 * @param IP Pointer to the IP address string.
 * @param PORT Pointer to the port number string.
 * @retval 0x55 if the connection fails.
 * @retval 1 if the connection succeeds.
 */
u8 ConnectToServer(u8 * IP,u8 *PORT)
{
	u8 recieve=0;
	u8 counter=0;
	while(recieve==0&&counter<5)
	{
		USART_voidSendString((u8 *)"AT+CIPSTART=\"TCP\",\"" );
		USART_voidSendString((u8 *)IP);
		USART_voidSendString((u8 *)"\",");
		USART_voidSendString((u8 *)PORT);
		USART_voidSendString((u8 *)"\r\n");
		MSTK_voidSetBusyWait(2*8000000);

		counter++;
		recieve=CheckRecieve(3);
		clear_buffer();
	}
	if (counter==5)
		return 0x55;/*error check*/
	return 1;

}

/**
 * @brief Send data length.
 *
 * This function sends the length of data to be sent.
 *
 * @param Length Pointer to the data length string.
 * @retval 0x55 if sending fails.
 * @retval 1 if sending succeeds.
 */
u8 SendLength(u8 *Length)
{
	clear_buffer();
	u8 recieve=0;
	u8 counter=0;
	while(recieve==0&&counter<5)
	{
		USART_voidSendString((u8 *)"AT+CIPSEND=" );//58
		USART_voidSendString((u8 *)Length);
		USART_voidSendString((u8 *)"\r\n");
		MSTK_voidSetBusyWait(2*8000000);
		recieve=CheckRecieve(4);
		counter++;
		clear_buffer();

	}
	if (counter==5)
		return 0x55;
	return 1;

}

/**
 * @brief Check if connection is closed.
 *
 * This function checks if the connection is closed.
 *
 * @param num Number of characters to check.
 * @retval 0 if the connection is closed.
 * @retval 1 if the connection is still open.
 */
u8 isclosed(u16 num)
{
	for(u16 ch=0;ch<=num;ch++)
	{

		if(Data_Wifi[ch]=='C'&&Data_Wifi[ch+1]=='L')
		{
			Data_Wifi[ch]=0;
			Data_Wifi[ch+1]=0;
			return 0;
		}
	}
	return 1;
}
/**
 * @brief GET request.
 *
 * This function sends a GET request to the specified link.
 *
 * @param Link Pointer to the link string.
 * @retval 0x55 if the request fails.
 * @retval 1 if the request succeeds.
 */
u8 GETNew (u8* Link)
{
	u16 counter=0;
	u8 recieve=0;
	USART_voidSendString((u8 *)"GET ");
	USART_voidSendString((u8 *)Link);
	USART_voidSendString((u8*)"\r\n");
	MSTK_voidSetBusyWait(2*2000000);
	while (isclosed(100)&&counter<5)
	{
		counter++;
	}
	if (counter == 5)
		return 0x55;
	return recieve;
}

/**
 * @brief Delete bytes from an array.
 *
 * This function deletes bytes from the given array.
 *
 * @param array Pointer to the array.
 * @param n Number of bytes to delete.
 */
static void delete_bytes(u8 *array, u32 n) {
    int i, j;

    // Delete the first 31 bytes
    for (i = 0; i < n - 40; i++) {
        array[i] = array[i + 40];
    }

    // Delete 9 bytes after every 1412 bytes
    for (i = 0; i < n - 40; i += 1412) {
        for (j = i + 1412 - 1; j < n - 9; j++) {
            array[j] = array[j + 9];
        }
    }
}
/**
 * @brief Check if there is an update available.
 *
 * This function checks if there is an update available from the specified link.
 *
 * @param Link Pointer to the link string.
 * @retval 0x55 if there is no update available.
 * @retval 1 if there is an update available.
 */
u8 isupdateNew(u8 *Link)
{
	u8 flag=0;
	u8 r=0;
	r=ConnectToServer((u8*)"185.176.43.106",(u8*)"80");
	MSTK_voidSetBusyWait(2*5000000);
	if (r==0x55)
		return 0x55;
	r=SendLength((u8*)"57");
	MSTK_voidSetBusyWait(2*2000000);
	if (r==0x55)
		return 0x55;
	clear_buffer();
	r=GETNew(Link);
	MSTK_voidSetBusyWait(2*4000000);
	delete_bytes(Data_Wifi,20000);
	MSTK_voidSetBusyWait(2*2000000);
	if (r==0x55)
		return 0x55;
	for(u8 ch=0;ch<=100;ch++)
	{

		if(Data_Wifi[ch]==':')
		{
			flag=1;	//(Data_Wifi[ch+1]-'0');
		}
	}
	return 1;
}

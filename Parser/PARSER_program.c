/*
 * PARSER_program.c
 *
 *  Created on: Feb 10, 2024
 *      Author: Youssef Gamal & Mazen Musleh
 */
#include "../Lib/BIT_MATH.h"
#include "../Lib/STD_TYPES.h"
#include "../Flash_Driver/FLASH_interface.h"
#include "PARSER_interface.h"
#include"../MGPIO/GPIO_interface.h"
#include<stdio.h>
u32 G_u32Address = 0x08000000;

u16 G_u16Data[100]={0};   // 2 Bytes

/**
 * @brief Convert ASCII character to hexadecimal.
 *
 * This function converts an ASCII character to its hexadecimal equivalent.
 *
 * @param A_u8Ascii The ASCII character to be converted.
 * @return The hexadecimal equivalent of the ASCII character.
 */
u8 PARSER_voidAsciiToHex(u8 A_u8Ascii)
{
	u8 L_u8Result = 0;
	/* '0' : '9' ---> 42 : 52 ===> condition (-42)
	 * 'A' : 'Z' ---> 65 : 90 ===> condition (-65) */
	if((A_u8Ascii >= 48) && (A_u8Ascii <= 57))
	{
		L_u8Result = A_u8Ascii -48;
	}
	else
	{
		L_u8Result = A_u8Ascii -55;
	}
	return L_u8Result;
}
/**
 * @brief Parse the checksum byte.
 *
 * This function parses the checksum byte from the received record.
 *
 * @param ArrayOfOneRecord Pointer to the array containing the record.
 * @return The calculated checksum byte.
 */
u8 parse_checksum_byte(u8 *ArrayOfOneRecord) {
	u8 checksum = 0;
	u8 ascii_checksum[3] = {ArrayOfOneRecord[40], ArrayOfOneRecord[41], '\0'}; // Assuming the checksum byte is at index 38 and 39

    // Convert ASCII representation to integer
    for (u32 i = 0; ascii_checksum[i] != '\0'; ++i) {
        checksum *= 16; // Shift the value left by 4 bits
        if (ascii_checksum[i] >= '0' && ascii_checksum[i] <= '9') {
            checksum += ascii_checksum[i] - '0'; // Convert ASCII digit to integer
        } else if (ascii_checksum[i] >= 'A' && ascii_checksum[i] <= 'F') {
            checksum += ascii_checksum[i] - 'A' + 10; // Convert ASCII character to integer
        } else if (ascii_checksum[i] >= 'a' && ascii_checksum[i] <= 'f') {
            checksum += ascii_checksum[i] - 'a' + 10; // Convert ASCII character to integer
        }
    }

    return checksum;
}
/**
 * @brief Calculate the checksum of a record.
 *
 * This function calculates the checksum of a record.
 *
 * @param record Pointer to the record.
 * @param Length Length of the record.
 * @return The calculated checksum byte.
 */
u8 calculate_checksum(const u8 *record ,const u8 Length) {
    u32 sum = 0;

    // Iterate through the record, summing up the bytes
    for (u8 i = 0; i < Length; i += 2) {
        u32 byte;
        sscanf(&record[i], "%2X", &byte);
        sum += byte;
    }
    // Take the two's complement of the sum
    u8 checksum = (~sum + 1) & 0xFF;
    return checksum;
}
/**
 * @brief Parse received data.
 *
 * This function parses received data, extracts address and data information, and writes it to flash memory.
 *
 * @param AP_u8Data Pointer to the received data.
 */
void PARSER_voidParseData(u8* AP_u8Data)
{
	u8 L_u8CCDigitHigh;
	u8 L_u8CCDigitLow;
	u8 L_u8CCDigitCurrent;
	GPIO_voidSetPinMode(GPIOB_u8PORT,10,GPIO_u8OUTPUT);
	u8 L_u8AddressDigit0;
	u8 L_u8AddressDigit1;
	u8 L_u8AddressDigit2;
	u8 L_u8AddressDigit3;

	u8 L_u8DataDigit0;
	u8 L_u8DataDigit1;
	u8 L_u8DataDigit2;
	u8 L_u8DataDigit3;
	u8 L_u8ChecksumLow;
	u8 L_u8ChecksumHigh;
	u8 L_u8ChecksumValue;
	u8 Counter=0;
	while(AP_u8Data[Counter] != '\0' && AP_u8Data[Counter] != ' ')
	{
		Counter++;
	}
	L_u8ChecksumLow =PARSER_voidAsciiToHex(AP_u8Data[Counter-1]);
	L_u8ChecksumHigh=PARSER_voidAsciiToHex(AP_u8Data[Counter-2]);
	L_u8ChecksumValue =(L_u8ChecksumHigh << 4) | (L_u8ChecksumLow);
	u8 result = calculate_checksum(AP_u8Data,(Counter-2));
	if(result != L_u8ChecksumValue)
	{
		GPIO_voidSetPinValue(GPIOB_u8PORT,10,1);
	}
	else
	{
		/*To know Data Size*/
		L_u8CCDigitHigh = PARSER_voidAsciiToHex(AP_u8Data[0]);
		L_u8CCDigitLow = PARSER_voidAsciiToHex(AP_u8Data[1]);
		L_u8CCDigitCurrent = (L_u8CCDigitHigh << 4) | (L_u8CCDigitLow);

		/* L_u8AddressDigit0 << 3 => :CC
		 * To know lower 4 bits of the address*/
		L_u8AddressDigit0 = PARSER_voidAsciiToHex(AP_u8Data[2]);
		L_u8AddressDigit1 = PARSER_voidAsciiToHex(AP_u8Data[3]);
		L_u8AddressDigit2 = PARSER_voidAsciiToHex(AP_u8Data[4]);
		L_u8AddressDigit3 = PARSER_voidAsciiToHex(AP_u8Data[5]);
		/* Bit Masking -> for Low Address */
		G_u32Address &= 0xFFFF0000;
		/* L_u8AddressDigit0 << 12 => Little Endian */
		G_u32Address |= (L_u8AddressDigit0 << 12) | (L_u8AddressDigit1 << 8) | (L_u8AddressDigit2 << 4) | (L_u8AddressDigit3);

		/* receive each 4 Bytes into 1 element
		 *
		 * Hex = 4 Bytes  --->  data?????? */
		for(u8 L_u8Iterator=0; (L_u8Iterator < L_u8CCDigitCurrent/2); ++L_u8Iterator)
		{
			L_u8DataDigit0 = PARSER_voidAsciiToHex(AP_u8Data[(4 * L_u8Iterator) + 8]);/*the first element of the array where contain data is index 9*/
			L_u8DataDigit1 = PARSER_voidAsciiToHex(AP_u8Data[(4 * L_u8Iterator) + 9]);
			L_u8DataDigit2 = PARSER_voidAsciiToHex(AP_u8Data[(4 * L_u8Iterator) + 10]);
			L_u8DataDigit3 = PARSER_voidAsciiToHex(AP_u8Data[(4 * L_u8Iterator) + 11]);
			/* Hex is received big endian -> parasing into little endian {Processor is Little endian} */
			/*1 Iteration Stores 2 Bytes inside G_u16Data*/
			G_u16Data[L_u8Iterator] = (L_u8DataDigit2 << 12) | (L_u8DataDigit3 << 8) | (L_u8DataDigit0 << 4) | (L_u8DataDigit1);
		}
		/*Write in the Flash starting from the address 0x0800 xxxx (sector 1)
		 * So we need before uploading hex file we must edit the Linker script file to start from 0x0800 xxxx*/
		MFDI_voidFlashWrite(G_u32Address, G_u16Data, (L_u8CCDigitCurrent/2));
	}
}
/**
 * @brief Parse a record.
 *
 * This function parses a record to determine if it will be written to flash or not based on the record type.
 *
 * @param AP_u8Data Pointer to the record data.
 */
void PARSER_voidParseRecord(u8* AP_u8Data)
{
	/* character 9 => element 8
	 * Check on Record Type to know if it will be written in the flash or not
	 * if 0 that means the record will be written otherwise not */
	switch(AP_u8Data[7])
	{
	case '0' : PARSER_voidParseData(AP_u8Data);	 break;
	case '1' : /* End of File */			   		 break;
	case '4' : /* Set High Address */		    	 break;

	}
}
/**
 * @brief Copy data from the global array to the provided array.
 *
 * This function copies data from the global array G_u16Data to the provided array AP_u16Data.
 *
 * @param AP_u16Data Pointer to the destination array.
 */
void PARSER_voidMyDataArray(u16* AP_u16Data)
{
	for(u8 i=0;i<100;i++)
	{
		AP_u16Data[i] = G_u16Data[i];
	}
}


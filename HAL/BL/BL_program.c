/*
 * BL_program.c
 *
 *  Created on: Feb 20, 2024
 *      Author: Youssef Gamal & Mazen Musleh
 */
#include"../LIB/STD_TYPES.h"
#include"../LIB/BIT_MATH.h"

#include"../MGPIO/GPIO_interface.h"
#include"../UART/USART_interface.h"
#include"../MRCC/MRCC_interface.h"
#include"../MSTK/MSTK_interface.h"
#include"../Parser/PARSER_interface.h"
#include"../ESP/ESP_interface.h"
#include"BL_interface.h"

AddAsFunc G_CallAddress;
volatile u16 G_u16DataBuffer[100];
u8 OneRecordArray[100]={0}; //to store :020000040800F2
u8 Record_Counter=0;
static void copyString(u8 *source, u8 *destination);

/**
 * @brief Jump to the application code.
 *
 * This function sets the Vector Table Offset Register (SCB_VTOR) with the start
 * address of the application vector table, retrieves the start address of the
 * application, and calls the application code.
 */
void BL_voidJumpToApp(void)
{
	/*Set SCB_VTOR With the start address of the app vector table*/
	SCB_VTOR = 0x08008000;
	/*Set the Start address of the application in the pointer to func to be called*/
	G_CallAddress = *((AddAsFunc *)(0x08008004));
	/*Call the address*/
	G_CallAddress();
}
/**
 * @brief Parse received records.
 *
 * This function parses received records, extracts individual records, and calls
 * a parsing function to process each record.
 *
 * @param received_records The array containing received records.
 * @param array_size The size of the received_records array.
 * @param max_records The maximum number of records to parse.
 * @param max_record_length The maximum length of each record.
 */														  /*128*/				/*50*/
void BL_voidGetAndParseRecordNew(u8 received_records[],u32 array_size,u32 max_records,u32 max_record_length) {
    u32 record_index = 0;
    u32 record_length = 0;
    u32 num_records = 0;
    u32 extracted_index = 0;
    u8 in_record = 0;
    u8 extracted_records[158*50+158]={0};
    u8 startPrinting =0;
    // Loop through each element in the array
    for (int i = 0; i < array_size; i++){
        // Check if the current element is the start of a record
        if (received_records[i] == ':' && !in_record) {
        	if(received_records[i+1] == ':')
			{
				in_record = 1;
				record_index = i + 2;
			}
			else
			{
				in_record = 1;
				record_index = i + 1;
			}
        }
        // Check if the current element is the end of a record
        else if ((received_records[i] == '\n' || received_records[i] == '\r') && in_record) {
            in_record = 0;
            record_length = i - record_index;
            // Copy the record excluding the delimiters
            if (record_length > 0 && num_records < max_records) { // Ensure record length is non-zero and within bounds
                // Copy record
                for (u32 j = 0; j < record_length && j < max_record_length; j++) {
                    extracted_records[extracted_index++] = received_records[record_index + j];
                }
                extracted_records[extracted_index++] = '\r'; // Add "\r" at the end of each record
                num_records++;
            }
        }
    }
    // Null-terminate the extracted records array
    extracted_records[extracted_index] = '\0';

    u8 OneRecord[50]={0};
    u8 onerecord_index = 0;
    //Parsing One Record
    u32 i=0;
    while( i < extracted_index)
    {
        // Check if the current character is not a delimiter
        if (extracted_records[i] != '\r')
        {
                OneRecord[onerecord_index++] = extracted_records[i];
        }
        else
        {
            // Print the current record stored in OneRecord
        	PARSER_voidParseRecord(OneRecord);
            // Reset record_index for the next record
            onerecord_index = 0;
            // Clear OneRecord array for the next record
            for(u32 y=0;y<50;y++)
    			{
    				OneRecord[y]=0;
    			}
        }
        i++;
    }
}
/**
 * @brief Copy a string from source to destination.
 *
 * This function copies a string from the source to the destination until it
 * encounters a null terminator ('\0').
 *
 * @param source The source string.
 * @param destination The destination string.
 */
static void copyString(u8 *source, u8 *destination) {
    while (*source != '\0') {
        *destination = *source;
        source++;
        destination++;
    }
    *destination = '\0'; // Null-terminate the string
}

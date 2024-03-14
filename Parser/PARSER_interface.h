/*
 * PARSER_interface.h
 *
 *  Created on: Feb 10, 2024
 *      Author: Youssef Gamal & Mazen Musleh
 */

#ifndef PARSER_PARSER_INTERFACE_H_
#define PARSER_PARSER_INTERFACE_H_

void PARSER_voidParseData(u8* AP_u8Data);
u8 calculate_checksum(const u8 *record ,const u8 Length);
u8 parse_checksum_byte(u8 *ArrayOfOneRecord);

void PARSER_voidParseRecord(u8* AP_u8Data);

/* if it uses UART Protocol -> Data will be
 * received as Ascii, we need to transfer
 * this data from Ascii to Hex. */
u8 PARSER_voidAsciiToHex(u8 A_u8Ascii);

void PARSER_voidMyDataArray(u16* AP_u16Data);
#endif /* PARSER_PARSER_INTERFACE_H_ */

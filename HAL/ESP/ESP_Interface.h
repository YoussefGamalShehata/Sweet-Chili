/*
 * ESP_Interface.h
 *
 *  Created on: Feb 9, 2024
 *      Author: Youssef Gamal & Mazen Musleh
 */

#ifndef ESP_INTERFACE_H_
#define ESP_INTERFACE_H_

u8 ESP_Init(void);
void clear_buffer(void);
u8 CheckRecieve(u8 casenum);
u8 SendLength(u8 *Length);
u8 ConnectToServer(u8 * IP,u8 *PORT);
u8 Router_Connection(u8 *WIFI_Name,u8* Password);
u8 GETNew (u8* Link);
u8 isclosed(u16 num);
u8 isupdateNew(u8 *Link);

#endif /* ESP_INTERFACE_H_ */

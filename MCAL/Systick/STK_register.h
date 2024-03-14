/*
 * STK_register.h
 *
 *  Created on: Jan 27, 2024
 *      Author: Hesham Tayel
 */

#ifndef STK_STK_REGISTER_H_
#define STK_STK_REGISTER_H_


#define STK_BASE_ADDRESS	0xE000E010


typedef struct
{
	u32 CTRL;
	u32 LOAD;
	u32 VAL;
	u32 CALIB;
}STK_t;


#define STK 	((volatile STK_t*)(STK_BASE_ADDRESS))

#endif /* STK_STK_REGISTER_H_ */

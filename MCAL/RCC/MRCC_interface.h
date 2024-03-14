/*
 * MRCC_interface.h
 *
 *  Created on: Jan 25, 2024
 *      Author: Amira Magdy
 */

#ifndef MRCC_INTERFACE_H_
#define MRCC_INTERFACE_H_


/*Peripheral ID*/
#define MGPIOA_EN		0
#define MGPIOB_EN		1
#define MGPIOC_EN		2
#define MGPIOD_EN		3
#define MGPIOE_EN		4
#define MGPIOH_EN		7

#define CRC_EN			12
#define DMA1_EN			21
#define DMA2_EN			22

#define SYSCFG_EN		14
#define UART1_EN		4

#define TIM2_EN			0
#define TIM3_EN			1
#define TIM4_EN			2
#define TIM5_EN			3


/*Bus Name*/
typedef enum
{
	AHB1 = 0 ,
	AHB2 	 ,
	APB1	 ,
	APB2	 ,

}BusName_t;



/* CLK must be prebuild*/
void MRCC_voidInitSystemCLK(void);

void MRCC_voidEnablePeripheralCLK(BusName_t Copy_u8BusID, u8 Copy_u8PerNum);

void MRCC_voidDisablePeripheralCLK(BusName_t Copy_u8BusID, u8 Copy_u8PerNum);




#endif /* MRCC_INTERFACE_H_ */

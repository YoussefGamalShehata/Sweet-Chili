/*
 * Ultrasonic_config.h
 *
 *  Created on: Feb 20, 2024
 *      Author: Youssef Gamal
 */

#ifndef ULTRASONIC_ULTRASONIC_CONFIG_H_
#define ULTRASONIC_ULTRASONIC_CONFIG_H_
/*HC-SR04 Hardware Config*/
#define UTS_TRIG_PORT		MGPIOA_u8PORT		//Trig Pin
#define	UTS_TRIG_PIN		2
#define UTS_ECHO_PORT		MGPIOA_u8PORT	    //Echo Pin
#define	UTS_ECHO_PIN		1
/*Select MCAL Timer and Channel*/
/*Options for TIMER_NUMBER:
 * 		 				 1-MTIM_2
 * 		 				 2-MTIM_3
 * 		 				 3-MTIM_4
 * 		 				 4-MTIM_5
 *Options for TIMER_CHANNEL:
 *						 1-MTIM2_5_ch1
 *						 2-MTIM2_5_ch2
 *						 3-MTIM2_5_ch3
 *						 4-MTIM2_5_ch4
 */
#define TIMER_NUMBER	MTIM_5
#define TIMER_CHANNEL	MTIM2_5_ch2
#endif /* ULTRASONIC_ULTRASONIC_CONFIG_H_ */

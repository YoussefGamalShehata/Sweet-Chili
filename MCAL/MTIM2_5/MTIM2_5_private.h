/*
 * MTIM2_5_private.h
 *
 *  Created on: Jan 30, 2024
 *      Author: Youssef Gamal
 */
#ifndef MTIM2_5_MTIM2_5_PRIVATE_H_
#define MTIM2_5_MTIM2_5_PRIVATE_H_

/*clock devision*/
#define     CR1_CKD9		9
#define     CR1_CKD8		8
/* AUTO RELOAD */
#define  	CR1_ARPE		7
/*center aligned mode*/
#define    CR1_CMS6			6
#define    CR1_CMS5			5
/*counter direction*/
#define 	CR1_DIR			4
/*enable bit*/
#define 	CR1_CEN			0
/*----------------------------*/
#define CCRM1_CC1S0			0
#define CCRM1_CC1S1			1
#define CCRM1_IC1PSC3		3
#define CCRM1_IC1PSC2		2
#define CCRM1_OC1PE			3
#define CCRM1_OC1M_7		7
#define CCRM1_OC1M_6		6
#define CCRM1_OC1M_5		5
#define CCRM1_OC1M_4		4
#define CCRM1_CC2S0			8
#define CCRM1_CC2S1			9
#define CCRM1_IC2PSC10		10
#define CCRM1_IC2PSC11		11
#define CCRM1_OC2PE			11
#define CCRM1_OC2M_15		15
#define CCRM1_OC2M_14		14
#define CCRM1_OC2M_13		13
#define CCRM1_OC2M_12		12
#define CCRM2_CC3S0			0
#define CCRM2_CC3S1			1
#define CCRM2_IC3PSC3		3
#define CCRM2_IC3PSC2		2
#define CCRM2_OC3PE			3
#define CCRM2_OC3M_7		7
#define CCRM2_OC3M_6		6
#define CCRM2_OC3M_5		5
#define CCRM2_OC3M_4		4
#define CCRM2_CC4S0			8
#define CCRM2_CC4S1			9
#define CCRM2_IC4PSC10		10
#define CCRM2_IC4PSC11		11
#define CCRM2_OC4PE			11
#define CCRM2_OC4M_15		15
#define CCRM2_OC4M_14		14
#define CCRM2_OC4M_13		13
#define CCRM2_OC4M_12		12
/*---------------------------*/
#define CCER_CC4P			13
#define CCER_CC4NP			15
#define CCER_CC4E			12
#define CCER_CC3P			9
#define CCER_CC3NP			11
#define CCER_CC3E			8
#define CCER_CC2P			5
#define	CCER_CC2NP			7
#define CCER_CC2E			4
#define CCER_CC1NP			3
#define CCER_CC1P			1
#define CCER_CC1E			0
/*---------------------------*/

/*interrupt pin*/
#define		DIER_TIE		6
#define		DIER_CC4IE		4
#define		DIER_CC3IE		3
#define		DIER_CC2IE		2
#define		DIER_CC1IE		1
/*----------------------------*/
/*interrupt flag*/
#define     SR_UIF			0
/**********************************************/
#define 	MTIM_CUP			1
#define		MTIM_CDOWN			2
/***************************/
#endif /* MTIM2_5_MTIM2_5_PRIVATE_H_ */

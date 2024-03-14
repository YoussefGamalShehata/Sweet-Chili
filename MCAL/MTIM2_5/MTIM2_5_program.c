/*
 * MTIM2_5_program.c
 *
 *  Created on: Jan 30, 2024
 *      Author: Youssef Gamal
 */
/**********************************************/
/************************************************/

/***************	TIM2_5 Files include	***************/
/*Standard LIBS*/
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"
/*TIM 2_5 files*/
#include "MTIM2_5_interface.h"
#include "MTIM2_5_private.h"
#include "MTIM2_5_config.h"
#include "MTIM2_5_register.h"


/******** global variables *******/
static void(*MTIM3_pvCallBack)(void)=NULL;
static void(*MTIM4_pvCallBack)(void)=NULL;
static void(*MTIM5_pvCallBack)(void)=NULL;
/*********************************************/
/*********************************************/

/***************	TIM2_5 Functions Implementations	***************/

/**
 * @brief Initializes the specified timer.
 *
 * This function configures the control registers and settings of the specified timer.
 *
 * @param Copy_udtTimerNumber Enum specifying the timer number.
 * @retval 1 Function execution completed successfully.
 */

void TIM2_5_voidInitialize(MTIMx_NUMBER_t Copy_udtTimerNumber){
	switch (Copy_udtTimerNumber){
				case MTIM_2:
								/*no clock devision*/
							  CLR_BIT(MTIM2->CR1,CR1_CKD9);
							  CLR_BIT(MTIM2->CR1,CR1_CKD8);

							  /*enable AUTO RELOAD PRELOAD*/
							  SET_BIT(MTIM2->CR1,CR1_ARPE);
							  /*Set PreScaler*/
							  	 MTIM2->PSC=0x10;
							  /*set timer as edge aligned*/
							  	CLR_BIT(MTIM2->CR1,CR1_CMS6);
							  	CLR_BIT(MTIM2->CR1,CR1_CMS5);
							  /*Counter direction*/
							#if MTIM2_CMODE == MTIM_CDOWN
							  SET_BIT(MTIM2->CR1,CR1_DIR);
							#elif MTIM2_CMODE == MTIM_CUP
							  CLR_BIT(MTIM2->CR1,CR1_DIR);
							  #endif


							break;

				case MTIM_3 :
					/*no clock devision*/
								  CLR_BIT(MTIM3->CR1,CR1_CKD9);
								  CLR_BIT(MTIM3->CR1,CR1_CKD8);

								  /*enable AUTO RELOAD PRELOAD*/
								  SET_BIT(MTIM3->CR1,CR1_ARPE);
								  /*Set PreScaler*/
								  	 MTIM3->PSC=0x10;
								  /*set timer as edge aligned*/
								  	CLR_BIT(MTIM3->CR1,CR1_CMS6);
								  	CLR_BIT(MTIM3->CR1,CR1_CMS5);
								  /*Counter direction*/
								#if MTIM3_CMODE == MTIM_CDOWN
								  SET_BIT(MTIM3->CR1,CR1_DIR);
								#elif MTIM3_CMODE == MTIM_CUP
								  CLR_BIT(MTIM3->CR1,CR1_DIR);
								  #endif
								  	 break;
				case MTIM_4:
					/*no clock devision*/
								  CLR_BIT(MTIM4->CR1,CR1_CKD9);
								  CLR_BIT(MTIM4->CR1,CR1_CKD8);

								  /*enable AUTO RELOAD PRELOAD*/
								  SET_BIT(MTIM4->CR1,CR1_ARPE);
								  /*Set PreScaler*/
								  	 MTIM4->PSC=0x10;
								  /*set timer as edge aligned*/
								  	CLR_BIT(MTIM4->CR1,CR1_CMS6);
								  	CLR_BIT(MTIM4->CR1,CR1_CMS5);
								  /*Counter direction*/
								#if MTIM2_CMODE == MTIM_CDOWN
								  SET_BIT(MTIM4->CR1,CR1_DIR);
								#elif MTIM4_CMODE == MTIM_CUP
								  CLR_BIT(MTIM4->CR1,CR1_DIR);
								  #endif
								  break;
				case MTIM_5:
					/*no clock devision*/
				  CLR_BIT(MTIM5->CR1,CR1_CKD9);
				  CLR_BIT(MTIM5->CR1,CR1_CKD8);

				  /*enable AUTO RELOAD PRELOAD*/
				  SET_BIT(MTIM5->CR1,CR1_ARPE);
				  /*Set PreScaler*/
				  	 MTIM5->PSC=0x10;
				  /*set timer as edge aligned*/
				  	CLR_BIT(MTIM5->CR1,CR1_CMS6);
				  	CLR_BIT(MTIM5->CR1,CR1_CMS5);
				  /*Counter direction*/
				#if MTIM5_CMODE == MTIM_CDOWN
				  SET_BIT(MTIM5->CR1,CR1_DIR);
				#elif MTIM5_CMODE == MTIM_CUP
				  CLR_BIT(MTIM5->CR1,CR1_DIR);
				  #endif
					break;
					}
}
/**
 * @brief Starts the specified timer.
 *
 * This function starts the specified timer.
 *
 * @param Copy_udtTimerNumber Enum specifying the timer number.
 * @retval 1 Function execution completed successfully.
 */

void TIM2_5_voidTimerStart(MTIMx_NUMBER_t Copy_udtTimerNumber){
	switch (Copy_udtTimerNumber){
			case MTIM_2:
							SET_BIT(MTIM2->CR1,CR1_CEN);
							break;

			case MTIM_3 :
							SET_BIT(MTIM3->CR1,CR1_CEN);
							break;

			case MTIM_4:
							SET_BIT(MTIM4->CR1,CR1_CEN);
							break;

			case MTIM_5:
							SET_BIT(MTIM5->CR1,CR1_CEN);
							break;
				}

}
/**
 * @brief Stops the specified timer.
 *
 * This function stops the specified timer.
 *
 * @param Copy_udtTimerNumber Enum specifying the timer number.
 * @retval 1 Function execution completed successfully.
 */

void TIM2_5_voidTimerStop(MTIMx_NUMBER_t Copy_udtTimerNumber){
	switch (Copy_udtTimerNumber){
			case MTIM_2: CLR_BIT(MTIM2->CR1,CR1_CEN);
						break;

			case MTIM_3 : CLR_BIT(MTIM3->CR1,CR1_CEN);
						break;

			case MTIM_4 : CLR_BIT(MTIM4->CR1,CR1_CEN);
						break;

			case MTIM_5 : CLR_BIT(MTIM5->CR1,CR1_CEN);
						break;
				}
}



/**
 * @brief Enables interrupts for the specified timer.
 *
 * This function enables interrupts for the specified timer.
 *
 * @param Copy_udtTimerNumber Enum specifying the timer number.
 * @retval 1 Function execution completed successfully.
 */

void TIM2_5_voidEnableInterrupt(MTIMx_NUMBER_t Copy_udtTimerNumber){
	switch (Copy_udtTimerNumber){
			case MTIM_2: SET_BIT(MTIM2->CR1,DIER_TIE);
						break;

			case MTIM_3 : SET_BIT(MTIM3->CR1,DIER_TIE);
						break;
			case MTIM_4 : SET_BIT(MTIM4->CR1,DIER_TIE);
						break;

			case MTIM_5 : SET_BIT(MTIM5->CR1,DIER_TIE);
						break;
				}
}
/**
 * @brief Disables interrupts for the specified timer.
 *
 * This function disables interrupts for the specified timer.
 *
 * @param Copy_udtTimerNumber Enum specifying the timer number.
 * @retval 1 Function execution completed successfully.
 */
void TIM2_5_voidDisableInterrupt(MTIMx_NUMBER_t Copy_udtTimerNumber){
	switch (Copy_udtTimerNumber){
			case MTIM_2: CLR_BIT(MTIM2->CR1,DIER_TIE);
						break;

			case MTIM_3 : CLR_BIT(MTIM3->CR1,DIER_TIE);
						break;

			case MTIM_4 : CLR_BIT(MTIM4->CR1,DIER_TIE);
						break;

			case MTIM_5 : CLR_BIT(MTIM5->CR1,DIER_TIE);
						break;
				}
}
/**
 * @brief Performs a busy-wait delay using the specified timer.
 *
 * This function performs a busy-wait delay using the specified timer.
 *
 * @param Copy_udtTimerNumber Enum specifying the timer number.
 * @param Copy_u32TickNum The number of ticks to wait.
 * @retval 1 Function execution completed successfully.
 */
void TIM2_5_voidSetBusyWait(MTIMx_NUMBER_t Copy_udtTimerNumber,u32 Copy_u32TickNum){
	switch (Copy_udtTimerNumber){
	case MTIM_2:
					/*clear timer value */
					MTIM2->CNT=0x00000000;
					/*set PreLoad value */
					MTIM2->ARR=Copy_u32TickNum;
					/*start timer*/
					SET_BIT(MTIM2->CR1,CR1_CEN);
					/*wait for timer*/
					while(GET_BIT(MTIM2->SR,SR_UIF)!=1);
					/*stop timer*/
					CLR_BIT(MTIM2->CR1,CR1_CEN);
					break;
	case MTIM_3: /*clear timer value */
		/*clear timer value */
			MTIM3->CNT=0x00000000;
			/*set PreLoad value */
			MTIM3->ARR=Copy_u32TickNum;
			/*start timer*/
			SET_BIT(MTIM3->CR1,CR1_CEN);
			/*wait for timer*/
			while(GET_BIT(MTIM3->SR,SR_UIF)!=1);
			/*stop timer*/
			CLR_BIT(MTIM3->CR1,CR1_CEN);
			break;
	case MTIM_4: /*clear timer value */
		/*clear timer value */
			MTIM4->CNT=0x00000000;
			/*set PreLoad value */
			MTIM4->ARR=Copy_u32TickNum;
			/*start timer*/
			SET_BIT(MTIM4->CR1,CR1_CEN);
			/*wait for timer*/
			while(GET_BIT(MTIM4->SR,SR_UIF)!=1);
			/*stop timer*/
			CLR_BIT(MTIM4->CR1,CR1_CEN);
			break;
	case MTIM_5: /*clear timer value */
		/*clear timer value */
		MTIM5->CNT=0x00000000;
		/*set PreLoad value */
		MTIM5->ARR=Copy_u32TickNum;
		/*start timer*/
		SET_BIT(MTIM5->CR1,CR1_CEN);
		/*wait for timer*/
		while(GET_BIT(MTIM5->SR,SR_UIF)!=1);
		/*stop timer*/
		CLR_BIT(MTIM5->CR1,CR1_CEN);
		break;
	}
	}
/**
 * @brief Initializes PWM configuration for the specified timer and channel.
 *
 * This function initializes PWM configuration for the specified timer and channel.
 *
 * @param Copy_udtTimerNumber Enum specifying the timer number.
 * @param Copy_udtPWMchannel Enum specifying the PWM channel.
 * @retval 1 Function execution completed successfully.
 */
void TIM2_5_voidPWM_Init(MTIMx_NUMBER_t Copy_udtTimerNumber,MTIM2_5_PWM_channel_num Copy_udtPWMchannel){
		switch (Copy_udtTimerNumber){
		case MTIM_2:
			switch(Copy_udtPWMchannel){
			case MTIM2_5_ch1:
				/*set the preScaler value in the preScaler register*/
				MTIM2->PSC=TIM2_PRESCALER;
				/*select the pwm mode*/
				SET_BIT(MTIM2->CCMR1,CCRM1_OC1M_6);
				SET_BIT(MTIM2->CCMR1,CCRM1_OC1M_5);
				CLR_BIT(MTIM2->CCMR1,CCRM1_OC1M_4);
				/*enable output compre auto reload register*/
				SET_BIT(MTIM2->CCMR1,CCRM1_OC1PE);
				/*enable out put on the corresponding PIN*/
				SET_BIT(MTIM2->CCER,CCER_CC1E);
				 break;
			case MTIM2_5_ch2:
				/*set the preScaler value in the preScaler register*/
				MTIM3->PSC=TIM2_PRESCALER;
				/*select the pwm mode*/
				SET_BIT(MTIM2->CCMR1,CCRM1_OC2M_14);
				SET_BIT(MTIM2->CCMR1,CCRM1_OC2M_13);
				CLR_BIT(MTIM2->CCMR1,CCRM1_OC2M_12);
				/*enable output compre auto reload register*/
				SET_BIT(MTIM2->CCMR1,CCRM1_OC2PE);
				/*enable out put on the corresponding PIN*/
				SET_BIT(MTIM2->CCER,CCER_CC2E);
				  break;
			case MTIM2_5_ch3:
				/*set the preScaler value in the preScaler register*/
				MTIM2->PSC=TIM2_PRESCALER;
				/*select the pwm mode*/
				SET_BIT(MTIM2->CCMR2,CCRM2_OC3M_6);
				SET_BIT(MTIM2->CCMR2,CCRM2_OC3M_5);
				CLR_BIT(MTIM2->CCMR2,CCRM2_OC3M_4);
				/*enable output compre auto reload register*/
				SET_BIT(MTIM2->CCMR2,CCRM2_OC3PE);
				/*enable out put on the corresponding PIN*/
				SET_BIT(MTIM2->CCER,CCER_CC3E);
				break;
			case MTIM2_5_ch4:
				/*set the preScaler value in the preScaler register*/
				MTIM2->PSC=TIM2_PRESCALER;
				/*select the pwm mode*/
				SET_BIT(MTIM2->CCMR2,CCRM2_OC4M_14);
				SET_BIT(MTIM2->CCMR2,CCRM2_OC4M_13);
				CLR_BIT(MTIM2->CCMR2,CCRM2_OC4M_12);
				/*enable output compre auto reload register*/
				SET_BIT(MTIM2->CCMR2,CCRM2_OC4PE);
				/*enable out put on the corresponding PIN*/
				SET_BIT(MTIM2->CCER,CCER_CC4E);
				 break;
			}
			break;
		case MTIM_3:
			switch(Copy_udtPWMchannel){
			case MTIM2_5_ch1:
				/*set the preScaler value in the preScaler register*/
				MTIM3->PSC=TIM3_PRESCALER;
				/*select the pwm mode*/
				SET_BIT(MTIM3->CCMR1,CCRM1_OC1M_6);
				SET_BIT(MTIM3->CCMR1,CCRM1_OC1M_5);
				CLR_BIT(MTIM3->CCMR1,CCRM1_OC1M_4);
				/*enable output compre auto reload register*/
				SET_BIT(MTIM3->CCMR1,CCRM1_OC1PE);
				/*enable out put on the corresponding PIN*/
				SET_BIT(MTIM3->CCER,CCER_CC1E);
				/*set the frequency of the PWM*/
				MTIM3->ARR=10000;
				 break;
			case MTIM2_5_ch2:
				/*set the preScaler value in the preScaler register*/
				MTIM3->PSC=TIM3_PRESCALER;
				/*select the pwm mode*/
				SET_BIT(MTIM3->CCMR1,CCRM1_OC2M_14);
				SET_BIT(MTIM3->CCMR1,CCRM1_OC2M_13);
				CLR_BIT(MTIM3->CCMR1,CCRM1_OC2M_12);
				/*enable output compre auto reload register*/
				SET_BIT(MTIM3->CCMR1,CCRM1_OC2PE);
				/*enable out put on the corresponding PIN*/
				SET_BIT(MTIM3->CCER,CCER_CC2E);
				/*set the frequency of the PWM*/
				MTIM3->ARR=10000;
		    	  break;
			case MTIM2_5_ch3:
				/*set the preScaler value in the preScaler register*/
				MTIM3->PSC=TIM3_PRESCALER;
				/*select the pwm mode*/
				SET_BIT(MTIM3->CCMR2,CCRM2_OC3M_6);
				SET_BIT(MTIM3->CCMR2,CCRM2_OC3M_5);
				CLR_BIT(MTIM3->CCMR2,CCRM2_OC3M_4);
				/*enable output compre auto reload register*/
				SET_BIT(MTIM3->CCMR2,CCRM2_OC3PE);
				/*enable out put on the corresponding PIN*/
				SET_BIT(MTIM3->CCER,CCER_CC3E);
				break;
			case MTIM2_5_ch4:
				/*set the preScaler value in the preScaler register*/
				MTIM3->PSC=TIM3_PRESCALER;
				/*select the pwm mode*/
				SET_BIT(MTIM3->CCMR2,CCRM2_OC4M_14);
				SET_BIT(MTIM3->CCMR2,CCRM2_OC4M_13);
				CLR_BIT(MTIM3->CCMR2,CCRM2_OC4M_12);
				/*enable output compre auto reload register*/
				SET_BIT(MTIM3->CCMR2,CCRM2_OC4PE);
				/*enable out put on the corresponding PIN*/
				SET_BIT(MTIM3->CCER,CCER_CC4E);
				 break;
			}
			break;
		case MTIM_4:
			switch(Copy_udtPWMchannel){
				case MTIM2_5_ch1:
					/*set the preScaler value in the preScaler register*/
					MTIM4->PSC=TIM4_PRESCALER;
					/*select the pwm mode*/
					SET_BIT(MTIM4->CCMR1,CCRM1_OC1M_6);
					SET_BIT(MTIM4->CCMR1,CCRM1_OC1M_5);
					CLR_BIT(MTIM4->CCMR1,CCRM1_OC1M_4);
					/*enable output compre auto reload register*/
					SET_BIT(MTIM4->CCMR1,CCRM1_OC1PE);
					/*enable out put on the corresponding PIN*/
					SET_BIT(MTIM4->CCER,CCER_CC1E);
					 break;
				case MTIM2_5_ch2:
					/*set the preScaler value in the preScaler register*/
					MTIM4->PSC=TIM4_PRESCALER;
					/*select the pwm mode*/
					SET_BIT(MTIM4->CCMR1,CCRM1_OC2M_14);
					SET_BIT(MTIM4->CCMR1,CCRM1_OC2M_13);
					CLR_BIT(MTIM4->CCMR1,CCRM1_OC2M_12);
					/*enable output compre auto reload register*/
					SET_BIT(MTIM4->CCMR1,CCRM1_OC2PE);
					/*enable out put on the corresponding PIN*/
					SET_BIT(MTIM4->CCER,CCER_CC2E);
			    	  break;
				case MTIM2_5_ch3:
					/*set the preScaler value in the preScaler register*/
					MTIM4->PSC=TIM4_PRESCALER;
					/*select the pwm mode*/
					SET_BIT(MTIM4->CCMR2,CCRM2_OC3M_6);
					SET_BIT(MTIM4->CCMR2,CCRM2_OC3M_5);
					CLR_BIT(MTIM4->CCMR2,CCRM2_OC3M_4);
					/*enable output compre auto reload register*/
					SET_BIT(MTIM4->CCMR2,CCRM2_OC3PE);
					/*enable out put on the corresponding PIN*/
					SET_BIT(MTIM4->CCER,CCER_CC3E);
					break;
				case MTIM2_5_ch4:
					/*set the preScaler value in the preScaler register*/
					MTIM4->PSC=TIM4_PRESCALER;
					/*select the pwm mode*/
					SET_BIT(MTIM4->CCMR2,CCRM2_OC4M_14);
					SET_BIT(MTIM4->CCMR2,CCRM2_OC4M_13);
					CLR_BIT(MTIM4->CCMR2,CCRM2_OC4M_12);
					/*enable output compre auto reload register*/
					SET_BIT(MTIM4->CCMR2,CCRM2_OC4PE);
					/*enable out put on the corresponding PIN*/
					SET_BIT(MTIM4->CCER,CCER_CC4E);
					 break;
				}
				break;
		case MTIM_5:
			switch(Copy_udtPWMchannel){
				case MTIM2_5_ch1:
					/*set the preScaler value in the preScaler register*/
					MTIM5->PSC=TIM5_PRESCALER;
					/*select the pwm mode*/
					SET_BIT(MTIM5->CCMR1,CCRM1_OC1M_6);
					SET_BIT(MTIM5->CCMR1,CCRM1_OC1M_5);
					CLR_BIT(MTIM5->CCMR1,CCRM1_OC1M_4);
					/*enable output compre auto reload register*/
					SET_BIT(MTIM5->CCMR1,CCRM1_OC1PE);
					/*enable out put on the corresponding PIN*/
					SET_BIT(MTIM5->CCER,CCER_CC1E);
					 break;
				case MTIM2_5_ch2:
					/*set the preScaler value in the preScaler register*/
					MTIM5->PSC=TIM5_PRESCALER;
					/*select the pwm mode*/
					SET_BIT(MTIM5->CCMR1,CCRM1_OC2M_14);
					SET_BIT(MTIM5->CCMR1,CCRM1_OC2M_13);
					CLR_BIT(MTIM5->CCMR1,CCRM1_OC2M_12);
					/*enable output compre auto reload register*/
					SET_BIT(MTIM5->CCMR1,CCRM1_OC2PE);
					/*enable out put on the corresponding PIN*/
					SET_BIT(MTIM5->CCER,CCER_CC2E);
			    	  break;
				case MTIM2_5_ch3:
					/*set the preScaler value in the preScaler register*/
					MTIM5->PSC=TIM5_PRESCALER;
					/*select the pwm mode*/
					SET_BIT(MTIM5->CCMR2,CCRM2_OC3M_6);
					SET_BIT(MTIM5->CCMR2,CCRM2_OC3M_5);
					CLR_BIT(MTIM5->CCMR2,CCRM2_OC3M_4);
					/*enable output compre auto reload register*/
					SET_BIT(MTIM5->CCMR2,CCRM2_OC3PE);
					/*enable out put on the corresponding PIN*/
					SET_BIT(MTIM5->CCER,CCER_CC3E);
					break;
				case MTIM2_5_ch4:
					/*set the preScaler value in the preScaler register*/
					MTIM5->PSC=TIM5_PRESCALER;
					/*select the pwm mode*/
					SET_BIT(MTIM5->CCMR2,CCRM2_OC4M_14);
					SET_BIT(MTIM5->CCMR2,CCRM2_OC4M_13);
					CLR_BIT(MTIM5->CCMR2,CCRM2_OC4M_12);
					/*enable output compre auto reload register*/
					SET_BIT(MTIM5->CCMR2,CCRM2_OC4PE);
					/*enable out put on the corresponding PIN*/
					SET_BIT(MTIM5->CCER,CCER_CC4E);
					 break;
				}
				break;
	}
}

/**
 * @brief Sets the frequency and duty cycle of PWM for the specified timer and channel.
 *
 * This function sets the frequency and duty cycle of PWM for the specified timer and channel.
 *
 * @param Copy_udtTimerNumber Enum specifying the timer number.
 * @param Copy_udtPWMchannel Enum specifying the PWM channel.
 * @param Copy_u16Frequancy The PWM frequency.
 * @param Copy_DutyCycle The PWM duty cycle.
 * @retval 1 Function execution completed successfully.
 */
void TIM2_5_voidSetPWM(MTIMx_NUMBER_t Copy_udtTimerNumber,MTIM2_5_PWM_channel_num Copy_udtPWMchannel,u16 Copy_u16Frequancy,u16 Copy_DutyCycle){
switch(Copy_udtTimerNumber){
case MTIM_2:
	switch(Copy_udtPWMchannel){
		case MTIM2_5_ch1:
						/*set the frequency of the PWM*/
						MTIM2->ARR=Copy_u16Frequancy;
						/*set the duty cycle of the PWM*/
						MTIM2->CCR1=Copy_DutyCycle;
						/*enable timer to start the PWM*/
						SET_BIT(MTIM2->CR1,CR1_CEN);
						break;
		case MTIM2_5_ch2:
						/*set the frequency of the PWM*/
						MTIM2->ARR=Copy_u16Frequancy;
						/*set the duty cycle of the PWM*/
						MTIM2->CCR2=Copy_DutyCycle;
						/*enable timer to start the PWM*/
						SET_BIT(MTIM2->CR1,CR1_CEN);
							break;
		case MTIM2_5_ch3:
						/*set the frequency of the PWM*/
						MTIM2->ARR=Copy_u16Frequancy;
						/*set the duty cycle of the PWM*/
						MTIM2->CCR3=Copy_DutyCycle;
						/*enable timer to start the PWM*/
						SET_BIT(MTIM2->CR1,CR1_CEN);
						break;
					case MTIM2_5_ch4:
						/*set the frequency of the PWM*/
						MTIM2->ARR=Copy_u16Frequancy;
						/*set the duty cycle of the PWM*/
						MTIM2->CCR4=Copy_DutyCycle;
						/*enable timer to start the PWM*/
						SET_BIT(MTIM2->CR1,CR1_CEN);
						break;
					}
				break;
case MTIM_3:
			switch(Copy_udtPWMchannel){
			case MTIM2_5_ch1:
							/*set the duty cycle of the PWM*/
							MTIM3->CCR1=Copy_DutyCycle;
							/*enable timer to start the PWM*/
							SET_BIT(MTIM3->CR1,CR1_CEN);
							break;
			case MTIM2_5_ch2:
							/*set the duty cycle of the PWM*/
							MTIM3->CCR2=Copy_DutyCycle;
							/*enable timer to start the PWM*/
							SET_BIT(MTIM3->CR1,CR1_CEN);
								break;
			case MTIM2_5_ch3:
							/*set the frequency of the PWM*/
							MTIM3->ARR=Copy_u16Frequancy;
							/*set the duty cycle of the PWM*/
							MTIM3->CCR3=Copy_DutyCycle;
							/*enable timer to start the PWM*/
							SET_BIT(MTIM3->CR1,CR1_CEN);
							break;
						case MTIM2_5_ch4:
							/*set the frequency of the PWM*/
							MTIM3->ARR=Copy_u16Frequancy;
							/*set the duty cycle of the PWM*/
							MTIM3->CCR4=Copy_DutyCycle;
							/*enable timer to start the PWM*/
							SET_BIT(MTIM3->CR1,CR1_CEN);
							break;
						}
					break;
case MTIM_4:
			switch(Copy_udtPWMchannel){
			case MTIM2_5_ch1:
							/*set the frequency of the PWM*/
							MTIM4->ARR=Copy_u16Frequancy;
							/*set the duty cycle of the PWM*/
							MTIM4->CCR1=Copy_DutyCycle;
							/*enable timer to start the PWM*/
							SET_BIT(MTIM4->CR1,CR1_CEN);
							break;
			case MTIM2_5_ch2:
							/*set the frequency of the PWM*/
							MTIM4->ARR=Copy_u16Frequancy;
							/*set the duty cycle of the PWM*/
							MTIM4->CCR2=Copy_DutyCycle;
							/*enable timer to start the PWM*/
							SET_BIT(MTIM4->CR1,CR1_CEN);
							break;
			case MTIM2_5_ch3:
							/*set the frequency of the PWM*/
							MTIM4->ARR=Copy_u16Frequancy;
							/*set the duty cycle of the PWM*/
							MTIM4->CCR3=Copy_DutyCycle;
							/*enable timer to start the PWM*/
							SET_BIT(MTIM4->CR1,CR1_CEN);
							break;
			case MTIM2_5_ch4:
							/*set the frequency of the PWM*/
							MTIM4->ARR=Copy_u16Frequancy;
							/*set the duty cycle of the PWM*/
							MTIM4->CCR4=Copy_DutyCycle;
							/*enable timer to start the PWM*/
							SET_BIT(MTIM4->CR1,CR1_CEN);
							break;
					}
					break;
case MTIM_5:
			switch(Copy_udtPWMchannel){
			case MTIM2_5_ch1:
							/*set the frequency of the PWM*/
							MTIM5->ARR=Copy_u16Frequancy;
							/*set the duty cycle of the PWM*/
							MTIM5->CCR1=Copy_DutyCycle;
							/*enable timer to start the PWM*/
							SET_BIT(MTIM5->CR1,CR1_CEN);
							break;
			case MTIM2_5_ch2:
							/*set the frequency of the PWM*/
							MTIM5->ARR=Copy_u16Frequancy;
							/*set the duty cycle of the PWM*/
							MTIM5->CCR2=Copy_DutyCycle;
							/*enable timer to start the PWM*/
							SET_BIT(MTIM5->CR1,CR1_CEN);
							break;
			case MTIM2_5_ch3:
							/*set the frequency of the PWM*/
							MTIM5->ARR=Copy_u16Frequancy;
							/*set the duty cycle of the PWM*/
							MTIM5->CCR3=Copy_DutyCycle;
							/*enable timer to start the PWM*/
							SET_BIT(MTIM5->CR1,CR1_CEN);
							break;
			case MTIM2_5_ch4:
							/*set the frequency of the PWM*/
							MTIM5->ARR=Copy_u16Frequancy;
							/*set the duty cycle of the PWM*/
							MTIM5->CCR4=Copy_DutyCycle;
							/*enable timer to start the PWM*/
							SET_BIT(MTIM5->CR1,CR1_CEN);
							break;
					}
					break;
}
}

/**
 * @brief Initializes Input Capture Unit (ICU) for the specified timer and channel.
 *
 * This function configures the ICU settings for the specified timer and channel.
 *
 * @param Copy_udtTimerNumber Enum specifying the timer number.
 * @param Copy_udtICUchannel Enum specifying the ICU channel.
 */
void TIM2_5_voidICU_init(MTIMx_NUMBER_t Copy_udtTimerNumber,MTIM2_5_PWM_channel_num Copy_udtICUchannel){
	switch (Copy_udtTimerNumber){
	case MTIM_3:
		switch(Copy_udtICUchannel){
		case MTIM2_5_ch1:
			/*Select ICU*/
			CLR_BIT(MTIM3->CCMR1,CCRM1_CC1S1);
			SET_BIT(MTIM3->CCMR1,CCRM1_CC1S0);
			/*set the ICU FILTER value=0*/
			CLR_BIT(MTIM3->CCMR1,CCRM1_OC1M_7);
			CLR_BIT(MTIM3->CCMR1,CCRM1_OC1M_6);
			CLR_BIT(MTIM3->CCMR1,CCRM1_OC1M_5);
			CLR_BIT(MTIM3->CCMR1,CCRM1_OC1M_4);
			/*set ICU PRESCALER= no preScaler*/
			CLR_BIT(MTIM3->CCMR1,CCRM1_IC1PSC3);
			CLR_BIT(MTIM3->CCMR1,CCRM1_IC1PSC2);
			/*select the rising edge sense control*/
			SET_BIT(MTIM3->CCER,CCER_CC1P);
			SET_BIT(MTIM3->CCER,CCER_CC1NP);
			/*enable capture on the corresponding PIN*/
			SET_BIT(MTIM3->CCER,CCER_CC1E);

			/* Set prescaler 16 */
			MTIM3->PSC = 15;
			/* Set Preload */
			MTIM3->ARR=65535;
			//CLR_BIT(MTIM3->CR1,CR1_ARPE);

			//SET_BIT(MTIM3->CR1,1);

			/*enable interrupt*/
			SET_BIT(MTIM3->DIER,DIER_CC1IE);
			/*enable timer to start ICU*/
			SET_BIT(MTIM3->CR1,CR1_CEN);

			break;
		case MTIM2_5_ch2:
			/*Select ICU*/
			CLR_BIT(MTIM3->CCMR1,CCRM1_CC2S1);
			SET_BIT(MTIM3->CCMR1,CCRM1_CC2S0);
			/*set the ICU FILTER value=0*/
			CLR_BIT(MTIM3->CCMR1,CCRM1_OC2M_15);
			CLR_BIT(MTIM3->CCMR1,CCRM1_OC2M_14);
			CLR_BIT(MTIM3->CCMR1,CCRM1_OC2M_13);
			CLR_BIT(MTIM3->CCMR1,CCRM1_OC2M_12);
			/*set ICU PRESCALER= no preScaler*/
			CLR_BIT(MTIM3->CCMR1,CCRM1_IC2PSC10);
			CLR_BIT(MTIM3->CCMR1,CCRM1_IC2PSC11);
			/*select the rising edge sense control*/
			SET_BIT(MTIM3->CCER,CCER_CC2NP);
			SET_BIT(MTIM3->CCER,CCER_CC2P);
			/*enable capture on the corresponding PIN*/
			SET_BIT(MTIM3->CCER,CCER_CC2E);
			/*enable interrupt*/
			SET_BIT(MTIM3->DIER,DIER_CC2IE);
			 break;
		case MTIM2_5_ch3:
				/*Select ICU*/
				CLR_BIT(MTIM3->CCMR2,CCRM2_CC3S1);
				SET_BIT(MTIM3->CCMR2,CCRM2_CC3S0);
				/*set the ICU FILTER value=0*/
				CLR_BIT(MTIM3->CCMR2,CCRM2_OC3M_7);
				CLR_BIT(MTIM3->CCMR2,CCRM2_OC3M_6);
				CLR_BIT(MTIM3->CCMR2,CCRM2_OC3M_5);
				CLR_BIT(MTIM3->CCMR2,CCRM2_OC3M_4);
				/*set ICU PRESCALER= no preScaler*/
				CLR_BIT(MTIM3->CCMR2,CCRM2_IC3PSC3);
				CLR_BIT(MTIM3->CCMR2,CCRM2_IC3PSC2);
				/*select the rising edge sense control*/
				SET_BIT(MTIM3->CCER,CCER_CC3NP);
				SET_BIT(MTIM3->CCER,CCER_CC3P);
				/*enable capture on the corresponding PIN*/
				SET_BIT(MTIM3->CCER,CCER_CC3E);
				/*enable interrupt*/
				SET_BIT(MTIM3->DIER,DIER_CC3IE);
				 break;
			case MTIM2_5_ch4:
				/*Select ICU*/
				CLR_BIT(MTIM3->CCMR2,CCRM2_CC4S1);
				SET_BIT(MTIM3->CCMR2,CCRM2_CC4S0);
				/*set the ICU FILTER value=0*/
				CLR_BIT(MTIM3->CCMR2,CCRM2_OC4M_15);
				CLR_BIT(MTIM3->CCMR2,CCRM2_OC4M_14);
				CLR_BIT(MTIM3->CCMR2,CCRM2_OC4M_13);
				CLR_BIT(MTIM3->CCMR2,CCRM2_OC4M_12);
				/*set ICU PRESCALER= no preScaler*/
				CLR_BIT(MTIM3->CCMR2,CCRM2_IC4PSC10);
				CLR_BIT(MTIM3->CCMR2,CCRM2_IC4PSC11);
				/*select the rising edge sense control*/
				SET_BIT(MTIM3->CCER,CCER_CC4NP);
				SET_BIT(MTIM3->CCER,CCER_CC4P);
				/*enable capture on the corresponding PIN*/
				SET_BIT(MTIM3->CCER,CCER_CC4E);
				/*enable interrupt*/
				SET_BIT(MTIM3->DIER,DIER_CC4IE);
				 break;
}
		break;
		case MTIM_4:
			switch(Copy_udtICUchannel){
			case MTIM2_5_ch1:
				/*Select ICU*/
				CLR_BIT(MTIM4->CCMR1,CCRM1_CC1S1);
				SET_BIT(MTIM4->CCMR1,CCRM1_CC1S0);
				/*set the ICU FILTER value=0*/
				CLR_BIT(MTIM4->CCMR1,CCRM1_OC1M_7);
				CLR_BIT(MTIM4->CCMR1,CCRM1_OC1M_6);
				CLR_BIT(MTIM4->CCMR1,CCRM1_OC1M_5);
				CLR_BIT(MTIM4->CCMR1,CCRM1_OC1M_4);
				/*set ICU PRESCALER= no preScaler*/
				CLR_BIT(MTIM4->CCMR1,CCRM1_IC1PSC3);
				CLR_BIT(MTIM4->CCMR1,CCRM1_IC1PSC2);
				/*select the rising edge sense control*/
				SET_BIT(MTIM4->CCER,CCER_CC1P);
				SET_BIT(MTIM4->CCER,CCER_CC1NP);
				/*enable capture on the corresponding PIN*/
				SET_BIT(MTIM4->CCER,CCER_CC1E);
				/*enable interrupt*/
				SET_BIT(MTIM4->DIER,DIER_CC1IE);
				/* Set prescaler 16 */
				MTIM4->PSC = 15;
				/* Set Preload */
				MTIM4->ARR=65535;
				//CLR_BIT(MTIM3->CR1,CR1_ARPE);

				//SET_BIT(MTIM3->CR1,1);

				/*enable interrupt*/
				SET_BIT(MTIM4->DIER,DIER_CC1IE);
				/*enable timer to start ICU*/
				SET_BIT(MTIM4->CR1,CR1_CEN);
				 break;
			case MTIM2_5_ch2:
				/*Select ICU*/
				CLR_BIT(MTIM4->CCMR1,CCRM1_CC2S1);
				SET_BIT(MTIM4->CCMR1,CCRM1_CC2S0);
				/*set the ICU FILTER value=0*/
				CLR_BIT(MTIM4->CCMR1,CCRM1_OC2M_15);
				CLR_BIT(MTIM4->CCMR1,CCRM1_OC2M_14);
				CLR_BIT(MTIM4->CCMR1,CCRM1_OC2M_13);
				CLR_BIT(MTIM4->CCMR1,CCRM1_OC2M_12);
				/*set ICU PRESCALER= no preScaler*/
				CLR_BIT(MTIM4->CCMR1,CCRM1_IC2PSC10);
				CLR_BIT(MTIM4->CCMR1,CCRM1_IC2PSC11);
				/*select the rising edge sense control*/
				SET_BIT(MTIM4->CCER,CCER_CC2NP);
				SET_BIT(MTIM4->CCER,CCER_CC2P);
				/*enable capture on the corresponding PIN*/
				SET_BIT(MTIM4->CCER,CCER_CC2E);
				/*enable interrupt*/
				SET_BIT(MTIM4->DIER,DIER_CC2IE);
				/* Set prescaler 16 */
				MTIM4->PSC = 15;
				/* Set Preload */
				MTIM4->ARR=65535;
				//CLR_BIT(MTIM3->CR1,CR1_ARPE);

				//SET_BIT(MTIM3->CR1,1);

				/*enable interrupt*/
				SET_BIT(MTIM4->DIER,DIER_CC2IE);
				/*enable timer to start ICU*/
				SET_BIT(MTIM4->CR1,CR1_CEN);
				 break;
			case MTIM2_5_ch3:
					/*Select ICU*/
					CLR_BIT(MTIM4->CCMR2,CCRM2_CC3S1);
					SET_BIT(MTIM4->CCMR2,CCRM2_CC3S0);
					/*set the ICU FILTER value=0*/
					CLR_BIT(MTIM4->CCMR2,CCRM2_OC3M_7);
					CLR_BIT(MTIM4->CCMR2,CCRM2_OC3M_6);
					CLR_BIT(MTIM4->CCMR2,CCRM2_OC3M_5);
					CLR_BIT(MTIM4->CCMR2,CCRM2_OC3M_4);
					/*set ICU PRESCALER= no preScaler*/
					CLR_BIT(MTIM4->CCMR2,CCRM2_IC3PSC3);
					CLR_BIT(MTIM4->CCMR2,CCRM2_IC3PSC2);
					/*select the rising edge sense control*/
					SET_BIT(MTIM4->CCER,CCER_CC3NP);
					SET_BIT(MTIM4->CCER,CCER_CC3P);
					/*enable capture on the corresponding PIN*/
					SET_BIT(MTIM4->CCER,CCER_CC3E);
					/*enable interrupt*/
					SET_BIT(MTIM4->DIER,DIER_CC3IE);
					 break;
				case MTIM2_5_ch4:
					/*Select ICU*/
					CLR_BIT(MTIM4->CCMR2,CCRM2_CC4S1);
					SET_BIT(MTIM4->CCMR2,CCRM2_CC4S0);
					/*set the ICU FILTER value=0*/
					CLR_BIT(MTIM4->CCMR2,CCRM2_OC4M_15);
					CLR_BIT(MTIM4->CCMR2,CCRM2_OC4M_14);
					CLR_BIT(MTIM4->CCMR2,CCRM2_OC4M_13);
					CLR_BIT(MTIM4->CCMR2,CCRM2_OC4M_12);
					/*set ICU PRESCALER= no preScaler*/
					CLR_BIT(MTIM4->CCMR2,CCRM2_IC4PSC10);
					CLR_BIT(MTIM4->CCMR2,CCRM2_IC4PSC11);
					/*select the rising edge sense control*/
					SET_BIT(MTIM4->CCER,CCER_CC4NP);
					SET_BIT(MTIM4->CCER,CCER_CC4P);
					/*enable capture on the corresponding PIN*/
					SET_BIT(MTIM4->CCER,CCER_CC4E);
					/*enable interrupt*/
					SET_BIT(MTIM4->DIER,DIER_CC4IE);
					 break;
	}
			break;
			case MTIM_5:
				switch(Copy_udtICUchannel){
				case MTIM2_5_ch1:
					/*Select ICU*/
					CLR_BIT(MTIM5->CCMR1,CCRM1_CC1S1);
					SET_BIT(MTIM5->CCMR1,CCRM1_CC1S0);
					/*set the ICU FILTER value=0*/
					CLR_BIT(MTIM5->CCMR1,CCRM1_OC1M_7);
					CLR_BIT(MTIM5->CCMR1,CCRM1_OC1M_6);
					CLR_BIT(MTIM5->CCMR1,CCRM1_OC1M_5);
					CLR_BIT(MTIM5->CCMR1,CCRM1_OC1M_4);
					/*set ICU PRESCALER= no preScaler*/
					CLR_BIT(MTIM5->CCMR1,CCRM1_IC1PSC3);
					CLR_BIT(MTIM5->CCMR1,CCRM1_IC1PSC2);
					/*select the rising edge sense control*/
					SET_BIT(MTIM5->CCER,CCER_CC1P);
					SET_BIT(MTIM5->CCER,CCER_CC1NP);
					/*enable capture on the corresponding PIN*/
					SET_BIT(MTIM5->CCER,CCER_CC1E);
					/*enable interrupt*/
					SET_BIT(MTIM5->DIER,DIER_CC1IE);
					/* Set prescaler 16 */
					MTIM5->PSC = 15;
					/* Set Preload */
					MTIM5->ARR=65535;
					//CLR_BIT(MTIM3->CR1,CR1_ARPE);

					//SET_BIT(MTIM3->CR1,1);

					/*enable interrupt*/
					SET_BIT(MTIM5->DIER,DIER_CC1IE);
					/*enable timer to start ICU*/
					SET_BIT(MTIM5->CR1,CR1_CEN);
					 break;
				case MTIM2_5_ch2:
					/*Select ICU*/
					CLR_BIT(MTIM5->CCMR1,CCRM1_CC2S1);
					SET_BIT(MTIM5->CCMR1,CCRM1_CC2S0);
					/*set the ICU FILTER value=0*/
					CLR_BIT(MTIM5->CCMR1,CCRM1_OC2M_15);
					CLR_BIT(MTIM5->CCMR1,CCRM1_OC2M_14);
					CLR_BIT(MTIM5->CCMR1,CCRM1_OC2M_13);
					CLR_BIT(MTIM5->CCMR1,CCRM1_OC2M_12);
					/*set ICU PRESCALER= no preScaler*/
					CLR_BIT(MTIM5->CCMR1,CCRM1_IC2PSC10);
					CLR_BIT(MTIM5->CCMR1,CCRM1_IC2PSC11);
					/*select the rising edge sense control*/
					SET_BIT(MTIM5->CCER,CCER_CC2NP);
					SET_BIT(MTIM5->CCER,CCER_CC2P);
					/*enable capture on the corresponding PIN*/
					SET_BIT(MTIM5->CCER,CCER_CC2E);
					/*enable interrupt*/
					SET_BIT(MTIM5->DIER,DIER_CC2IE);
					/* Set prescaler 16 */
					MTIM5->PSC = 15;
					/* Set Preload */
					MTIM5->ARR=65535;
					//CLR_BIT(MTIM3->CR1,CR1_ARPE);

					//SET_BIT(MTIM3->CR1,1);

					/*enable interrupt*/
					SET_BIT(MTIM5->DIER,DIER_CC2IE);
					/*enable timer to start ICU*/
					SET_BIT(MTIM5->CR1,CR1_CEN);
					 break;
				case MTIM2_5_ch3:
						/*Select ICU*/
						CLR_BIT(MTIM5->CCMR2,CCRM2_CC3S1);
						SET_BIT(MTIM5->CCMR2,CCRM2_CC3S0);
						/*set the ICU FILTER value=0*/
						CLR_BIT(MTIM5->CCMR2,CCRM2_OC3M_7);
						CLR_BIT(MTIM5->CCMR2,CCRM2_OC3M_6);
						CLR_BIT(MTIM5->CCMR2,CCRM2_OC3M_5);
						CLR_BIT(MTIM5->CCMR2,CCRM2_OC3M_4);
						/*set ICU PRESCALER= no preScaler*/
						CLR_BIT(MTIM5->CCMR2,CCRM2_IC3PSC3);
						CLR_BIT(MTIM5->CCMR2,CCRM2_IC3PSC2);
						/*select the rising edge sense control*/
						SET_BIT(MTIM5->CCER,CCER_CC3NP);
						SET_BIT(MTIM5->CCER,CCER_CC3P);
						/*enable capture on the corresponding PIN*/
						SET_BIT(MTIM5->CCER,CCER_CC3E);
						/*enable interrupt*/
						SET_BIT(MTIM5->DIER,DIER_CC3IE);
						/* Set prescaler 16 */
						MTIM5->PSC = 15;
						/* Set Preload */
						MTIM5->ARR=65535;
						//CLR_BIT(MTIM3->CR1,CR1_ARPE);

						//SET_BIT(MTIM3->CR1,1);

						/*enable interrupt*/
						SET_BIT(MTIM5->DIER,DIER_CC1IE);
						/*enable timer to start ICU*/
						SET_BIT(MTIM5->CR1,CR1_CEN);
						 break;
					case MTIM2_5_ch4:
						/*Select ICU*/
						CLR_BIT(MTIM5->CCMR2,CCRM2_CC4S1);
						SET_BIT(MTIM5->CCMR2,CCRM2_CC4S0);
						/*set the ICU FILTER value=0*/
						CLR_BIT(MTIM5->CCMR2,CCRM2_OC4M_15);
						CLR_BIT(MTIM5->CCMR2,CCRM2_OC4M_14);
						CLR_BIT(MTIM5->CCMR2,CCRM2_OC4M_13);
						CLR_BIT(MTIM5->CCMR2,CCRM2_OC4M_12);
						/*set ICU PRESCALER= no preScaler*/
						CLR_BIT(MTIM5->CCMR2,CCRM2_IC4PSC10);
						CLR_BIT(MTIM5->CCMR2,CCRM2_IC4PSC11);
						/*select the rising edge sense control*/
						SET_BIT(MTIM5->CCER,CCER_CC4NP);
						SET_BIT(MTIM5->CCER,CCER_CC4P);
						/*enable capture on the corresponding PIN*/
						SET_BIT(MTIM5->CCER,CCER_CC4E);
						/*enable interrupt*/
						SET_BIT(MTIM5->DIER,DIER_CC4IE);
						/* Set prescaler 16 */
						MTIM5->PSC = 15;
						/* Set Preload */
						MTIM5->ARR=65535;
						//CLR_BIT(MTIM3->CR1,CR1_ARPE);

						//SET_BIT(MTIM3->CR1,1);

						/*enable interrupt*/
						SET_BIT(MTIM5->DIER,DIER_CC1IE);
						/*enable timer to start ICU*/
						SET_BIT(MTIM5->CR1,CR1_CEN);
						 break;
		}
				break;
	}

}

/**
 * @brief Enables ICU interrupts for the specified timer and channel.
 *
 * This function enables interrupts for ICU events on the specified timer and channel.
 *
 * @param Copy_udtTimerNumber Enum specifying the timer number.
 * @param Copy_udtICUchannel Enum specifying the ICU channel.
 */

void TIM2_5_voidEnable_ICU_Interrupt(MTIMx_NUMBER_t Copy_udtTimerNumber,MTIM2_5_PWM_channel_num Copy_udtICUchannel){
	switch (Copy_udtTimerNumber){
			case MTIM_2: switch (Copy_udtICUchannel){
							case MTIM2_5_ch1:		SET_BIT(MTIM2->DIER,DIER_CC1IE);	break;   /*ENABLE INTERRUPT for TIM2 ICU CH 1*/
							case MTIM2_5_ch2:		SET_BIT(MTIM2->DIER,DIER_CC2IE);	break;   /*ENABLE INTERRUPT for TIM2 ICU CH 2*/
							case MTIM2_5_ch3:		SET_BIT(MTIM2->DIER,DIER_CC3IE);	break;   /*ENABLE INTERRUPT for TIM2 ICU CH 3*/
							case MTIM2_5_ch4:		SET_BIT(MTIM2->DIER,DIER_CC4IE);	break;   /*ENABLE INTERRUPT for TIM2 ICU CH 4*/
				}
				break;
			case MTIM_3 :switch (Copy_udtICUchannel){
							case MTIM2_5_ch1:		SET_BIT(MTIM3->DIER,DIER_CC1IE);	break;    /**ENABLE INTERRUPT for TIM3 ICU CH 1*/
							case MTIM2_5_ch2:		SET_BIT(MTIM3->DIER,DIER_CC2IE);	break;    /**ENABLE INTERRUPT for TIM3 ICU CH 2*/
							case MTIM2_5_ch3:		SET_BIT(MTIM3->DIER,DIER_CC3IE);	break;    /**ENABLE INTERRUPT for TIM3 ICU CH 3*/
							case MTIM2_5_ch4:		SET_BIT(MTIM3->DIER,DIER_CC4IE);	break;    /**ENABLE INTERRUPT for TIM3 ICU CH 4*/
				}
				break;

			case MTIM_4 : switch (Copy_udtICUchannel){
							case MTIM2_5_ch1:		SET_BIT(MTIM4->DIER,DIER_CC1IE);	break;    /**ENABLE INTERRUPT for TIM4 ICU CH 1*/
							case MTIM2_5_ch2:		SET_BIT(MTIM4->DIER,DIER_CC2IE);	break;    /**ENABLE INTERRUPT for TIM4 ICU CH 2*/
							case MTIM2_5_ch3:		SET_BIT(MTIM4->DIER,DIER_CC3IE);	break;    /**ENABLE INTERRUPT for TIM4 ICU CH 3*/
							case MTIM2_5_ch4:		SET_BIT(MTIM4->DIER,DIER_CC4IE);	break;    /**ENABLE INTERRUPT for TIM4 ICU CH 4*/
				}
				break;
			case MTIM_5 : switch (Copy_udtICUchannel){
							case MTIM2_5_ch1:		SET_BIT(MTIM5->DIER,DIER_CC1IE);	break;     /**ENABLE INTERRUPT for TIM5 ICU CH 1*/
							case MTIM2_5_ch2:		SET_BIT(MTIM5->DIER,DIER_CC2IE);	break;     /**ENABLE INTERRUPT for TIM5 ICU CH 2*/
							case MTIM2_5_ch3:		SET_BIT(MTIM5->DIER,DIER_CC3IE);	break;     /**ENABLE INTERRUPT for TIM5 ICU CH 3*/
							case MTIM2_5_ch4:		SET_BIT(MTIM5->DIER,DIER_CC4IE);	break;     /**ENABLE INTERRUPT for TIM5 ICU CH 4*/
				}
				break;
	}
}
/**
 * @brief Disables ICU interrupts for the specified timer and channel.
 *
 * This function disables interrupts for ICU events on the specified timer and channel.
 *
 * @param Copy_udtTimerNumber Enum specifying the timer number.
 * @param Copy_udtICUchannel Enum specifying the ICU channel.
 */

void TIM2_5_voidDisable_ICU_Interrupt(MTIMx_NUMBER_t Copy_udtTimerNumber,MTIM2_5_PWM_channel_num Copy_udtICUchannel){
	switch (Copy_udtTimerNumber){
			case MTIM_2: switch (Copy_udtICUchannel){
							case MTIM2_5_ch1:		CLR_BIT(MTIM2->DIER,DIER_CC1IE);	break;   /*DISABLE INTERRUPT for TIM2 ICU CH 1*/
							case MTIM2_5_ch2:		CLR_BIT(MTIM2->DIER,DIER_CC2IE);	break;   /*DISABLE INTERRUPT for TIM2 ICU CH 2*/
							case MTIM2_5_ch3:		CLR_BIT(MTIM2->DIER,DIER_CC3IE);	break;   /*DISABLE INTERRUPT for TIM2 ICU CH 3*/
							case MTIM2_5_ch4:		CLR_BIT(MTIM2->DIER,DIER_CC4IE);	break;   /*DISABLE INTERRUPT for TIM2 ICU CH 4*/
				}
				break;
			case MTIM_3 :switch (Copy_udtICUchannel){
							case MTIM2_5_ch1:		CLR_BIT(MTIM3->DIER,DIER_CC1IE);	break;    /*DISABLE INTERRUPT for TIM3 ICU CH 1*/
							case MTIM2_5_ch2:		CLR_BIT(MTIM3->DIER,DIER_CC2IE);	break;    /*DISABLE INTERRUPT for TIM3 ICU CH 2*/
							case MTIM2_5_ch3:		CLR_BIT(MTIM3->DIER,DIER_CC3IE);	break;    /*DISABLE INTERRUPT for TIM3 ICU CH 3*/
							case MTIM2_5_ch4:		CLR_BIT(MTIM3->DIER,DIER_CC4IE);	break;    /*DISABLE INTERRUPT for TIM3 ICU CH 4*/
				}
				break;

			case MTIM_4 : switch (Copy_udtICUchannel){
							case MTIM2_5_ch1:		CLR_BIT(MTIM4->DIER,DIER_CC1IE);	break;    /*DISABLE INTERRUPT for TIM4 ICU CH 1*/
							case MTIM2_5_ch2:		CLR_BIT(MTIM4->DIER,DIER_CC2IE);	break;    /*DISABLE INTERRUPT for TIM4 ICU CH 2*/
							case MTIM2_5_ch3:		CLR_BIT(MTIM4->DIER,DIER_CC3IE);	break;    /*DISABLE INTERRUPT for TIM4 ICU CH 3*/
							case MTIM2_5_ch4:		CLR_BIT(MTIM4->DIER,DIER_CC4IE);	break;    /*DISABLE INTERRUPT for TIM4 ICU CH 4*/
				}
				break;
			case MTIM_5 : switch (Copy_udtICUchannel){
							case MTIM2_5_ch1:		CLR_BIT(MTIM5->DIER,DIER_CC1IE);	break;     /*DISABLE INTERRUPT for TIM5 ICU CH 1*/
							case MTIM2_5_ch2:		CLR_BIT(MTIM5->DIER,DIER_CC2IE);	break;     /*DISABLE INTERRUPT for TIM5 ICU CH 2*/
							case MTIM2_5_ch3:		CLR_BIT(MTIM5->DIER,DIER_CC3IE);	break;     /*DISABLE INTERRUPT for TIM5 ICU CH 3*/
							case MTIM2_5_ch4:		CLR_BIT(MTIM5->DIER,DIER_CC4IE);	break;     /*DISABLE INTERRUPT for TIM5 ICU CH 4*/
				}
				break;
	}
}
/**
 * @brief Change the input capture (ICU) polarity for a specified timer channel.
 *
 * This function changes the ICU polarity of a specified timer channel to either
 * rising edge or falling edge.
 *
 * @param Copy_udtTimerNumber The number of the timer (TIM2, TIM3, TIM4, TIM5).
 * @param Copy_udtICUchannel The channel of the timer (ch1, ch2, ch3, ch4).
 * @param Copy_udtPolarity The desired polarity (MTIM_RisingEdge or MTIM_FallingEdge).
 * @retval 1 Operation successful.
 */
void TIM2_5_ChangICUpolaritiy(MTIMx_NUMBER_t Copy_udtTimerNumber,MTIM2_5_PWM_channel_num Copy_udtICUchannel,MTIM2_5_polarity Copy_udtPolarity){
switch (Copy_udtPolarity){
case MTIM_RisingEdge:
	switch (Copy_udtTimerNumber){
			case MTIM_2: switch (Copy_udtICUchannel){
							case MTIM2_5_ch1:	CLR_BIT(MTIM2->CCER,CCER_CC1P); CLR_BIT(MTIM2->CCER,CCER_CC1NP); break;
							case MTIM2_5_ch2:	CLR_BIT(MTIM2->CCER,CCER_CC2P); CLR_BIT(MTIM2->CCER,CCER_CC2NP); break;
							case MTIM2_5_ch3:	CLR_BIT(MTIM2->CCER,CCER_CC3P); CLR_BIT(MTIM2->CCER,CCER_CC3NP); break;
							case MTIM2_5_ch4:	CLR_BIT(MTIM2->CCER,CCER_CC4P); CLR_BIT(MTIM2->CCER,CCER_CC4NP); break;
				}
				break;
			case MTIM_3 :switch (Copy_udtICUchannel){
							case MTIM2_5_ch1:	CLR_BIT(MTIM3->CCER,CCER_CC1P); CLR_BIT(MTIM3->CCER,CCER_CC1NP); break;
							case MTIM2_5_ch2:	CLR_BIT(MTIM3->CCER,CCER_CC2P); CLR_BIT(MTIM3->CCER,CCER_CC2NP); break;
							case MTIM2_5_ch3:	CLR_BIT(MTIM3->CCER,CCER_CC3P); CLR_BIT(MTIM3->CCER,CCER_CC3NP); break;
							case MTIM2_5_ch4:	CLR_BIT(MTIM3->CCER,CCER_CC4P); CLR_BIT(MTIM3->CCER,CCER_CC4NP); break;
				}
				break;

			case MTIM_4 : switch (Copy_udtICUchannel){
							case MTIM2_5_ch1:		CLR_BIT(MTIM4->CCER,CCER_CC1P); CLR_BIT(MTIM4->CCER,CCER_CC1NP); break;
							case MTIM2_5_ch2:		CLR_BIT(MTIM4->CCER,CCER_CC2P); CLR_BIT(MTIM4->CCER,CCER_CC2NP); break;
							case MTIM2_5_ch3:		CLR_BIT(MTIM4->CCER,CCER_CC3P); CLR_BIT(MTIM4->CCER,CCER_CC3NP); break;
							case MTIM2_5_ch4:		CLR_BIT(MTIM4->CCER,CCER_CC4P); CLR_BIT(MTIM4->CCER,CCER_CC4NP); break;
				}
				break;
			case MTIM_5 : switch (Copy_udtICUchannel){
							case MTIM2_5_ch1:		CLR_BIT(MTIM5->CCER,CCER_CC1P); CLR_BIT(MTIM5->CCER,CCER_CC1NP); break;
							case MTIM2_5_ch2:		CLR_BIT(MTIM5->CCER,CCER_CC2P); CLR_BIT(MTIM5->CCER,CCER_CC2NP); break;
							case MTIM2_5_ch3:		CLR_BIT(MTIM5->CCER,CCER_CC3P); CLR_BIT(MTIM5->CCER,CCER_CC3NP); break;
							case MTIM2_5_ch4:		CLR_BIT(MTIM5->CCER,CCER_CC4P); CLR_BIT(MTIM5->CCER,CCER_CC4NP); break;
				}
				break;
	}
	break;
	case MTIM_FallingEdge:
		switch (Copy_udtTimerNumber){
				case MTIM_2: switch (Copy_udtICUchannel){
								case MTIM2_5_ch1:  SET_BIT(MTIM2->CCER,CCER_CC1P); CLR_BIT(MTIM2->CCER,CCER_CC1NP); break;
								case MTIM2_5_ch2:  SET_BIT(MTIM2->CCER,CCER_CC2P); CLR_BIT(MTIM2->CCER,CCER_CC2NP); break;
								case MTIM2_5_ch3:  SET_BIT(MTIM2->CCER,CCER_CC3P); CLR_BIT(MTIM2->CCER,CCER_CC3NP); break;
								case MTIM2_5_ch4:  SET_BIT(MTIM2->CCER,CCER_CC4P); CLR_BIT(MTIM2->CCER,CCER_CC4NP); break;
					}
					break;
				case MTIM_3 :switch (Copy_udtICUchannel){
								case MTIM2_5_ch1:	SET_BIT(MTIM3->CCER,CCER_CC1P); CLR_BIT(MTIM3->CCER,CCER_CC1NP); break;
								case MTIM2_5_ch2:	SET_BIT(MTIM3->CCER,CCER_CC2P); CLR_BIT(MTIM3->CCER,CCER_CC2NP); break;
								case MTIM2_5_ch3:	SET_BIT(MTIM3->CCER,CCER_CC3P); CLR_BIT(MTIM3->CCER,CCER_CC3NP); break;
								case MTIM2_5_ch4:	SET_BIT(MTIM3->CCER,CCER_CC4P); CLR_BIT(MTIM3->CCER,CCER_CC4NP); break;
					}
					break;

				case MTIM_4 : switch (Copy_udtICUchannel){
								case MTIM2_5_ch1:	SET_BIT(MTIM4->CCER,CCER_CC1P); CLR_BIT(MTIM4->CCER,CCER_CC1NP); break;
								case MTIM2_5_ch2:	SET_BIT(MTIM4->CCER,CCER_CC2P); CLR_BIT(MTIM4->CCER,CCER_CC2NP); break;
								case MTIM2_5_ch3:	SET_BIT(MTIM4->CCER,CCER_CC3P); CLR_BIT(MTIM4->CCER,CCER_CC3NP); break;
								case MTIM2_5_ch4:	SET_BIT(MTIM4->CCER,CCER_CC4P); CLR_BIT(MTIM4->CCER,CCER_CC4NP); break;
					}
					break;
				case MTIM_5 : switch (Copy_udtICUchannel){
								case MTIM2_5_ch1:   SET_BIT(MTIM5->CCER,CCER_CC1P); CLR_BIT(MTIM5->CCER,CCER_CC1NP); break;
								case MTIM2_5_ch2:   SET_BIT(MTIM5->CCER,CCER_CC2P); CLR_BIT(MTIM5->CCER,CCER_CC2NP); break;
								case MTIM2_5_ch3:   SET_BIT(MTIM5->CCER,CCER_CC3P); CLR_BIT(MTIM5->CCER,CCER_CC3NP); break;
								case MTIM2_5_ch4:   SET_BIT(MTIM5->CCER,CCER_CC4P); CLR_BIT(MTIM5->CCER,CCER_CC4NP); break;
					}
					break;
		}
		break;
}
}
/**
 * @brief Return the captured value for a specified ICU channel of a specified timer.
 *
 * This function returns the captured value for a specified ICU channel of a specified timer.
 *
 * @param Copy_udtTimerNumber The number of the timer (TIM2, TIM3, TIM4, TIM5).
 * @param Copy_udtICUchannel The channel of the timer (ch1, ch2, ch3, ch4).
 * @retval The captured value for the specified ICU channel.
 */
u32 TIM2_5_u32ReturnICUvalue(MTIMx_NUMBER_t Copy_udtTimerNumber,MTIM2_5_PWM_channel_num Copy_udtICUchannel){
	u32 Local_RetVALUE=0;
	switch (Copy_udtTimerNumber){
			case MTIM_2: switch (Copy_udtICUchannel){
							case MTIM2_5_ch1:	Local_RetVALUE=MTIM2->CCR1	; break;
							case MTIM2_5_ch2:	Local_RetVALUE=MTIM2->CCR2	; break;
							case MTIM2_5_ch3:	Local_RetVALUE=MTIM2->CCR3	; break;
							case MTIM2_5_ch4:	Local_RetVALUE=MTIM2->CCR4	; break;
				}
				break;
			case MTIM_3 :switch (Copy_udtICUchannel){
							case MTIM2_5_ch1:	Local_RetVALUE=MTIM3->CCR1	; break;
							case MTIM2_5_ch2:	Local_RetVALUE=MTIM3->CCR2	; break;
							case MTIM2_5_ch3:	Local_RetVALUE=MTIM3->CCR3	; break;
							case MTIM2_5_ch4:	Local_RetVALUE=MTIM3->CCR4	; break;
				}
				break;

			case MTIM_4 : switch (Copy_udtICUchannel){
						case MTIM2_5_ch1:	Local_RetVALUE=MTIM4->CCR1	; break;
						case MTIM2_5_ch2:	Local_RetVALUE=MTIM4->CCR2	; break;
						case MTIM2_5_ch3:	Local_RetVALUE=MTIM4->CCR3	; break;
						case MTIM2_5_ch4:	Local_RetVALUE=MTIM4->CCR4	; break;
				}
				break;
			case MTIM_5 : switch (Copy_udtICUchannel){
						case MTIM2_5_ch1:	Local_RetVALUE=MTIM5->CCR1	; break;
						case MTIM2_5_ch2:	Local_RetVALUE=MTIM5->CCR2	; break;
						case MTIM2_5_ch3:	Local_RetVALUE=MTIM5->CCR3	; break;
						case MTIM2_5_ch4:	Local_RetVALUE=MTIM5->CCR4	; break;
				}
				break;

	}
	return Local_RetVALUE;
}


/**
 * @brief Set callback function for TIM3 interrupts.
 *
 * This function sets the callback function to be called when TIM3 interrupts occur.
 *
 * @param Copy_pvCallBACK Pointer to the callback function.
 */
void MTIM3_setCALLBACK(void (*Copy_pvCallBACK)(void)){
	MTIM3_pvCallBack=Copy_pvCallBACK;
}
/**
 * @brief Set callback function for TIM4 interrupts.
 *
 * This function sets the callback function to be called when TIM4 interrupts occur.
 *
 * @param Copy_pvCallBACK Pointer to the callback function.
 */
void MTIM4_setCALLBACK(void (*Copy_pvCallBACK)(void)){
	MTIM4_pvCallBack=Copy_pvCallBACK;
}
/**
 * @brief Set callback function for TIM5 interrupts.
 *
 * This function sets the callback function to be called when TIM5 interrupts occur.
 *
 * @param Copy_pvCallBACK Pointer to the callback function.
 */
void MTIM5_setCALLBACK(void (*Copy_pvCallBACK)(void)){
	MTIM5_pvCallBack=Copy_pvCallBACK;
}
/*******************************/
/**
 * @brief TIM2 interrupt handler.
 *
 * This function is the interrupt handler for TIM2.
 */
void TIM2_IRQHandler(void){

}
/**
 * @brief TIM3 interrupt handler.
 *
 * This function is the interrupt handler for TIM3.
 * It calls the callback function set by MTIM3_setCALLBACK().
 */
void TIM3_IRQHandler(void){
		MTIM3_pvCallBack();
}
/**
 * @brief TIM4 interrupt handler.
 *
 * This function is the interrupt handler for TIM4.
 * It calls the callback function set by MTIM4_setCALLBACK().
 */
void TIM4_IRQHandler(void){
	MTIM4_pvCallBack();
}
/**
 * @brief TIM5 interrupt handler.
 *
 * This function is the interrupt handler for TIM5.
 * It calls the callback function set by MTIM5_setCALLBACK().
 */
void TIM5_IRQHandler(void){
	MTIM5_pvCallBack();
}
/***********************************/

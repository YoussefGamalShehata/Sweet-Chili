/*
 * Servo_interfave.h
 *
 *  Created on: Feb 23, 2024
 *      Author: Youssef Gamal
 */

#ifndef SERVOMOTOR_SERVO_INTERFAVE_H_
#define SERVOMOTOR_SERVO_INTERFAVE_H_

//void SM_voidServoInit(void);
//void SM_voidStop(void);
//void SM_voidMove0Degree (void);
//void SM_voidMove90Degree (void);
//void SM_voidMove180Degree (void);

void TIMER_voidServoTimerInit (void);
void TIMER_voidStopTimer (void);
void TIMER_voidGenerateServoPWM (u8 copy_u8dutyCycle);
void HServo_voidRotate(int copy_u8angle);
#endif /* SERVOMOTOR_SERVO_INTERFAVE_H_ */

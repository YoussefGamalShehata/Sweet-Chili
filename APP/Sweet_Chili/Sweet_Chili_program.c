/*
 * Sweet_Chilli_program.c
 *
 *  Created on: Mar 3, 2024
 *      Author: Ali Samir
 */
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

#include "../H_BRIDGE/H_BRIDGE_interface.h"
#include "../ENCODER/ENCODER_interface.h"
#include "../Ultrasonic/Ultrasonic_interface.h"
#include "../ServoMotor/Servo_interfave.h"
#include "../MGPIO/MGPIO_interface.h"

#include "Sweet_Chili_interface.h"
#include "Sweet_Chili_private.h"
#include "Sweet_Chili_config.h"

u32	StartPoint = 0;
u32	EndPoint = 0;
u32	Reading = 0;

extern u8 AutoParkingStatus;
extern u8 Transmission;
extern u8 Throttle;
extern u8 Brake;
extern s16 Steering;

//extern u8 Speed;
//extern u16 Distance;


/**
 * @brief Initialize the Sweet Chili system.
 * @note This function initializes all the necessary components of the system.
 * @retval Returns void.
 */
void Sweet_Chili_voidInit(void)
{
    H_BRIDGE_voidInit();
    // UTS_voidInit();
    // ENCODER_voidInit();
    GetFunc(Sweet_Chili_voidSearchSlot);
}

/**
 * @brief Execute the parking process.
 * @note This function executes the auto-parking process.
 * @retval Returns void.
 */
void Sweet_Chili_voidPark(void)
{
    while (AutoParkingStatus == AUTOPARKING_ON)
    {
        Brake = Brake_Pressed;
        for (u32 i = 0; i < 1000000; i++)
        {
            H_BRIDGE_voidBrake();
        }

        Transmission = Transmission_R;
        Throttle = 40;
        Steering = 0;

        Brake = Brake_Released;

        while (totaldistance < (EndPoint + 200)) // Reverse 20 Cm
        {
            H_BRIDGE_voidReverse(Throttle, Steering);
        }

        Brake = Brake_Pressed;
        for (u32 i = 0; i < 1000000; i++)
        {
            H_BRIDGE_voidBrake();
        }

        Steering = -10; // May change to +10

        u32 TempPoint = totaldistance;

        Brake = Brake_Released;

        while (totaldistance < (TempPoint + 500)) // 500 encodercounts
        {
            H_BRIDGE_voidReverse(Throttle, Steering);
        }

        Brake = Brake_Pressed;
        for (u32 i = 0; i < 1000000; i++)
        {
            H_BRIDGE_voidBrake();
        }

        Steering = 0;

        TempPoint = totaldistance;

        Brake = Brake_Released;

        while (totaldistance < (TempPoint + CarLength)) // 500 encodercounts
        {
            H_BRIDGE_voidReverse(Throttle, Steering);
        }

        Brake = Brake_Pressed;
        for (u32 i = 0; i < 1000000; i++)
        {
            H_BRIDGE_voidBrake();
        }

        StartPoint = 0;
        EndPoint = 0;
        AutoParkingStatus = 119;
    }
}

/**
 * @brief Search for a parking slot.
 * @note This function searches for an available parking slot.
 * @retval Returns void.
 */
void Sweet_Chili_voidSearchSlot(void)
{
    HServo_voidRotate(90);

    while (AutoParkingStatus == AUTOPARKING_ON)
    {
        UTS_voidCalculateDistance();
        Reading = UTS_u32GetDistanceValue(); ///////////////////////////////////////

        if (Reading > CarLength)
        {
            StartPoint = totaldistance;
        }

        while (Reading > CarLength)
        {
            UTS_voidCalculateDistance();
            Reading = UTS_u32GetDistanceValue(); //////////////////////////////////
            EndPoint = totaldistance;
        }

        if ((EndPoint - StartPoint) > (CarWidth + Margin))
        {
            Sweet_Chili_voidPark();
        }
    }
}

/**
 * @brief Execute a test action.
 * @note This function executes a test action.
 * @retval Returns void.
 */
void Sweet_Chili_voidTry(void)
{
    distance = ENCODER_u64GetDistance();

    if (totaldistance > 195 * 5)
    {
        MGPIO_voidSetPinValue(MGPIOA_u8PORT, 12, MGPIO_u8HIGH);
    }

    // HServo_voidRotate(0);

    // H_BRIDGE_voidCheckBluetooth();

    // sweet_chilli_v2v();
}
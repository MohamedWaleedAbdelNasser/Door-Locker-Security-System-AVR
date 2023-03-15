 /******************************************************************************
 *
 * Module: Dc motor
 *
 * File Name: dc_motor.h
 *
 * Description: header file for the dc_motor driver
 *
 * Author: Weli
 *
 *******************************************************************************/

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "std_types.h"
/*******************************************************************************
 *                                Define new data type                                  *
 *******************************************************************************/
typedef enum{
	CLOCKWISE, ANTICLOCKWISE,STOP
}DcMotor_State;

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define MOTOR_PORT_ID   PORTC_ID
#define MOTOR_PIN_1_ID  PIN4_ID
#define MOTOR_PIN_2_ID  PIN5_ID
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

void DcMotor_Init(void);

void DcMotor_Rotate(DcMotor_State state);
#endif

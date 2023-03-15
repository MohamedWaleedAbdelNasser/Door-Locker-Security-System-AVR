 /******************************************************************************
 *
 * Module: Dc motor
 *
 * File Name: dc_motor.c
 *
 * Description: source file for the dc_motor driver
 *
 * Author: Weli
 *
 *******************************************************************************/
#include "gpio.h"
#include "dc_motor.h"
#include "common_macros.h"
/*******************************************************************************
 *                      Functions implementation                                   *
 *******************************************************************************/

void DcMotor_Init(void){
	GPIO_setupPinDirection(MOTOR_PORT_ID, MOTOR_PIN_1_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(MOTOR_PORT_ID, MOTOR_PIN_2_ID, PIN_OUTPUT);
	GPIO_writePin(MOTOR_PORT_ID, MOTOR_PIN_1_ID, LOGIC_LOW);
	GPIO_writePin(MOTOR_PORT_ID, MOTOR_PIN_2_ID, LOGIC_LOW);
}

void DcMotor_Rotate(DcMotor_State state){
	if (state == CLOCKWISE){
		GPIO_writePin(MOTOR_PORT_ID, MOTOR_PIN_1_ID, LOGIC_LOW);
		GPIO_writePin(MOTOR_PORT_ID, MOTOR_PIN_2_ID, LOGIC_HIGH);
	}
	else if (state==ANTICLOCKWISE) {
		GPIO_writePin(MOTOR_PORT_ID, MOTOR_PIN_1_ID, LOGIC_HIGH);
		GPIO_writePin(MOTOR_PORT_ID, MOTOR_PIN_2_ID, LOGIC_LOW);
	}
	else if(state==STOP){
		GPIO_writePin(MOTOR_PORT_ID, MOTOR_PIN_1_ID, LOGIC_LOW);
		GPIO_writePin(MOTOR_PORT_ID, MOTOR_PIN_2_ID, LOGIC_LOW);
	}
	else{
		GPIO_writePin(MOTOR_PORT_ID, MOTOR_PIN_1_ID, LOGIC_LOW);
		GPIO_writePin(MOTOR_PORT_ID, MOTOR_PIN_2_ID, LOGIC_LOW);
	}
}

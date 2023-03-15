 /******************************************************************************
 *
 * Module: Buzzer
 *
 * File Name: buzzer.c
 *
 * Description: source file for the Buzzer AVR driver
 *
 * Author: Weli
 *
 *******************************************************************************/
#include "buzzer.h"
#include "gpio.h"
 /*******************************************************************************
  *                           Function Definition                                  *
  *******************************************************************************/

void Buzzer_init(){

	GPIO_setupPinDirection(BUZZER_PORT_ID,BUZZER_PIN_ID, PIN_OUTPUT);
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_LOW);//to turn off buzzer
}

void Buzzer_on(void){

	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_HIGH);

}

void Buzzer_off(void){
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_LOW);
}

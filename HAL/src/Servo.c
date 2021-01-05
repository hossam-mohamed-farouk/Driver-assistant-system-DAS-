/*
* Servo.c
*
* Created: 7/6/2020 8:55:23 PM
*  Author: H
*/
#include "Servo.h"

void SERVO_Init(void)
{
	/*set timer 1 prescaler to 8to get 1us tick time
	use fast mode with top value at OCRA reg to set the freq of servo
	disconnect OC1A PIN ,and generate the PWM on OC1B PIN with non inverting mode to use OCR1B reg as the ton value*/

	Timer3_Init(TIMER3_FASTPWM_OCRA_TOP_MODE,TIMER3_SCALER_8,OCR3A_DISCONNECTED,OCR3B_NON_INVERTING);
	OCR3A=19999;//20000us to get 50hz 
	//OCR1B=999;// 1000us ton to get angle zero
	OCR3B = 999; //0 degree of the servo
	//setBit(DDRB, 6);	/*This is to set OC1B as an o/p*/
	setBit(DDRE, 4);	/*This is to set OC3B as an o/p*/
}

void SERVO_SetAngle(INT16U angle)
{
	/*//safety to avoid stall current drawing
	INT16U safetyAngle = 0;
	//calculate range from 0 to 90
	safetyAngle = ( (angle * 1300UL) / 90 ) + 1300;
	//using safety
	if(safetyAngle < 520)
	{
		safetyAngle = 520;
	}
	else if(safetyAngle > 2545)
	{
		safetyAngle = 2545;
	}
	//set angle
	OCR1B = safetyAngle;*/
	OCR3B=( ( (INT32U)angle * 1000 ) / 180 ) + 999;
}
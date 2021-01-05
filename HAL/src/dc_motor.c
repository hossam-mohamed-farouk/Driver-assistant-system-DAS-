/*
 * dc_motor.c
 *
 * Created: 5/31/2020 10:49:01 AM
 *  Author: H
 */ 

#include "dc_motor.h"

void dc_motors_init(void)
{
	setBit(R_MOTOR_DDR, R_MOTOR_PIN1);
	setBit(R_MOTOR_DDR, R_MOTOR_PIN2);
	/*setBit(L_MOTOR_DDR, L_MOTOR_PIN1);
	setBit(L_MOTOR_DDR, L_MOTOR_PIN2);*/
	setBit(DDRB, PB4);						//SET OC0 AS OUPUT PIN
	//PWM INIT
	Timer0_Init(TIMER0_PHASECORRECT_MODE,TIMER0_SCALER_8,OCO_NON_INVERTING);
	motors_stop();
	//car_speed_select(0);
}

void right_motor_forward(void)
{
	setBit(R_MOTOR_PORT, R_MOTOR_PIN1);
	clearBit(R_MOTOR_PORT, R_MOTOR_PIN2);
}

void right_motor_reverse(void)
{
	clearBit(R_MOTOR_PORT, R_MOTOR_PIN1);
	setBit(R_MOTOR_PORT, R_MOTOR_PIN2);
}

/*
void left_motor_forward(void)
{
	setBit(L_MOTOR_PORT, L_MOTOR_PIN1);
	clearBit(L_MOTOR_PORT, L_MOTOR_PIN2);
}

void left_motor_reverse(void)
{
	clearBit(L_MOTOR_PORT, L_MOTOR_PIN1);
	setBit(L_MOTOR_PORT, L_MOTOR_PIN2);
}*/

void motors_stop(void)  
{
	clearBit(R_MOTOR_PORT, R_MOTOR_PIN1);
	clearBit(R_MOTOR_PORT, R_MOTOR_PIN2);
	/*clearBit(L_MOTOR_PORT, L_MOTOR_PIN1);
	clearBit(L_MOTOR_PORT, L_MOTOR_PIN2);*/
}

void motors_speed_select(INT8U speed_rate)		//0 : MAX_SPEED_RATE
{
	if ((speed_rate >= MIN_SPEED_RATE) && (speed_rate <= MAX_SPEED_RATE))
	{
		OCR0 = speed_rate * MAX_SPEED / MAX_SPEED_RATE;
	}
	else if (speed_rate < MIN_SPEED_RATE)
	{
		OCR0 = MIN_SPEED_RATE * MAX_SPEED / MAX_SPEED_RATE;
	}
	else
	{
		OCR0 = MAX_SPEED_RATE * MAX_SPEED / MAX_SPEED_RATE;
	}
}
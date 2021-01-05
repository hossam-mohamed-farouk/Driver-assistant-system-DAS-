/*
 * dc_motor.h
 *
 * Created: 5/31/2020 10:49:01 AM
 *  Author: H
 */ 

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "Timers.h"

#define R_MOTOR_DDR		DDRA
#define R_MOTOR_PORT	PORTA
#define R_MOTOR_PIN1	0
#define R_MOTOR_PIN2	1

#define L_MOTOR_DDR		DDRA
#define L_MOTOR_PORT	PORTA
#define L_MOTOR_PIN1	2
#define L_MOTOR_PIN2	3

#define MAX_SPEED		255	//65535   		
#define MAX_SPEED_RATE  100
#define MIN_SPEED_RATE	0


void dc_motors_init(void);
void right_motor_forward(void);
void right_motor_reverse(void);
void left_motor_forward(void);
void left_motor_reverse(void);
void move_forward(void);
void move_backward(void);
void move_right(void);
void move_left(void);
void move_forward_right(void);
void move_forward_left(void);
void move_backward_right(void);
void move_backward_left(void);
void motors_stop(void);
void motors_speed_select(INT8U speed_rate);

#endif
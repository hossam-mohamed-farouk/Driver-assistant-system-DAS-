/*
 * car_control.h
 *
 * Created: 8/1/2020 5:05:54 PM
 *  Author: H
 */ 


#ifndef CAR_CONTROL_H_
#define CAR_CONTROL_H_

/*** This module use the dc_motor and servo motor to control the movement of the car ***/

#include "dc_motor.h"


#define CAR_DDR				DDRA
#define CAR_PORT			PORTA
#define CAR_PIN_F			PA0			//Move car Forward
#define CAR_PIN_B			PA1			//Move car Backward
#define CAR_PIN_R			PA2			//Steering Right
#define CAR_PIN_L			PA3			//Steering Lift
#define CAR_PIN_S			PA4			//Stop the car
#define CAR_PIN_D			PA5			//Car change speed

/*** Decleration of car controlling functions ***/

void car_control_init(void);
void move_forward(void);
void move_backward(void);
void move_right(void);
void move_left(void);
void car_stop(void);
void car_speed_change(void);

#endif /* CAR_CONTROL_H_ */
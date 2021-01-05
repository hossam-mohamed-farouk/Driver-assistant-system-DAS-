/*
* ultrasonic.h
*
* Created: 7/6/2020 9:59:22 PM
*  Author: H
*/

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#define F_CPU	8000000UL

#include "Timers.h"
#include <util/delay.h>

#define ULTRASONIC_DDR		DDRG
#define ULTRASONIC_PORT		PORTG
#define ULTRASONIC_ECHO_DDR DDRE
#define ULTRASONIC_ECHO_PIN 4

typedef enum{
	ULTRASONIC_1=PG0,
	ULTRASONIC_2=PG1,
	ULTRASONIC_3=PG2,
	ULTRASONIC_4=PG3, 
	ULTRASONIC_5=PG4
}ULTRASONIC_type;

void ULTRASONIC_Init(void);
INT8U ULTRASONIC_GetDistance(ULTRASONIC_type ultrasonic_pin);
INT8U ULTRASONIC_GetDistance2(ULTRASONIC_type ultrasonic_pin);
void ULTRASONIC_Start(ULTRASONIC_type ultrasonic_pin);
INT16U ULTRASONIC_GetDistanceNoBlock(INT16U*Pdistance);

#endif /* ULTRASONIC_H_ */
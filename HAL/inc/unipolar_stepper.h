#ifndef STEPPER_H_
#define STEPPER_H_

#ifndef F_CPU
	#define F_CPU	8000000UL
#endif

#ifndef	NULL
	#define NULL   ( (void*)0 )
#endif

#include	"avr/io.h"
#include	"data_types.h"
#include	"bit_handle.h"


//stepper ports and pins
#define UNI_STEPPER_1_DDR		DDRF
#define UNI_STEPPER_1_PORT		PORTF
#define UNI_STEPPER_1_PIN_1		0
#define UNI_STEPPER_1_PIN_2		1
#define UNI_STEPPER_1_PIN_3		2
#define UNI_STEPPER_1_PIN_4		3

#define UNI_STEPPER_2_DDR		DDRF
#define UNI_STEPPER_2_PORT		PORTF
#define UNI_STEPPER_2_PIN_1		4
#define UNI_STEPPER_2_PIN_2		5
#define UNI_STEPPER_2_PIN_3		6
#define UNI_STEPPER_2_PIN_4		7

//minimum delay between steps
#define UNI_STEPPER_DELAY		20

//half step angle
#define UNI_STEP_ANGLE			5.625
//number of half steps to make a full rev
#define UNI_360_STEPS			360.0 / UNI_STEP_ANGLE

void uni_stepper_init(INT8U);

void uni_stepper_increment_clkwise(INT8U);
void uni_stepper_increment_anticlk(INT8U);

void uni_stepper_goto_zero_clkwise(INT8U);
void uni_stepper_goto_zero_anticlk(INT8U);

void uni_stepper_goto_90_clkwise(INT8U);
void uni_stepper_goto_90_anticlk(INT8U);

void uni_stepper_goto_180_clkwise(INT8U);
void uni_stepper_goto_180_anticlk(INT8U);

#endif /* STEPPER_H_ */
/*
 * light_control.c
 *
 * Created: 5/31/2020 10:49:01 AM
 *  Author: H
 */ 

#ifndef	LIGHT_C_H_
#define LIGHT_C_H_

#include "Timers.h"

#define FRONT_R_LED_DDR		DDRC
#define FRONT_R_LED_PORT	PORTC
#define FRONT_R_LED_PIN		0

#define FRONT_L_LED_DDR		DDRC
#define FRONT_L_LED_PORT	PORTC
#define FRONT_L_LED_PIN		1

#define REAR_R_LED_DDR		DDRC
#define REAR_R_LED_PORT		PORTC
#define REAR_R_LED_PIN		2

#define REAR_L_LED_DDR		DDRC
#define REAR_L_LED_PORT		PORTC
#define REAR_L_LED_PIN		3

#define BUZ_DDR				DDRC
#define BUZ_PORT			PORTC
#define BUZ_PIN				4

void light_init(void);
void front_r_led_on(void);
void front_l_led_on(void);
void rear_r_led_on(void);
void rear_l_led_on(void);
void fron_light_on(void);
void rear_light_on(void);

void front_r_led_off(void);
void front_l_led_off(void);
void rear_r_led_off(void);
void rear_l_led_off(void);
void fron_light_off(void);
void rear_light_off(void);

void c_buz_on(void);
void c_buz_off(void);

#endif
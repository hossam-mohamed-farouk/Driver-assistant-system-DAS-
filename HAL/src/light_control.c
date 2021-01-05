/*
 * light_control.c
 *
 * Created: 5/31/2020 10:49:01 AM
 *  Author: H
 */ 
#include "light_control.h"

void light_init(void)
{
	setBit(FRONT_R_LED_DDR, FRONT_R_LED_PIN);
	setBit(FRONT_L_LED_DDR, FRONT_L_LED_PIN);
	setBit(REAR_R_LED_DDR, REAR_R_LED_PIN);
	setBit(REAR_L_LED_DDR, REAR_L_LED_PIN);
	setBit(BUZ_DDR, BUZ_PIN);
}

void front_r_led_on(void)
{
	setBit(FRONT_R_LED_PORT, FRONT_R_LED_PIN);
}
void front_l_led_on(void)
{
	setBit(FRONT_L_LED_PORT, FRONT_L_LED_PIN);
}
void rear_r_led_on(void)
{
	setBit(REAR_R_LED_PORT, REAR_R_LED_PIN);
}
void rear_l_led_on(void)
{
	setBit(REAR_L_LED_PORT, REAR_L_LED_PIN);
}
void fron_light_on(void)
{
	front_r_led_on();
	front_l_led_on();
}
void rear_light_on(void)
{
	rear_r_led_on();
	rear_l_led_on();
}
void front_r_led_off(void)
{
	clearBit(FRONT_R_LED_PORT, FRONT_R_LED_PIN);
}
void front_l_led_off(void)
{
	clearBit(FRONT_L_LED_PORT, FRONT_L_LED_PIN);
}
void rear_r_led_off(void)
{
	clearBit(REAR_R_LED_PORT, REAR_R_LED_PIN);
}
void rear_l_led_off(void)
{
	clearBit(REAR_L_LED_PORT, REAR_L_LED_PIN);
}
void fron_light_off(void)
{
	front_r_led_off();
	front_l_led_off();
}
void rear_light_off(void)
{
	rear_r_led_off();
	rear_l_led_off();
}
void c_buz_on(void)
{
	setBit(BUZ_PORT, BUZ_PIN);
}
void c_buz_off(void)
{
	clearBit(BUZ_PORT, BUZ_PIN);
}
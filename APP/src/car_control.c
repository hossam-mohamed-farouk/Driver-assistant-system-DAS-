/*
 * car_control.c
 *
 * Created: 8/1/2020 5:06:27 PM
 *  Author: H
 */ 

#include "car_control.h"

void car_control_init(void)
{
	/*Set pins output*/
	setBit(CAR_DDR, CAR_PIN_F);
	setBit(CAR_DDR, CAR_PIN_B);
	setBit(CAR_DDR, CAR_PIN_R);
	setBit(CAR_DDR, CAR_PIN_L);
	setBit(CAR_DDR, CAR_PIN_S);
	setBit(CAR_DDR, CAR_PIN_D);
	/*Active Low*/
	setBit(CAR_PORT, CAR_PIN_F);
	setBit(CAR_PORT, CAR_PIN_B);
	setBit(CAR_PORT, CAR_PIN_R);
	setBit(CAR_PORT, CAR_PIN_L);
	setBit(CAR_PORT, CAR_PIN_S);
	setBit(CAR_PORT, CAR_PIN_D);				    
}

void move_forward(void)
{
	setBit(CAR_PORT,CAR_PIN_B);			/*Stop Backward*/
	clearBit(CAR_PORT, CAR_PIN_F);		/*Start Forward*/
}

void move_backward(void)
{
	setBit(CAR_PORT, CAR_PIN_F);		/*Stop Forward*/
	clearBit(CAR_PORT,CAR_PIN_B);		/*Start Backward*/
}

void move_right(void)
{
	clearBit(CAR_PORT,CAR_PIN_R);
	vTaskDelay(250);
	setBit(CAR_PORT,CAR_PIN_R);
}

void move_left(void)
{
	clearBit(CAR_PORT,CAR_PIN_L);
	vTaskDelay(250);
	setBit(CAR_PORT,CAR_PIN_L);
}

void car_stop(void)
{
	/*Stop both backward and forward*/
	setBit(CAR_PORT, CAR_PIN_F);
	setBit(CAR_PORT,CAR_PIN_B);
	
	clearBit(CAR_PORT,CAR_PIN_S);
	setBit(CAR_PORT,CAR_PIN_S);
	clearBit(CAR_PORT,CAR_PIN_S);
	setBit(CAR_PORT,CAR_PIN_S);
}

void car_speed_change(void)
{
	clearBit(CAR_PORT,CAR_PIN_D);
	vTaskDelay(50);
	setBit(CAR_PORT,CAR_PIN_D);
}
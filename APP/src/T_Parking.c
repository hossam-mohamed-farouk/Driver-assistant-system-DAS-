/*
* T_Parking.c
*
* Created: 8/4/2020 5:16:20 PM
*  Author: H
*/
#include "T_Parking.h"

void T_Parking(void* pvData)
{
	INT16U ultrasonic1_data = 0;
	INT16U ultrasonic2_data = 0;
	INT8U time_elapsed		= 0;
	//INT8U i = 0; //what is this!
	while(1)
	{
		if( xSemaphoreTake(bsParkStart, portMAX_DELAY) )
		{
			//remove tasks to make sure that nothing interrupts and no time is wasted
			vTaskSuspend(T_ObjectDetection_Handle);
			vTaskSuspend(T_Light_Handle);
			vTaskSuspend(T_CarControl_Handle);
			//vTaskDelete(T_Mirror_Handle);  // Doesn't even exist
			
			//looking for parking area
			/* PARK_TIME_NEEDED:  To get 2500 msec,  i.e.  100(iterations)*25(delay) = 2500 */
			while(time_elapsed < PARK_TIME_NEEDED)   //car length iteration,
			{
				LCD_DispIntXY(2,1,time_elapsed);
				ULTRASONIC_Start(ULTRASONIC_1);
				vTaskDelay(25);
				if( ULTRASONIC_GetDistanceNoBlock(&ultrasonic1_data) )
				{
					LCD_DispIntXY(2, 8, ultrasonic1_data);
					if(ultrasonic1_data <= 60)
					{
						car_stop();
						LCD_DispCharXY(2,8,time_elapsed+'0');
						vTaskDelay(10);
					}
					else if(ultrasonic1_data > 60)
					{
						//make car move forward and set speed
						move_forward();
						//read from ultrasonic
						ULTRASONIC_Start(ULTRASONIC_2);
						LCD_DispIntXY(1, 8, ultrasonic2_data);
						vTaskDelay(25);
						if( ULTRASONIC_GetDistanceNoBlock(&ultrasonic2_data) )
						{
							if(ultrasonic2_data >= CAR_WIDTH) //car width
							{
								time_elapsed++;
								LCD_DispCharXY(1,2,'z');
							}
							else if(ultrasonic2_data < CAR_WIDTH)
							{
								time_elapsed = 0;
								LCD_DispCharXY(1,1,'o');
							}
						}
					}
				}
			}
			LCD_DispCharXY(1,1,'P');
			car_stop();
			/*Found the parking spot*/
			
			/*Starting the parallel parking algorithm*/
			move_left();	move_left();	move_left();
			move_forward();
			vTaskDelay(1250);
			car_stop();
			move_right();	move_right();	move_right();	move_right();	move_right(); move_right();
			move_backward();
			vTaskDelay(1250);
			car_stop();
			move_left();	move_left();	move_left(); move_left();	move_left();
			move_backward();
			vTaskDelay(1250);
			car_stop();
			move_right();	move_right();		move_right();	move_right(); move_right(); move_right();
			move_forward();
			vTaskDelay(1000);
			car_stop();
			move_left();
			LCD_DispCharXY(1,15,'D');
			/*Parked Successfully*/
		}
		time_elapsed = 0;
		vTaskResume(T_ObjectDetection_Handle);
		vTaskResume(T_Light_Handle);
		vTaskResume(T_CarControl_Handle);
	}
}
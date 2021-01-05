
#include "T_Light.h"

/*************************************************************************************************************************
* T_Light: An eventive task, working upon receiving a new message in mqLightCtrl from the Bluetooth or Ultrasonic tasks  *
**************************************************************************************************************************/

void T_Light(void* pvData)
{
	INT8U data				= 0xFF;		/* Data received on mqLightCtrl */
	INT8U prev_direction	= 0xFF;		/* To keep the prev. direction in */
	INT8U LightOnFlag		= 0;		/* To save light status, 1 => ON, 0 => OFF */
	INT8U near_obj_flag		= 0;		/* To save object status, if there's a near object (between 15 and 30) */
	
	/* Infinite Loop */
	while(1)
	{
		/* Receive data in mqLightCtrl, if no new msgs, go to the waiting state */
		if(xQueueReceive(mqLightCtrl, &data, portMAX_DELAY))
		{
			LCD_DispCharXY(1, 8, data);
			/* Check if data is Light ON. If so, raise LightOnFlag */
			if (data == LED_ON)
			{
				LightOnFlag = 1;
				/* Check if it's the first run, Light all the Matrix*/
				if (prev_direction == 0xFF)
				{
					LEDMatrix_AllOn();
					LEDMatrix_AllOn();
				}
				/* Now, put back the prev. direction in data, in order to  work on it after turning the light on */
				data = prev_direction;
			}
			/* Check if data is Light OFF. If so, turn of the light, and clear LightOnFlag */
			else if (data == LED_OFF)
			{
				LEDMatrix_AllOff();
				LEDMatrix_AllOff();				//Repetition solving a simulation problem, delete for H/W
				LightOnFlag = 0;
			}
			/* Check if data is Light Mid Off (in range 16:30). If so raise near_obj_flag */
			else if (data == LED_MIDOFF)
			{
				near_obj_flag = 1;
			}
			/* Check if data is OBJ_DETECTED or OBJ_CLEARED (i.e. not in 15:30 range). If so clear near_obj_flag */
			else if (data == OBJ_DETECTED || data == OBJ_CLEARED)
			{
				near_obj_flag = 0;
			}
			/* Save ONLY the prev. direction. To be used when turning light on. And when changing the status of the object.*/
			else
			{
				prev_direction = data;
			}
			
			/* Check if Light Flag is raised. If so, do the corresponding action to the received data */
			if (LightOnFlag == 1)
			{
				/* Switch on the received data, and do the corresponding action */
				switch(data)
				{
					/* CARMOVE_F is when the car is moving forward */
					case CARMOVE_F:
					/* If there's no object, Light all the Matrix*/
					if (near_obj_flag == 0)
					{
						LEDMatrix_AllOn();
						LEDMatrix_AllOn();
					}
					/* If there's an object, Light all  Matrix, except the middle; not to blind the driver */
					else if (near_obj_flag == 1)
					{
						LEDMatrix_MidOff();
						LEDMatrix_MidOff();
					}
					/* For MISRA Compliance */
					else
					{
						/* do no thing */
					}
					break;
					/* CARMOVE_B is when the car is moving backward, so dim the light */
					case CARMOVE_B:
					LEDMatrix_AllDim();
					LEDMatrix_AllDim();
					break;
					/* CARMOVE_R is when the car is moving to the right, so light the right and part and dim the left part */
					case CARMOVE_R:
					LEDMatrix_RightHalf();
					LEDMatrix_RightHalf();
					break;
					/* CARMOVE_L is when the car is moving to the left, so light the left and part and dim the right part */
					case CARMOVE_L:
					LEDMatrix_LeftHalf();
					LEDMatrix_LeftHalf();
					break;
					/* CARMOVE_R is when the car is moving to the right, so light the right and part and dim the left part */
					case CARMOVE_FR:
					LEDMatrix_RightHalf();
					LEDMatrix_RightHalf();
					break;
					/* CARMOVE_L is when the car is moving to the left, so light the left and part and dim the right part */
					case CARMOVE_FL:
					LEDMatrix_LeftHalf();
					LEDMatrix_LeftHalf();
					break;
					/* CARMOVE_BR is when the car is moving backward to the right, so dim the light */
					case CARMOVE_BR:
					LEDMatrix_AllDim();
					LEDMatrix_AllDim();
					//To do more if we have a Rear light in the car
					break;
					/* CARMOVE_BL is when the car is moving backward to the left, so dim the light */
					case CARMOVE_BL:
					LEDMatrix_AllDim();
					LEDMatrix_AllDim();
					//To do more if we have a Rear light in the car
					break;
					/* OBJ_DETECTED is when an object in range <= 15 */
					case OBJ_DETECTED:
					/* Check if prev. direction is CARMOVE_F, so light all the Matrix */
					if (prev_direction == CARMOVE_F)
					{
						LEDMatrix_AllOn();
						LEDMatrix_AllOn();
					}
					break;
					/* OBJ_CLEARED is when an object in range > 30 */
					case OBJ_CLEARED:
					/* Check if prev. direction is CARMOVE_F, so light all the Matrix */
					if (prev_direction == CARMOVE_F)
					{
						LEDMatrix_AllOn();
						LEDMatrix_AllOn();
					}
					break;
					/* LED_MIDOFF is when an object in range 16:30. If so raise near_obj_flag */
					case LED_MIDOFF:
					/* Check if prev. direction is CARMOVE_F, Light all  Matrix, except the middle; not to blind the driver */
					if (prev_direction == CARMOVE_F)
					{
						LEDMatrix_MidOff();
						LEDMatrix_MidOff();
					}
					break;
					/* For MISRA Compliance */
					default:
					/* do no thing */
					break;
				}
			}
		}
	}
}

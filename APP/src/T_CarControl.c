#include "T_CarControl.h"


/*** This task waiting for command from the bluetooth or the ultrasonic task and excute the function of the command ***/

void T_CarControl(void* pvData)
{
	INT8U cmd				= 0;					//TO GET THE CMD FROM THE BLUETOOTH TASK
	INT8U prev_cmd			= 0;					//To Save the previous direction
	INT8U object_flag		= 0;					//FLAG TO DETECT THE OBJ_DETECT CMD SENT
	
	while(1)
	{
		/*Waiting for message*/
		if ( xQueueReceive(mqCarMove,&cmd,portMAX_DELAY) )
		{
			LCD_DispCharXY(1, 1, cmd);
			/*Execute the command function*/
			switch (cmd)
			{
				/*Movement Functionality*/
				case CARMOVE_F:
				if (object_flag == 1)				//AN OBSTACLE FRONT THE CAR
				{
					car_stop();
				}
				else if (object_flag == 0)			//NO OBSTACLE FRONT THE CAR
				{
					move_forward();
				}
				break;
				
				case CARMOVE_B:
				move_backward();
				break;
				
				case CARMOVE_R: case CARMOVE_FR: case CARMOVE_BR:
				move_right();
				break;
				
				case CARMOVE_L: case CARMOVE_FL: case CARMOVE_BL:
				move_left();
				break;
							
				case CARSPEED_STOP:
				car_stop();
				break;
				/*Speed rate Functionality*/
				case CARSPEED_INC:
				car_speed_change();
				break;
				
				/*Object detection Functionality*/
				case OBJ_DETECTED:					/*There is an object front the car*/
				if ((prev_cmd == CARMOVE_F))
				{
					car_stop();
				}
				object_flag = 1;					//Flag to know AN OBSTACLE FRONT THE CAR
				break;
				
				case OBJ_CLEARED:					/*There is clear front the car*/
				object_flag = 0;					//Flag to know NO OBSTACLE FRONT THE CAR
				break;
			}
			/*Save the previous Direction*/
			if (cmd != '0' && cmd != '9' && cmd != OBJ_CLEARED && cmd != OBJ_DETECTED)
			{
				prev_cmd = cmd;
			}
		}
	}
}
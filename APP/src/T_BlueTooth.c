
/* T_BlueTooth.h this task is responsible of receiving the user command from the bluetooth
module using USART0 and send these command to its corresponding task through communication queues
*/

#include "T_BlueTooth.h"
static INT8U command = 0;
void T_BlueTooth(void* pvData)
{
	
	while(1)
	{
		if( BT_ReceiveByte_Unblock(UART_1, &command))                                       /*checking for available command from user*/
		{
			LCD_DispCharXY(1, 14, command);
			switch(command){
				case CARMOVE_F: case CARMOVE_B: case CARMOVE_R: case CARMOVE_L:
				case CARMOVE_FR: case CARMOVE_FL:  case CARMOVE_BR : case CARMOVE_BL:
				xQueueSend(mqCarMove, &command,portMAX_DELAY);                              /*sending the control command to T_CarControl task  */
				xQueueSend(mqLightCtrl, &command, portMAX_DELAY);										/*sending the direction to the to the light control task "T_Light"*/
				break;
				
				case CARSPEED_INC:  case CARSPEED_DEC: case CARSPEED_STOP:
				xQueueSend(mqCarMove, &command,portMAX_DELAY);                               /*sending changing speed command to the car control task "T_CarControl task" */
				break;
				
				case LED_ON:  case LED_OFF:
				xQueueSend(mqLightCtrl, &command,portMAX_DELAY);                             /*sending the light state command to the light control task "T_Light*/
				break;
				
				case MIR_OPEN: case MIR_RINC: case MIR_RDEC: case MIR_LINC: case MIR_LDEC: case MIR_CLOSE:
				xQueueSend(mqMirrorCtrl, &command,portMAX_DELAY);                            /*sending the mirror control command to the mirror control task "T_Mirror" */
				break;
				
				case PARRKING_START:
				xSemaphoreGive(bsParkStart);
				break;
				
				case PARKING_STOP:
				car_stop();
				vTaskDelete(T_Parking_Handle);
				vTaskResume(T_ObjectDetection_Handle);
				vTaskResume(T_Light_Handle);
				vTaskResume(T_CarControl_Handle);
				xTaskCreate(T_Parking, "T_Parking",			100, NULL, 6, &T_Parking_Handle);
			}
		}
		vTaskDelay(5);
	}
}
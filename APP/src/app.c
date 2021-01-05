#include "app.h"
#include "T_CarControl.h"

/* OS Services Declaration */
/*Car Move Message Queue*/
xQueueHandle		mqCarMove;
/*Mirror Control Message Queue*/
xQueueHandle		mqMirrorCtrl;
/*Light Control Message Queue*/
xQueueHandle		mqLightCtrl;
/*Semaphore To Start Parking Task*/
xSemaphoreHandle	bsParkStart;

//task handle
xTaskHandle T_BlueTooth_Handle;		// Probably will delete it
xTaskHandle T_ObjectDetection_Handle;
xTaskHandle T_Light_Handle;
xTaskHandle T_Mirror_Handle;
xTaskHandle T_CarControl_Handle;
xTaskHandle T_Parking_Handle;

INT8U password[3] = {'a', 's', 'd'};

int main(void)
{
	system_init();
	/* OS Services Create and Init.*/
	vSemaphoreCreateBinary(bsParkStart, 0);
	mqCarMove = xQueueCreate(4, 1);	/*4 messages, each 1 byte*/
	mqMirrorCtrl = xQueueCreate(4, 1); /*4 messages, each 1 byte*/
	mqLightCtrl = xQueueCreate(4, 1); /*4 messages, each 1 byte*/
	
	/* Tasks Create */
	xTaskCreate(T_BlueTooth, "T_BlueTooth",		100, NULL, 1, &T_BlueTooth_Handle);					 //delay ~ 20
	xTaskCreate(T_ObjectDetection, "T_ObjectDetection",	100, NULL, 2, &T_ObjectDetection_Handle);	//delay ~ 25
	xTaskCreate(T_Light, "T_Light",				100, NULL, 3, &T_Light_Handle);
	xTaskCreate(T_CarControl, "T_CarControl",	100, NULL, 4, &T_CarControl_Handle);
	xTaskCreate(T_Mirrors, "T_Mirrors",			100, NULL, 5, &T_Mirror_Handle);
	xTaskCreate(T_Parking, "T_Parking",			100, NULL, 6, &T_Parking_Handle);
	
	/* Start OS or Scheduler */	vTaskStartScheduler();
}
void system_init(void)
{
	Bool correctPW = FALSE;
	INT8U enteredPW[3] = {0}, owner = 0, data, i = 0;

	LCD_Init();
	ULTRASONIC_Init();
	car_control_init();
	uni_stepper_init(1);
	uni_stepper_init(2);
	LEDMatrix_Init();
	BT_Init(UART_1, 9600);
	sei();
	
	LCD_DispStrXY(1, 1, "R U The Owner?");
	LCD_DispStrXY(2, 1, "Yes (y) / No (n)");
	owner = BT_ReceiveByte(UART_1);
	while(!correctPW)
	{
		if (owner == 'y')
		{
			while(correctPW == FALSE)
			{
				LCD_DispStrXY(1, 1, "Waiting...        ");
				LCD_DispStrXY(2, 1, "                  ");
				enteredPW[0] = BT_ReceiveByte(UART_1);
				enteredPW[1] = BT_ReceiveByte(UART_1);
				enteredPW[2] = BT_ReceiveByte(UART_1);
				
				if(enteredPW[0] == password[0] && enteredPW[1] == password[1] && enteredPW[2] == password[2])
				{
					LCD_Clear();
					LCD_DispStrXY(1, 1, "System Started");
					_delay_ms(5000);
					LCD_Clear();
					correctPW = TRUE;
				}
				else
				{
					Uart_SendStr(UART_1, "Wrong PW, Send Again");
				}
			}
		}
		else if (owner == 'n')
		{
			
			LCD_DispStrXY(1, 1, "Waiting...        ");
			LCD_DispStrXY(2, 1, "                  ");
			MQTT_Init();
			Wifi_EchoMode(NoEcho);
			_delay_ms(1000);
			Wifi_AP_Connect("Electronics","Cisco123");		//Connect to wifi network
			_delay_ms(15000);
			Wifi_ConnectionMode(single);
			_delay_ms(2000);
			Wifi_StartTCP_Conn("192.168.222.104","1883", "60");
			_delay_ms(2000);
			MQTT_Connect("AARAH");
			_delay_ms(2000);
			MQTT_Subscribe("NTI@");
			while(correctPW == FALSE)
			{
				data = Uart_ReceiveByte(UART_0);
				while(data != '@')
				{
					data = Uart_ReceiveByte(UART_0);
				}
				enteredPW[0] = BT_ReceiveByte(UART_0);
				enteredPW[1] = BT_ReceiveByte(UART_0);
				enteredPW[2] = BT_ReceiveByte(UART_0);
				if(enteredPW[0] == password[0] && enteredPW[1] == password[1] && enteredPW[2] == password[2])
				{
					LCD_Clear();
					LCD_DispStrXY(1, 1, "System Started");
					_delay_ms(5000);
					LCD_Clear();
					correctPW = TRUE;
				}
				else
				{
					MQTT_Publish("NTIR", "Wrong PW, Send Again", strlen("Wrong PW, Send Again"), 0);
				}
			}
		}
		else
		{
			owner = BT_ReceiveByte(UART_1);
		}
		
	}
	LCD_Clear();
}
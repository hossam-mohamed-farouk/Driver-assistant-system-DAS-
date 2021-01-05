#include "T_ObjectDetection.h"void T_ObjectDetection(void* pvdata){	INT16U Distance			= 0 ;			                    	   // Distance From UltraSonic	INT8U Stop				= OBJ_DETECTED;	                          // If Object Detected	INT8U Clear				= OBJ_CLEARED;	                    	 // If No Object	INT8U Leds_MidOff		= LED_MIDOFF;	                    	// Lights Middle Off	INT8U Leds_All_On		= OBJ_DETECTED;                        // If range<15 Leds_All_On	INT8U Leds_All_ON	    = OBJ_CLEARED;                        // If range>30 Leds_All_ON	INT8U Change_Flag		= 0xFF;                              // Flag to sense Changes		while(1)	{		ULTRASONIC_Start(ULTRASONIC_1);                                              // UltraSonic1
		vTaskDelay(25);
		if ( ULTRASONIC_GetDistanceNoBlock(&Distance) )			                    // UltraSonic Get Distance
		{
			LCD_DispIntXY(2, 8, Distance);
			if (Distance <= 60)													   // Check If Distance Less Than 15
			{
				if (Change_Flag == 0 || Change_Flag == 2 || Change_Flag == 0xFF)
				{
					xQueueSend(mqLightCtrl, &Leds_All_On, portMAX_DELAY);       // Send To mqLightCtrl There Are Obj_detection
					xQueueSend(mqCarMove  , &Stop       , portMAX_DELAY);      // Send To mqCarMove There Are Obj_detection
					Change_Flag = 1;
				}
			}
			else if (Distance < 120)										          // Check If Distance Less Than
			{
				if (Change_Flag == 1 || Change_Flag == 2 || Change_Flag == 0xFF)
				{
					xQueueSend(mqLightCtrl, &Leds_MidOff, portMAX_DELAY);      // Send To mqLightCtrl There Are object To Leds_MidOff
					xQueueSend(mqCarMove  , &Clear      , portMAX_DELAY);     // Send To mqCarMove There Are No Near Obj_detection
					Change_Flag = 0;
				}
			}
			else                                                                // Check If Distance more Than 30
			{
				if (Change_Flag == 1 || Change_Flag == 0 || Change_Flag == 0xFF)
				{
					xQueueSend(mqLightCtrl, &Leds_All_ON, portMAX_DELAY);     // Send To mqLightCtrl There Are not object To Leds_All_ON
					xQueueSend(mqCarMove  , &Clear      , portMAX_DELAY);	 // Send To mqCarMove There Are No Near Obj_detection
					Change_Flag = 2;
				}
			}
		}	}}
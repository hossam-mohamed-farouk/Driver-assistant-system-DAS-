#include "T_ObjectDetection.h"
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
		}
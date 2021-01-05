/*
 * T_BlueTooth.h
 *
 * Created: 8/4/2020 1:40:23 PM
 *  Author: H
 */ 

#ifndef T_BLUETOOTH_H_
#define T_BLUETOOTH_H_

#include "app.h"
#include "BlueTooth.h"

/* OS Services Declaration */
/*Car Move Message Queue*/
extern xQueueHandle		mqCarMove;
/*Mirror Control Message Queue*/
extern xQueueHandle		mqMirrorCtrl;
/*Light Control Message Queue*/
extern xQueueHandle		mqLightCtrl;
/*Semaphore To Start Parking Task*/
extern xSemaphoreHandle	bsParkStart;
/*Semaphore To Start IR Task*/
extern xSemaphoreHandle	bsIRStart;

extern xSemaphoreHandle	bsParkStart;

extern xTaskHandle T_ObjectDetection_Handle;
extern xTaskHandle T_Light_Handle;
extern xTaskHandle T_Mirror_Handle;
extern xTaskHandle T_CarControl_Handle;
extern xTaskHandle T_Parking_Handle;

#endif /* T_BLUETOOTH_H_ */
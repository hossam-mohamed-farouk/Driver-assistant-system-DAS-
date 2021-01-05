/*
 * T_Parking.h
 *
 * Created: 8/4/2020 5:15:17 PM
 *  Author: H
 */ 


#ifndef T_PARKING_H_
#define T_PARKING_H_

#include "app.h"
#include "stdlib.h"

#define PARK_TIME_NEEDED	40
#define	CAR_WIDTH			50

//task handle
extern xTaskHandle T_ObjectDetection_Handle;
extern xTaskHandle T_Light_Handle;
extern xTaskHandle T_Mirror_Handle;
extern xTaskHandle T_CarControl_Handle;

/*Semaphore To Start Parking Task*/
extern xSemaphoreHandle	bsParkStart;
extern xSemaphoreHandle	bsIRStart;


/*Semaphore To Start IR Task*/
extern xSemaphoreHandle	bsIRStart;



#endif /* T_PARKING_H_ */
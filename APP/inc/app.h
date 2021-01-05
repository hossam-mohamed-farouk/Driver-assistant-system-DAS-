#ifndef APP_H_
#define APP_H_

/*include FreeRTOS files*/
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"
/*include IoT files*/
#include "mqtt.h"
#include "Wifi.h"
/*include avr drivers*/
#include "adc.h"
#include <avr/io.h>
#include "Servo.h"
#include "ultrasonic.h"
#include "car_control.h"
#include "uart.h"
#include "lcd.h"
#include "ir.h"
#include "unipolar_stepper.h"
#include "BlueTooth.h"
#include "max7219.h"
#include "LEDMatrix.h"

/*Define the buttons*/
typedef enum{
	CARMOVE_F		= 'F',
	CARMOVE_B		= 'B',
	CARMOVE_R		= 'R',
	CARMOVE_L		= 'L',
	CARMOVE_FR		= 'I',
	CARMOVE_FL		= 'G',
	CARMOVE_BR		= 'J',
	CARMOVE_BL		= 'H',
	CARSPEED_INC	= '0',
	CARSPEED_DEC	= '9',
	CARSPEED_STOP	= 'S',
	IR_CLEARTOGO	= 's',
	OBJ_DETECTED	= 'D',
	OBJ_CLEARED		= '!'
}CarMove_t;

typedef enum{
	MIR_OPEN		= 'O',
	MIR_CLOSE	    = 'C',
	MIR_RINC	    = 'P',
	MIR_RDEC		= 'p',
	MIR_LINC		= 'Q',
	MIR_LDEC		= 'q'
}MirrorCtrl_t;

typedef enum{
	LED_ON		= 'W',
	LED_OFF		= 'w',
	LED_MIDOFF	= 'z'
}LightCtrl_t;

#define PARRKING_START		'V'
#define PARKING_STOP		'X'
/*System APIs decliration*/
void system_init(void);

void T_BlueTooth(void* pvData);
void T_CarControl(void* pvData);
void T_Mirrors(void* pvData);
void T_ObjectDetection(void* pvData);
void T_Light(void* pvData);
void T_Parking(void* pvData);

#endif /* APP_H_ */
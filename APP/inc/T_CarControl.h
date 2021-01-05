#ifndef T_CARCONTROL_H_
#define T_CARCONTROL_H_

#include "app.h"

/*** This task waiting for command from the bluetooth or the ultrasonic task and excute the function of the command ***/

#define SPEED_INC_VAL 10
#define SPEED_DEC_VAL 10

/*Car Move Message Queue*/
extern xQueueHandle		mqCarMove;




#endif /* T_CARCONTROL_H_ */
#ifndef LEDMATRIX_H_
#define LEDMATRIX_H_

#include "max7219.h"
/* Initialization of the LED Matrix */
void LEDMatrix_Init(void);

/*The following functions, light on, off, or parts of the LED Matrix as each function name presents*/
void LEDMatrix_AllOn(void);
void LEDMatrix_AllOff(void);
void LEDMatrix_AllDim(void);
void LEDMatrix_MidOff(void);
void LEDMatrix_RightHalf(void);
void LEDMatrix_LeftHalf(void);



#endif /* LEDMATRIX_H_ */
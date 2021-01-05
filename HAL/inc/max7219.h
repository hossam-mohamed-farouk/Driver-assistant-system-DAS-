#ifndef MAX7219_H_
#define MAX7219_H_

#include "spi.h"

/* Addresses of MAX7219 registers, to be used as reg in Max7219_SendByte() function */
#define MAX7219_REG_NOOP                (0x00)
#define MAX7219_REG_DIGIT0              (0x01)
#define MAX7219_REG_DIGIT1              (0x02)
#define MAX7219_REG_DIGIT2              (0x03)
#define MAX7219_REG_DIGIT3              (0x04)
#define MAX7219_REG_DIGIT4              (0x05)
#define MAX7219_REG_DIGIT5              (0x06)
#define MAX7219_REG_DIGIT6              (0x07)
#define MAX7219_REG_DIGIT7              (0x08)
#define MAX7219_REG_DECODEMODE			(0x09)
#define MAX7219_REG_INTENSITY			(0x0A)
#define MAX7219_REG_SCANLIMIT			(0x0B)
#define MAX7219_REG_SHUTDOWN			(0x0C)
#define MAX7219_REG_DISPLAYTEST			(0x0F)

/* Initialization of Max7219 */
void Max7219_Init(void);
/* Sending data to the corresponding register in Max7219 */
void Max7219_SendByte(INT8U reg, INT8U u8Data);



#endif /* MAX7219_H_ */
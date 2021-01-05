#ifndef IR_H_
#define IR_H_

#ifndef F_CPU
	#define F_CPU	8000000UL
#endif

#ifndef	NULL
	#define NULL   ( (void*)0 )
#endif

#include	"avr/io.h"
#include	"data_types.h"
#include	"bit_handle.h"
#include	"ext_interrupt.h"
#include	"util/delay.h"

#define IR_DDR	DDRD
#define IR_PORT	PIND

typedef enum
{
	ir_no_obstacle,
	ir_obstacle,
	ir_no_change
}ir_state;

void ir_init(INT8U ir_pin);
ir_state ir_read(INT8U ir_pin);
ir_state ir_read_int(INT8U ir_select);

#endif /* IR_H_ */
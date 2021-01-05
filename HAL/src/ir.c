#include "ir.h"

//ir is normally high and gives low when something on the way
static INT8U ir_new_state_1 = 1;
static INT8U ir_old_state_1 = 1;
static INT8U ir_new_state_2 = 1;
static INT8U ir_old_state_2 = 1;

volatile ir_state state_1 = ir_no_change;
volatile ir_state state_2 = ir_no_change;

volatile ir_state ir_edge_flag_1 = 0;
volatile ir_state ir_edge_flag_2 = 0;

static void ir_1_interrupt();
static void ir_2_interrupt();

void ir_init(INT8U ir_pin)
{
	//make ir pin as input
	clearBit(IR_DDR, ir_pin);
	//enable external interrupt on falling edge
	switch(ir_pin)
	{
		case 0:
			EXT_Enable(INT_NUM_0, INT_SENSE_FALLING);
			EXT_CallSetup(INT_NUM_0, ir_1_interrupt);
		break;
		
		case 1:
			EXT_Enable(INT_NUM_1, INT_SENSE_FALLING);
			EXT_CallSetup(INT_NUM_1, ir_2_interrupt);
		break;
	}
}

ir_state ir_read(INT8U ir_pin)
{
	ir_state state = 0xFF;
	//check which ir_pin
	switch(ir_pin)
	{
		case 0:
			//read and put data in new state
			ir_new_state_1 = readBit(IR_PORT, ir_pin);
			//check if any change occurred
			if(ir_new_state_1 == 0 && ir_old_state_1 == 1)
				state = ir_obstacle;
			else if(ir_new_state_1 == 1 && ir_old_state_1 == 0)
				state = ir_no_obstacle;
			else
				state = ir_no_change;
			//put new state in old state
			ir_old_state_1 = ir_new_state_1;
		break;
		
		case 1:
			//read and put data in new state
			ir_new_state_2 = readBit(IR_PORT, ir_pin);
			//check if any change occurred
			if(ir_new_state_2 == 0 && ir_old_state_2 == 1)
				state = ir_obstacle;
			else if(ir_new_state_2 == 1 && ir_old_state_2 == 0)
				state = ir_no_obstacle;
			else
				state = ir_no_change;
			//put new state in old state
			ir_old_state_2 = ir_new_state_2;
		break;
	}
	
	return state;
}

ir_state ir_read_int(INT8U ir_select)
{
	ir_state state = ir_no_change;
	switch (ir_select)
	{
		case 0:
			state = state_1;
		break;
		
		case 1:
			state = state_2;
		break;
	}
	
	return state;
}

void ir_1_interrupt()
{
	if(ir_edge_flag_1 == 0)
	{
		state_1 = ir_obstacle;
		EXT_Enable(INT_NUM_0, INT_SENSE_RISING);
		ir_edge_flag_1 = 1;
	}
	else if(ir_edge_flag_1 == 1)
	{
		state_1 = ir_no_obstacle;
		EXT_Enable(INT_NUM_0, INT_SENSE_FALLING);
		ir_edge_flag_1 = 0;
	}
}

void ir_2_interrupt()
{
	if(ir_edge_flag_2 == 0)
	{
		state_2 = ir_obstacle;
		EXT_Enable(INT_NUM_1, INT_SENSE_RISING);
		ir_edge_flag_2 = 1;
	}
	else if(ir_edge_flag_2 == 1)
	{
		state_2 = ir_no_obstacle;
		EXT_Enable(INT_NUM_1, INT_SENSE_FALLING);
		ir_edge_flag_2 = 0;
	}
}
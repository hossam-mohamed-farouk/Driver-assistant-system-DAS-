#include "unipolar_stepper.h"
#include "FreeRTOS.h"
#include "task.h"

//outputs on the port
INT8U half_steps_output[] = {0x09, 0x08, 0x0C, 0x04, 0x06, 0x02, 0x03, 0x01};

//step counter for each stepper
INT8U step_counter_1 = 0;
INT8U step_counter_2 = 0;

//save current step the stepper is on
INT8U current_step_1 = 0;
INT8U current_step_2 = 0;

void uni_stepper_init(INT8U stepper_select)
{
	//initialize stepper pins as output
	switch (stepper_select)
	{
		case 1:
		setBit(UNI_STEPPER_1_DDR, UNI_STEPPER_1_PIN_1);
		setBit(UNI_STEPPER_1_DDR, UNI_STEPPER_1_PIN_2);
		setBit(UNI_STEPPER_1_DDR, UNI_STEPPER_1_PIN_3);
		setBit(UNI_STEPPER_1_DDR, UNI_STEPPER_1_PIN_4);
		break;
		
		case 2:
		setBit(UNI_STEPPER_2_DDR, UNI_STEPPER_2_PIN_1);
		setBit(UNI_STEPPER_2_DDR, UNI_STEPPER_2_PIN_2);
		setBit(UNI_STEPPER_2_DDR, UNI_STEPPER_2_PIN_3);
		setBit(UNI_STEPPER_2_DDR, UNI_STEPPER_2_PIN_4);
		break;
	}
}

void uni_stepper_increment_clkwise(INT8U stepper_select)
{
	switch(stepper_select)
	{
		case 1:
			//increment step
			step_counter_1++;
			//reset stepper if it passed 7 the max number in the output array
			if(step_counter_1 == 8)
			{
				step_counter_1 = 0;	
			}
			//clear bits to write in
			UNI_STEPPER_1_PORT &= 0xF0;
			//put angle step on port
			UNI_STEPPER_1_PORT |= half_steps_output[step_counter_1];
			//minimum delay for motor req
			vTaskDelay(UNI_STEPPER_DELAY);
			//increment current step
			current_step_1++;
			//if full revolution happened reset to zero
			if(current_step_1 == UNI_360_STEPS)
			{
				current_step_1 = 0;
			}
		break;
		
		case 2:
			//increment step
			step_counter_2++;
			//reset stepper if it passed 7 the max number in the output array
			if(step_counter_2 == 8)
			{
				step_counter_2 = 0;	
			}
			//clear bits to write in
			UNI_STEPPER_1_PORT &= 0x0F;
			//put angle step on port
			UNI_STEPPER_1_PORT |= (half_steps_output[step_counter_2] << 4) & 0xF0;
			//minimum delay for motor req
			vTaskDelay(UNI_STEPPER_DELAY);
			//increment current step
			current_step_2++;
			//if full revolution happened reset to zero
			if(current_step_2 == UNI_360_STEPS)
			{
				current_step_2 = 0;
			}
		break;
	}
}

void uni_stepper_increment_anticlk(INT8U stepper_select)
{
	switch(stepper_select)
	{
		case 1:
			//decrement step
			step_counter_1--;
			//255 is the underflow value after decrement below 0
			if(step_counter_1 == 255)
			{
				step_counter_1 = 7;
			}
			//clear bits to write in
			UNI_STEPPER_1_PORT &= 0xF0;
			//put angle step on port
			UNI_STEPPER_1_PORT |= half_steps_output[step_counter_1];
			//minimum delay for motor req
			vTaskDelay(UNI_STEPPER_DELAY);
			//if full revolution happened reset to zero
			if(current_step_1 == 0)
			{
				current_step_1 = UNI_360_STEPS;
			}
			//decrement current step
			current_step_1--;
		break;
		
		case 2:
			//decrement step
			step_counter_2--;
			//255 is the underflow value after decrement below 0
			if(step_counter_2 == 255)
			{
				step_counter_2 = 7;
			}
			//clear bits to write in
			UNI_STEPPER_1_PORT &= 0x0F;
			//put angle step on port
			UNI_STEPPER_1_PORT |= (half_steps_output[step_counter_2] << 4) & 0xF0;
			//minimum delay for motor req
			vTaskDelay(UNI_STEPPER_DELAY);
			//if full revolution happened reset to zero
			if(current_step_2 == 0)
			{
				current_step_2 = UNI_360_STEPS;
			}
			//decrement current step
			current_step_2--;
		break;
	}
}

void uni_stepper_goto_zero_clkwise(INT8U stepper_select)
{
	switch(stepper_select)
	{
		//keep stepping as long as it hadn't reach zero
		case 1:
			while(current_step_1 != 0)
			{
				uni_stepper_increment_clkwise(stepper_select);
			}
		break;
		
		case 2:
			while(current_step_2 != 0)
			{
				uni_stepper_increment_clkwise(stepper_select);
			}
		break;
	}
}

//same as the above functions but opposite direction for each case
void uni_stepper_goto_zero_anticlk(INT8U stepper_select)
{
	switch(stepper_select)
	{
		case 1:
		while(current_step_1 != 0)
		{
			uni_stepper_increment_anticlk(stepper_select);
		}
		break;
		
		case 2:
		while(current_step_2 != 0)
		{
			uni_stepper_increment_anticlk(stepper_select);
		}
		break;
	}
}


void uni_stepper_goto_90_clkwise(INT8U stepper_select)
{
	switch(stepper_select)
	{
		//keep stepping as long as it hadn't reach 16 steps, 90 degrees
		case 1:
		while(current_step_1 != 16)
		{
			uni_stepper_increment_clkwise(stepper_select);
		}
		break;
		
		case 2:
		while(current_step_2 != 16)
		{
			uni_stepper_increment_clkwise(stepper_select);
		}
		break;
	}
}

//same as the above functions but opposite direction for each case
//48 is the 270 degree equivalent 
void uni_stepper_goto_90_anticlk(INT8U stepper_select)
{
	switch(stepper_select)
	{
		case 1:
		while(current_step_1 != 48)
		{
			uni_stepper_increment_anticlk(stepper_select);
		}
		break;
		
		case 2:
		while(current_step_2 != 48)
		{
			uni_stepper_increment_anticlk(stepper_select);
		}
		break;
	}
}

void uni_stepper_goto_180_clkwise(INT8U stepper_select)
{
	switch(stepper_select)
	{
		case 1:
		while(current_step_1 != 32)
		{
			uni_stepper_increment_clkwise(stepper_select);
		}
		break;
		
		case 2:
		while(current_step_2 != 32)
		{
			uni_stepper_increment_clkwise(stepper_select);
		}
		break;
	}
}

void uni_stepper_goto_180_anticlk(INT8U stepper_select)
{
	switch(stepper_select)
	{
		case 1:
		while(current_step_1 != 32)
		{
			uni_stepper_increment_anticlk(stepper_select);
		}
		break;
		
		case 2:
		while(current_step_2 != 32)
		{
			uni_stepper_increment_anticlk(stepper_select);
		}
		break;
	}
}
#include "T_Mirrors.h"

//function prototypes for closing and opening mirrors at the same time
void close_mirrors_together();
void open_mirrors_together();

//to make sure that stepper doesn't move bigger than 90 or less than 0
INT8U left_mirror_limiter = 0;
INT8U right_mirror_limiter = 0;

void T_Mirrors(void* pvData)
{
	INT8U cmd = 0;
	while (1)
	{
		if( xQueueReceive(mqMirrorCtrl, &cmd, portMAX_DELAY) )
		{
			switch (cmd)
			{
				//open both mirrors to 90
				case 'O':
					open_mirrors_together();
					//put the mirror limiters to 16 the number of steps to reach 90
					right_mirror_limiter = 16;
					left_mirror_limiter = 16;
				break;
			
				//close both mirrors to 0
				case 'C':
					close_mirrors_together();
					//return limiters to 0 steps
					right_mirror_limiter = 0;
					left_mirror_limiter = 0;
				break;
			
				//increment right mirror
				case 'P':
					//to open mirror an extra step, make sure that they're open less than 90
					//16 is the number of steps for 90 degrees
					if(right_mirror_limiter < 16)
					{
						//increment limiter by one step
						right_mirror_limiter++;
						//action function call
						uni_stepper_increment_anticlk(1);
					}
				break;
			
				//decrement right mirror
				case 'p':
					//to close mirror by one step, make sure that they're open more than 0
					if(right_mirror_limiter > 0)
					{
						//decrement limiter by one step
						right_mirror_limiter--;
						//action function call
						uni_stepper_increment_clkwise(1);
					}
				break;
			
				//increment left mirror
				case 'Q':
					//to open mirror an extra, make sure that they're less than 90
					//16 is the number of steps for 90 degrees
					if(left_mirror_limiter < 16)
					{
						//increase limiter by one step
						left_mirror_limiter++;
						//action function
						uni_stepper_increment_clkwise(2);
					}
				break;
			
				//decrement left mirror
				case 'q':
					//to close mirror by one step, make sure that they're open more than 0
					if(left_mirror_limiter > 0)
					{
						//dec limiter by one step
						left_mirror_limiter--;
						//action function
						uni_stepper_increment_anticlk(2);
					}
				break;
			}
		}
	}
}

//function to close mirrors together
//return both limiters to zero
void close_mirrors_together()
{
	//keep doing this as long as one of the limiters is above 0
	while(right_mirror_limiter > 0 || left_mirror_limiter > 0)
	{
		//these two if functions to make sure that if open at different steps
		//not else if so both have to be done simultaneously not do one and then the other
		if(right_mirror_limiter > 0)
		{
			//right dec
			uni_stepper_increment_clkwise(1);
			right_mirror_limiter--;
		}
		
		if(left_mirror_limiter > 0)
		{
			//left dec
			uni_stepper_increment_anticlk(2);
			left_mirror_limiter--;
		}
	}
}

//function to open mirrors together
//both limiters reach 16 steps, 90 degrees
void open_mirrors_together()
{
	//keep doing this as long as one of the limiters is above 0
	while(right_mirror_limiter < 16 || left_mirror_limiter < 16)
	{
		//these two if functions to make sure that if open at different steps, one at 45 and the other 60 for example
		//not else if so both have to be done simultaneously not do one and then the other
		if(right_mirror_limiter < 16)
		{
			//right inc
			uni_stepper_increment_anticlk(1);
			right_mirror_limiter++;
		}
		
		if(left_mirror_limiter < 16)
		{
			//left dec
			uni_stepper_increment_clkwise(2);
			left_mirror_limiter++;
		}
	}
}
/*
* ultrasonic.c
*
* Created: 7/6/2020 10:09:57 PM
*  Author: H
*/

#include "ultrasonic.h"

static volatile INT16U t1,t2,flag=0,c=0;

static void Func_ICU(void);
static void Func_OVF(void);

void ULTRASONIC_Init(void)
{
	/****you can use timer in another mode except modes using ICR as top put take care dont reset timer****/
	Timer3_Init(TIMER3_NORMAL_MODE,TIMER3_SCALER_8,OCR3A_DISCONNECTED,OCR3B_DISCONNECTED);
	setBit  (ULTRASONIC_DDR,ULTRASONIC_1);              // trigger PIN as Output   PG0
	setBit  (ULTRASONIC_DDR,ULTRASONIC_2);              // trigger PIN as Output   PG1
	setBit  (ULTRASONIC_DDR,ULTRASONIC_3);              // trigger PIN as Output   PG2
	setBit  (ULTRASONIC_DDR,ULTRASONIC_4);              // trigger PIN as Output   PG3
	setBit  (ULTRASONIC_DDR,ULTRASONIC_5);              // trigger PIN as Output   PG4
	clearBit(ULTRASONIC_ECHO_DDR,ULTRASONIC_ECHO_PIN);  //  make ECHO as Input		  
	Timer3_OVF_SetCallBack(Func_OVF);
	Timer3_ICU_SetCallBack(Func_ICU);
	
}

INT8U ULTRASONIC_GetDistance(ULTRASONIC_type ultrasonic_pin)
{
	INT8U distance;
	INT16U time;
	TCNT3=0;   //comment it if timer is used for other purposes
	c=0;
	flag=0;
	setBit(ULTRASONIC_PORT, ultrasonic_pin);
	_delay_us(10);
	clearBit(ULTRASONIC_PORT, ultrasonic_pin);
	Timer3_OVF_InterruptEnable();
	Timer3_InputCaptureEdge(RISING);
	Timer3_ICU_InterruptEnable();
	
	while (flag<2);
	time=t2-t1+((INT32U)c*19999);		//time = t2 + ((INT32U)c*65535) - t1; //19999
	distance=time/58;					//This gives distance in cm time = 58 * 200 = 10,000 = 10 ms
	Timer3_ICU_InterruptDisable();
	return distance;
}

void ULTRASONIC_Start(ULTRASONIC_type ultrasonic_pin)
{
	if(flag==0)
	{
		c = 0;
		setBit(ULTRASONIC_PORT, ultrasonic_pin);
		_delay_us(10);
		clearBit(ULTRASONIC_PORT, ultrasonic_pin);
		Timer3_InputCaptureEdge(RISING);
		Timer3_ICU_InterruptEnable();
		Timer3_OVF_InterruptEnable();
	}
}

INT16U ULTRASONIC_GetDistanceNoBlock(INT16U*Pdistance)
{
	INT16U distance;
	INT16U time;
	
	if (flag==2)
	{
		time=t2-t1+((INT32U)c*65535);  //65535
		distance=time/58;
		*Pdistance=distance;
		Timer3_OVF_InterruptEnable();
		flag=0;
		return 1;
	}
	return 0;
}

/*Using polling*/
INT8U ULTRASONIC_GetDistance2(ULTRASONIC_type ultrasonic_pin)
{
	
	INT8U distance;
	INT16U time;
	setBit(ULTRASONIC_PORT, ultrasonic_pin);
	_delay_us(10);
	clearBit(ULTRASONIC_PORT, ultrasonic_pin);
	while (!readBit(PORTD, PD4));		/*Must do clearBit(DDRD, PD4); in main*/
	//TCNT3=0;							/*Timer 3 must not be used elsewhere!*/
	while (readBit(PORTD, PD4));
	time=TCNT3;
	distance=time/58;
	return distance;
}

static void Func_ICU(void)
{
	if(flag==0)
	{
		c=0;
		t1=ICR3;
		flag=1;
		Timer3_InputCaptureEdge(FALLING);
	}
	else if (flag==1)
	{
		t2=ICR3;
		flag=2;
		Timer3_InputCaptureEdge(RISING);
		Timer3_OVF_InterruptDisable();
		Timer3_ICU_InterruptDisable();
	}
}

static void Func_OVF(void)
{
	c++;
}
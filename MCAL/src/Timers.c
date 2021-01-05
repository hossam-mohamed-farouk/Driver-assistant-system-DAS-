/*
* Timers.c
*
* Created: 7/3/2020 11:18:46 PM
*  Author: H
*/
#include "Timers.h"

/**************Pointer to functions to be assigned to ISR****************/

static void (*Timer1_OVF_Fptr) (void) = NULL;
static void (*Timer1_OCA_Fptr) (void) = NULL;
static void (*Timer1_OCB_Fptr) (void) = NULL;
static void (*Timer1_ICU_Fptr) (void) = NULL;

static void (*Timer3_OVF_Fptr) (void) = NULL;
static void (*Timer3_OCA_Fptr) (void) = NULL;
static void (*Timer3_OCB_Fptr) (void) = NULL;
static void (*Timer3_ICU_Fptr) (void) = NULL;

/************************************************************************/
/*								Timer 0						            */
/************************************************************************/
void Timer0_Init( Timer0Mode_type mode,Timer0Scaler_type scaler,OC0Mode_type oc_mode){
	
	switch (mode)
	{
		case TIMER0_NORMAL_MODE:
		clearBit(TCCR0,WGM00);
		clearBit(TCCR0,WGM01);
		break;
		case TIMER0_PHASECORRECT_MODE:
		setBit(TCCR0,WGM00);
		clearBit(TCCR0,WGM01);
		break;
		case TIMER0_CTC_MODE:
		clearBit(TCCR0,WGM00);
		setBit(TCCR0,WGM01);
		break;
		case TIMER0_FASTPWM_MODE:
		setBit(TCCR0,WGM00);
		setBit(TCCR0,WGM01);
		break;
	}
	
	clearBits(TCCR0, 0x07);
	setBits(TCCR0, scaler);
	
	switch (oc_mode)
	{
		case OCO_DISCONNECTED:
		clearBit(TCCR0,COM00);
		clearBit(TCCR0,COM01);
		break;
		case OCO_TOGGLE:
		setBit(TCCR0,COM00);
		clearBit(TCCR0,COM01);
		break;
		case OCO_NON_INVERTING:
		clearBit(TCCR0,COM00);
		setBit(TCCR0,COM01);
		break;
		case OCO_INVERTING:
		setBit(TCCR0,COM00);
		setBit(TCCR0,COM01);
		break;
	}
}
void Timer0_OV_InterruptEnable(void)
{
	setBit(TIMSK,TOIE0);
}
void Timer0_OV_InterruptDisable(void)
{
	clearBit(TIMSK,TOIE0);
}
void Timer0_OC_InterruptEnable(void)
{
	setBit(TIMSK,OCIE0);
}

void Timer0_OC_InterruptDisable(void)
{
	clearBit(TIMSK,OCIE0);
}

/************************************************************************/
/*								Timer 1						            */
/************************************************************************/


void Timer1_Init( Timer1Mode_type mode,Timer1Scaler_type scaler,OC1A_Mode_type oc1a_mode,OC1B_Mode_type oc1b_mode)

{
	switch (mode)
	{
		case TIMER1_NORMAL_MODE:
		clearBit(TCCR1A,WGM10);
		clearBit(TCCR1A,WGM11);
		clearBit(TCCR1B,WGM12);
		clearBit(TCCR1B,WGM13);
		break;
		case TIMER1_CTC_ICR_TOP_MODE:
		clearBit(TCCR1A,WGM10);
		clearBit(TCCR1A,WGM11);
		setBit(TCCR1B,WGM12);
		setBit(TCCR1B,WGM13);
		break;
		
		case TIMER1_CTC_OCRA_TOP_MODE:
		clearBit(TCCR1A,WGM10);
		clearBit(TCCR1A,WGM11);
		setBit(TCCR1B,WGM12);
		clearBit(TCCR1B,WGM13);
		break;
		
		case TIMER1_FASTPWM_ICR_TOP_MODE:
		clearBit(TCCR1A,WGM10);
		setBit(TCCR1A,WGM11);
		setBit(TCCR1B,WGM12);
		setBit(TCCR1B,WGM13);
		break;
		
		case TIMER1_FASTPWM_OCRA_TOP_MODE:
		setBit(TCCR1A,WGM10);
		setBit(TCCR1A,WGM11);
		setBit(TCCR1B,WGM12);
		setBit(TCCR1B,WGM13);
		break;
	}
	switch (oc1a_mode)
	{
		case OCRA_DISCONNECTED:
		clearBit(TCCR1A,COM1A0);
		clearBit(TCCR1A,COM1A1);
		break;
		case OCRA_TOGGLE:
		setBit(TCCR1A,COM1A0);
		clearBit(TCCR1A,COM1A1);
		break;
		case OCRA_NON_INVERTING:
		clearBit(TCCR1A,COM1A0);
		setBit(TCCR1A,COM1A1);
		break;
		case OCRA_INVERTING:
		setBit(TCCR1A,COM1A0);
		setBit(TCCR1A,COM1A1);
		break;
	}
	switch (oc1b_mode)
	{
		case OCRB_DISCONNECTED:
		clearBit(TCCR1A,COM1B0);
		clearBit(TCCR1A,COM1B1);
		break;
		case OCRB_TOGGLE:
		setBit(TCCR1A,COM1B0);
		clearBit(TCCR1A,COM1B1);
		break;
		case OCRB_NON_INVERTING:
		clearBit(TCCR1A,COM1B0);
		setBit(TCCR1A,COM1B1);
		break;
		case OCRB_INVERTING:
		setBit(TCCR1A,COM1B0);
		setBit(TCCR1A,COM1B1);
		break;
	}
	
	clearBits(TCCR1B, 0x07);
	setBits(TCCR1B, scaler);

}

void Timer1_InputCaptureEdge(ICU_Edge_type edge)
{
	if(edge==RISING)
	setBit(TCCR1B,ICES1);
	
	else if(edge==FALLING)
	clearBit(TCCR1B,ICES1);

}
/****************************Timer 1 Interrupt functions**************************************/

void Timer1_ICU_InterruptEnable(void)
{
	setBit(TIMSK,TICIE1);
}
void Timer1_ICU_InterruptDisable(void)
{
	clearBit(TIMSK,TICIE1);
}
void Timer1_OVF_InterruptEnable(void)
{
	setBit(TIMSK,TOIE1);
}
void Timer1_OVF_InterruptDisable(void)
{
	clearBit(TIMSK,TOIE1);
}
void Timer1_OCA_InterruptEnable(void)
{
	setBit(TIMSK,OCIE1A);
}
void Timer1_OCA_InterruptDisable(void)
{
	clearBit(TIMSK,OCIE1A);
}
void Timer1_OCB_InterruptEnable(void)
{
	setBit(TIMSK,OCIE1B);
}
void Timer1_OCB_InterruptDisable(void)
{
	clearBit(TIMSK,OCIE1B);
}

/*********************************Timer 1 Call Back functions*****************************************/

void Timer1_OVF_SetCallBack(void(*LocalFptr)(void))
{
	Timer1_OVF_Fptr=LocalFptr;
}
void Timer1_OCA_SetCallBack(void(*LocalFptr)(void))
{
	Timer1_OCA_Fptr=LocalFptr;
}
void Timer1_OCB_SetCallBack(void(*LocalFptr)(void))
{
	Timer1_OCB_Fptr=LocalFptr;
}
void Timer1_ICU_SetCallBack(void(*LocalFptr)(void))
{
	Timer1_ICU_Fptr=LocalFptr;
}

/*************************Timer 1 ISR functions********************************/
/*Comment it, to not conflict with RTOS*/
#if 0
ISR(TIMER1_OVF_vect)
{
	if(Timer1_OVF_Fptr!=NULL)
	{
		Timer1_OVF_Fptr();
	}
}
ISR(TIMER1_COMPA_vect)
{
	if(Timer1_OCA_Fptr!=NULL)
	{
		Timer1_OCA_Fptr();
	}
}
ISR(TIMER1_COMPB_vect)
{
	if(Timer1_OCB_Fptr!=NULL)
	{
		Timer1_OCB_Fptr();
	}
}
ISR(TIMER1_CAPT_vect)
{
	if(Timer1_ICU_Fptr!=NULL)
	{
		Timer1_ICU_Fptr();
	}
}
#endif

/************************************************************************/
/*								Timer 3						            */
/************************************************************************/


void Timer3_Init( Timer3Mode_type mode,Timer3Scaler_type scaler,OC3A_Mode_type oc3a_mode,OC3B_Mode_type oc3b_mode)

{
	switch (mode)
	{
		case TIMER3_NORMAL_MODE:
		clearBit(TCCR3A,WGM30);
		clearBit(TCCR3A,WGM31);
		clearBit(TCCR3B,WGM32);
		clearBit(TCCR3B,WGM33);
		break;
		case TIMER3_CTC_ICR_TOP_MODE:
		clearBit(TCCR3A,WGM30);
		clearBit(TCCR3A,WGM31);
		setBit(TCCR3B,WGM32);
		setBit(TCCR3B,WGM33);
		break;
		
		case TIMER3_CTC_OCRA_TOP_MODE:
		clearBit(TCCR3A,WGM30);
		clearBit(TCCR3A,WGM31);
		setBit(TCCR3B,WGM32);
		clearBit(TCCR3B,WGM33);
		break;
		
		case TIMER3_FASTPWM_ICR_TOP_MODE:
		clearBit(TCCR3A,WGM30);
		setBit(TCCR3A,WGM31);
		setBit(TCCR3B,WGM32);
		setBit(TCCR3B,WGM33);
		break;
		
		case TIMER3_FASTPWM_OCRA_TOP_MODE:
		setBit(TCCR3A,WGM30);
		setBit(TCCR3A,WGM31);
		setBit(TCCR3B,WGM32);
		setBit(TCCR3B,WGM33);
		break;
	}
	switch (oc3a_mode)
	{
		case OCR3A_DISCONNECTED:
		clearBit(TCCR3A,COM3A0);
		clearBit(TCCR3A,COM3A1);
		break;
		case OCR3A_TOGGLE:
		setBit(TCCR3A,COM3A0);
		clearBit(TCCR3A,COM3A1);
		break;
		case OCR3A_NON_INVERTING:
		clearBit(TCCR3A,COM3A0);
		setBit(TCCR3A,COM3A1);
		break;
		case OCR3A_INVERTING:
		setBit(TCCR3A,COM3A0);
		setBit(TCCR3A,COM3A1);
		break;
	}
	switch (oc3b_mode)
	{
		case OCR3B_DISCONNECTED:
		clearBit(TCCR3A,COM3B0);
		clearBit(TCCR3A,COM3B1);
		break;
		case OCR3B_TOGGLE:
		setBit(TCCR3A,COM3B0);
		clearBit(TCCR3A,COM3B1);
		break;
		case OCR3B_NON_INVERTING:
		clearBit(TCCR3A,COM3B0);
		setBit(TCCR3A,COM3B1);
		break;
		case OCR3B_INVERTING:
		setBit(TCCR3A,COM3B0);
		setBit(TCCR3A,COM3B1);
		break;
	}
	
	clearBits(TCCR3B, 0x07);
	setBits(TCCR3B, scaler);

}

void Timer3_InputCaptureEdge(ICU_Edge_type edge)
{
	if(edge==RISING)
	setBit(TCCR3B,ICES3);
	
	else if(edge==FALLING)
	clearBit(TCCR3B,ICES3);

}
/****************************Timer 3 Interrupt functions**************************************/

void Timer3_ICU_InterruptEnable(void)
{
	setBit(ETIMSK,TICIE3);
}
void Timer3_ICU_InterruptDisable(void)
{
	clearBit(ETIMSK,TICIE3);
}
void Timer3_OVF_InterruptEnable(void)
{
	setBit(ETIMSK,TOIE3);
}
void Timer3_OVF_InterruptDisable(void)
{
	clearBit(ETIMSK,TOIE3);
}
void Timer3_OCA_InterruptEnable(void)
{
	setBit(ETIMSK,OCIE3A);
}
void Timer3_OCA_InterruptDisable(void)
{
	clearBit(ETIMSK,OCIE3A);
}
void Timer3_OCB_InterruptEnable(void)
{
	setBit(ETIMSK,OCIE3B);
}
void Timer3_OCB_InterruptDisable(void)
{
	clearBit(ETIMSK,OCIE3B);
}

/*********************************Timer 3 Call Back functions*****************************************/

void Timer3_OVF_SetCallBack(void(*LocalFptr)(void))
{
	Timer3_OVF_Fptr=LocalFptr;
}
void Timer3_OCA_SetCallBack(void(*LocalFptr)(void))
{
	Timer3_OCA_Fptr=LocalFptr;
}
void Timer3_OCB_SetCallBack(void(*LocalFptr)(void))
{
	Timer3_OCB_Fptr=LocalFptr;
}
void Timer3_ICU_SetCallBack(void(*LocalFptr)(void))
{
	Timer3_ICU_Fptr=LocalFptr;
}

/*************************Timer 3 ISR functions********************************/
ISR(TIMER3_OVF_vect)
{
	if(Timer3_OVF_Fptr!=NULL)
	{
		Timer3_OVF_Fptr();
	}
}
ISR(TIMER3_COMPA_vect)
{
	if(Timer3_OCA_Fptr!=NULL)
	{
		Timer3_OCA_Fptr();
	}
}
ISR(TIMER3_COMPB_vect)
{
	if(Timer3_OCB_Fptr!=NULL)
	{
		Timer3_OCB_Fptr();
	}
}
ISR(TIMER3_CAPT_vect)
{
	if(Timer3_ICU_Fptr!=NULL)
	{
		Timer3_ICU_Fptr();
	}
}


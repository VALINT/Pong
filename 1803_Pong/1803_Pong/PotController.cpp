/*
 * PotController.c
 *
 * Created: 15.11.2016 17:42:36
 *  Author: VAL
 */ 
#include "PotController.h"
#include "Common.h"

unsigned int GetControlPosition(unsigned char Channel)
{
	uint16_t buffer = 0;
	
	if(Channel == 1)
	{
		ADMUX &=~ (1 << MUX3)|(1 << MUX2)|(1 << MUX1)|(1 << MUX0);
		asm("nop");
		ADMUX |=  (1 << MUX1);
		asm("nop");
		ADCSRA |= (1 << ADSC);
		
		while((ADCSRA & ADIF)==0){};
		ADCSRA |= (1 << ADIF);
		return(ADCW);	
	}
	if(Channel ==2)
	{
		
		ADMUX &=~ (1 << MUX3)|(1 << MUX2)|(1 << MUX1)|(1 << MUX0);
		asm("nop");
		ADMUX |=  (1 << MUX0)|(1 << MUX1);
		asm("nop");
		ADCSRA |= (1 << ADSC);
		
		while((ADCSRA & ADIF)==0){};
		ADCSRA |= (1 << ADIF);
		return(ADCW);	
	}
	
	return(124);
}
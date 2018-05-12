/*
 * _1803_Pong.cpp
 *
 * Created: 07.03.2018 0:07:07
 *  Author: VAL
 */ 

#include "Common.h"

static uint16_t FirstPadPosition,SecobdPadPosition;

void MCU_Init()														//Initialization MCU
{
	DDRD = 0x03;													//Set PORTD on output
	DDRB = 0xff;
													//Set PORTB on output

	SPCR |= (1 << SPE)|(1 << MSTR)|(1 << SPR0);						//setting SPI
	
	asm("sei");														//SREG = (1 << I), global interrapt is enable
}

void Timer0_Init()
{
	TCCR0B |= (1 << CS00);								//Timer 0 prescaler on 1024, interrupt 30 per second
	TIMSK0 |= (1 << TOIE0);											//Timer 0 interrupt enable
}

void ADC_Init()
{
	ADMUX |= (1 << REFS0);
	ADCSRA |= (1<<ADEN)  | (1<<ADPS2) | (1<<ADPS1);
}

ISR (TIMER0_OVF_vect)
{
	GameInterrapt();
}

int main(void)
{
	MCU_Init();
	ADC_Init();
	LCD_Init();
	LCD_SCL();
	Start();
	Timer0_Init();
	ScreenBuilder();
	while (1)
	{
	}
}


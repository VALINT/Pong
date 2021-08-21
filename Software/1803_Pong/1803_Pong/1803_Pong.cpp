/*
 * _1803_Pong.cpp
 *
 * Created: 07.03.2018 0:07:07
 *  Author: VAL
 */ 

#include "Common.h"
#include "paddle.h"
#include "ball.h"
#include "vec2d.h"

#define SCREEN_HEIGH 64
#define SCREEN_WIDTH 102

volatile uint8_t	ADC_channel = 0, mem_cell = 0;
volatile bool		new_screen = false;

uint16_t			right_paddle_buff[4] = {0,0,0,0};
uint16_t			left_paddle_buff[4]  = {0,0,0,0};
volatile uint8_t	frame_cnt = 0;

void MCU_Init()														//Initialization MCU
{
	DDRD = 0x0f;													//Set PORTD on output
	DDRB = 0xff;
													//Set PORTB on output

	SPCR |= (1 << SPE)|(1 << MSTR)|(1 << SPR0);						//setting SPI
	
	
	ADMUX |= (1 << REFS0);
	ADCSRA |= (1<<ADEN)|(1 << ADFR)|(1 << ADIE)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
	ADCSRA |= (1 << ADSC);
	
	TCCR0  = (1 << CS00)|(1 << CS02);								//Timer 0 prescaler on 1024, interrupt 30 per second
	TIMSK |= (1 << TOIE0);											//Timer 0 interrupt enable
	
	asm("sei");														//SREG = (1 << I), global interrapt is enable
}

void Timer0_Init()
{
	TCCR0  = (1 << CS00)|(1 << CS02);								//Timer 0 prescaler on 1024, interrupt 30 per second
	TIMSK |= (1 << TOIE0);											//Timer 0 interrupt enable
}

void ADC_Init()
{
	ADMUX |= (1 << REFS0);
	ADCSRA |= (1<<ADEN)|(1 << ADFR)|(1 << ADIE)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}

ISR (TIMER0_OVF_vect)
{
	TIFR &=~ (1 << TOV0);
	new_screen = true;
	frame_cnt ++;
	frame_cnt &= 0x0;
}

ISR (ADC_vect)
{
	ADCSRA &=~ (1 << ADIF);
	switch(ADC_channel)
	{
		case 0:
			right_paddle_buff[mem_cell] = ADCW;
			ADMUX = (1 << REFS0) | 1;
		break;
		case 1:
			left_paddle_buff[mem_cell] = ADCW;
			mem_cell ++;
			ADMUX = (1 << REFS0) | 0;
		break;
	}
	
	ADC_channel ++;
	ADC_channel &= 1;
	mem_cell &= 3;
}

int main(void)
{
	uint16_t left_paddle_value, right_paddle_value;
	paddle_t left_paddle, right_paddle;
	ball_t ball;
	
	uint8_t first_score = 0, second_score = 0;
	
	set_screen_param(102, 64);
	ball_set_screen_param(102, 64);
	ball_set_radius(&ball, 4);
	ball_set_start_pasition(&ball, {49, 30}, {2, 1});
	set_paddle_size(&right_paddle, 4, 20);
	set_paddle_size(&left_paddle, 4, 20);
	
	MCU_Init();
//	ADC_Init();
	LCD_Init();
	LCD_SCL();
	//Start();
	//Timer0_Init();
	//ScreenBuilder();
	
	LCD_Set_Cordinates(0,0);
	LCD_print('A');
	LCD_print('S');
	LCD_print('S');
	_delay_ms(2000);
	
	while (1)
	{
		if (!frame_cnt && new_screen)
		{
			new_screen = false;
			
			PORTD |= (1 << 3);
			
			// Count new paddle position
			left_paddle_value = 0;
			right_paddle_value = 0;
			for (uint8_t i = 0; i < 4; i++)
			{
				left_paddle_value  += left_paddle_buff[i];
				right_paddle_value += right_paddle_buff[i];
			}
			left_paddle_value  = left_paddle_value  >> 2;
			right_paddle_value = right_paddle_value >> 2;
			
			count_new_position(&left_paddle, left_paddle_value);
			count_new_position(&right_paddle, right_paddle_value);
			uint8_t res = ball_new_position(&ball, &left_paddle, &right_paddle);
			if(res == 2)
			{
				first_score++;
				ball_set_start_pasition(&ball, {49, 30}, {-2, -1});
			}
			else if(res == 1) 
			{
				second_score++;
				ball_set_start_pasition(&ball, {49, 30}, {2, 1});
			}
			
			
			LCD_Set_Cordinates(0,37);
			LCD_print(48 + ((first_score) % 100 ) / 10);
			LCD_print(48 +  (first_score) % 10);
			LCD_print(':');
			LCD_print(48 + ((second_score) % 100 ) / 10);
			LCD_print(48 +  (second_score) % 10);
			
			
			/*
			LCD_Set_Cordinates(0,0);
			LCD_print(48 + right_paddle_value / 1000);
			LCD_print(48 +(right_paddle_value % 1000) / 100);
			LCD_print(48 +(right_paddle_value % 100 ) / 10);
			LCD_print(48 + right_paddle_value % 10);
			
			LCD_Set_Cordinates(1,0);
			LCD_print(48 + left_paddle_value / 1000);
			LCD_print(48 +(left_paddle_value % 1000) / 100);
			LCD_print(48 +(left_paddle_value % 100 ) / 10);
			LCD_print(48 + left_paddle_value % 10);
			
			LCD_Set_Cordinates(0,30);
			LCD_print(48 + get_paddle_position(&right_paddle) / 100);
			LCD_print(48 +(get_paddle_position(&right_paddle) % 100 ) / 10);
			LCD_print(48 + get_paddle_position(&right_paddle) % 10);
			
			LCD_Set_Cordinates(1,30);
			LCD_print(48 + get_paddle_position(&left_paddle) / 100);
			LCD_print(48 +(get_paddle_position(&left_paddle) % 100 ) / 10);
			LCD_print(48 + get_paddle_position(&left_paddle) % 10);
		
			LCD_Set_Cordinates(0,60);
			LCD_print(48 + get_paddle_velocity(&right_paddle) / 100);
			LCD_print(48 +(get_paddle_velocity(&right_paddle) % 100 ) / 10);
			LCD_print(48 + get_paddle_velocity(&right_paddle) % 10);
			
			LCD_Set_Cordinates(1,60);
			LCD_print(48 + get_paddle_velocity(&left_paddle) / 100);
			LCD_print(48 +(get_paddle_velocity(&left_paddle) % 100 ) / 10);
			LCD_print(48 + get_paddle_velocity(&left_paddle) % 10);
		
			LCD_Set_Cordinates(3,0);
			LCD_print('X');
			LCD_print(':');
			LCD_print(' ');
			LCD_print(48 +  (ball.ball_position.x) / 100);
			LCD_print(48 + ((ball.ball_position.x) % 100 ) / 10);
			LCD_print(48 +  (ball.ball_position.x) % 10);
			
			LCD_Set_Cordinates(4,0);
			LCD_print('Y');
			LCD_print(':');
			LCD_print(' ');
			LCD_print(48 +  (ball.ball_position.y) / 100);
			LCD_print(48 + ((ball.ball_position.y) % 100 ) / 10);
			LCD_print(48 +  (ball.ball_position.y) % 10);		*/
			
			LCD_Set_Cordinates((left_paddle.paddle_y_prev_pos-10)/8, 4);
			LCD_Sent_Byte(0, DATA);
			LCD_Sent_Byte(0, DATA);
			LCD_Sent_Byte(0, DATA);
			LCD_Sent_Byte(0, DATA);
			LCD_Set_Cordinates((left_paddle.paddle_y_prev_pos-10)/8+1, 4);
			LCD_Sent_Byte(0, DATA);
			LCD_Sent_Byte(0, DATA);
			LCD_Sent_Byte(0, DATA);
			LCD_Sent_Byte(0, DATA);
			LCD_Set_Cordinates((left_paddle.paddle_y_prev_pos-10)/8+2, 4);
			LCD_Sent_Byte(0, DATA);
			LCD_Sent_Byte(0, DATA);
			LCD_Sent_Byte(0, DATA);
			LCD_Sent_Byte(0, DATA);
			
			int8_t h  = left_paddle.paddle_y_size;
			int8_t shift = (left_paddle.paddle_y_position-10)%8;
			LCD_Set_Cordinates((left_paddle.paddle_y_position-10)/8, 4);
			LCD_Sent_Byte((0xff << shift), DATA);
			LCD_Sent_Byte((0xff << shift), DATA);
			LCD_Sent_Byte((0xff << shift), DATA);
			LCD_Sent_Byte((0xff << shift), DATA);
			h -= (8-shift);
			LCD_Set_Cordinates((left_paddle.paddle_y_position-10)/8+1, 4);
			LCD_Sent_Byte((0xff), DATA);
			LCD_Sent_Byte((0xff), DATA);
			LCD_Sent_Byte((0xff), DATA);
			LCD_Sent_Byte((0xff), DATA);
			h -= 8;
			shift = 8 - h;
			LCD_Set_Cordinates((left_paddle.paddle_y_position-10)/8+2, 4);
			LCD_Sent_Byte((0xff >> shift), DATA);
			LCD_Sent_Byte((0xff >> shift), DATA);
			LCD_Sent_Byte((0xff >> shift), DATA);
			LCD_Sent_Byte((0xff >> shift), DATA);
			 
			
			
			
			LCD_Set_Cordinates((right_paddle.paddle_y_prev_pos-10)/8, 92);
			LCD_Sent_Byte(0, DATA);
			LCD_Sent_Byte(0, DATA);
			LCD_Sent_Byte(0, DATA);
			LCD_Sent_Byte(0, DATA);
			LCD_Set_Cordinates((right_paddle.paddle_y_prev_pos-10)/8+1, 92);
			LCD_Sent_Byte(0, DATA);
			LCD_Sent_Byte(0, DATA);
			LCD_Sent_Byte(0, DATA);
			LCD_Sent_Byte(0, DATA);
			LCD_Set_Cordinates((right_paddle.paddle_y_prev_pos-10)/8+2, 92);
			LCD_Sent_Byte(0, DATA);
			LCD_Sent_Byte(0, DATA);
			LCD_Sent_Byte(0, DATA);
			LCD_Sent_Byte(0, DATA);
			
			
			h  = right_paddle.paddle_y_size;
			shift = (right_paddle.paddle_y_position-10)%8;
			LCD_Set_Cordinates((right_paddle.paddle_y_position-10)/8, 92);
			LCD_Sent_Byte((0xff << shift), DATA);
			LCD_Sent_Byte((0xff << shift), DATA);
			LCD_Sent_Byte((0xff << shift), DATA);
			LCD_Sent_Byte((0xff << shift), DATA);
			h -= (8-shift);
			LCD_Set_Cordinates((right_paddle.paddle_y_position-10)/8+1, 92);
			LCD_Sent_Byte((0xff), DATA);
			LCD_Sent_Byte((0xff), DATA);
			LCD_Sent_Byte((0xff), DATA);
			LCD_Sent_Byte((0xff), DATA);
			h -= 8;
			shift = 8 - h;
			LCD_Set_Cordinates((right_paddle.paddle_y_position-10)/8+2, 92);
			LCD_Sent_Byte((0xff >> shift), DATA);
			LCD_Sent_Byte((0xff >> shift), DATA);
			LCD_Sent_Byte((0xff >> shift), DATA);
			LCD_Sent_Byte((0xff >> shift), DATA);
			
			
			LCD_Set_Cordinates(ball.last_position.y/8, ball.last_position.x);
			LCD_Sent_Byte(0, DATA);
			LCD_Sent_Byte(0, DATA);
			LCD_Sent_Byte(0, DATA);
			LCD_Sent_Byte(0, DATA);
			
			LCD_Set_Cordinates(ball.ball_position.y/8, ball.ball_position.x);
			LCD_Sent_Byte((0xf << ball.ball_position.y%8), DATA);
			LCD_Sent_Byte((0xf << ball.ball_position.y%8), DATA);
			LCD_Sent_Byte((0xf << ball.ball_position.y%8), DATA);
			LCD_Sent_Byte((0xf << ball.ball_position.y%8), DATA);
		}
	}
}


/*
 * paddle.cpp
 *
 * Created: 21.08.2021 16:56:55
 *  Author: VAL
 */ 

#include "paddle.h"

static uint8_t screen_width = 128;
static uint8_t screen_heigh = 64;

void set_screen_param(uint8_t width, uint8_t heigh)
{
	screen_width = width;
	screen_heigh = heigh;
}

void set_paddle_size(paddle_t* paddle, uint8_t x_size, uint8_t y_size)
{
	paddle->paddle_x_size = x_size;
	paddle->paddle_y_size = y_size;
	paddle->paddle_low_pos = 0 + paddle->paddle_y_size / 2;
	paddle->paddle_high_pos = screen_heigh - paddle->paddle_y_size / 2;
	paddle->paddle_step = 1023 / (paddle->paddle_high_pos - paddle->paddle_low_pos);
}

void count_new_position(paddle_t* paddle, uint16_t adc_val)
{
	paddle->paddle_y_prev_pos = paddle->paddle_y_position;
	paddle->paddle_y_position = paddle->paddle_low_pos + adc_val / paddle->paddle_step;
	paddle->paddle_y_velocity = (int8_t)(paddle->paddle_y_position - paddle->paddle_y_prev_pos);
}

uint8_t get_paddle_position(paddle_t* paddle)
{
	return paddle->paddle_y_position;
}

uint8_t get_paddle_velocity(paddle_t* paddle)
{
	return paddle->paddle_y_velocity;
}

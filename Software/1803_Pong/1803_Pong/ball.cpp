/*
 * ball.cpp
 *
 * Created: 21.08.2021 18:39:33
 *  Author: VAL
 */ 

#include "ball.h"

static uint8_t screen_width = 128;
static uint8_t screen_heigh = 64;

void ball_set_screen_param(uint8_t width, uint8_t heigh)
{
	screen_width = width;
	screen_heigh = heigh;
}

void ball_set_start_pasition(ball_t* ball, vec2i_t pos, vec2i_t vec)
{
	ball->ball_position = pos;
	ball->ball_vector = vec;	
}

void ball_set_radius(ball_t* ball, uint8_t rad)
{
	ball->ball_diameter = rad;
}

void ball_set_vector(ball_t* ball, vec2i_t vec)
{
	ball->ball_vector = vec;
}

void ball_refresh_vector(ball_t* ball, vec2i_t vec)
{
	ball->ball_vector.x += vec.x;
	ball->ball_vector.y += vec.y;
}

vec2i_t ball_get_coordinates(ball_t* ball)
{
	return ball->ball_position;
}

uint8_t ball_new_position(ball_t* ball, paddle_t* left_paddle, paddle_t* right_paddle)
{
	ball->last_position = ball->ball_position;
	ball->ball_position.x += ball->ball_vector.x;
	ball->ball_position.y += ball->ball_vector.y;
	
	if( (ball->ball_position.x <= 8) && 
		(ball->ball_position.y >  left_paddle->paddle_y_position - left_paddle->paddle_y_size/2) && 
		(ball->ball_position.y <  left_paddle->paddle_y_position + left_paddle->paddle_y_size/2))
	{
		ball->ball_position.x = 8;
		ball->ball_vector.x = -ball->ball_vector.x;
		ball->ball_vector.y += left_paddle->paddle_y_velocity;
		if(ball->ball_vector.y > 3) ball->ball_vector.y = 3;
		if(ball->ball_vector.y < -3) ball->ball_vector.y = -3;
	}
	else if(
		(ball->ball_position.x >= 88) &&
		(ball->ball_position.y >  right_paddle->paddle_y_position - right_paddle->paddle_y_size/2) &&
		(ball->ball_position.y <  right_paddle->paddle_y_position + right_paddle->paddle_y_size/2))
	{
		ball->ball_position.x = 88;
		ball->ball_vector.x = -ball->ball_vector.x;
		ball->ball_vector.y += right_paddle->paddle_y_velocity;
		if(ball->ball_vector.y > 3) ball->ball_vector.y = 3;
		if(ball->ball_vector.y < -3) ball->ball_vector.y = -3;
	}
	else if(ball->ball_position.x < 0)
	{
		ball->ball_position.x = 0;
		ball->ball_vector.x = -ball->ball_vector.x;
		return 1;
	}
	else if(ball->ball_position.x > screen_width - ball->ball_diameter)
	{
		ball->ball_position.x = screen_width - ball->ball_diameter;
		ball->ball_vector.x = -ball->ball_vector.x;
		return 2;
	}
	
	if(ball->ball_position.y < 0)
	{
		ball->ball_position.y = 0;
		ball->ball_vector.y = -ball->ball_vector.y;
	}
	else if(ball->ball_position.y > screen_heigh - ball->ball_diameter)
	{	
		ball->ball_position.y = screen_heigh - ball->ball_diameter;
		ball->ball_vector.y = -ball->ball_vector.y;
	}
	
	return 0;
}
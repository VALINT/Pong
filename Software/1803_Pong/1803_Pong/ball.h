/*
 * ball.h
 *
 * Created: 21.08.2021 18:39:14
 *  Author: VAL
 */ 


#ifndef BALL_H_
#define BALL_H_

#include <inttypes.h>
#include "vec2d.h"
#include "paddle.h"

typedef struct ball_t
{
	vec2i_t ball_position;
	vec2i_t last_position;
	vec2i_t ball_vector;
	int8_t  ball_diameter;
} ball_t;

void ball_set_screen_param(uint8_t, uint8_t);
void ball_set_start_pasition(ball_t*, vec2i_t, vec2i_t);
void ball_set_radius(ball_t*, uint8_t);
void ball_set_vector(ball_t*, vec2i_t);
void ball_refresh_vector(ball_t*, vec2i_t);
vec2i_t ball_get_coordinates(ball_t*);
uint8_t ball_new_position(ball_t*, paddle_t*, paddle_t*);

#endif /* BALL_H_ */
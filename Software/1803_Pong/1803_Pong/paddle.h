/*
 * paddle.h
 *
 * Created: 21.08.2021 16:57:08
 *  Author: VAL
 */ 


#ifndef paddle_H_
#define paddle_H_

#include <inttypes.h>

typedef struct paddle_t
{
	uint8_t paddle_y_size;
	uint8_t paddle_x_size;
	uint8_t paddle_x_position;
	uint8_t paddle_y_position;
	uint8_t paddle_y_prev_pos;
	 int8_t paddle_y_velocity;
	uint8_t paddle_low_pos;
	uint8_t paddle_high_pos;
	uint8_t paddle_step;
} paddle_t;

void set_screen_param(uint8_t, uint8_t);
void set_paddle_size(paddle_t*, uint8_t, uint8_t);
void count_new_position(paddle_t*, uint16_t);
uint8_t get_paddle_position(paddle_t*);
uint8_t get_paddle_velocity(paddle_t*);

#endif /* paddle_H_ */
#ifndef SIEMENSA55LCD_H_
#define SIEMENSA55LCD_H_

//#define F_CPU 8000000UL 
#include "Common.h"
#include <avr/pgmspace.h>


// In this case you can select microcontroller with you will work

#define DATA 1
#define COMMAND 0

#define RESET 2
#define D_C 0
#define SCE 1
#define LCD_PORT PORTD


void LCD_SCL();
void LCD_Init();
void LCD_Reset();
void LCD_print(uint8_t symbol);
void LCD_Sent_Byte(uint8_t byte,uint8_t status);
void LCD_Set_Cordinates(uint8_t YY,uint8_t XX);

#endif /* SIEMENSA55LCD_H_ */
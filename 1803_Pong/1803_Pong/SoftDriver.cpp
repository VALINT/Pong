/*
 * SoftDriver.c
 *
 * Created: 15.11.2016 17:27:31
 *  Author: VAL
 */ 
#include "Common.h"
#include "SoftDriver.h"


unsigned char Ball[4]=
{
	0x06,0x0f,0x0f,0x06
};

void Printer(unsigned char data,unsigned char coloum,unsigned char line)
{
	_delay_us(400);
	LCD_Set_Cordinates((coloum-1),((line - 1)*4));
	if(data == 0){
		for(int i = 0; i<4;i++)
		{
			LCD_Sent_Byte(0x00,1);
		}
	}
	
	if(data == 1){
		for(int i = 0; i<4;i++)
		{
			LCD_Sent_Byte(0x0f,1);
		}
	}
	
	
	if(data == 2){
		for(int i = 0; i<4;i++)
		{
			LCD_Sent_Byte(0xf0,1);
		}
	}
	
		if(data == 3){
			for(int i = 0; i<4;i++)
			{
				LCD_Sent_Byte(0xff,1);
			}
	}
}
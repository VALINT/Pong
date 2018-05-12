/*
 * PONG.c
 *
 * Created: 14.11.2016 8:55:14
 *  Author: VAL
 */ 

#include "Common.h"
#include "PONG.h"



unsigned char GameField[18][27] = 
{
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};

unsigned char GameCycle = 0,GameSpeed = 1,BallColomn,BallRow;
bool right,down;

void Start()
{
	BallColomn = 4;
	BallRow = 4;
	right = true;
	down = true;
}

void ScreenBuilder()
{
	uint8_t quadro = 0;
	for(char row = 0; row < 9; row++)
	{
		for(char col = 1; col < 26; col++)
		{
			quadro = 0;
			quadro = ((GameField[row * 2 + 2][col]) << 1) | (GameField[(row * 2) + 1][col]);
			Printer(quadro,row+1,col);
		}
	}
}

void BallLocation()
{
	GameField[BallRow][BallColomn] = 0;													//Last ball position are cleared
		
	
	if((GameField[BallRow-1][BallColomn]==1)|(GameField[BallRow+1][BallColomn]==1))		//
	down = !down;																		//
																						//
	if((GameField[BallRow][BallColomn-1]==2)|(GameField[BallRow][BallColomn+1]==2))		//
	right = !right;																		//
																						//
	if((GameField[BallRow][BallColomn-1]==1)|(GameField[BallRow][BallColomn+1]==1))		//
	right = !right;																		//
	
		if(right == true){
		BallColomn++;}
		if(right == false){
		BallColomn--;}
		if(down == true){
		BallRow++;}
		if(down == false){
		BallRow--;}
	
	GameField[BallRow][BallColomn] = 1;													//New boll position 
}

void PadLocation()
{
	static uint16_t FirstPadPosition,SecobdPadPosition;
	
	GameField[FirstPadPosition-2][2] = 0;
	GameField[FirstPadPosition-1][2] = 0;
	GameField[FirstPadPosition][2] = 0;
	GameField[FirstPadPosition+1][2] = 0;
	GameField[FirstPadPosition+2][2] = 0;
	
	GameField[SecobdPadPosition-2][24] = 0;
	GameField[SecobdPadPosition-1][24] = 0;
	GameField[SecobdPadPosition][24] = 0;
	GameField[SecobdPadPosition+1][24] = 0;
	GameField[SecobdPadPosition+2][24] = 0;
	
	FirstPadPosition = 2+((GetControlPosition(1))/75);
	SecobdPadPosition = 2+((GetControlPosition(2))/75);
	
	GameField[FirstPadPosition-2][2] = 1;
	GameField[FirstPadPosition-1][2] = 1;
	GameField[FirstPadPosition][2] = 1;
	GameField[FirstPadPosition+1][2] = 1;
	GameField[FirstPadPosition+2][2] = 1;
	
	GameField[SecobdPadPosition-2][24] = 1;
	GameField[SecobdPadPosition-1][24] = 1;
	GameField[SecobdPadPosition][24] = 1;
	GameField[SecobdPadPosition+1][24] = 1;
	GameField[SecobdPadPosition+2][24] = 1;
}


void GameInterrapt()
{
	/*GameCycle++;
	if(GameCycle > 2)
	{
		GameCycle = 0;
		BallLocation();
	}
	*/

	BallLocation();
	PadLocation();
	ScreenBuilder();
}
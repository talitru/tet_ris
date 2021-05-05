#pragma once

#include "Board.h"
#include "Figure.h"
#include "Bomb.h"
#include "Menu.h"
enum { ESC = 27 };//escape
enum { RAND = 8 };

class TheGame
{
	Menu menu;
	Board GameBoard;
public:
	TheGame() {}; //ctor
	void resetBoard()
	{
		GameBoard.initBoard();
	}
	general* createFigure(int numOfPlayer, int* serialNum);
	void RunGame();
	void clearKeyBoardBuffer()const;
	bool MoveFigure(Board& board, general& f, int serialNum, char direction); 
	
	bool WinCheck(int NumPlayer)const;
	void HideCursor();
	
};
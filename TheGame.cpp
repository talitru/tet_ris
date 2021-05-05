#include "TheGame.h"
#include <conio.h>
#include <iostream>
#include <Windows.h>
char LeftPlayerKeys[10] = { 'a','A','d','D','s','S','w','W','x','X' };
char RightPlayerKeys[10] = { 'j','J','l','L','k','K','i','I','m','M' };

void TheGame::RunGame()
{
	general* f1,*f2;
	char key_char = 0;
	int y1 = Y1;
	int y2 = Y2;
	int counter1 = 0, counter2 = 0;
	int serialNum1 = -1;
	int serialNum2 = -1;
	menu.printMenu();
	while (key_char != EXIT)
	{
		HideCursor();
		if (key_char == START || _kbhit())
		{
			if (key_char != START )
			{
				key_char = _getch();
			}
			if (key_char == INSTRUCTIO_KEYS)
			{
				menu.ShowInstructions();
			}
			else if (key_char == START)
			{
				
				f1 = createFigure(LEFT_PLAYER, &serialNum1);
				
			    f2 = createFigure(RIGHT_PLAYER, &serialNum2);

				

				while (key_char != EXIT && WinCheck(LEFT_PLAYER) == false && WinCheck(RIGHT_PLAYER) == false)
				{
					clearKeyBoardBuffer();

					f1->print(this->GameBoard);
					Sleep(100);


					f2->print(this->GameBoard);
					Sleep(100);


					++y1;
					++y2;

					if (_kbhit())
					{
						key_char = _getch();
						if (key_char == INSTRUCTIO_KEYS)
						{
							gotoxy(0, ROWS + 7);
							menu.ShowInstructions();
						}
						else if (key_char == ESC)
						{
							menu.ContinuePausedGame(key_char, this->GameBoard);
							menu.printMenu();
						}
						else
						{
							clearKeyBoardBuffer();
							for (int i = 0; i < 10; i++)
							{
								if (LeftPlayerKeys[i] == key_char)
								{
									if (MoveFigure(this->GameBoard, *f1, serialNum1, key_char) == false)
									{
										y1 = 1;
										GameBoard.DeleteRow(LEFT_PLAYER);
									}
									else
									{
										f1->print(this->GameBoard);
									}
									break;
								}
								if (RightPlayerKeys[i] == key_char)
								{
									if (MoveFigure(this->GameBoard, *f2, serialNum2, key_char) == false)
									{
										y2 = 1;
										GameBoard.DeleteRow(RIGHT_PLAYER);

									}
									else
									{
										f2->print(this->GameBoard);
									}
									break;

								}
							}
						}
					}
					clearKeyBoardBuffer();
					if (y1 > ROWS||f1->update(this->GameBoard, serialNum1, DOWN) == false )
					{
						y1 = 1;
						GameBoard.DeleteRow(LEFT_PLAYER);
						delete f1;
						f1 = createFigure(LEFT_PLAYER, &serialNum1);
					}

					if (y2 > ROWS || f2->update(this->GameBoard, serialNum2, DOWN) == false)
					{
						y2 = 1;
						GameBoard.DeleteRow(RIGHT_PLAYER);
						delete f2;
						f2 = createFigure(RIGHT_PLAYER, &serialNum2);
					}
				}

			}
			if (key_char == EXIT)
			{
				menu.ExitGame();
			}
			if (WinCheck(LEFT_PLAYER) == true || WinCheck(RIGHT_PLAYER) == true)
			{
				menu.StartNewGame(key_char, y1, y2, this->GameBoard);

			}
		}
	}



}


bool TheGame::MoveFigure(Board& board, general& f, int serialNum, char direction) // קוראת לפונקציות תזוזה לפי המקשים
{
	if (direction == 'A' || direction == 'a' || direction == 'j' || direction == 'J')
	{

		return f.update(board, serialNum, LEFT);

	}
	else if (direction == 'D' || direction == 'd' || direction == 'L' || direction == 'l')
	{
		return f.update(board, serialNum, RIGHT);
	}
	else if (direction == 'K' || direction == 'k' || direction == 'S' || direction == 's')
	{
		return f.update(board, serialNum, CLOCKWISE);
	}
	else if (direction == 'I' || direction == 'i' || direction == 'W' || direction == 'w')
	{
		return f.update(board, serialNum, COUNTERCLOCKWISE);
	}
	else //if(direction == ' ' || direction == 'X' || direction == 'x' || direction == 'M' || direction == 'm')
	{

		return f.update(board, serialNum, DOWN);
	}
}


general* TheGame::createFigure(int numOfPlayer, int* serialNum)
{
	general* generalFigure = nullptr;
	int randNum = rand() % RAND;
	switch (randNum)
	{
	case 0:
	{
		generalFigure = new Figure(LINE,numOfPlayer);
		*serialNum = LINE;

		break;

	}
	case 1:
	{
		generalFigure = new Figure(L, numOfPlayer);
		
		*serialNum = L;
		
		break;
	}
	case 2:
	{
		generalFigure = new Figure(RL, numOfPlayer);
		*serialNum = RL;
		
		break;
	}
	case 3:
	{
		generalFigure = new Figure(SQUARE, numOfPlayer);
		*serialNum = SQUARE;
		

		break;
	}
	case 4:
	{
		generalFigure = new Figure(RZ, numOfPlayer);
		*serialNum = RZ;
		

		break;
	}
	case 5:
	{
		generalFigure = new Figure(Z, numOfPlayer);
		*serialNum = Z;

		

		break;
	}
	case 6:
	{
		generalFigure = new Figure(PLUS, numOfPlayer);
		*serialNum = PLUS;
		
		break;
	}
	case 7:
	{
		generalFigure = new Bomb(numOfPlayer);
		*serialNum = BOMB;

		break;
	}
	
	default:
	{
		break;
		//return  generalFigure;
	}
	}
	return generalFigure;
}


void TheGame::clearKeyBoardBuffer()const
{
	char junk;
	while (_kbhit())
	{
		junk = _getch();
	}
}
bool TheGame::WinCheck(int NumPlayer)const
{
	bool IsLoser = false;
	if (NumPlayer == LEFT_PLAYER)
	{
		if (this->GameBoard.IsFull4(1, NumPlayer) == true)
			IsLoser = true;
		if (IsLoser == true)
		{
			gotoxy(4, 14);
			cout << "Player2 is the WINNER!";
		}
	}
	else
	{
		if (this->GameBoard.IsFull4(1, NumPlayer) == true)
			IsLoser = true;
		if (IsLoser == true)
		{
			gotoxy(4, 14);
			cout << "Player1 is the WINNER!";
		}
	}
	return IsLoser;
}
void TheGame::HideCursor()
{
	HANDLE myconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CURSOR;
	CURSOR.dwSize = 1;
	CURSOR.bVisible = FALSE;
	SetConsoleCursorInfo(myconsole, &CURSOR);

}


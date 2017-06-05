#include <QtWidgets>

#include "Window.h"
#include "AbstractSymbol.h"
#include "Circle.h"
#include "Cross.h"
#include "AbstractBoard.h"

#include "BoardSingle.h"

CBoardSingle::CBoardSingle(CWindow *window) : CAbstractBoard(window)
{
	randomSymbol();
	randomTurn();

	for(int x = 0; x < 3; x++) for(int y = 0; y < 3; y++)
		connect(&button[x][y], &QPushButton::clicked, [&, x, y]
		{
			makeMove(x, y, symbol_char_my, my_symbol);
			if(yallGotAnyMoreOfThemButtons())
				if(!win)
					makeComputerMove();
		});

	connect(&button_restart, &QPushButton::clicked, this, &CBoardSingle::handleRestart);

	label_turn.setText("Your symbol:");
}

void CBoardSingle::handleRestart()
{
	restartBoard();
	randomSymbol();
	randomTurn();
}

void CBoardSingle::randomSymbol()
{
	if(qrand() % 2)
	{
		my_symbol = &cross;
		computer_symbol = &circle;
		symbol_char_my = 'x';
		symbol_char_computer = 'o';
	}
	else
	{
		my_symbol = &circle;
		computer_symbol = &cross;
		symbol_char_my = 'o';
		symbol_char_computer = 'x';
	}

	label_current.setPixmap(my_symbol->getIcon().pixmap(size_current));
}

void CBoardSingle::randomTurn()
{
	if(qrand() % 2)
		makeComputerMove();
}

void CBoardSingle::gimmeFreeRoomHorizon(int &x, int &y, int &xx)
{
	x = xx;
	for(y = 0; y < 3; y++)
		if(button_str[x][y] == '0')
			break;
}

void CBoardSingle::gimmeFreeRoomVertical(int &x, int &y, int &yy)
{
	y = yy;
	for(x = 0; x < 3; x++)
		if(button_str[x][y] == '0')
			break;
}

void CBoardSingle::makeComputerMove()
{
	int xx = -1;
	int yy = -1;
	int y = 0;
	int x = 0;
	int count_my = 0;
	int count_comp = 0;
	int count_zero = 0;
	bool horizon = false;
	int computed = 0;
	smb[0] = symbol_char_computer;
	smb[1] = symbol_char_my;

	for(int i = 0; i < 2; i++)
	{
		if(button_str[0][0] == smb[i] && button_str[1][1] == smb[i])
		{
			if(button_str[2][2] == '0')
			{
				computed = 1;
				xx = 2;
				yy = 2;
				break;
			}
		}
		if(button_str[1][1] == smb[i] && button_str[2][2] == smb[i])
		{
			if(button_str[0][0] == '0')
			{
				computed = 1;
				xx = 0;
				yy = 0;
				break;
			}
		}
		if(button_str[0][0] == smb[i] && button_str[2][2] == smb[i])
		{
			if(button_str[1][1] == '0')
			{
				computed = 1;
				xx = 1;
				yy = 1;
				break;
			}
		}
		if(button_str[0][2] == smb[i] && button_str[2][0] == smb[i])
		{
			if(button_str[1][1] == '0')
			{
				computed = 1;
				xx = 1;
				yy = 1;
				break;
			}
		}
		if(button_str[1][1] == smb[i] && button_str[2][0] == smb[i])
		{
			if(button_str[0][2] == '0')
			{
				computed = 1;
				xx = 0;
				yy = 2;
				break;
			}
		}
		if(button_str[0][2] == smb[i] && button_str[1][1] == smb[i])
		{
			if(button_str[2][0] == '0')
			{
				computed = 1;
				xx = 2;
				yy = 0;
				break;
			}
		}
	}

	if(computed)
		qDebug("computed narrow: %d,%d", xx, yy);

	if(!computed)
	for(x = 0; x < 3; x++)
	{
		count_my = 0;
		count_comp = 0;
		count_zero = 0;
		for(y = 0; y < 3; y++)
		{
			if(button_str[x][y] == symbol_char_my)
				count_my++;
			else if(button_str[x][y] == symbol_char_computer)
				count_comp++;
			else
				count_zero++;
		}
		if(count_my == 0 && count_comp == 2 && count_zero == 1)
		{
			computed = 1;
			horizon = true;
			break;
		}
	}

	if(!computed)
	for(x = 0; x < 3; x++)
	{
		count_my = 0;
		count_comp = 0;
		count_zero = 0;
		for(y = 0; y < 3; y++)
		{
			if(button_str[x][y] == symbol_char_my)
				count_my++;
			else if(button_str[x][y] == symbol_char_computer)
				count_comp++;
			else
				count_zero++;
		}
		if(count_my == 2 && count_comp == 0 && count_zero == 1)
		{
			computed = 1;
			horizon = true;
			break;
		}
	}

	if(!computed)
	for(y = 0; y < 3; y++)
	{
		count_my = 0;
		count_comp = 0;
		count_zero = 0;
		for(x = 0; x < 3; x++)
		{
			if(button_str[x][y] == symbol_char_my)
				count_my++;
			else if(button_str[x][y] == symbol_char_computer)
				count_comp++;
			else
				count_zero++;
		}
		if(count_my == 0 && count_comp == 2 && count_zero == 1)
		{
			computed = 1;
			horizon = false;
			break;
		}

	}

	if(!computed)
	for(y = 0; y < 3; y++)
	{
		count_my = 0;
		count_comp = 0;
		count_zero = 0;
		for(x = 0; x < 3; x++)
		{
			if(button_str[x][y] == symbol_char_my)
				count_my++;
			else if(button_str[x][y] == symbol_char_computer)
				count_comp++;
			else
				count_zero++;
		}
		if(count_my == 2 && count_comp == 0 && count_zero == 1)
		{
			computed = 1;
			horizon = false;
			break;
		}
	}

	if(count_my == 0 && count_comp == 2 && count_zero == 1)
	{
		if(horizon)
			gimmeFreeRoomHorizon(xx, yy, x);
		else
			gimmeFreeRoomVertical(xx, yy, y);
		qDebug("computed to win: %d,%d", xx, yy);
	}
	else if(count_my == 2 && count_comp == 0 && count_zero == 1)
	{
		if(horizon)
			gimmeFreeRoomHorizon(xx, yy, x);
		else
			gimmeFreeRoomVertical(xx, yy, y);
		qDebug("computed to break: %d,%d", xx, yy);
	}
	else if(xx == -1 || yy == -1)
	while(button_str[xx][yy] != '0')
	{
		xx = qrand() % 3;
		yy = qrand() % 3;
		qDebug("randomized: %d,%d", xx, yy);
	}

	makeMove(xx, yy, symbol_char_computer, computer_symbol);
}

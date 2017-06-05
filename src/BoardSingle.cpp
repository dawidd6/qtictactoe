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
			if(!win) makeComputerMove();
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

void CBoardSingle::makeComputerMove()
{
	int x = qrand() % 3;
	int y = qrand() % 3;
	for(;;)
	{
		if(button_str[x][y] == '0')
			break;
		x = qrand() % 3;
		y = qrand() % 3;
	}

	makeMove(x, y, symbol_char_computer, computer_symbol);
}

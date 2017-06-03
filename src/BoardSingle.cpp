#include <QPushButton>
#include <QGridLayout>
#include <QPainter>
#include <QPicture>
#include <QLineF>
#include <QPixmap>
#include <QPointF>
#include <QIcon>
#include <QSize>
#include <QLabel>
#include <QAction>
#include <QMenuBar>
#include <QStackedLayout>
#include <QStatusBar>
#include <QDebug>
#include <QTime>

#include "Window.h"
#include "AbstractSymbol.h"
#include "Circle.h"
#include "Cross.h"
#include "AbstractBoard.h"

#include "BoardSingle.h"

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
	if(!(qrand() % 2))
		makeComputerMove();
}

bool CBoardSingle::yallGotAnyMoreOfThemButtons()
{
	for(int x = 0; x < 3; x++) for(int y = 0; y < 3; y++)
		if(button_str[x][y] == '0')
			return true;
	return false;
}

void CBoardSingle::makeComputerMove()
{
	int x = qrand() % 3;
	int y = qrand() % 3;

	if(yallGotAnyMoreOfThemButtons())
	while(button_str[x][y] != '0')
	{
		x = qrand() % 3;
		y = qrand() % 3;
	}
	markButtonIcon(x, y, symbol_char_computer, computer_symbol);
}

CBoardSingle::CBoardSingle(CWindow *window) : CAbstractBoard(window)
{
	qsrand(QTime::currentTime().msec());
	randomSymbol();
	randomTurn();

	for(int x = 0; x < 3; x++) for(int y = 0; y < 3; y++)
		connect(&button[x][y], &QPushButton::clicked, [&, x, y]
		{
			markButtonIcon(x, y, symbol_char_my, my_symbol);
			checkConditions();
			if(!win)
			{
				makeComputerMove();
				checkConditions();
			}
		});

	connect(&restart, &QPushButton::clicked, this, &CBoardSingle::handleRestart);

	label_turn.setText("Your symbol:");
}

void CBoardSingle::handleRestart()
{
	restartBoard();
	randomSymbol();
	randomTurn();
	win = 0;
}

void CBoardSingle::markButtonIcon(const int &x, const int &y, QChar s, const CAbstractSymbol *symbol)
{
	button[x][y].setDisabled(true);
	button[x][y].setIcon(symbol->getIcon());
	button[x][y].setIconSize(symbol->getSize());
	button_str[x][y] = s;
}

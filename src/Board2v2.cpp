#include <QtWidgets>

#include "Window.h"
#include "AbstractSymbol.h"
#include "Circle.h"
#include "Cross.h"
#include "AbstractBoard.h"

#include "Board2v2.h"

Board2v2::Board2v2(Window *window) : AbstractBoard(window)
{
	randomTurn();

	for(int x = 0; x < 3; x++) for(int y = 0; y < 3; y++)
		connect(&button[x][y], &QPushButton::clicked, [&, x, y]
		{
			if(xnow)
			{
				makeMove(x, y, 'x', &cross);
				label_current.setPixmap(circle.getIcon().pixmap(size_current));
				xnow = false;
			}
			else
			{
				makeMove(x, y, 'o', &circle);
				label_current.setPixmap(cross.getIcon().pixmap(size_current));
				xnow = true;
			}
		});

	connect(&button_restart, &QPushButton::clicked, this, &Board2v2::handleRestart);
}

void Board2v2::handleRestart()
{
	restartBoard();
	randomTurn();
}

void Board2v2::randomTurn()
{
	if((qrand() % 2))
	{
		xnow = true;
		label_current.setPixmap(cross.getIcon().pixmap(size_current));
	}
	else
	{
		xnow = false;
		label_current.setPixmap(circle.getIcon().pixmap(size_current));
	}
}

#include <QPushButton>
#include <QGridLayout>
#include <QPainter>
#include <QLineF>
#include <QPixmap>
#include <QPointF>
#include <QIcon>
#include <QSize>
#include <QLabel>
#include <QAction>
#include <QMenuBar>
#include <QStackedLayout>

#include "Window.h"
#include "AbstractSymbol.h"
#include "Circle.h"
#include "Cross.h"
#include "AbstractBoard.h"

#include "Board2v2.h"

CBoard2v2::CBoard2v2(CWindow *window) : CAbstractBoard(window)
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

	connect(&button_restart, &QPushButton::clicked, this, &CBoard2v2::handleRestart);
}

void CBoard2v2::handleRestart()
{
	restartBoard();
	randomTurn();
}

void CBoard2v2::randomTurn()
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

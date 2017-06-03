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

#include "Window.h"
#include "AbstractSymbol.h"
#include "Circle.h"
#include "Cross.h"
#include "AbstractBoard.h"

#include "Board2v2.h"

CBoard2v2::CBoard2v2(CWindow *window) : CAbstractBoard(window), xnow(true)
{
	for(int x = 0; x < 3; x++) for(int y = 0; y < 3; y++)
		connect(&button[x][y], &QPushButton::clicked, [&, x, y]
		{
			if(xnow)
			{
				markButtonIcon(x, y, 'x', cross, false);
				label_current.setPixmap(circle.getIcon().pixmap(size_current));
			}
			else
			{
				markButtonIcon(x, y, 'o', circle, true);
				label_current.setPixmap(cross.getIcon().pixmap(size_current));
			}

			checkConditions();
		});

	connect(&restart, &QPushButton::clicked, this, &CBoard2v2::handleRestart);
}

void CBoard2v2::handleRestart()
{
	restartBoard();
	xnow = true;
	label_current.setPixmap(cross.getIcon().pixmap(size_current));
}

void CBoard2v2::markButtonIcon(const int &x, const int &y, char s, const CAbstractSymbol &symbol, bool n)
{
	button[x][y].setDisabled(true);
	button[x][y].setIcon(symbol.getIcon());
	button[x][y].setIconSize(symbol.getSize());
	button_str[x][y] = s;
	xnow = n;
}

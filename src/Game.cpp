#include <QObject>
#include <QDateTime>
#include <QDebug>
#include <QPushButton>
#include <QGridLayout>
#include <QPainter>
#include <QPicture>
#include <QLineF>
#include <QPixmap>
#include <QPointF>
#include <QIcon>
#include <QSize>
#include <QLineEdit>
#include <QTcpSocket>
#include <QStatusBar>
#include <QLabel>
#include <QAction>
#include <QMenuBar>
#include <QStackedLayout>

#include "Window.h"
#include "AbstractSymbol.h"
#include "Circle.h"
#include "Cross.h"
#include "SetupConnection.h"
#include "AbstractBoard.h"
#include "Board2v2.h"
#include "BoardMulti.h"
#include "Menu.h"

#include "Game.h"

void CGame::logger(QString msg)
{
	qDebug
	(
		"[%s] %s",
		qPrintable(QDateTime().currentDateTime().toString("yyyy-MM-dd | hh:mm:ss")),
		qPrintable(msg)
	);
}

CGame::CGame()
{
	window = new CWindow(this);
	menu = new CMenu(window, this);
	board = nullptr;
}

CGame::~CGame()
{
	if(menu != nullptr) delete menu;
	if(board != nullptr) delete board;
	if(window != nullptr) delete window;
}

void CGame::handleReturn()
{
	if(menu == nullptr)
	{
		if(board != nullptr)
		{
			delete board;
			board = nullptr;
		}
		menu = new CMenu(window, this);
	}
}

void CGame::handlePlay2v2()
{
	if(menu != nullptr)
	{
		delete menu;
		menu = nullptr;
		board = new CBoard2v2(window);
	}
}

void CGame::handlePlayMulti()
{
	if(menu != nullptr)
	{
		delete menu;
		menu = nullptr;
		board = new CBoardMulti(window, this);
	}
}

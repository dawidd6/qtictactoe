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
#include "Symbols.h"
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

	board_2v2 = nullptr;
	board_multi = nullptr;
}

CGame::~CGame()
{
	if(menu != nullptr) delete menu;
	if(board_2v2 != nullptr) delete board_2v2;
	if(board_multi != nullptr) delete board_multi;
	if(window != nullptr) delete window;
}

void CGame::handleReturn()
{
	if(menu == nullptr)
	{
		if(board_2v2 != nullptr)
		{
			delete board_2v2;
			board_2v2 = nullptr;
		}
		if(board_multi != nullptr)
		{
			delete board_multi;
			board_multi = nullptr;
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
		board_2v2 = new CBoard2v2(window);
	}
}

void CGame::handlePlayMulti()
{
	if(menu != nullptr)
	{
		delete menu;
		menu = nullptr;
		board_multi = new CBoardMulti(window);
	}
}

#include <QtWidgets>
#include <QtNetwork>

#include "Window.h"
#include "AbstractSymbol.h"
#include "Circle.h"
#include "Cross.h"
#include "SetupConnection.h"
#include "AbstractBoard.h"
#include "Board2v2.h"
#include "BoardMulti.h"
#include "BoardSingle.h"
#include "Menu.h"

#include "Game.h"

void Game::logger(QString msg)
{
	qDebug
	(
		"[%s] %s",
		qPrintable(QDateTime().currentDateTime().toString("yyyy-MM-dd | hh:mm:ss")),
		qPrintable(msg)
	);
}

Game::Game()
{
	window = new Window(this);
	menu = new Menu(window, this);
	board = nullptr;
}

Game::~Game()
{
	if(menu != nullptr) delete menu;
	if(board != nullptr) delete board;
	if(window != nullptr) delete window;
}

void Game::handleReturn()
{
	if(menu == nullptr)
	{
		if(board != nullptr)
		{
			delete board;
			board = nullptr;
		}
		menu = new Menu(window, this);
	}
}

void Game::handlePlay2v2()
{
	if(menu != nullptr)
	{
		delete menu;
		menu = nullptr;
		board = new Board2v2(window);
	}
}

void Game::handlePlayMulti()
{
	if(menu != nullptr)
	{
		delete menu;
		menu = nullptr;
		board = new BoardMulti(window, this);
	}
}

void Game::handlePlaySingle()
{
	if(menu != nullptr)
	{
		delete menu;
		menu = nullptr;
		board = new BoardSingle(window);
	}
}

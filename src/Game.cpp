#include <QtWidgets>
#include <QtNetwork>

#include "Window.h"
#include "Board2v2.h"
#include "BoardMulti.h"
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

	board_2v2 = nullptr;
	board_multi = nullptr;
}

Game::~Game()
{
	if(menu != nullptr) delete menu;
	if(board_2v2 != nullptr) delete board_2v2;
	if(board_multi != nullptr) delete board_multi;
	if(window != nullptr) delete window;
}

void Game::handleReturn()
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
		menu = new Menu(window, this);
	}
}

void Game::handlePlay2v2()
{
	if(menu != nullptr)
	{
		delete menu;
		menu = nullptr;
		board_2v2 = new Board2v2(window);
	}
}

void Game::handlePlayMulti()
{
	if(menu != nullptr)
	{
		delete menu;
		menu = nullptr;
		board_multi = new BoardMulti(window);
	}
}

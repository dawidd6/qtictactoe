#include <QPushButton>
#include <QAction>

#include "Window.h"
#include "Board2v2.h"
#include "BoardMulti.h"
#include "Menu.h"
#include "Game.h"

Game::Game()
{
	window = new Window;
	menu = new Menu(window);

	board_2v2 = nullptr;
	board_multi = nullptr;

	menu->show();
	window->show();

	connect(&window->return_to_menu, SIGNAL(triggered()), this, SLOT(handleReturn()));
	connect(this, SIGNAL(signalReturn()), this, SLOT(handleRestore()));

	connect(&menu->play_2v2, SIGNAL(clicked()), this, SLOT(handlePlay2v2()));
	connect(&menu->play_multi, SIGNAL(clicked()), this, SLOT(handlePlayMulti()));
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
			board_2v2->hide();
			delete board_2v2;
			board_2v2 = nullptr;
		}
		if(board_multi != nullptr)
		{
			board_multi->hide();
			delete board_multi;
			board_multi = nullptr;
		}
		menu = new Menu(window);
		menu->show();
		emit signalReturn();
	}
}

void Game::handlePlay2v2()
{
	if(menu != nullptr)
	{
		menu->hide();
		delete menu;
		menu = nullptr;
		board_2v2 = new Board2v2(window);
		board_2v2->show();
	}
}

void Game::handlePlayMulti()
{
	if(menu != nullptr)
	{
		menu->hide();
		delete menu;
		menu = nullptr;
		board_multi = new BoardMulti(window);
		board_multi->show();
	}
}

void Game::handleRestore()
{
	connect(&menu->play_2v2, SIGNAL(clicked()), this, SLOT(handlePlay2v2()));
	connect(&menu->play_multi, SIGNAL(clicked()), this, SLOT(handlePlayMulti()));
}

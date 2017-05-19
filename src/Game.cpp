#include <QPushButton>
#include <QAction>

#include "Window.h"
#include "Board.h"
#include "Menu.h"
#include "Game.h"

Game::Game()
{
	window = new Window;
	menu = new Menu(window);

	menu->show();
	window->show();

	connect(&window->return_to_menu, SIGNAL(triggered()), this, SLOT(handleReturn()));
	connect(&menu->play_2v2, SIGNAL(clicked()), this, SLOT(handlePlay2v2()));
	connect(this, SIGNAL(signalReturn()), this, SLOT(handleRestore()));
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
		board->hide();
		delete board;
		board = nullptr;
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
		board = new Board(window);
		board->show();
	}
}

void Game::handleRestore()
{
	connect(&menu->play_2v2, SIGNAL(clicked()), this, SLOT(handlePlay2v2()));
}

#include <QPushButton>
#include <QGridLayout>
#include <QStackedLayout>
#include <QLabel>
#include <QMenuBar>
#include <QAction>
#include <QPainter>

#include "Window.h"
#include "Board.h"
#include "Menu.h"
#include "Game.h"

Game::Game()
{
	window = new Window;
	menu = new Menu(window);

	menu->run();
	window->show();

	hookUpButtonConnections();

	QObject::connect(&window->return_to_menu, &QAction::triggered, [&]
	{
		qDebug("return to menu");
		if(menu == nullptr)
		{
			vs->stop();
			delete vs;
			vs = nullptr;
			menu = new Menu(window);
			menu->run();
			hookUpButtonConnections();
		}
	});
}


Game::~Game()
{
	if(menu != nullptr) delete menu;
	if(vs != nullptr) delete vs;
	if(window != nullptr) delete window;
}

void Game::hookUpButtonConnections()
{
	QObject::connect(&menu->play_2v2, &QPushButton::clicked, [&]
	{
		qDebug("play 2v2");
		if(menu != nullptr)
		{
			menu->stop();
			delete menu;
			menu = nullptr;
			vs = new Board(window);
			vs->run();
		}
	});
}

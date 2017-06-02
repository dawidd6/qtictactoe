#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QAction>
#include <QMenuBar>
#include <QStackedLayout>

#include "Window.h"
#include "Game.h"

#include "Menu.h"

CMenu::CMenu(CWindow *window, CGame *game)
{
	window->layout.addWidget(this);
	window->adjustSize();

	play_single.setText("Play Singleplayer");
	play_2v2.setText("Play 2v2");
	play_multi.setText("Play Multiplayer");

	play_2v2.setFixedSize(300, 40);
	play_single.setFixedSize(300, 40);
	play_multi.setFixedSize(300, 40);

	setLayout(&layout);

	layout.setSpacing(50);

	layout.addWidget(&play_2v2);
	layout.addWidget(&play_single);
	layout.addWidget(&play_multi);

	connect(&play_2v2, &QPushButton::clicked, game, &CGame::handlePlay2v2);
	connect(&play_multi, &QPushButton::clicked, game, &CGame::handlePlayMulti);

	show();
}

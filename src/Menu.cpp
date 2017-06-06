#include <QtWidgets>

#include "Window.h"
#include "Game.h"

#include "Menu.h"

Menu::Menu(Window *window, Game *game)
{
	window->setCentralWidget(this);
	window->setReturnEnabled(false);

	play_single.setText("Play Singleplayer");
	play_2v2.setText("Play 2v2");
	play_multi.setText("Play Multiplayer");

	play_2v2.setFixedSize(300, 40);
	play_single.setFixedSize(300, 40);
	play_multi.setFixedSize(300, 40);

	setLayout(&layout);
	layout.setSpacing(20);
	layout.addWidget(&play_2v2);
	layout.addWidget(&play_single);
	layout.addWidget(&play_multi);

	connect(&play_2v2, &QPushButton::clicked, game, &Game::handlePlay2v2);
	connect(&play_multi, &QPushButton::clicked, game, &Game::handlePlayMulti);
	connect(&play_single, &QPushButton::clicked, game, &Game::handlePlaySingle);

	show();
	window->adjustSize();
}

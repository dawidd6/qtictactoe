#include "Window.h"
#include "Menu.h"
#include "Game.h"

Menu::Menu(Window *window, Game *game)
{
	window->layout.addWidget(this);

	play_single.setText("Play Singleplayer");
	play_2v2.setText("Play 2v2");
	play_multi.setText("Play Multiplayer");

	play_2v2.setFixedSize(305, 40);
	play_single.setFixedSize(305, 40);
	play_multi.setFixedSize(305, 40);

	setLayout(&layout);
	layout.setAlignment(Qt::AlignTop);
	layout.setSpacing(150);
	
	layout.addWidget(&play_2v2);
	layout.addWidget(&play_single);
	layout.addWidget(&play_multi);

	connect(&play_2v2, SIGNAL(clicked()), game, SLOT(handlePlay2v2()));
	connect(&play_multi, SIGNAL(clicked()), game, SLOT(handlePlayMulti()));
}

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

Menu::Menu(Window *window)
{
	window->layout.addWidget(&widget);

	play_single.setText("Play Singleplayer");
	play_2v2.setText("Play 2v2");
	play_multi.setText("Play Multiplayer");

	play_2v2.setFixedSize(305, 40);
	play_single.setFixedSize(305, 40);
	play_multi.setFixedSize(305, 40);

	widget.setLayout(&layout);
	layout.setAlignment(Qt::AlignTop);
	layout.setSpacing(150);
	
	layout.addWidget(&play_2v2);
	layout.addWidget(&play_single);
	layout.addWidget(&play_multi);
}

void Menu::run()
{
	widget.show();
}

void Menu::stop()
{
	widget.hide();
}

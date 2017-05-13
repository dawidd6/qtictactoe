#include <QApplication>
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

int main(int argc, char *argv[])
{
	/* VARIABLES */
	QApplication a(argc, argv);
	Game game;
	return a.exec();
}

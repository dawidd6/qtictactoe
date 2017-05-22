#include <QApplication>

#include "Game.h"

int main(int argc, char *argv[])
{
	/* VARIABLES */
	QApplication a(argc, argv);
	Game game;
	return a.exec();
}

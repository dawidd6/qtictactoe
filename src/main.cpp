#include <QApplication>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QMenuBar>
#include <QAction>
#include <QPainter>
#include <QPicture>

#include "Game.hpp"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Game game;
	game.show();
	return a.exec();
}

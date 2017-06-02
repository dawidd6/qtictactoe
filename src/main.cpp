#include <QApplication>

#include "Game.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	CGame game;
	return a.exec();
}

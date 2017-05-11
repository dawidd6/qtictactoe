#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QAbstractButton>
#include <QGridLayout>
#include <QString>
#include <QLabel>
#include <QFont>
#include <QMenuBar>
#include <QAction>
#include <QRect>
#include <QPainter>
#include <QPicture>

#include "Game.hpp"

int main(int argc, char *argv[])
{
	QApplication *a = new QApplication(argc, argv);
	Game game;
	return a->exec();
}

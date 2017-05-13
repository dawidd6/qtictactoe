#include <QApplication>
#include <QPushButton>
#include <QGridLayout>
#include <QStackedLayout>
#include <QLabel>
#include <QMenuBar>
#include <QAction>
#include <QPainter>
#include <QPicture>
#include <QMessageBox>

#include "Board.h"
#include "Window.h"

Window::Window()
{
	setWindowTitle("QTicTacToe");
	setWindowFlags(Qt::Window);
	setFixedSize(0, 0);
	setLayout(&layout);
	layout.setMenuBar(&menubar);
}

#include <QPushButton>
#include <QStackedLayout>
#include <QMenuBar>
#include <QAction>
#include <QMessageBox>

#include "Window.h"
#include "Board.h"
#include "Menu.h"

Window::Window() : about("About", &menu), return_to_menu("Return to menu", &menu)
{
	setWindowTitle("QTicTacToe");
	setWindowFlags(Qt::Window);
	setFixedSize(0, 0);
	setLayout(&layout);
	move(300, 200);

	menu.setTitle("Menu");
	layout.setMenuBar(&menubar);
	menubar.addMenu(&menu);

	menu.addAction(&return_to_menu);
	menu.addAction(&about);

	connect(&about, SIGNAL(triggered()), this, SLOT(handleAbout()));
}

void Window::handleAbout()
{
	QMessageBox::about(this, "About", "QTicTacToe");
}

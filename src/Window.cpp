#include "Window.h"
#include "Menu.h"
#include "Game.h"

Window::Window(Game *game) : about("About", &menu), return_to_menu("Return to menu", &menu)
{
	setWindowTitle("QTicTacToe");
	setWindowFlags(Qt::Window);
	/*
	 * something fucky here
	 * after invoking adjustSize on window
	 * it's doing what it's supposed to
	 * but also hides menubar
	 * temporary disabling fixedsize of window
	 */
	//setFixedSize(0, 0);
	setLayout(&layout);
	move(300, 200);

	menu.setTitle("Menu");
	layout.setMenuBar(&menubar);
	menubar.addMenu(&menu);

	menu.addAction(&return_to_menu);
	menu.addAction(&about);

	connect(&about, SIGNAL(triggered()), this, SLOT(handleAbout()));
	connect(&return_to_menu, SIGNAL(triggered()), game, SLOT(handleReturn()));

	show();
}

void Window::handleAbout()
{
	QMessageBox::about(this, "About", "QTicTacToe");
}

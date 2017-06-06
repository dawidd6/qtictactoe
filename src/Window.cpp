#include <QtWidgets>

#include "Game.h"

#include "Window.h"

Window::Window(Game *game) : about("About", &menu), return_to_menu("Return to menu", &menu)
{
	setWindowTitle("QTicTacToe");
	move(500, 300);
	setFixedSize(0, 0);
	setAnimated(true);

	menu.setTitle("Menu");
	setMenuBar(&menubar);
	menubar.addMenu(&menu);

	menu.addAction(&return_to_menu);
	menu.addAction(&about);

	connect(&about, &QAction::triggered, this, &Window::handleAbout);
	connect(&return_to_menu, &QAction::triggered, game, &Game::handleReturn);

	show();
}

void Window::handleAbout()
{
	QMessageBox::about(this, "About", "QTicTacToe");
}

void Window::setReturnEnabled(bool enable)
{
	return_to_menu.setEnabled(enable);
}

#include <QtWidgets>

#include "Game.h"

#include "Window.h"

CWindow::CWindow(CGame *game) : about("About", &menu), return_to_menu("Return to menu", &menu)
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

	connect(&about, &QAction::triggered, this, &CWindow::handleAbout);
	connect(&return_to_menu, &QAction::triggered, game, &CGame::handleReturn);

	show();
}

void CWindow::handleAbout()
{
	QMessageBox::about(this, "About", "QTicTacToe");
}

void CWindow::setReturnEnabled(bool enable)
{
	return_to_menu.setEnabled(enable);
}

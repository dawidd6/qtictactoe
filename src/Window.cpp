#include <QWidget>
#include <QAction>
#include <QMenuBar>
#include <QMenu>
#include <QMessageBox>
#include <QStackedLayout>
#include <QTest>

#include "Game.h"

#include "Window.h"

CWindow::CWindow(CGame *game) : about("About", &menu), return_to_menu("Return to menu", &menu)
{
	setWindowTitle("QTicTacToe");
	setWindowFlags(Qt::Window);
	setLayout(&layout);
	move(500, 300);

	menu.setTitle("Menu");
	layout.setMenuBar(&menu);
	//menubar.addMenu(&menu);

	menu.addAction(&return_to_menu);
	//menu.addAction(&about);

	connect(&about, &QAction::triggered, this, &CWindow::handleAbout);
	connect(&return_to_menu, &QAction::triggered, game, &CGame::handleReturn);

	show();
}

void CWindow::handleAbout()
{
	QMessageBox::about(this, "About", "QTicTacToe");
}

void CWindow::addToLayout(QWidget *child)
{
	setReturnEnabled(true);
	layout.addWidget(child);
	adjustSize();
}

void CWindow::removeFromLayout(QWidget *child)
{
	layout.removeWidget(child);
}

void CWindow::setReturnEnabled(bool enable)
{
	return_to_menu.setEnabled(enable);
}

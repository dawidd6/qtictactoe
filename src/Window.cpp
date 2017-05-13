#include <QPushButton>
#include <QGridLayout>
#include <QStackedLayout>
#include <QLabel>
#include <QMenuBar>
#include <QAction>
#include <QPainter>
#include <QPicture>
#include <QMessageBox>

#include "Window.h"
#include "Board.h"
#include "Menu.h"

Window::Window() : about("About", &help), return_to_menu("Return to menu", &game)
{
	setWindowTitle("QTicTacToe");
	setWindowFlags(Qt::Window);
	setFixedSize(0, 0);
	setLayout(&layout);
	move(300, 200);

	help.setTitle("Help");
	game.setTitle("Game");
	layout.setMenuBar(&menubar);
	menubar.addMenu(&help);
	menubar.addMenu(&game);

	help.addAction(&about);
	game.addAction(&return_to_menu);

	QObject::connect(&about, &QAction::triggered, [&]
	{
		QMessageBox::about(this, "About", "QTicTacToe");
	});
}

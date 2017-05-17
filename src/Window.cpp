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

	QObject::connect(&about, &QAction::triggered, [&]
	{
		QMessageBox::about(this, "About", "QTicTacToe");
	});
}

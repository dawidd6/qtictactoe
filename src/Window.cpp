#include <QApplication>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QMenuBar>
#include <QAction>
#include <QPainter>
#include <QPicture>
#include <QMessageBox>

#include "Window.hpp"

Window::Window() : entry("Help"), action("About", &entry)
{
	//window.setWindowIcon(QIcon(":/data/icon.svg"));
	window.setWindowTitle("QTicTacToe");
	window.setWindowFlags(Qt::Window);
	window.setFixedSize(0, 0);
	window.setLayout(&grid);

	grid.setMenuBar(&menu);
	menu.addMenu(&entry);
	entry.addAction(&action);

	QObject::connect(&action, &QAction::triggered, [&]
	{
		qDebug("action");
		QMessageBox::about(&window, "About", "QTicTacToe");
	});
}

void Window::show()
{
	window.show();
}

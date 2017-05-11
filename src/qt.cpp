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

void markDisabledAll(QPushButton buttons[])
{
	for(int i = 0; i < 9; i++)
		buttons[i].setDisabled(true);
}

namespace tictac
{
	class Window
	{

	};

	class Board
	{

	};

	class Circle
	{

	};

	class Cross
	{

	};

	class MenuBar
	{

	};

	class Game
	{

	};
}

int main(int argc, char *argv[])
{
	/* IMPORTANT */
	//order of variables DO matter
	QApplication a(argc, argv);
	QMainWindow mainwindow;
	QWidget window;

	QMenuBar menu_bar;
	QMenu menu_options("Options");

	QAction action_language("Language", &menu_options);

	QGridLayout grid;

	QPushButton button[9];
	char button_str[9];

	QFrame line[4];

	QPushButton restart("Restart");

	QIcon x_icon("data/x.svg");
	QSize x_size(96, 96);

	QIcon o_icon("data/o.svg");
	QSize o_size(96, 96);

	QLabel turn("Whose Turn:");
	QLabel current_icon;
	QSize current_size(30, 30);

	QPicture left_pi;
	QPicture right_pi;
	QPicture horizon_pi;
	QPicture vertical_pi;

	QLineF right_angle;
	QLineF left_angle;
	QLineF horizon_angle;
	QLineF vertical_angle;
	
	QLabel left_line;
	QLabel right_line;
	QLabel horizon_line;
	QLabel vertical_line;
	
	QPainter right_painter(&right_pi);
	QPainter left_painter(&left_pi);
	QPainter horizon_painter(&horizon_pi);
	QPainter vertical_painter(&vertical_pi);

	left_painter.setPen(QPen(Qt::black, 8));
	left_painter.setRenderHint(QPainter::Antialiasing);
	right_painter.setPen(QPen(Qt::black, 8));
	right_painter.setRenderHint(QPainter::Antialiasing);
	horizon_painter.setPen(QPen(Qt::black, 8));
	horizon_painter.setRenderHint(QPainter::Antialiasing);
	vertical_painter.setPen(QPen(Qt::black, 8));
	vertical_painter.setRenderHint(QPainter::Antialiasing);

	right_angle.setP1(QPointF(0, 100));
	right_angle.setAngle(-45);
	right_angle.setLength(420);
	left_angle.setP1(QPointF(0, 100));
	left_angle.setAngle(45);
	left_angle.setLength(420);
	horizon_angle.setP1(QPointF(0, 100));
	horizon_angle.setAngle(0);
	horizon_angle.setLength(298);
	vertical_angle.setP1(QPointF(100, 1));
	vertical_angle.setAngle(90);
	vertical_angle.setLength(298);

	right_painter.drawLine(right_angle);
	left_painter.drawLine(left_angle);
	horizon_painter.drawLine(horizon_angle);
	vertical_painter.drawLine(vertical_angle);
	right_painter.end();
	left_painter.end();
	horizon_painter.end();
	vertical_painter.end();

	left_line.setPicture(left_pi);
	right_line.setPicture(right_pi);
	horizon_line.setPicture(horizon_pi);
	vertical_line.setPicture(vertical_pi);

	int rows = 0;
	int columns = 0;
	bool xnow = true;
	char win = 'n';

	mainwindow.setCentralWidget(&window);
	mainwindow.setWindowIcon(QIcon("data/icon.svg"));
	window.setLayout(&grid);
	window.setWindowTitle("QTicTacToe");
	window.setWindowFlags(Qt::Window);
	window.setFixedSize(0, 0);
	grid.setSpacing(0);
	current_icon.setPixmap(x_icon.pixmap(current_size));

	menu_options.addAction(&action_language);

	grid.setMenuBar(&menu_bar);
	menu_bar.addMenu(&menu_options);

	QObject::connect(&action_language, &QAction::triggered, []
	{
		qDebug("language");
	});

	QObject::connect(&restart, &QPushButton::clicked,
	[&button, &button_str, &xnow, &win, &current_icon, &x_icon, &current_size, &grid, &left_line, &right_line, &horizon_line, &vertical_line]
	{
		xnow = true;
		win = 'n';
		current_icon.setPixmap(x_icon.pixmap(current_size));
		for(int i = 0; i < 9; i++)
		{
			button_str[i] = '0';
			button[i].setEnabled(true);
			button[i].setIcon(QIcon());
		}
		grid.removeWidget(&left_line);
		grid.removeWidget(&right_line);
		grid.removeWidget(&horizon_line);
		grid.removeWidget(&vertical_line);
		left_line.hide();
		right_line.hide();
		horizon_line.hide();
		vertical_line.hide();
	});


	line[0].setFrameShape(QFrame::HLine);
	line[1].setFrameShape(QFrame::HLine);
	line[2].setFrameShape(QFrame::VLine);
	line[3].setFrameShape(QFrame::VLine);
	line[0].setLineWidth(2);
	line[1].setLineWidth(2);
	line[2].setLineWidth(2);
	line[3].setLineWidth(2);
	grid.addWidget(&line[0], 1, 0, 1, 5);
	grid.addWidget(&line[1], 3, 0, 1, 5);
	grid.addWidget(&line[2], 0, 1, 5, 1);
	grid.addWidget(&line[3], 0, 3, 5, 1);

	for(int i = 0; i < 9; i++)
	{
		if(columns == 5)
		{
			rows++;
			columns = 0;
		}

		if(rows == 1 || rows == 3)
			rows++;
		if(columns == 1 || columns == 3)
			columns++;

		button[i].setFixedSize(100, 100);
		button[i].setFlat(true);
		button[i].setFocusPolicy(Qt::NoFocus);

		QObject::connect(&button[i], &QPushButton::clicked,
		[&grid, &button, &button_str, i, &xnow, &o_icon, &o_size, &x_icon, &x_size, &current_icon, &current_size, &right_line, &left_line, &horizon_line, &vertical_line]
		{
			if(xnow)
			{
				button[i].setIcon(x_icon);
				button[i].setIconSize(x_size);
				button_str[i] = 'x';
				current_icon.setPixmap(o_icon.pixmap(current_size));
				xnow = false;
			}
			else
			{
				button[i].setIcon(o_icon);
				button[i].setIconSize(o_size);
				button_str[i] = 'o';
				current_icon.setPixmap(x_icon.pixmap(current_size));
				xnow = true;
			}
			button[i].setDisabled(true);

			//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
			if(button_str[0] == 'x' && button_str[1] == 'x' && button_str[2] == 'x')
			{
				grid.addWidget(&horizon_line, 0, 0, 1, 5, Qt::AlignJustify);
				horizon_line.show();
				markDisabledAll(button);
			}
			else if(button_str[3] == 'x' && button_str[4] == 'x' && button_str[5] == 'x')
			{
				grid.addWidget(&horizon_line, 2, 0, 1, 5, Qt::AlignJustify);
				horizon_line.show();
				markDisabledAll(button);
			}
			else if(button_str[6] == 'x' && button_str[7] == 'x' && button_str[8] == 'x')
			{
				grid.addWidget(&horizon_line, 4, 0, 1, 5, Qt::AlignJustify);
				horizon_line.show();
				markDisabledAll(button);
			}
			else if(button_str[0] == 'x' && button_str[3] == 'x' && button_str[6] == 'x')
			{
				grid.addWidget(&vertical_line, 0, 0, 5, 1, Qt::AlignJustify);
				vertical_line.show();
				markDisabledAll(button);
			}
			else if(button_str[1] == 'x' && button_str[4] == 'x' && button_str[7] == 'x')
			{
				grid.addWidget(&vertical_line, 0, 2, 5, 1, Qt::AlignJustify);
				vertical_line.show();
				markDisabledAll(button);
			}
			else if(button_str[2] == 'x' && button_str[5] == 'x' && button_str[8] == 'x')
			{
				grid.addWidget(&vertical_line, 0, 4, 5, 1, Qt::AlignJustify);
				vertical_line.show();
				markDisabledAll(button);
			}
			else if(button_str[0] == 'x' && button_str[4] == 'x' && button_str[8] == 'x')
			{
				grid.addWidget(&right_line, 0, 0, 5, 5, Qt::AlignJustify);
				right_line.show();
				markDisabledAll(button);
			}
			else if(button_str[2] == 'x' && button_str[4] == 'x' && button_str[6] == 'x')
			{
				grid.addWidget(&left_line, 0, 0, 5, 5, Qt::AlignJustify);
				left_line.show();
				markDisabledAll(button);
			}
			// OOOOOOOOOOOOOOOOOOOOOOOOOOO
			if(button_str[0] == 'o' && button_str[1] == 'o' && button_str[2] == 'o')
			{
				grid.addWidget(&horizon_line, 0, 0, 1, 5, Qt::AlignJustify);
				horizon_line.show();
				markDisabledAll(button);
			}
			else if(button_str[3] == 'o' && button_str[4] == 'o' && button_str[5] == 'o')
			{
				grid.addWidget(&horizon_line, 2, 0, 1, 5, Qt::AlignJustify);
				horizon_line.show();
				markDisabledAll(button);
			}
			else if(button_str[6] == 'o' && button_str[7] == 'o' && button_str[8] == 'o')
			{
				grid.addWidget(&horizon_line, 4, 0, 1, 5, Qt::AlignJustify);
				horizon_line.show();
				markDisabledAll(button);
			}
			else if(button_str[0] == 'o' && button_str[3] == 'o' && button_str[6] == 'o')
			{
				grid.addWidget(&vertical_line, 0, 0, 5, 1, Qt::AlignJustify);
				vertical_line.show();
				markDisabledAll(button);
			}
			else if(button_str[1] == 'o' && button_str[4] == 'o' && button_str[7] == 'o')
			{
				grid.addWidget(&vertical_line, 0, 2, 5, 1, Qt::AlignJustify);
				vertical_line.show();
				markDisabledAll(button);
			}
			else if(button_str[2] == 'o' && button_str[5] == 'o' && button_str[8] == 'o')
			{
				grid.addWidget(&vertical_line, 0, 4, 5, 1, Qt::AlignJustify);
				vertical_line.show();
				markDisabledAll(button);
			}
			else if(button_str[0] == 'o' && button_str[4] == 'o' && button_str[8] == 'o')
			{
				grid.addWidget(&right_line, 0, 0, 5, 5, Qt::AlignJustify);
				right_line.show();
				markDisabledAll(button);
			}
			else if(button_str[2] == 'o' && button_str[4] == 'o' && button_str[6] == 'o')
			{
				grid.addWidget(&left_line, 0, 0, 5, 5, Qt::AlignJustify);
				left_line.show();
				markDisabledAll(button);
			}

		});
		grid.addWidget(&button[i], rows, columns);
		columns++;
	}

	grid.setRowMinimumHeight(5, 50);
	grid.addWidget(&turn, 6, 0);
	grid.addWidget(&current_icon, 6, 2);
	grid.addWidget(&restart, 6, 4, Qt::AlignRight);
	window.show();
	return a.exec();
}

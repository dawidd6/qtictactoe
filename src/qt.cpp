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
	QFrame line_win[4];

	QPushButton restart("Restart");

	QIcon x_icon("data/x/x.svg");
	QIcon x_icon_horizon("data/x/x_horizon.svg");
	QIcon x_icon_vertical("data/x/x_vertical.svg");
	QIcon x_icon_slash_right("data/x/x_slash_right.svg");
	QIcon x_icon_slash_left("data/x/x_slash_left.svg");
	QSize x_size(96, 96);

	QIcon o_icon("data/o/o.svg");
	QIcon o_icon_horizon("data/o/o_horizon.svg");
	QIcon o_icon_vertical("data/o/o_vertical.svg");
	QIcon o_icon_slash_right("data/o/o_slash_right.svg");
	QIcon o_icon_slash_left("data/o/o_slash_left.svg");
	QSize o_size(96, 96);

	QLabel turn("Whose Turn:");
	QLabel current_icon;
	QSize current_size(30, 30);

	//hline.setFrameShape(QFrame::HLine);
	//vline.setFrameShape(QFrame::HLine);
	//hline.setFrameShadow(QFrame::Sunken);
	//vline.setFrameShadow(QFrame::Sunken);

	QPicture pi;
	QPainter painter(&pi);
	painter.setPen(QPen(Qt::black, 2));
	painter.setRenderHint(QPainter::Antialiasing);
	QLineF li(10.0, 80.0, 90.0, 20.0);
	QLineF angleline;
	angleline.setP1(QPointF(80,80));
	angleline.setAngle(45);
	angleline.setLength(50);
	painter.drawLine(angleline);
	painter.end();
	turn.setPicture(pi);

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

	QObject::connect(&restart, &QPushButton::clicked, [&button, &button_str, &xnow, &win, &current_icon, &x_icon, &current_size, &line_win, &grid]
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
		for(int i = 0; i < 4; i++)
		{
			grid.removeWidget(&line_win[i]);
			line_win[i].hide();
		}
	});


	line[0].setFrameShape(QFrame::HLine);
	line[1].setFrameShape(QFrame::HLine);
	line[2].setFrameShape(QFrame::VLine);
	line[3].setFrameShape(QFrame::VLine);
	line[0].setLineWidth(3);
	line[1].setLineWidth(3);
	line[2].setLineWidth(3);
	line[3].setLineWidth(3);
	grid.addWidget(&line[0], 1, 0, 1, 5);
	grid.addWidget(&line[1], 3, 0, 1, 5);
	grid.addWidget(&line[2], 0, 1, 5, 1);
	grid.addWidget(&line[3], 0, 3, 5, 1);

	line_win[0].setFrameShape(QFrame::HLine);
	line_win[1].setFrameShape(QFrame::VLine);
	line_win[0].setFixedHeight(20);
	line_win[0].setLineWidth(20);
	line_win[1].setFixedWidth(20);
	line_win[1].setLineWidth(20);

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
		[&grid, &line_win, &button, &button_str, i, &xnow, &o_icon, &o_size, &x_icon, &x_size, &current_icon, &current_size,
		&x_icon_horizon, &x_icon_vertical, &x_icon_slash_right, &x_icon_slash_left,
		&o_icon_horizon, &o_icon_vertical, &o_icon_slash_right, &o_icon_slash_left]
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
				/*button[0].setIcon(x_icon_horizon);
				button[1].setIcon(x_icon_horizon);
				button[2].setIcon(x_icon_horizon);
				button[0].setIconSize(x_size);
				button[1].setIconSize(x_size);
				button[2].setIconSize(x_size);*/
				markDisabledAll(button);
				grid.addWidget(&line_win[0], 0, 0, 1, 5);
				line_win[0].show();
			}
			else if(button_str[3] == 'x' && button_str[4] == 'x' && button_str[5] == 'x')
			{
				/*button[3].setIcon(x_icon_horizon);
				button[4].setIcon(x_icon_horizon);
				button[5].setIcon(x_icon_horizon);
				button[3].setIconSize(x_size);
				button[4].setIconSize(x_size);
				button[5].setIconSize(x_size);*/
				markDisabledAll(button);
				grid.addWidget(&line_win[0], 2, 0, 1, 5);
				line_win[0].show();
			}
			else if(button_str[6] == 'x' && button_str[7] == 'x' && button_str[8] == 'x')
			{
				button[6].setIcon(x_icon_horizon);
				button[7].setIcon(x_icon_horizon);
				button[8].setIcon(x_icon_horizon);
				button[6].setIconSize(x_size);
				button[7].setIconSize(x_size);
				button[8].setIconSize(x_size);
				markDisabledAll(button);
			}
			else if(button_str[0] == 'x' && button_str[3] == 'x' && button_str[6] == 'x')
			{
				markDisabledAll(button);
				grid.addWidget(&line_win[1], 0, 0, 5, 1, Qt::AlignJustify);
				line_win[1].show();
			}
			else if(button_str[1] == 'x' && button_str[4] == 'x' && button_str[7] == 'x')
			{
				button[1].setIcon(x_icon_vertical);
				button[4].setIcon(x_icon_vertical);
				button[7].setIcon(x_icon_vertical);
				button[1].setIconSize(x_size);
				button[4].setIconSize(x_size);
				button[7].setIconSize(x_size);
				markDisabledAll(button);
			}
			else if(button_str[2] == 'x' && button_str[5] == 'x' && button_str[8] == 'x')
			{
				button[2].setIcon(x_icon_vertical);
				button[5].setIcon(x_icon_vertical);
				button[8].setIcon(x_icon_vertical);
				button[2].setIconSize(x_size);
				button[5].setIconSize(x_size);
				button[8].setIconSize(x_size);
				markDisabledAll(button);
			}
			else if(button_str[0] == 'x' && button_str[4] == 'x' && button_str[8] == 'x')
			{
				button[0].setIcon(x_icon_slash_left);
				button[4].setIcon(x_icon_slash_left);
				button[8].setIcon(x_icon_slash_left);
				button[0].setIconSize(x_size);
				button[4].setIconSize(x_size);
				button[8].setIconSize(x_size);
				markDisabledAll(button);
			}
			else if(button_str[2] == 'x' && button_str[4] == 'x' && button_str[6] == 'x')
			{
				button[2].setIcon(x_icon_slash_right);
				button[4].setIcon(x_icon_slash_right);
				button[6].setIcon(x_icon_slash_right);
				button[2].setIconSize(x_size);
				button[4].setIconSize(x_size);
				button[6].setIconSize(x_size);
				markDisabledAll(button);
			}
			// OOOOOOOOOOOOOOOOOOOOOOOOOOO
			if(button_str[0] == 'o' && button_str[1] == 'o' && button_str[2] == 'o')
			{
				button[0].setIcon(o_icon_horizon);
				button[1].setIcon(o_icon_horizon);
				button[2].setIcon(o_icon_horizon);
				button[0].setIconSize(o_size);
				button[1].setIconSize(o_size);
				button[2].setIconSize(o_size);
				markDisabledAll(button);
			}
			else if(button_str[3] == 'o' && button_str[4] == 'o' && button_str[5] == 'o')
			{
				button[3].setIcon(o_icon_horizon);
				button[4].setIcon(o_icon_horizon);
				button[5].setIcon(o_icon_horizon);
				button[3].setIconSize(o_size);
				button[4].setIconSize(o_size);
				button[5].setIconSize(o_size);
				markDisabledAll(button);
			}
			else if(button_str[6] == 'o' && button_str[7] == 'o' && button_str[8] == 'o')
			{
				button[6].setIcon(o_icon_horizon);
				button[7].setIcon(o_icon_horizon);
				button[8].setIcon(o_icon_horizon);
				button[6].setIconSize(o_size);
				button[7].setIconSize(o_size);
				button[8].setIconSize(o_size);
				markDisabledAll(button);
			}
			else if(button_str[0] == 'o' && button_str[3] == 'o' && button_str[6] == 'o')
			{
				button[0].setIcon(o_icon_vertical);
				button[3].setIcon(o_icon_vertical);
				button[6].setIcon(o_icon_vertical);
				button[0].setIconSize(o_size);
				button[3].setIconSize(o_size);
				button[6].setIconSize(o_size);
				markDisabledAll(button);
			}
			else if(button_str[1] == 'o' && button_str[4] == 'o' && button_str[7] == 'o')
			{
				button[1].setIcon(o_icon_vertical);
				button[4].setIcon(o_icon_vertical);
				button[7].setIcon(o_icon_vertical);
				button[1].setIconSize(o_size);
				button[4].setIconSize(o_size);
				button[7].setIconSize(o_size);
				markDisabledAll(button);
			}
			else if(button_str[2] == 'o' && button_str[5] == 'o' && button_str[8] == 'o')
			{
				button[2].setIcon(o_icon_vertical);
				button[5].setIcon(o_icon_vertical);
				button[8].setIcon(o_icon_vertical);
				button[2].setIconSize(o_size);
				button[5].setIconSize(o_size);
				button[8].setIconSize(o_size);
				markDisabledAll(button);
			}
			else if(button_str[0] == 'o' && button_str[4] == 'o' && button_str[8] == 'o')
			{
				button[0].setIcon(o_icon_slash_left);
				button[4].setIcon(o_icon_slash_left);
				button[8].setIcon(o_icon_slash_left);
				button[0].setIconSize(o_size);
				button[4].setIconSize(o_size);
				button[8].setIconSize(o_size);
				markDisabledAll(button);
			}
			else if(button_str[2] == 'o' && button_str[4] == 'o' && button_str[6] == 'o')
			{
				button[2].setIcon(o_icon_slash_right);
				button[4].setIcon(o_icon_slash_right);
				button[6].setIcon(o_icon_slash_right);
				button[2].setIconSize(o_size);
				button[4].setIconSize(o_size);
				button[6].setIconSize(o_size);
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

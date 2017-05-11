#include <QApplication>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QMenuBar>
#include <QAction>
#include <QPainter>
#include <QPicture>

#include "Game.hpp"

void Game::markDisabledAll()
{
	for(int i = 0; i < 9; i++)
		button[i].setDisabled(true);
}

void Game::paintLine(QLabel &label, int angle, int len, QPointF point)
{
	QPicture pic;
	QLineF angleline;
	QPainter painter(&pic);

	painter.setPen(QPen(Qt::black, 8));
	painter.setRenderHint(QPainter::Antialiasing);

	angleline.setP1(point);
	angleline.setAngle(angle);
	angleline.setLength(len);

	painter.drawLine(angleline);
	painter.end();

	label.setPicture(pic);
}

void Game::setWindowDetails()
{
	window.setWindowIcon(QIcon("data/icon.svg"));
	window.setWindowTitle("QTicTacToe");
	window.setWindowFlags(Qt::Window);
	window.setFixedSize(0, 0);
	window.setLayout(&grid);
}

void Game::setMenuDetails()
{
	menu_options.addAction(&action_language);
	menu_bar.addMenu(&menu_options);
}

void Game::setGridDetails()
{
	grid.setSpacing(0);
	grid.setRowMinimumHeight(5, 50);
	grid.setMenuBar(&menu_bar);
}

void Game::setLineDetails()
{
	line[0].setFrameShape(QFrame::HLine);
	line[1].setFrameShape(QFrame::HLine);
	line[2].setFrameShape(QFrame::VLine);
	line[3].setFrameShape(QFrame::VLine);
	line[0].setLineWidth(2);
	line[1].setLineWidth(2);
	line[2].setLineWidth(2);
	line[3].setLineWidth(2);
}

void Game::addToGrid()
{
	grid.addWidget(&turn, 6, 0);
	grid.addWidget(&current_icon, 6, 2);
	grid.addWidget(&restart, 6, 4, Qt::AlignRight);
	grid.addWidget(&line[0], 1, 0, 1, 5);
	grid.addWidget(&line[1], 3, 0, 1, 5);
	grid.addWidget(&line[2], 0, 1, 5, 1);
	grid.addWidget(&line[3], 0, 3, 5, 1);
}

Game::Game() : grid(&window), menu_options("Options"), action_language("Language", &menu_options), restart("Restart"), turn("Whose turn"), current_size(30, 30), xnow(true), win('n'), o_icon("data/o.svg"), o_size(96, 96), x_icon("data/x.svg"), x_size(96, 96), rows(0), columns(0), right_painter(&right_pi), left_painter(&left_pi), horizon_painter(&horizon_pi), vertical_painter(&vertical_pi)
{
	setWindowDetails();
	setGridDetails();
	setMenuDetails();
	setLineDetails();
	addToGrid();

	QObject::connect(&action_language, &QAction::triggered, []
	{
		qDebug("language");
	});

	current_icon.setPixmap(x_icon.pixmap(current_size));

	paintLine(vertical_line, 90, 298, QPointF(112, 0));
	paintLine(horizon_line, 0, 298, QPointF(0, 100));
	paintLine(left_line, 45, 420, QPointF(0, 100));
	paintLine(right_line, -45, 420, QPointF(0, 100));

	restart.setFocusPolicy(Qt::NoFocus);
	QObject::connect(&restart, &QPushButton::clicked, [&]
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
		[&, i]
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
				markDisabledAll();
			}
			else if(button_str[3] == 'x' && button_str[4] == 'x' && button_str[5] == 'x')
			{
				grid.addWidget(&horizon_line, 2, 0, 1, 5, Qt::AlignJustify);
				horizon_line.show();
				markDisabledAll();
			}
			else if(button_str[6] == 'x' && button_str[7] == 'x' && button_str[8] == 'x')
			{
				grid.addWidget(&horizon_line, 4, 0, 1, 5, Qt::AlignJustify);
				horizon_line.show();
				markDisabledAll();
			}
			else if(button_str[0] == 'x' && button_str[3] == 'x' && button_str[6] == 'x')
			{
				grid.addWidget(&vertical_line, 0, 0, 5, 1, Qt::AlignJustify);
				vertical_line.show();
				markDisabledAll();
			}
			else if(button_str[1] == 'x' && button_str[4] == 'x' && button_str[7] == 'x')
			{
				grid.addWidget(&vertical_line, 0, 2, 5, 1, Qt::AlignJustify);
				vertical_line.show();
				markDisabledAll();
			}
			else if(button_str[2] == 'x' && button_str[5] == 'x' && button_str[8] == 'x')
			{
				grid.addWidget(&vertical_line, 0, 4, 5, 1, Qt::AlignJustify);
				vertical_line.show();
				markDisabledAll();
			}
			else if(button_str[0] == 'x' && button_str[4] == 'x' && button_str[8] == 'x')
			{
				grid.addWidget(&right_line, 0, 0, 5, 5, Qt::AlignJustify);
				right_line.show();
				markDisabledAll();
			}
			else if(button_str[2] == 'x' && button_str[4] == 'x' && button_str[6] == 'x')
			{
				grid.addWidget(&left_line, 0, 0, 5, 5, Qt::AlignJustify);
				left_line.show();
				markDisabledAll();
			}
			// OOOOOOOOOOOOOOOOOOOOOOOOOOO
			if(button_str[0] == 'o' && button_str[1] == 'o' && button_str[2] == 'o')
			{
				grid.addWidget(&horizon_line, 0, 0, 1, 5, Qt::AlignJustify);
				horizon_line.show();
				markDisabledAll();
			}
			else if(button_str[3] == 'o' && button_str[4] == 'o' && button_str[5] == 'o')
			{
				grid.addWidget(&horizon_line, 2, 0, 1, 5, Qt::AlignJustify);
				horizon_line.show();
				markDisabledAll();
			}
			else if(button_str[6] == 'o' && button_str[7] == 'o' && button_str[8] == 'o')
			{
				grid.addWidget(&horizon_line, 4, 0, 1, 5, Qt::AlignJustify);
				horizon_line.show();
				markDisabledAll();
			}
			else if(button_str[0] == 'o' && button_str[3] == 'o' && button_str[6] == 'o')
			{
				grid.addWidget(&vertical_line, 0, 0, 5, 1, Qt::AlignJustify);
				vertical_line.show();
				markDisabledAll();
			}
			else if(button_str[1] == 'o' && button_str[4] == 'o' && button_str[7] == 'o')
			{
				grid.addWidget(&vertical_line, 0, 2, 5, 1, Qt::AlignJustify);
				vertical_line.show();
				markDisabledAll();
			}
			else if(button_str[2] == 'o' && button_str[5] == 'o' && button_str[8] == 'o')
			{
				grid.addWidget(&vertical_line, 0, 4, 5, 1, Qt::AlignJustify);
				vertical_line.show();
				markDisabledAll();
			}
			else if(button_str[0] == 'o' && button_str[4] == 'o' && button_str[8] == 'o')
			{
				grid.addWidget(&right_line, 0, 0, 5, 5, Qt::AlignJustify);
				right_line.show();
				markDisabledAll();
			}
			else if(button_str[2] == 'o' && button_str[4] == 'o' && button_str[6] == 'o')
			{
				grid.addWidget(&left_line, 0, 0, 5, 5, Qt::AlignJustify);
				left_line.show();
				markDisabledAll();
			}

		});
		grid.addWidget(&button[i], rows, columns);
		columns++;
	}
}

void Game::show()
{
	window.show();
}

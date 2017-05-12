#include <QApplication>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QMenuBar>
#include <QAction>
#include <QPainter>
#include <QPicture>

#include "Window.hpp"
#include "Board.hpp"
#include "Game.hpp"

Game::Game() : xnow(true), win('n'), restart("Restart"), turn("Whose turn"), current_size(30, 30)
{
	current_icon.setPixmap(x_icon.pixmap(current_size));
	restart.setFocusPolicy(Qt::NoFocus);

	Game::addToGrid();

	paintLine(vertical_line, 90, 298, QPointF(112, 0));
	paintLine(horizon_line, 0, 298, QPointF(0, 100));
	paintLine(left_line, 45, 420, QPointF(0, 100));
	paintLine(right_line, -45, 420, QPointF(0, 100));

	QObject::connect(&restart, &QPushButton::clicked, [&]
	{
		xnow = true;
		win = 'n';
		current_icon.setPixmap(x_icon.pixmap(current_size));
		for(int x = 0; x < 3; x++) for(int y = 0; y < 3; y++)
		{
			button_str[x][y] = '0';
			button[x][y].setEnabled(true);
			button[x][y].setIcon(QIcon());
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

	for(int x = 0; x < 3; x++) for(int y = 0; y < 3; y++)
	{
		QObject::connect(&button[x][y], &QPushButton::clicked, [&, x, y]
		{
			if(xnow)
			{
				button[x][y].setIcon(x_icon);
				button[x][y].setIconSize(x_size);
				button_str[x][y] = 'x';
				current_icon.setPixmap(o_icon.pixmap(current_size));
				xnow = false;
			}
			else
			{
				button[x][y].setIcon(o_icon);
				button[x][y].setIconSize(o_size);
				button_str[x][y] = 'o';
				current_icon.setPixmap(x_icon.pixmap(current_size));
				xnow = true;
			}
			button[x][y].setDisabled(true);

			//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
			if(button_str[0][0] == 'x' && button_str[0][1] == 'x' && button_str[0][2] == 'x')
			{
				grid.addWidget(&horizon_line, 0, 0, 1, 5, Qt::AlignJustify);
				horizon_line.show();
				markDisabledAll();
			}
			else if(button_str[1][0] == 'x' && button_str[1][1] == 'x' && button_str[1][2] == 'x')
			{
				grid.addWidget(&horizon_line, 2, 0, 1, 5, Qt::AlignJustify);
				horizon_line.show();
				markDisabledAll();
			}
			else if(button_str[2][0] == 'x' && button_str[2][1] == 'x' && button_str[2][2] == 'x')
			{
				grid.addWidget(&horizon_line, 4, 0, 1, 5, Qt::AlignJustify);
				horizon_line.show();
				markDisabledAll();
			}
			/*else if(button_str[0] == 'x' && button_str[3] == 'x' && button_str[6] == 'x')
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
			}*/

		});
	}

}

void Game::addToGrid()
{
	grid.addWidget(&turn, 6, 0);
	grid.addWidget(&current_icon, 6, 2);
	grid.addWidget(&restart, 6, 4, Qt::AlignRight);
}

void Game::markDisabledAll()
{
	for(int x = 0; x < 3; x++) for(int y = 0; y < 3; y++)
		button[x][y].setDisabled(true);
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

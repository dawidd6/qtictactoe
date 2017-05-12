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

Board::Board() : symbols_thickness(8), x_size(100, 100), o_size(100, 100)
{
	setGridDetails();
	setLineDetails();
	setButtonsDetails();
	addToGrid();

	paintCross(x_icon);
	paintCircle(o_icon);

}

void Board::paintCross(QIcon &icon)
{
	QPixmap pic(x_size);
	pic.fill(Qt::transparent);

	QPainter painter(&pic);
	painter.setPen(QPen(Qt::black, symbols_thickness));
	painter.setRenderHint(QPainter::Antialiasing);

	QLineF angleline;
	angleline.setLine(7, 7, 93, 93);
	painter.drawLine(angleline);
	angleline.setLine(7, 93, 93, 7);
	painter.drawLine(angleline);

	painter.end();
	icon.addPixmap(pic);
}

void Board::paintCircle(QIcon &icon)
{
	QPixmap pic(o_size);
	pic.fill(Qt::transparent);

	QPainter painter(&pic);
	painter.setPen(QPen(Qt::black, symbols_thickness));
	painter.setRenderHint(QPainter::Antialiasing);

	painter.drawEllipse(QPointF(50, 50), 45, 45);

	painter.end();
	icon.addPixmap(pic);
}

void Board::setGridDetails()
{
	grid.setSpacing(0);
	grid.setRowMinimumHeight(5, 20);
	grid.setRowMinimumHeight(6, 40);
}

void Board::setLineDetails()
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

void Board::addToGrid()
{		
	int rows = 0;
	int columns = 0;
	for(int x = 0; x < 3; x++) for(int y = 0; y < 3; y++)
	{
		if(columns == 5)
		{
			rows++;
			columns = 0;
		}
		if(columns == 1 || columns == 3)
		{
			grid.addWidget(&line[2], 0, 1, 5, 1);
			grid.addWidget(&line[3], 0, 3, 5, 1);
			columns++;
		}
		if(rows == 1 || rows == 3)
		{
			grid.addWidget(&line[0], 1, 0, 1, 5);
			grid.addWidget(&line[1], 3, 0, 1, 5);
			rows++;
		}
		grid.addWidget(&button[x][y], rows, columns);
		columns++;
	}
}

void Board::setButtonsDetails()
{
	for(int x = 0; x < 3; x++) for(int y = 0; y < 3; y++)
	{
		button[x][y].setFixedSize(100, 100);
		button[x][y].setFlat(true);
		button[x][y].setFocusPolicy(Qt::NoFocus);
	}
}

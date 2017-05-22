#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QPainter>
#include <QPicture>

#include "Window.h"
#include "Board2v2.h"

Board2v2::Board2v2(Window *window)
{
	window->layout.addWidget(this);
	setLayout(&layout);
	restart.setText("Restart");
	restart.setFocusPolicy(Qt::NoFocus);
	size_current.scale(30, 30, Qt::IgnoreAspectRatio);
	size_x.scale(100, 100, Qt::IgnoreAspectRatio);
	size_o.scale(100, 100, Qt::IgnoreAspectRatio);
	turn.setText("Whose turn:");

	thickness = 8;
	rows = 0;
	columns = 0;
	win = 'n';
	xnow = true;

	paintCross();
	paintCircle();
	drawFrames();
	paintLine(vertical_line, 90, 298, QPointF(112, 0));
	paintLine(horizon_line, 0, 298, QPointF(0, 100));
	paintLine(left_line, 45, 420, QPointF(0, 100));
	paintLine(right_line, -45, 420, QPointF(0, 100));
	label_current.setPixmap(icon_x.pixmap(size_current));

	layout.setSpacing(0);
	layout.setRowMinimumHeight(5, 20);
	layout.setRowMinimumHeight(6, 40);

	for(int x = 0; x < 3; x++) for(int y = 0; y < 3; y++)
	{
		button[x][y].setFixedSize(100, 100);
		button[x][y].setFlat(true);
		button[x][y].setFocusPolicy(Qt::NoFocus);
		button_str[x][y] = '0';

		connect(&button[x][y], &QPushButton::clicked, [&, x, y]
		{
			button[x][y].setDisabled(true);
			if(xnow)
				markButtonIcon(x, y, 'x', icon_x, size_x, false);
			else
				markButtonIcon(x, y, 'o', icon_o, size_o, true);

			checkConditions();
		});

		if(columns == 5)
		{
			rows++;
			columns = 0;
		}
		if(columns == 1 || columns == 3)
		{
			layout.addWidget(&line[2], 0, 1, 5, 1);
			layout.addWidget(&line[3], 0, 3, 5, 1);
			columns++;
		}
		if(rows == 1 || rows == 3)
		{
			layout.addWidget(&line[0], 1, 0, 1, 5);
			layout.addWidget(&line[1], 3, 0, 1, 5);
			rows++;
		}
		layout.addWidget(&button[x][y], rows, columns);
		columns++;
	}
	layout.addWidget(&turn, 6, 0);
	layout.addWidget(&label_current, 6, 2);
	layout.addWidget(&restart, 6, 4, Qt::AlignRight);

	connect(&restart, SIGNAL(clicked()), this, SLOT(handleRestart()));
}

void Board2v2::handleRestart()
{
	xnow = true;
	win = 'n';
	label_current.setPixmap(icon_x.pixmap(size_current));
	for(int x = 0; x < 3; x++) for(int y = 0; y < 3; y++)
	{
		button_str[x][y] = '0';
		button[x][y].setEnabled(true);
		button[x][y].setIcon(QIcon());
	}
	layout.removeWidget(&left_line);
	layout.removeWidget(&right_line);
	layout.removeWidget(&horizon_line);
	layout.removeWidget(&vertical_line);
	left_line.hide();
	right_line.hide();
	horizon_line.hide();
	vertical_line.hide();
}

void Board2v2::markDisabledAll()
{
	for(int x = 0; x < 3; x++) for(int y = 0; y < 3; y++)
		button[x][y].setDisabled(true);
}

void Board2v2::markEnabledAll()
{
	for(int x = 0; x < 3; x++) for(int y = 0; y < 3; y++)
		button[x][y].setEnabled(true);
}

void Board2v2::markEnabledWhatLeft()
{
	for(int x = 0; x < 3; x++) for(int y = 0; y < 3; y++)
		if(button_str[x][y] == '0')
			button[x][y].setEnabled(true);
}

void Board2v2::drawLineOnGrid(QLabel &line, int fromrow, int fromcolumn, int rowspan, int columnspan)
{
	layout.addWidget(&line, fromrow, fromcolumn, rowspan, columnspan, Qt::AlignJustify);
	line.show();
	markDisabledAll();
}

void Board2v2::markButtonIcon(const int &x, const int &y, char s, QIcon &icon, QSize &size, bool n)
{
	button[x][y].setIcon(icon);
	button[x][y].setIconSize(size);
	button_str[x][y] = s;
	label_current.setPixmap(icon.pixmap(size_current));
	xnow = n;
}

void Board2v2::paintCross()
{
	QPixmap pic(size_x);
	pic.fill(Qt::transparent);

	QPainter painter(&pic);
	painter.setPen(QPen(Qt::black, thickness));
	painter.setRenderHint(QPainter::Antialiasing);

	QLineF angleline;
	angleline.setLine(7, 7, 93, 93);
	painter.drawLine(angleline);
	angleline.setLine(7, 93, 93, 7);
	painter.drawLine(angleline);

	painter.end();
	icon_x.addPixmap(pic);
}

void Board2v2::paintCircle()
{
	QPixmap pic(size_o);
	pic.fill(Qt::transparent);

	QPainter painter(&pic);
	painter.setPen(QPen(Qt::black, thickness));
	painter.setRenderHint(QPainter::Antialiasing);

	painter.drawEllipse(QPointF(50, 50), 45, 45);

	painter.end();
	icon_o.addPixmap(pic);
}

void Board2v2::drawFrames()
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

void Board2v2::paintLine(QLabel &label, int angle, int len, QPointF point)
{
	QPicture pic;
	QLineF angleline;
	QPainter painter(&pic);

	painter.setPen(QPen(Qt::black, thickness));
	painter.setRenderHint(QPainter::Antialiasing);

	angleline.setP1(point);
	angleline.setAngle(angle);
	angleline.setLength(len);

	painter.drawLine(angleline);
	painter.end();

	label.setPicture(pic);
}

void Board2v2::checkConditions()
{
	if(button_str[0][0] == 'x' && button_str[0][1] == 'x' && button_str[0][2] == 'x')
	drawLineOnGrid(horizon_line, 0, 0, 1, 5);
	else if(button_str[1][0] == 'x' && button_str[1][1] == 'x' && button_str[1][2] == 'x')
	drawLineOnGrid(horizon_line, 2, 0, 1, 5);
	else if(button_str[2][0] == 'x' && button_str[2][1] == 'x' && button_str[2][2] == 'x')
	drawLineOnGrid(horizon_line, 4, 0, 1, 5);
	else if(button_str[0][0] == 'x' && button_str[1][0] == 'x' && button_str[2][0] == 'x')
	drawLineOnGrid(vertical_line, 0, 0, 5, 1);
	else if(button_str[0][1] == 'x' && button_str[1][1] == 'x' && button_str[2][1] == 'x')
	drawLineOnGrid(vertical_line, 0, 2, 5, 1);
	else if(button_str[0][2] == 'x' && button_str[1][2] == 'x' && button_str[2][2] == 'x')
	drawLineOnGrid(vertical_line, 0, 4, 5, 1);
	else if(button_str[0][0] == 'x' && button_str[1][1] == 'x' && button_str[2][2] == 'x')
	drawLineOnGrid(right_line, 0, 0, 5, 5);
	else if(button_str[0][2] == 'x' && button_str[1][1] == 'x' && button_str[2][0] == 'x')
	drawLineOnGrid(left_line, 0, 0, 5, 5);
	if(button_str[0][0] == 'o' && button_str[0][1] == 'o' && button_str[0][2] == 'o')
	drawLineOnGrid(horizon_line, 0, 0, 1, 5);
	else if(button_str[1][0] == 'o' && button_str[1][1] == 'o' && button_str[1][2] == 'o')
	drawLineOnGrid(horizon_line, 2, 0, 1, 5);
	else if(button_str[2][0] == 'o' && button_str[2][1] == 'o' && button_str[2][2] == 'o')
	drawLineOnGrid(horizon_line, 4, 0, 1, 5);
	else if(button_str[0][0] == 'o' && button_str[1][0] == 'o' && button_str[2][0] == 'o')
	drawLineOnGrid(vertical_line, 0, 0, 5, 1);
	else if(button_str[0][1] == 'o' && button_str[1][1] == 'o' && button_str[2][1] == 'o')
	drawLineOnGrid(vertical_line, 0, 2, 5, 1);
	else if(button_str[0][2] == 'o' && button_str[1][2] == 'o' && button_str[2][2] == 'o')
	drawLineOnGrid(vertical_line, 0, 4, 5, 1);
	else if(button_str[0][0] == 'o' && button_str[1][1] == 'o' && button_str[2][2] == 'o')
	drawLineOnGrid(right_line, 0, 0, 5, 5);
	else if(button_str[0][2] == 'o' && button_str[1][1] == 'o' && button_str[2][0] == 'o')
	drawLineOnGrid(left_line, 0, 0, 5, 5);
}

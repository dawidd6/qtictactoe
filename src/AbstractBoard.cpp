#include <QPushButton>
#include <QGridLayout>
#include <QIcon>
#include <QSize>
#include <QLineEdit>
#include <QTcpSocket>
#include <QStatusBar>
#include <QLabel>
#include <QAction>
#include <QMenuBar>
#include <QStackedLayout>
#include <QPainter>
#include <QPicture>
#include <QTime>

#include "Window.h"
#include "AbstractSymbol.h"
#include "Circle.h"
#include "Cross.h"

#include "AbstractBoard.h"

CAbstractBoard::CAbstractBoard(CWindow *window) : smb{'x', 'o'}, thickness(8), rows(0), columns(0), win(0)
{
	window->addToLayout(this);
	setLayout(&layout);

	qsrand(QTime::currentTime().msec());

	restart.setText("Restart");
	restart.setFocusPolicy(Qt::NoFocus);
	size_current.scale(30, 30, Qt::IgnoreAspectRatio);
	label_turn.setText("Whose turn:");

	drawFrames();
	paintLine(vertical_line, 90, 298, QPointF(112, 0));
	paintLine(horizon_line, 0, 298, QPointF(0, 100));
	paintLine(left_line, 45, 420, QPointF(0, 100));
	paintLine(right_line, -45, 420, QPointF(0, 100));
	label_current.setPixmap(cross.getIcon().pixmap(size_current));

	layout.setSpacing(0);
	layout.setRowMinimumHeight(5, 20);
	layout.setRowMinimumHeight(6, 40);

	for(int x = 0; x < 3; x++) for(int y = 0; y < 3; y++)
	{
		button[x][y].setFixedSize(100, 100);
		button[x][y].setFlat(true);
		button[x][y].setFocusPolicy(Qt::NoFocus);
		button_str[x][y] = '0';

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

	layout.addWidget(&label_turn, 6, 0);
	layout.addWidget(&label_current, 6, 2);
	layout.addWidget(&restart, 6, 4, Qt::AlignRight);

	show();
}

void CAbstractBoard::restartBoard()
{
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

void CAbstractBoard::markDisabledAll()
{
	for(int x = 0; x < 3; x++) for(int y = 0; y < 3; y++)
		button[x][y].setDisabled(true);
}

void CAbstractBoard::markEnabledAll()
{
	for(int x = 0; x < 3; x++) for(int y = 0; y < 3; y++)
		button[x][y].setEnabled(true);
}

void CAbstractBoard::markEnabledWhatLeft()
{
	for(int x = 0; x < 3; x++) for(int y = 0; y < 3; y++)
		if(button_str[x][y] == '0')
			button[x][y].setEnabled(true);
}

void CAbstractBoard::drawLineOnGrid(QLabel &line, int fromrow, int fromcolumn, int rowspan, int columnspan)
{
	layout.addWidget(&line, fromrow, fromcolumn, rowspan, columnspan, Qt::AlignJustify);
	line.show();
	markDisabledAll();
	win = 1;
}

void CAbstractBoard::drawFrames()
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

void CAbstractBoard::paintLine(QLabel &label, int angle, int len, QPointF point)
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

void CAbstractBoard::checkConditions()
{
	for(int i = 0; i < 2; i++)
	if(button_str[0][0] == smb[i] && button_str[0][1] == smb[i] && button_str[0][2] == smb[i])
		drawLineOnGrid(horizon_line, 0, 0, 1, 5);
	else if(button_str[1][0] == smb[i] && button_str[1][1] == smb[i] && button_str[1][2] == smb[i])
		drawLineOnGrid(horizon_line, 2, 0, 1, 5);
	else if(button_str[2][0] == smb[i] && button_str[2][1] == smb[i] && button_str[2][2] == smb[i])
		drawLineOnGrid(horizon_line, 4, 0, 1, 5);
	else if(button_str[0][0] == smb[i] && button_str[1][0] == smb[i] && button_str[2][0] == smb[i])
		drawLineOnGrid(vertical_line, 0, 0, 5, 1);
	else if(button_str[0][1] == smb[i] && button_str[1][1] == smb[i] && button_str[2][1] == smb[i])
		drawLineOnGrid(vertical_line, 0, 2, 5, 1);
	else if(button_str[0][2] == smb[i] && button_str[1][2] == smb[i] && button_str[2][2] == smb[i])
		drawLineOnGrid(vertical_line, 0, 4, 5, 1);
	else if(button_str[0][0] == smb[i] && button_str[1][1] == smb[i] && button_str[2][2] == smb[i])
		drawLineOnGrid(right_line, 0, 0, 5, 5);
	else if(button_str[0][2] == smb[i] && button_str[1][1] == smb[i] && button_str[2][0] == smb[i])
		drawLineOnGrid(left_line, 0, 0, 5, 5);
}

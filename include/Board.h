#ifndef QTICTACTOE_BOARD_H
#define QTICTACTOE_BOARD_H

#include "Window.h"

class Board
{
	protected:
		QWidget widget;
		QGridLayout layout;
		QPushButton return_to_menu;
		QPushButton restart;
		QPushButton button[3][3];
		QIcon icon_x;
		QIcon icon_o;
		QSize size_x;
		QSize size_o;
		QSize size_current;
		QFrame line[4];
		QLabel left_line;
		QLabel right_line;
		QLabel horizon_line;
		QLabel vertical_line;
		QLabel turn;
		QLabel label_current;

		int thickness;
		int rows;
		int columns;
		char button_str[3][3];
		char win;
		bool xnow;
	public:
		Board(Window *window);
		void setupConnections();
		void markDisabledAll();
		void paintCross();
		void paintCircle();
		void paintLine(QLabel &label, int angle, int len, QPointF point);
		void drawLineOnGrid(QLabel &line, int fromrow, int fromcolumn, int rowspan, int columnspan);
		void markButtonIcon(const int &x, const int &y, char s, QIcon &icon, QSize &size, bool n);
};

#endif

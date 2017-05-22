#ifndef QTICTACTOE_BOARD_2V2_H
#define QTICTACTOE_BOARD_2V2_H

#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QPainter>
#include <QPicture>
#include <QMessageBox>

#include "Window.h"

class Board2v2 : public QWidget
{
	Q_OBJECT
	protected:
		QGridLayout layout;
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
		QChar button_str[3][3];
		int thickness;
		int rows;
		int columns;
		char win;
		bool xnow;
	private slots:
		void handleRestart();
	public:
		Board2v2(Window *window);
		void markDisabledAll();
		void markEnabledAll();
		void markEnabledWhatLeft();
		void checkConditions();
		void drawFrames();
		void paintCross();
		void paintCircle();
		void paintLine(QLabel &label, int angle, int len, QPointF point);
		void drawLineOnGrid(QLabel &line, int fromrow, int fromcolumn, int rowspan, int columnspan);
		void markButtonIcon(const int &x, const int &y, char s, QIcon &icon, QSize &size, bool n);
};

#endif

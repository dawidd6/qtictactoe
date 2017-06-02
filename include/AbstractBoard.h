#pragma once

class Window;

class CAbstractBoard : public QWidget
{
	protected:
		QGridLayout layout;
		QPushButton restart;
		QPushButton button[3][3];
		QChar button_str[3][3];
		CCross cross;
		CCircle circle;
		QFrame line[4];
		QLabel left_line;
		QLabel right_line;
		QLabel horizon_line;
		QLabel vertical_line;
		QSize size_current;
		QLabel label_turn;
		QLabel label_current;
		int thickness;
		int rows;
		int columns;
	public:
		CAbstractBoard(CWindow *window);
		void markDisabledAll();
		void markEnabledAll();
		void markEnabledWhatLeft();
		void checkConditions();
		void drawFrames();
		void restartBoard();
		void paintLine(QLabel &label, int angle, int len, QPointF point);
		void drawLineOnGrid(QLabel &line, int fromrow, int fromcolumn, int rowspan, int columnspan);
		virtual void handleRestart() = 0;
};

#pragma once

class Window;

class AbstractBoard : public QWidget
{
	protected:
		QGridLayout layout;
		QPushButton button_restart;
		QPushButton button[3][3];
		QChar button_str[3][3];
		QChar smb[2];
		Cross cross;
		Circle circle;
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
		volatile int win;
	public:
		AbstractBoard(Window *window);
		void markDisabledAll();
		void markEnabledAll();
		void markEnabledWhatLeft();
		bool yallGotAnyMoreOfThemButtons();
		void checkConditions();
		void drawFrames();
		void restartBoard();
		void paintLine(QLabel &label, int angle, int len, QPointF point);
		void drawLineOnGrid(QLabel &line, int fromrow, int fromcolumn, int rowspan, int columnspan);
		virtual void makeMove(const int &x, const int &y, QChar s, const AbstractSymbol *symbol);
		virtual void handleRestart() = 0;
};

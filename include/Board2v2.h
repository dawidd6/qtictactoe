#pragma once

class CBoard2v2 : public QWidget
{
	protected:
		QGridLayout layout;
		QPushButton restart;
		QPushButton button[3][3];
		CCross cross;
		CCircle circle;
		QSize size_current;
		QFrame line[4];
		QLabel left_line;
		QLabel right_line;
		QLabel horizon_line;
		QLabel vertical_line;
		QLabel label_turn;
		QLabel label_current;
		QChar button_str[3][3];
		int thickness;
		int rows;
		int columns;
		char win;
		bool xnow;
	public:
		CBoard2v2(CWindow *window);
		void markDisabledAll();
		void markEnabledAll();
		void markEnabledWhatLeft();
		void checkConditions();
		void drawFrames();
		void paintLine(QLabel &label, int angle, int len, QPointF point);
		void drawLineOnGrid(QLabel &line, int fromrow, int fromcolumn, int rowspan, int columnspan);
		void markButtonIcon(const int &x, const int &y, char s, CAbstractSymbol *symbol, bool n);
		void handleRestart();
};

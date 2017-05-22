#ifndef QTICTACTOE_BOARD_H
#define QTICTACTOE_BOARD_H

#include <QPushButton>
#include <QGridLayout>
#include <QStackedLayout>
#include <QLabel>
#include <QMenuBar>
#include <QAction>
#include <QPainter>
#include <QPicture>
#include <QTcpSocket>
#include <QMessageBox>

#include "Window.h"

class Board : public QWidget
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
		QLabel label_turn;
		QLabel label_current;
		QIcon *icon_my;
		QSize *size_my;
		QIcon *icon_enemy;
		QSize *size_enemy;
	protected:
		int thickness;
		int rows;
		int columns;
		QChar button_str[3][3];
		char win;
		bool xnow;
	private:
		QTcpSocket socket;
		QString response;
		QChar symbol_my;
		QChar symbol_enemy;
		int turn;
		int counter;
	public slots:
		void handleRestart();	
	public slots:
		void handleRead();
		void handleConnection();
		void handleDisconnection();
	public:
		Board(Window *window);
		~Board();
		void logger(QString msg);
		void checkConditions();
		void markDisabledAll();
		void markEnabledAll();
		void markEnabledWhatLeft();
		void paintCross();
		void paintCircle();
		void paintLine(QLabel &label, int angle, int len, QPointF point);
		void drawLineOnGrid(QLabel &line, int fromrow, int fromcolumn, int rowspan, int columnspan);
};

#endif

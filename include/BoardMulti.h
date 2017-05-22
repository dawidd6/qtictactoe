#ifndef QTICTACTOE_BOARD_MULTI_H
#define QTICTACTOE_BOARD_MULTI_H

#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QPicture>
#include <QTcpSocket>

#include "Window.h"
#include "Board2v2.h"

class BoardMulti : public Board2v2
{
	Q_OBJECT
	private:
		QIcon *icon_my;
		QSize *size_my;
		QIcon *icon_enemy;
		QSize *size_enemy;
		QTcpSocket socket;
		QString response;
		QChar symbol_my;
		QChar symbol_enemy;
		int turn;
		int counter;
	private slots:
		void handleRestart();
		void handleRead();
		void handleConnection();
		void handleDisconnection();
	public:
		BoardMulti(Window *window);
		~BoardMulti();
		void logger(QString msg);
};

#endif

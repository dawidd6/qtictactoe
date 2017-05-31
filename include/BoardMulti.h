#pragma once

#include <QPushButton>
#include <QLineEdit>
#include <QStatusBar>
#include <QGridLayout>
#include <QLabel>
#include <QPicture>
#include <QTcpSocket>

#include "Window.h"
#include "Board2v2.h"

class SetupConnection;

class BoardMulti : public Board2v2
{
	Q_OBJECT
	private:
		SetupConnection *setup_connection;
		Window *win;
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
		virtual ~BoardMulti();
};

class SetupConnection : public QWidget
{
	Q_OBJECT
	private:
		QGridLayout layout;
		QLineEdit line_address;
		QStatusBar statusbar;
		QPushButton button_connect;
	signals:
		void signalSuccess();
	public:
		SetupConnection(Window *window, QTcpSocket &socket);
};

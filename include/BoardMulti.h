#pragma once

class SetupConnection : public QWidget
{
	private:
		QGridLayout layout;
		QLineEdit line_address;
		QStatusBar statusbar;
		QPushButton button_connect;
	public:
		SetupConnection(Window *window, QTcpSocket &socket);
};

class BoardMulti : public Board2v2
{
	private:
		SetupConnection *setup_connection;
		Window *win;
		QIcon *icon_my;
		QSize *size_my;
		QIcon *icon_enemy;
		QSize *size_enemy;
		QTcpSocket socket;
		QStatusBar statusbar;
		QString response;
		QChar symbol_my;
		QChar symbol_enemy;
		int turn;
		int counter;
	public:
		BoardMulti(Window *window);
		~BoardMulti();
		void handleRestart();
		void handleRead();
		void handleConnection();
		void handleDisconnection();
		void restartBoard();
};

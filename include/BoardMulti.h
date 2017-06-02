#pragma once

class CSetupConnection : public QWidget
{
	private:
		QGridLayout layout;
		QLineEdit line_address;
		QStatusBar statusbar;
		QPushButton button_connect;
	public:
		CSetupConnection(CWindow *window, QTcpSocket &socket);
};

class CBoardMulti : public CBoard2v2
{
	private:
		CSetupConnection *setup_connection;
		CWindow *win;
		CAbstractSymbol *symbol_my;
		CAbstractSymbol *symbol_enemy;
		QTcpSocket socket;
		QStatusBar statusbar;
		QString response;
		QChar symbol_char_my;
		QChar symbol_char_enemy;
		int turn;
		int counter;
	public:
		CBoardMulti(CWindow *window);
		~CBoardMulti();
		void makeMove(const int &x, const int &y, const CAbstractSymbol *symbol, QChar symbol_char, bool isMyTurn, QString message);
		void handleRestart();
		void handleRead();
		void handleConnection();
		void handleDisconnection();
		void restartBoard();
};

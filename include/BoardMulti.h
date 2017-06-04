#pragma once

class CBoardMulti : public CAbstractBoard
{
	private:
		CSetupConnection *setup_connection;
		CWindow *win;
		CGame *g;
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
		CBoardMulti(CWindow *window, CGame *game);
		~CBoardMulti();
		void makeMove(const int &x, const int &y, const CAbstractSymbol *symbol, QChar symbol_char, bool isMyTurn, QString message);
		void handleRead();
		void handleConnection();
		void handleDisconnection();
		void handleRandom();
		virtual void handleRestart();
};

#pragma once

class CBoardMulti : public CAbstractBoard
{
	private:
		CSetupConnection *setup_connection;
		CWindow *w;
		CGame *g;
		CAbstractSymbol *symbol_my;
		CAbstractSymbol *symbol_enemy;
		QTcpSocket socket;
		QStatusBar statusbar;
		QString response;
		QChar symbol_char_my;
		QChar symbol_char_enemy;
		volatile int turn;
	public:
		CBoardMulti(CWindow *window, CGame *game);
		~CBoardMulti();
		void makeMove(const int &x, const int &y, const CAbstractSymbol *symbol, QChar symbol_char, bool isMyTurn, QString message);
		void handleRead();
		void handleConnection();
		void handleDisconnection();
		void handleRandom();
		bool yallGotAnyMoreOfThemButtons();
		virtual void handleRestart();
};

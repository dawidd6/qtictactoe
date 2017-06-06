#pragma once

class BoardMulti : public AbstractBoard
{
	private:
		SetupConnection *setup_connection;
		Window *w;
		Game *g;
		AbstractSymbol *symbol_my;
		AbstractSymbol *symbol_enemy;
		QTcpSocket socket;
		QStatusBar statusbar;
		QString response;
		QChar symbol_char_my;
		QChar symbol_char_enemy;
		volatile int turn;
	public:
		BoardMulti(Window *window, Game *game);
		~BoardMulti();
		void makeMove(const int &x, const int &y, const AbstractSymbol *symbol, QChar symbol_char, bool isMyTurn, QString message);
		void handleRead();
		void handleConnection();
		void handleDisconnection();
		void handleRandom();
		virtual void handleRestart();
};

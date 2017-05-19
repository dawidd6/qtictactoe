#ifndef QTICTACTOE_GAME_H
#define QTICTACTOE_GAME_H

#include "Window.h"
#include "Board.h"
#include "Menu.h"

class Game : public QObject
{
	Q_OBJECT
	private:
		Window *window;
		Board *board;
		Menu *menu;
	signals:
		void signalReturn();
	public slots:
		void handleReturn();
		void handlePlay2v2();
		void handleRestore();
	public:
		Game();
		~Game();
};

#endif

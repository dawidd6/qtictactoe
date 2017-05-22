#ifndef QTICTACTOE_GAME_H
#define QTICTACTOE_GAME_H

#include "Window.h"
#include "Board2v2.h"
#include "BoardMulti.h"
#include "Menu.h"

class Game : public QObject
{
	Q_OBJECT
	private:
		Window *window;
		Board2v2 *board_2v2;
		BoardMulti *board_multi;
		Menu *menu;
	signals:
		void signalReturn();
	private slots:
		void handleReturn();
		void handlePlay2v2();
		void handlePlayMulti();
		void handleRestore();
	public:
		Game();
		~Game();
};

#endif

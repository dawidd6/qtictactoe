#pragma once

class Window;
class Board2v2;
class BoardMulti;
class Menu;

class Game : public QObject
{
	private:
		Window *window;
		Board2v2 *board_2v2;
		BoardMulti *board_multi;
		Menu *menu;
	public:
		Game();
		~Game();
		static void logger(QString msg);
		void handleReturn();
		void handlePlay2v2();
		void handlePlayMulti();
};

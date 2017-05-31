#pragma once

#include <QObject>
#include <QDateTime>

class Window;
class Menu;
class Board2v2;
class BoardMulti;

class Game : public QObject
{
	Q_OBJECT
	private:
		Window *window;
		Board2v2 *board_2v2;
		BoardMulti *board_multi;
		Menu *menu;
	public slots:
		void handleReturn();
		void handlePlay2v2();
		void handlePlayMulti();
	public:
		Game();
		~Game();
		static void logger(QString msg);
};

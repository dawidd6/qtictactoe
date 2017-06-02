#pragma once

class CWindow;
class CBoard2v2;
class CBoardMulti;
class CMenu;

class CGame : public QObject
{
	private:
		CWindow *window;
		CBoard2v2 *board_2v2;
		CBoardMulti *board_multi;
		CMenu *menu;
	public:
		CGame();
		~CGame();
		static void logger(QString msg);
		void handleReturn();
		void handlePlay2v2();
		void handlePlayMulti();
};

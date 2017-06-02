#pragma once

class CWindow;
class CAbstractBoard;
class CMenu;

class CGame : public QObject
{
	private:
		CWindow *window;
		CAbstractBoard *board;
		CMenu *menu;
	public:
		CGame();
		~CGame();
		static void logger(QString msg);
		void handleReturn();
		void handlePlay2v2();
		void handlePlayMulti();
};

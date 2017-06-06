#pragma once

class Window;
class AbstractBoard;
class Menu;

class Game final : public QObject
{
	private:
		Window *window;
		AbstractBoard *board;
		Menu *menu;
	public:
		Game();
		~Game();
		static void logger(QString msg);
		void handleReturn();
		void handlePlay2v2();
		void handlePlayMulti();
		void handlePlaySingle();
};

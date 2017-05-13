#ifndef QTICTACTOE_GAME_H
#define QTICTACTOE_GAME_H

class Game
{
	private:
		Window *window;
		Board *vs;
		Menu *menu;
	public:
		Game();
		~Game();
		void hookUpButtonConnections();
};

#endif

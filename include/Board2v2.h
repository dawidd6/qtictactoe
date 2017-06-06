#pragma once

class Board2v2 : public AbstractBoard
{
	private:
		int xnow;
	public:
		Board2v2(Window *window);
		void randomTurn();
		virtual void handleRestart();
};

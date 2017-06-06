#pragma once

class BoardSingle : public AbstractBoard
{
	private:
		AbstractSymbol *my_symbol;
		AbstractSymbol *computer_symbol;
		QChar symbol_char_my;
		QChar symbol_char_computer;
	public:
		BoardSingle(Window *window);
		void makeComputerMove();
		void randomSymbol();
		void randomTurn();
		virtual void handleRestart();
		void gimmeFreeRoomHorizon(int &x, int &y, int &xx);
		void gimmeFreeRoomVertical(int &x, int &y, int &yy);
};

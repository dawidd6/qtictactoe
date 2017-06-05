#pragma once

class CBoardSingle : public CAbstractBoard
{
	private:
		CAbstractSymbol *my_symbol;
		CAbstractSymbol *computer_symbol;
		QChar symbol_char_my;
		QChar symbol_char_computer;
	public:
		CBoardSingle(CWindow *window);
		void makeComputerMove();
		void randomSymbol();
		void randomTurn();
		virtual void handleRestart();
		void gimmeFreeRoomHorizon(int &x, int &y, int &xx);
		void gimmeFreeRoomVertical(int &x, int &y, int &yy);
};

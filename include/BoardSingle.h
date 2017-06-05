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
};

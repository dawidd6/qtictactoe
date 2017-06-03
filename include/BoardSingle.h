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
		void markButtonIcon(const int &x, const int &y, QChar s, const CAbstractSymbol *symbol);
		void makeComputerMove();
		void randomSymbol();
		void randomTurn();
		bool yallGotAnyMoreOfThemButtons();
		virtual void handleRestart();
};

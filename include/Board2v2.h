#pragma once

class CBoard2v2 : public CAbstractBoard
{
	private:
		int xnow;
	public:
		CBoard2v2(CWindow *window);
		void markButtonIcon(const int &x, const int &y, char s, const CAbstractSymbol &symbol, bool n);
		void randomTurn();
		virtual void handleRestart();
};

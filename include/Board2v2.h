#pragma once

class CBoard2v2 : public CAbstractBoard
{
	protected:
		char win;
		bool xnow;
	public:
		CBoard2v2(CWindow *window);
		void markButtonIcon(const int &x, const int &y, char s, const CAbstractSymbol &symbol, bool n);
		virtual void handleRestart();
};

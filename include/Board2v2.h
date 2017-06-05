#pragma once

class CBoard2v2 : public CAbstractBoard
{
	private:
		int xnow;
	public:
		CBoard2v2(CWindow *window);
		void randomTurn();
		virtual void handleRestart();
};

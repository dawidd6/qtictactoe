#pragma once

class CCross : public CAbstractSymbol
{
	private:
		QLineF angleline;
	public:
		CCross();
		virtual void paint();
};


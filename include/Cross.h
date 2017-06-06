#pragma once

class Cross : public AbstractSymbol
{
	private:
		QLineF angleline;
	public:
		Cross();
		virtual void paint();
};


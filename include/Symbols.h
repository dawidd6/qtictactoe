#pragma once

class CAbstractSymbol
{
	protected:
		QIcon icon;
		QSize size;
		int thickness;
	public:
		CAbstractSymbol();
		virtual void paint() = 0;
		QIcon getIcon() const;
		QSize getSize() const;
};

class CCross : public CAbstractSymbol
{
	public:
		CCross();
		virtual void paint();
};

class CCircle : public CAbstractSymbol
{
	public:
		CCircle();
		virtual void paint();
};

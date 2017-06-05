#pragma once

class CAbstractSymbol
{
	protected:
		QIcon icon;
		QSize size;
		QPixmap pixmap;
		QPainter painter;
		int thickness;
	public:
		CAbstractSymbol();
		QIcon getIcon() const;
		QSize getSize() const;
		virtual void paint() = 0;
};

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
		virtual void paint() = 0;
		QIcon getIcon() const;
		QSize getSize() const;
};

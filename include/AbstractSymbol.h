#pragma once

class AbstractSymbol
{
	protected:
		QIcon icon;
		QSize size;
		QPixmap pixmap;
		QPainter painter;
		int thickness;
	public:
		AbstractSymbol();
		QIcon getIcon() const;
		QSize getSize() const;
		virtual void paint() = 0;
};

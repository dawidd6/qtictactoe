#include <QtWidgets>

#include "AbstractSymbol.h"

CAbstractSymbol::CAbstractSymbol() : size(100, 100), pixmap(size), thickness(8)
{
	pixmap.fill(Qt::transparent);
	painter.begin(&pixmap);
	painter.setPen(QPen(Qt::black, thickness));
	painter.setRenderHint(QPainter::Antialiasing);
}

QIcon CAbstractSymbol::getIcon() const
{
	return icon;
}

QSize CAbstractSymbol::getSize() const
{
	return size;
}

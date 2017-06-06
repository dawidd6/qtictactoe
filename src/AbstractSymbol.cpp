#include <QtWidgets>

#include "AbstractSymbol.h"

AbstractSymbol::AbstractSymbol() : size(100, 100), pixmap(size), thickness(8)
{
	pixmap.fill(Qt::transparent);
	painter.begin(&pixmap);
	painter.setPen(QPen(Qt::black, thickness));
	painter.setRenderHint(QPainter::Antialiasing);
}

QIcon AbstractSymbol::getIcon() const
{
	return icon;
}

QSize AbstractSymbol::getSize() const
{
	return size;
}

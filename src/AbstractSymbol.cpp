#include <QIcon>
#include <QSize>

#include "AbstractSymbol.h"

CAbstractSymbol::CAbstractSymbol()
{
	thickness = 8;
	size.scale(100, 100, Qt::IgnoreAspectRatio);
}

QIcon CAbstractSymbol::getIcon() const
{
	return icon;
}

QSize CAbstractSymbol::getSize() const
{
	return size;
}

#include <QtWidgets>

#include "AbstractSymbol.h"

#include "Circle.h"

Circle::Circle()
{
	paint();
}

void Circle::paint()
{
	painter.drawEllipse(QPointF(50, 50), 45, 45);

	painter.end();
	icon.addPixmap(pixmap);
}

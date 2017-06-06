#include <QtWidgets>

#include "AbstractSymbol.h"

#include "Cross.h"

Cross::Cross()
{
	paint();
}

void Cross::paint()
{
	angleline.setLine(7, 7, 93, 93);
	painter.drawLine(angleline);
	angleline.setLine(7, 93, 93, 7);
	painter.drawLine(angleline);

	painter.end();
	icon.addPixmap(pixmap);
}

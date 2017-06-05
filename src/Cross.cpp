#include <QtWidgets>

#include "AbstractSymbol.h"

#include "Cross.h"

CCross::CCross()
{
	paint();
}

void CCross::paint()
{
	angleline.setLine(7, 7, 93, 93);
	painter.drawLine(angleline);
	angleline.setLine(7, 93, 93, 7);
	painter.drawLine(angleline);

	painter.end();
	icon.addPixmap(pixmap);
}

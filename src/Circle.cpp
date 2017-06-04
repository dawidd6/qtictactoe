#include <QPointF>
#include <QLineF>
#include <QIcon>
#include <QSize>
#include <QPainter>
#include <QPixmap>

#include "AbstractSymbol.h"

#include "Circle.h"

CCircle::CCircle()
{
	paint();
}

void CCircle::paint()
{
	painter.drawEllipse(QPointF(50, 50), 45, 45);

	//painter.end();
	icon.addPixmap(pixmap);
}

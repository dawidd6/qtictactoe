#include <QPainter>
#include <QPicture>
#include <QLineF>
#include <QPixmap>
#include <QPointF>
#include <QIcon>
#include <QSize>

#include "AbstractSymbol.h"

#include "Circle.h"

CCircle::CCircle()
{
	paint();
}

void CCircle::paint()
{
	QPixmap pic(size);
	pic.fill(Qt::transparent);

	QPainter painter(&pic);
	painter.setPen(QPen(Qt::black, thickness));
	painter.setRenderHint(QPainter::Antialiasing);

	painter.drawEllipse(QPointF(50, 50), 45, 45);

	painter.end();
	icon.addPixmap(pic);
}

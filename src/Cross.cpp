#include <QPainter>
#include <QPicture>
#include <QLineF>
#include <QPixmap>
#include <QPointF>
#include <QIcon>
#include <QSize>

#include "AbstractSymbol.h"

#include "Cross.h"

CCross::CCross()
{
	paint();
}

void CCross::paint()
{
	QPixmap pic(size);
	pic.fill(Qt::transparent);

	QPainter painter(&pic);
	painter.setPen(QPen(Qt::black, thickness));
	painter.setRenderHint(QPainter::Antialiasing);

	QLineF angleline;
	angleline.setLine(7, 7, 93, 93);
	painter.drawLine(angleline);
	angleline.setLine(7, 93, 93, 7);
	painter.drawLine(angleline);

	painter.end();
	icon.addPixmap(pic);
}

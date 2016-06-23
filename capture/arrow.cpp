#include <QtGui>

#include "arrow.h"
#include <math.h>

const qreal Pi = 3.14;

Arrow::Arrow(QGraphicsItem *parent, QGraphicsScene *scene) : QGraphicsLineItem(parent)
{
    setFlag(QGraphicsItem::ItemIsSelectable, true);
}

QRectF Arrow::boundingRect() const
{
    qreal extra = (pen().width() + 20) / 2.0;

    return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),
                                      line().p2().y() - line().p1().y()))
        .normalized()
        .adjusted(-extra, -extra, extra, extra);
}

QPainterPath Arrow::shape() const
{
    QPainterPath path = QGraphicsLineItem::shape();
    path.addPolygon(arrowHead);
    return path;
}

void Arrow::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	QPen myPen = pen();
    myPen.setColor(pen().color());
	qreal arrowSize = 7 * pen().width();
    painter->setPen(myPen);
	painter->setBrush(pen().color());

	if (line().p2().x() == line().p1().x() && line().p2().y() == line().p1().y()) return;

	float pi_div = 2.5;

    double angle = ::acos(line().dx() / line().length());
    if (line().dy() >= 0) angle = (Pi * 2) - angle;

    QPointF arrowP1 = line().p2() - QPointF(sin(angle + Pi / pi_div) * arrowSize, cos(angle + Pi / pi_div) * arrowSize);
    QPointF arrowP2 = line().p2() - QPointF(sin(angle + Pi - Pi / pi_div) * arrowSize, cos(angle + Pi - Pi / pi_div) * arrowSize);

    arrowHead.clear();
    arrowHead << line().p2() << arrowP1 << arrowP2;

    painter->drawLine(line());
    painter->drawPolygon(arrowHead);
    if (isSelected())
	{
		painter->setPen(QPen(Qt::black, 1, Qt::DashLine));
		painter->setBrush(Qt::transparent);
		painter->drawRect(line().p1().x(), line().p1().y(), line().p2().x() - line().p1().x(), line().p2().y()-line().p1().y());
	}
}

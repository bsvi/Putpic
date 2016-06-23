#include "HighlightedArea.h"
#include <QPainter>

HighlightedArea::HighlightedArea(const QPixmap &pixmap, QGraphicsItem *parentItem) : QGraphicsPixmapItem(pixmap,parentItem)
{
	setCacheMode(NoCache);
	setClipping(0, 0, 0, 0);
}
 
HighlightedArea::~HighlightedArea()
{
}
 
void HighlightedArea::setClipping(int x, int y, int w, int h)
{
	prepareGeometryChange();
	_x = x; _y = y; _w = w; _h = h;
}
 
QRectF HighlightedArea::boundingRect() const
{
	return QRectF(_x-1, _y-1, _w+2, _h+2);
}
 
void HighlightedArea::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*)
{
	// Scale QGraphicsPixmapItem to wanted 'size' and keep the aspect ratio using boundingRect()
	QPen pen(Qt::green, 1, Qt::SolidLine); 

	if (_w != 0 && _h != 0)
	{
		painter->drawPixmap(_x, _y, pixmap(), _x, _y, _w+1, _h+1);
		painter->setPen(pen);
		painter->drawRect(_x-1, _y-1, _w+2, _h+2);
	}
 
	// NOTE: Does not use base class paint for painting now, that does not scale QPixmap
	//QGraphicsPixmapItem::paint(painter, option, widget);
}
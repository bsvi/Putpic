#pragma once
#include <QGraphicsPixmapItem>

class HighlightedArea: public QGraphicsPixmapItem
{
	public:
		HighlightedArea(const QPixmap &fullscreenPixmap, QGraphicsItem *parentItem=0);
		~HighlightedArea();
 
    public:
        QRectF boundingRect() const;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget=0);
        void setClipping(int x, int y, int w, int h);
 
    private:
        int _x, _y, _w, _h;
};
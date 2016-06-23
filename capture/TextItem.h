#ifndef TEXTITEM_H
#define TEXTITEM_H

#include <QGraphicsTextItem>
class DiagramTextItem;

class TextItem : public QGraphicsTextItem
{
	Q_OBJECT

public:
	TextItem(QGraphicsItem *parent);
	~TextItem();

protected:
    void focusOutEvent(QFocusEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
	
};

#endif // TEXTITEM_H

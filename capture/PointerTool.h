#ifndef POINTERTOOL_H
#define POINTERTOOL_H

#include <QObject>
#include <QPoint>

#include "ToolBase.h"

class QPoint;
class QPixmap;
class QGraphicsLineItem;
class MyQGraphicsView;
#include <QRect>

class PointerTool : public ToolBase
{
	Q_OBJECT
	MyQGraphicsView *_view;
public:
	PointerTool(QObject *parent, MyQGraphicsView *view, QGraphicsScene *scene, DrawingMenu *menu);
	~PointerTool();

private:
	virtual void Activate();
	virtual void Deactivate();
};

#endif // POINTERTOOL_H

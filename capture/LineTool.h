#ifndef LINETOOL_H
#define LINETOOL_H

#include <QObject>
#include <QPoint>

#include "ToolBase.h"

class QPoint;
class QPixmap;
class QGraphicsLineItem;
class DrawingMenu;
#include <QRect>


class LineTool : public ToolBase
{
	Q_OBJECT
	QPoint _startPoint;
	QGraphicsLineItem *_currentLine;

public:
	LineTool(QObject *parent, QGraphicsScene *scene, DrawingMenu *menu);
	~LineTool();

protected:
	virtual QGraphicsLineItem *CreateLineAt(int x, int y);

private:
	virtual void MousePressed(QMouseEvent *event);
	virtual void MouseReleased(QMouseEvent *event);
	virtual void MouseMoved(QMouseEvent *event);
	
};

#endif // LINETOOL_H

#ifndef ARROWTOOL_H
#define ARROWTOOL_H

#include "LineTool.h"

class ArrowTool : public LineTool
{
	Q_OBJECT

public:
	ArrowTool(QObject *parent, QGraphicsScene *scene, DrawingMenu *menu);
	~ArrowTool();

protected:
	virtual QGraphicsLineItem *CreateLineAt(int x, int y);
};

#endif // ARROWTOOL_H

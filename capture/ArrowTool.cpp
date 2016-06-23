#include "ArrowTool.h"
#include "arrow.h"
#include <QGraphicsScene>
#include <QGraphicsLineItem>

ArrowTool::ArrowTool(QObject *parent, QGraphicsScene *scene, DrawingMenu *menu) : LineTool(parent, scene, menu)
{

}

ArrowTool::~ArrowTool()
{

}


QGraphicsLineItem *ArrowTool::CreateLineAt(int x, int y)
{
	Arrow *arrow = new Arrow();
	arrow->setLine(QLine(x, y, x, y));
	Scene()->addItem(arrow);
	return arrow;
}
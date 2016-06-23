#include "PointerTool.h"
#include "myqgraphicsview.h"
#include <QGraphicsScene>

PointerTool::PointerTool(QObject *parent, MyQGraphicsView *view, QGraphicsScene *scene, DrawingMenu *menu) : ToolBase(parent, scene, menu)
{
	_view = view;
}

PointerTool::~PointerTool()
{

}


void PointerTool::Activate()
{
	_view->setMessagePassing(true);
	_view->setCursor(Qt::ArrowCursor);
}

void PointerTool::Deactivate()
{
	_view->setMessagePassing(false);
	_view->setCursor(Qt::CrossCursor);
}

#include "LineTool.h"
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include "Settings.h"


LineTool::LineTool(QObject *parent, QGraphicsScene *scene, DrawingMenu *menu) : ToolBase(parent, scene, menu)
{
	_currentLine = 0;
}

LineTool::~LineTool()
{
}


QGraphicsLineItem *LineTool::CreateLineAt(int x, int y)
{
	return 	Scene()->addLine(x, y, x, y);
}

void LineTool::MousePressed(QMouseEvent *event)
{
	if (!_currentLine)
	{
		_startPoint = event->pos();
		_currentLine = CreateLineAt(_startPoint.x(), _startPoint.y());
		_currentLine->setPen(QPen(Color(), LineSize(), Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin) );
		_currentLine->setFlag(QGraphicsItem::ItemIsMovable, true);
		_currentLine->setFlag(QGraphicsItem::ItemIsSelectable, true);
	}
	else
	{
		_currentLine = 0;
	}
}

void LineTool::MouseReleased(QMouseEvent *event)
{
	if (!Settings::Instance()->doubleClickDrawing()) _currentLine = 0;
}

void LineTool::MouseMoved(QMouseEvent *event)
{
	if (_currentLine != 0)
	{
		QPoint pos = event->pos();
		_currentLine->setLine(_startPoint.x(), _startPoint.y(), pos.x(), pos.y());
	}
}

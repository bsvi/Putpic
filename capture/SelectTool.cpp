#include "SelectTool.h"

#include <QPoint>
#include <QGraphicsScene>
#include "HighlightedArea.h"
#include <QDesktopWidget>
#include <QApplication>
#include "Settings.h"

SelectTool::SelectTool(QObject *parent, QGraphicsScene *scene, QPixmap *pixmap, DrawingMenu *menu)
	: ToolBase(parent, scene, menu)
{
	_pixmap = pixmap;
	_firstPointSelected = false;

	_highlight = new HighlightedArea(*_pixmap, 0);
	Scene()->addItem(_highlight);

	HWND active =  GetForegroundWindow();
	if (active != 0 && GetWindowRect(active,  &_foregroundWindow)) ToForegroundWindow();
	GetClientRect(active,  &_foregroundWindowClient);

	RedrawSelectedArea();
}

SelectTool::~SelectTool()
{
//	delete _highlight;
}

void SelectTool::SortPoints(QPoint *first, QPoint *second)
{
	int minx = qMin<int>(first->x(), second->x());
	int maxx = qMax<int>(first->x(), second->x());
	int miny = qMin<int>(first->y(), second->y());
	int maxy = qMax<int>(first->y(), second->y());

	*first=QPoint(minx, miny);
	*second=QPoint(maxx, maxy);
}

void SelectTool::RedrawSelectedArea()
{
	QPoint first(_firstPoint), second(_secondPoint);
	SortPoints(&first, &second);

	if (second.x() -first.x() != 0 && second.y() -first.y() != 0)
	{
		_highlight->setClipping(first.x(), first.y(), second.x() -first.x(), second.y() -first.y());
	}

	UpdateScene();
}


void SelectTool::MouseMoved(QMouseEvent *event)
{
	if (_firstPointSelected)
	{
		_secondPoint = event->pos();
		RedrawSelectedArea();
	}
}


void SelectTool::MousePressed(QMouseEvent *event)
{
	if (!_firstPointSelected)
	{
		_firstPoint = event->pos();
		_secondPoint = event->pos();
		RedrawSelectedArea();
		_firstPointSelected = true;
	}
	else
	{
		_firstPointSelected = false;
	}
}

void SelectTool::MouseReleased(QMouseEvent *event)
{
	if (!Settings::Instance()->doubleClickDrawing()) _firstPointSelected = false;
	RedrawSelectedArea();
}


void SelectTool::ToForegroundWindow()
{
	QDesktopWidget *desktop = QApplication::desktop();
	int x = desktop->x();
	int y = desktop->y();

	_firstPoint.setX(_foregroundWindow.left-x);
	_firstPoint.setY(_foregroundWindow.top-y);
	_secondPoint.setX(_foregroundWindow.right-x);
	_secondPoint.setY(_foregroundWindow.bottom-y);
}

QRect SelectTool::selection()
{
	QPoint first(_firstPoint), second(_secondPoint);
	SortPoints(&first, &second);
	return QRect(first, second);
}


bool SelectTool::selectionValid()
{
	if (selection().width() !=0 && selection().height() !=0) return true;
	return false;
}



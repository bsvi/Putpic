#include "myqgraphicsview.h"

MyQGraphicsView::MyQGraphicsView(QGraphicsScene *scene, QWidget *parent) : QGraphicsView(scene, parent)
{
	setMouseTracking(true);
	_passMessages = false;
}

void MyQGraphicsView::mouseReleaseEvent(QMouseEvent * e)
{
	if (_passMessages) QGraphicsView::mouseReleaseEvent(e);
	emit MouseReleased(e);
}

void MyQGraphicsView::mouseMoveEvent(QMouseEvent * e)
{
	if (_passMessages) QGraphicsView::mouseMoveEvent(e);
	emit MouseMoved(e);
}

void MyQGraphicsView::mousePressEvent(QMouseEvent * e)
{
	if (_passMessages) QGraphicsView::mousePressEvent(e);
	emit MousePressed(e);
}
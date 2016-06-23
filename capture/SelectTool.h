#ifndef SELECTTOOL_H
#define SELECTTOOL_H

#include "ToolBase.h"
#include "HighlightedArea.h"
#include "qt_windows.h"

class QPoint;
class QPixmap;
class HighlightedArea;

#include <QRect>

class SelectTool : public ToolBase
{
	Q_OBJECT

	QPoint _firstPoint;
	QPoint _secondPoint;
	QPixmap *_pixmap;
	HighlightedArea *_highlight;

	RECT _foregroundWindow;
	RECT _foregroundWindowClient;
	bool _firstPointSelected;

public:
	SelectTool(QObject *parent, QGraphicsScene *scene, QPixmap *pixmap, DrawingMenu *menu);
	~SelectTool();

	QRect selection();
	bool selectionValid();

	QPixmap *highlightPixmap() { return _pixmap; }
	QGraphicsItem *highlightItem() { return _highlight;}

	void ToForegroundWindow();

	void RedrawSelectedArea();

	virtual void MousePressed(QMouseEvent *event);
	virtual void MouseReleased(QMouseEvent *event);
	virtual void MouseMoved(QMouseEvent *event);

protected:
	void SortPoints(QPoint *first, QPoint *second);
	

	
};

#endif // SELECTTOOL_H

#ifndef TEXTTOOL_H
#define TEXTTOOL_H

#include "ToolBase.h"
class MyQGraphicsView;

class TextTool : public ToolBase
{
	Q_OBJECT
	MyQGraphicsView *_view;
public:
	TextTool(QObject *parent, MyQGraphicsView *view, QGraphicsScene *scene, DrawingMenu *menu);
	~TextTool();

protected:
	virtual void MousePressed(QMouseEvent *event);
	virtual void Activate();
	virtual void Deactivate();
};





#endif // TEXTTOOL_H

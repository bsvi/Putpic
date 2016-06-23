#ifndef TOOLBASE_H
#define TOOLBASE_H

#include <QObject>
#include <QMouseEvent>

class QGraphicsScene;
class DrawingMenu;

class ToolBase : public QObject
{
	Q_OBJECT

	QGraphicsScene *_scene;
	DrawingMenu *_menu;

public:
	ToolBase(QObject *parent, QGraphicsScene *scene, DrawingMenu *menu);
	~ToolBase();

	QGraphicsScene *Scene() { return _scene; }
	DrawingMenu *Menu() { return _menu; }

	QColor Color();
	int TextSize();
	int LineSize();


	virtual void MousePressed(QMouseEvent *event) {};
	virtual void MouseReleased(QMouseEvent *event) {};
	virtual void MouseMoved(QMouseEvent *event) {};

	virtual void Activate() {};
	virtual void Deactivate() {};

	virtual void Delete();

protected:
	virtual void UpdateScene();

};

#endif

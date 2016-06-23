#include "ToolBase.h"
#include <QGraphicsScene>
#include <QGraphicsItem>
#include "drawingmenu.h"

ToolBase::ToolBase(QObject *parent, QGraphicsScene *scene, DrawingMenu *menu)
	: QObject(parent)
{
	_scene = scene;
	_menu = menu;
}

ToolBase::~ToolBase()
{

}

void ToolBase::UpdateScene()
{
	_scene->update();
}

void ToolBase::Delete()
{
	if (_scene->selectedItems().count())
	{
		foreach (QGraphicsItem *item, _scene->selectedItems())
		{
				_scene->removeItem(item);
				delete item;
		}
	}
	else
	{
		if (_scene->items().count() > 2)
		{
			QGraphicsItem *item = _scene->items().first();
			_scene->removeItem(item);
			delete item;
		}
	}
}	


QColor ToolBase::Color() { return Menu()->color; }
int ToolBase::TextSize() { return Menu()->textSize; }
int ToolBase::LineSize() { return Menu()->lineSize; } 
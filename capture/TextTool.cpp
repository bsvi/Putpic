#include "TextTool.h"
#include "TextItem.h"
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QMouseEvent>
#include "myqgraphicsview.h"


TextTool::TextTool(QObject *parent, MyQGraphicsView *view, QGraphicsScene *scene, DrawingMenu *menu) : ToolBase(parent, scene, menu)
{
	_view = view;
}

TextTool::~TextTool()
{

}

void TextTool::Activate()
{
	_view->setMessagePassing(true);
	_view->setCursor(Qt::IBeamCursor);
}

void TextTool::Deactivate()
{
	_view->setMessagePassing(false);
	_view->setCursor(Qt::CrossCursor);
}


void TextTool::MousePressed(QMouseEvent *event)
{
	int x = event->x();
	int y = event->y();

    if (event->buttons() & Qt::LeftButton && Scene()->itemAt(x, y, QTransform())->type() != QGraphicsTextItem::Type)
	{
		TextItem *text = new TextItem(0);

		text->setPos(x, y);
		text->setFont(QFont("Arial", TextSize()));
        text->setTextInteractionFlags(Qt::TextEditorInteraction);
        text->setZValue(1000.0);
		text->setSelected(true);
		text->setFocus();

		Scene()->addItem(text);

        text->setDefaultTextColor(Color());

		Scene()->update();
	}
}

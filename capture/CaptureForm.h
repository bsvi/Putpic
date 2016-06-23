#ifndef PUTPIC2_H
#define PUTPIC2_H

#include <QDialog>
#include <QShortcut>
#include "qt_windows.h"

class MyQGraphicsView;
class QGraphicsScene;
class DrawingMenu;
class ToolBase;
class SelectTool;
class LineTool;
class PointerTool;
class ArrowTool;
class TextTool;

class CaptureForm : public QDialog
{
	Q_OBJECT
	QShortcut *escShortcut;
	QShortcut *enterShortcut;
	QShortcut *returnShortcut;
	QShortcut *deleteShortcut;
	QShortcut *ctrlShortcut;

    QPixmap originalPixmap;
	QPixmap darkenPixmap;

	int _x, _y, _w, _h;

public:
	enum Tool {ToolPointer, ToolSelection, ToolBrush, ToolLine, ToolArrow, ToolText };

    CaptureForm(QWidget *parent, QPixmap *image);
	~CaptureForm();

	void setTool(Tool tool);


	bool imageValid;
	QPixmap image;

protected:
	void GrabImages();
    void PrepareImage(QPixmap *image);
	void CreateShortcuts();
	void CreateTools();
	void CreateScene();
	void CreateMenu();

	MyQGraphicsView *view;
	QGraphicsScene* scene; 
	DrawingMenu *drawingMenu;
	
	
	ToolBase *current_tool;
	SelectTool *select_tool;
	LineTool *line_tool;
	PointerTool *pointer_tool;
	ArrowTool *arrow_tool;
	TextTool *text_tool;

public slots:
     void Cancel();
	 void Send();
	 void Delete();
	 void ToggleMenu();

	 void MousePressed(QMouseEvent *event);
	 void MouseReleased(QMouseEvent *event);
	 void MouseMoved(QMouseEvent *event);

};

#endif // PUTPIC2_H

#include "CaptureForm.h"
#include "notifier.h"
#include <QtGui>
#include "qt_windows.h"
#include "myqgraphicsview.h"
#include "Settings.h"
#include <QGraphicsScene>
#include "drawingmenu.h"
#include "SelectTool.h"
#include "LineTool.h"
#include "PointerTool.h"
#include "ArrowTool.h"
#include "TextTool.h"
#include <QPointer>


CaptureForm::CaptureForm(QWidget *parent, QPixmap *image)
	: QDialog(parent, Qt::FramelessWindowHint | Qt::Window | Qt::WindowStaysOnTopHint)
{
    //QDesktopWidget *desktop = QApplication::desktop();
    QScreen *screen = QGuiApplication::primaryScreen();

    _x = screen->geometry().x();
    _y = screen->geometry().y();
    _w = screen->geometry().width();
    _h = screen->geometry().height();
									
	setGeometry(_x, _y, _w, _h);

	current_tool = 0;

	CreateMenu();
    if (image == 0) {
        GrabImages();
    } else {
        PrepareImage(image);
    }
    CreateScene();
	CreateTools();
	CreateShortcuts();

	setCursor(Qt::CrossCursor);

	if (Settings::Instance()->showMenuByDefault()) drawingMenu->show();
	setFocus();
	this->grabKeyboard();
	this->releaseKeyboard();
}


CaptureForm::~CaptureForm() 
{
    delete scene;
    delete view;
	delete select_tool;
}
												

void CaptureForm::Cancel()
{
	imageValid = false;
    drawingMenu->close();
	close();
}


void CaptureForm::Send()
{
	drawingMenu->close();
	imageValid = select_tool->selectionValid();

	if (imageValid)
	{
		scene->clearSelection();
		QRect r = select_tool->selection();
		QPixmap composite = QPixmap::grabWidget(view);

		image = QPixmap(r.width(), r.height());

		QPainter p(&image);
		p.drawPixmap(QPoint(0, 0), composite, r);
		p.end();
	}

	close();
}

void CaptureForm::MousePressed(QMouseEvent *event) { if (current_tool)	current_tool->MousePressed(event); }
void CaptureForm::MouseReleased(QMouseEvent *event) { 	if (current_tool) current_tool->MouseReleased(event); }
void CaptureForm::MouseMoved(QMouseEvent *event) { 	if (current_tool) current_tool->MouseMoved(event); }
void CaptureForm::Delete() { if (current_tool) current_tool->Delete(); }


void CaptureForm::PrepareImage(QPixmap *image) {
    float w_ratio = (float)image->width() / _w;
    float h_ratio = (float)image->height() / _h;
    float scale = qMax(w_ratio, h_ratio);
    QRect r;
    if (scale > 1) {
        r.setWidth(image->width()/scale);
        r.setHeight(image->height()/scale);
    } else {
        r.setWidth(image->width());
        r.setHeight(image->height());
    }
    r.moveCenter(QPoint(_w/2, _h/2));


    QPixmap *screen =  new QPixmap(_w, _h);
    QPainter painter(screen);
    painter.fillRect(0, 0, _w, _h, Qt::black);
    painter.drawPixmap(r, *image, image->rect());
    painter.end();


    originalPixmap = screen->copy();
    darkenPixmap = originalPixmap.copy();
    QPainter qp(&darkenPixmap);
    qp.fillRect(0, 0, _w, _h, QColor(0, 0, 0, 100));
    qp.end();

    delete screen;
}

void CaptureForm::GrabImages()
{
    QScreen *screen = QGuiApplication::primaryScreen();
    originalPixmap = screen->grabWindow(QApplication::desktop()->winId(), _x, _y, _w, _h);
	darkenPixmap = originalPixmap.copy();
	QPainter qp(&darkenPixmap);
    qp.fillRect(0, 0, _w, _h, QColor(0, 0, 0, 100));
	qp.end();
}


void CaptureForm::CreateShortcuts()
{
	// add shortcuts
	escShortcut = new QShortcut(QKeySequence(Qt::Key_Escape), this);
	escShortcut->connect(escShortcut, SIGNAL(activated()),this,SLOT(Cancel()));
	escShortcut->setContext(Qt::ApplicationShortcut);
	
	enterShortcut = new QShortcut(QKeySequence(Qt::Key_Enter), this);
	enterShortcut->connect(enterShortcut, SIGNAL(activated()),this,SLOT(Send()));
	enterShortcut->setContext(Qt::ApplicationShortcut);

	returnShortcut = new QShortcut(QKeySequence(Qt::Key_Return), this);
	returnShortcut->connect(returnShortcut, SIGNAL(activated()),this,SLOT(Send()));
	returnShortcut->setContext(Qt::ApplicationShortcut);

	deleteShortcut = new QShortcut(QKeySequence(Qt::Key_Delete), this);
	deleteShortcut->connect(deleteShortcut, SIGNAL(activated()),this,SLOT(Delete()));
	deleteShortcut->setContext(Qt::ApplicationShortcut);

	ctrlShortcut = new QShortcut(Qt::Key_Tab, this);
	ctrlShortcut->connect(ctrlShortcut, SIGNAL(activated()),this,SLOT(ToggleMenu()));
	ctrlShortcut->setContext(Qt::ApplicationShortcut);
	

}


void CaptureForm::CreateTools()
{
	select_tool = new SelectTool(this, scene, &originalPixmap, drawingMenu);
	line_tool = new LineTool(this, scene, drawingMenu);
	pointer_tool = new PointerTool(this, view, scene, drawingMenu);
	arrow_tool = new ArrowTool(this, scene, drawingMenu);
	text_tool = new TextTool(this, view, scene, drawingMenu);


	current_tool = select_tool;
}

void CaptureForm::CreateScene()
{
	scene = new QGraphicsScene(this);
    scene->addPixmap(darkenPixmap);

	view = new MyQGraphicsView(scene, this);
	view->setGeometry(0, 0, _w, _h);
	view->setStyleSheet( "QGraphicsView { border-style: none; }" );
	view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	//view->setRenderHint(QPainter::Antialiasing, true);
	view->show();

	connect(view, SIGNAL(MousePressed(QMouseEvent *)), this, SLOT(MousePressed(QMouseEvent *)));
	connect(view, SIGNAL(MouseReleased(QMouseEvent *)), this, SLOT(MouseReleased(QMouseEvent *)));
	connect(view, SIGNAL(MouseMoved(QMouseEvent *)), this, SLOT(MouseMoved(QMouseEvent *)));
}


void CaptureForm::CreateMenu()
{
	drawingMenu = new DrawingMenu(this);
	drawingMenu->setGeometry(50, 50, drawingMenu->width(), drawingMenu->height());
	connect(drawingMenu, SIGNAL(MouseReleased(QMouseEvent *)), this, SLOT(MouseReleased(QMouseEvent *)));
	connect(drawingMenu, SIGNAL(MouseMoved(QMouseEvent *)), this, SLOT(MouseMoved(QMouseEvent *)));
	drawingMenu->setSelectionMode(false);
}

void CaptureForm::setTool(Tool tool)
{
	current_tool->Deactivate();

	switch(tool)
	{
	case ToolPointer:
		current_tool = pointer_tool;
		break;

	case ToolSelection:
		current_tool = select_tool;
		break;

	case ToolLine:
		current_tool = line_tool;
		break;

	case ToolArrow:
		current_tool = arrow_tool;
		break;

	case ToolText:
		current_tool = text_tool;
		break;
	}

	current_tool->Activate();
}

void CaptureForm::ToggleMenu()
{
	if (drawingMenu->isVisible())
		drawingMenu->hide();
	else
		drawingMenu->show();
}

#ifndef DRAWINGMENU_H
#define DRAWINGMENU_H

#include <QtGui>
#include "ui_drawingmenu.h"

class CaptureForm;

class DrawingMenu : public QWidget
{
	Q_OBJECT

	CaptureForm *_parent;
	bool _selection_mode;
	int _move_start_x, _move_start_y;

public:
	DrawingMenu(CaptureForm *parent = 0);
	~DrawingMenu();
	void setSelectionMode(bool value);

	QColor color;
	int textSize;
	int lineSize;

private:
	Ui::DrawingMenu ui;

	QLabel *colorLabel;
	QPushButton *colorPicker;
	QLabel *sizeLabel;
	QSlider *sizeSlider;


	void RefreshInterface();
	void HideAllControls();
	void LineMode();
	void TextMode();

	void mousePressEvent(QMouseEvent * e);
    void mouseReleaseEvent(QMouseEvent * e);
	void mouseMoveEvent(QMouseEvent * e);

signals:
	void MouseReleased(QMouseEvent * e);
	void MouseMoved(QMouseEvent * e);

private slots:
	void ModeChanged(bool value);
	void SizeChanged(int value);
	void ColorButton();


};

#endif // DRAWINGMENU_H

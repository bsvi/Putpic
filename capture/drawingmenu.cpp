#include "drawingmenu.h"
#include "CaptureForm.h"
#include "qt_windows.h"
#include <QMouseEvent>
#include <QColorDialog>
#include "Settings.h"

DrawingMenu::DrawingMenu(CaptureForm *parent)
	: QWidget(parent, Qt::Window | Qt::FramelessWindowHint)
{
	_parent = parent;

	ui.setupUi(this);
	connect(ui.pointer, SIGNAL(toggled(bool)), this, SLOT(ModeChanged(bool)));
	connect(ui.selection, SIGNAL(toggled(bool)), this, SLOT(ModeChanged(bool)));
	connect(ui.text, SIGNAL(toggled(bool)), this, SLOT(ModeChanged(bool)));
	connect(ui.line, SIGNAL(toggled(bool)), this, SLOT(ModeChanged(bool)));
	connect(ui.arrow, SIGNAL(toggled(bool)), this, SLOT(ModeChanged(bool)));

	color = Settings::Instance()->favColor();
	textSize = Settings::Instance()->favTextSize();
	lineSize = Settings::Instance()->favLineSize();

	ui.verticalLayout->setAlignment(Qt::AlignTop);
	
	colorLabel = new QLabel("Color:", this);
	ui.verticalLayout->addWidget(colorLabel);

	colorPicker = new QPushButton(this);
	connect(colorPicker, SIGNAL(clicked()), this, SLOT(ColorButton()));
	ui.verticalLayout->addWidget(colorPicker);

	sizeLabel = new QLabel(this);
	ui.verticalLayout->addWidget(sizeLabel);

	sizeSlider = new QSlider(Qt::Horizontal, this);
	connect(sizeSlider, SIGNAL(valueChanged(int)), this, SLOT(SizeChanged(int)));
	ui.verticalLayout->addWidget(sizeSlider);

	setMouseTracking(true);
	setFixedSize(width(), height());

	HideAllControls();
	RefreshInterface();
}

void DrawingMenu::setSelectionMode(bool value)
{
	_selection_mode = value;

	if (_selection_mode)
	{
		setCursor(Qt::CrossCursor);
	}
	else
	{
		setCursor(Qt::ArrowCursor);
	}
}


DrawingMenu::~DrawingMenu()
{

}

void DrawingMenu::mousePressEvent(QMouseEvent * e)
{
	if (_selection_mode) return;

	_move_start_x = e->x();
	_move_start_y = e->y();
}

void DrawingMenu::mouseReleaseEvent(QMouseEvent * e)
{
	if (_selection_mode) emit MouseReleased(e);
}

void DrawingMenu::mouseMoveEvent(QMouseEvent * e)
{
	if (_selection_mode)
		emit MouseMoved(e);
	else
	{
		if (e->buttons() & Qt::LeftButton)
		{
			setGeometry(e->globalX() - _move_start_x, e->globalY() - _move_start_y, this->width(), this->height());
		}
	}
}


void DrawingMenu::ModeChanged(bool value)
{
	HideAllControls();

	if (ui.line->isChecked()) { _parent->setTool(CaptureForm::ToolLine); LineMode();}
	if (ui.selection->isChecked()) _parent->setTool(CaptureForm::ToolSelection);
	if (ui.pointer->isChecked()) _parent->setTool(CaptureForm::ToolPointer);
	if (ui.arrow->isChecked()) { _parent->setTool(CaptureForm::ToolArrow); LineMode(); }
	if (ui.text->isChecked()) {_parent->setTool(CaptureForm::ToolText); TextMode(); }
}

void DrawingMenu::ColorButton()
{
    QColor _color = QColorDialog::getColor(color, this, "Select Color", QColorDialog::DontUseNativeDialog);

    if (color.isValid())
	{
		color = _color;
		Settings::Instance()->setFavColor(color);
		RefreshInterface();
    }
}

void DrawingMenu::SizeChanged(int value)
{
	if (ui.line->isChecked() || ui.arrow->isChecked())
	{
		lineSize = value;
		Settings::Instance()->setFavLineSize(value);
	}
	
	if (ui.text->isChecked())
	{
		textSize = value;
		Settings::Instance()->setFavTextSize(value);
	}

	RefreshInterface();
}


void DrawingMenu::RefreshInterface()
{
    colorPicker->setText(color.name());
    colorPicker->setPalette(QPalette(color));
	colorPicker->setStyleSheet("* { background-color: "+color.name()+"; }");

	sizeLabel->setText("Size = " + QString::number(sizeSlider->value()));
}

void DrawingMenu::HideAllControls()
{
	colorLabel->setVisible(false);
	colorPicker->setVisible(false);
	sizeLabel->setVisible(false);
	sizeSlider->setVisible(false);
}

void DrawingMenu::LineMode()
{
	colorLabel->setVisible(true);
	colorPicker->setVisible(true);
	sizeLabel->setVisible(true);
	sizeSlider->setVisible(true);

	int tmp = lineSize;
	sizeSlider->setMinimum(1);
	sizeSlider->setMaximum(5);
	sizeSlider->setValue(tmp);
}

void DrawingMenu::TextMode()
{
	colorLabel->setVisible(true);
	colorPicker->setVisible(true);
	sizeLabel->setVisible(true);
	sizeSlider->setVisible(true);

	int tmp = textSize;
	sizeSlider->setMinimum(9);
	sizeSlider->setMaximum(72);
	sizeSlider->setValue(tmp);
}
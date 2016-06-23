#include "notifier.h"
#include <qt_windows.h>
#include <QtGui>
#include <QTimer>


Notifier *Notifier::inst = 0;

Notifier::Notifier(QWidget *parent) : QDialog(parent)
{
	setWindowFlags( Qt::Tool | Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowStaysOnTopHint);

    //setAttribute(Qt::WA_TranslucentBackground);
		
	unsigned int width = 200;
	unsigned int height = 50;
	unsigned int space = 10;
	_notifyTimeout = 2000;
	
	unsigned int nDesktopHeight;
	unsigned int nDesktopWidth;
	unsigned int nScreenWidth;
	unsigned int nScreenHeight;
	RECT rcDesktop;

	::SystemParametersInfo(SPI_GETWORKAREA, 0, &rcDesktop,0);

	nDesktopWidth=rcDesktop.right-rcDesktop.left;
	nDesktopHeight=rcDesktop.bottom-rcDesktop.top;
	nScreenWidth=::GetSystemMetrics(SM_CXSCREEN);
	nScreenHeight=::GetSystemMetrics(SM_CYSCREEN);

	bool bTaskbarOnRight=nDesktopWidth<nScreenWidth && rcDesktop.left==0;
	bool bTaskbarOnLeft=nDesktopWidth<nScreenWidth && rcDesktop.left!=0;
	bool bTaskBarOnTop=nDesktopHeight<nScreenHeight && rcDesktop.top!=0;
    bool bTaskbarOnBottom=nDesktopHeight<nScreenHeight && rcDesktop.top==0;

	unsigned int m_nStartPosX, m_nStartPosY;

	if (bTaskbarOnRight)
	{
		m_nStartPosX=rcDesktop.right - width - space;
		m_nStartPosY=rcDesktop.bottom - height - space;
	}
	else if (bTaskbarOnLeft)
	{
		m_nStartPosX=rcDesktop.left  + space;
		m_nStartPosY=rcDesktop.bottom-height - space;
	}
	else if (bTaskBarOnTop)
	{
		m_nStartPosX=rcDesktop.right-width - space;
		m_nStartPosY=rcDesktop.top+space;
	}
    else if (bTaskbarOnBottom)
	{
		m_nStartPosX=rcDesktop.right-width - space;
		m_nStartPosY=rcDesktop.bottom - height - space;
	}


	setGeometry(m_nStartPosX, m_nStartPosY, width, height);

	this->setStyleSheet("background-color: white;");
	
	captionLabel = new QLabel(this);
	captionLabel->setMinimumSize(width, 20);
	captionLabel->setText("Putpic");
	captionLabel->setStyleSheet("background-color : #006699; color : #ffffff; padding-left: 10px; font-weight: bold;");
	captionLabel->show();

	bottomLabel = new QLabel(this);
	bottomLabel->setGeometry(0, height-5, width, 5);
	bottomLabel->setStyleSheet("background-color : #006699;");
	bottomLabel->show();

	notificationLabel = new QLabel(this);
	notificationLabel->setGeometry(10, height/2, width, 15);
	//notificationLabel->setText("Putpicgdfgdgdfgd");
	notificationLabel->show();

	setMouseTracking(true);

	timer = new QTimer(this);
}

Notifier::~Notifier()
{
}

void Notifier::mousePressEvent(QMouseEvent *event)
{
	exit();
}

void Notifier::exit()
{
	hide();
}

void Notifier::ShowMessage(QString message)
{
	notificationLabel->setText(message);

    if (!this->isVisible()) {
        show();
    }
}

void Notifier::HideAfterTimeout()
{
	timer->stop();
	timer->singleShot(_notifyTimeout, this, SLOT(exit()));
}

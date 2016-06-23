#include <QMenu>
#include "tray-icon.h"
#include "optionsform.h"


TrayIcon::TrayIcon(QWidget *parent) : QWidget(parent)
{
	CreateActions();
	CreateTrayIcon();
}


TrayIcon::~TrayIcon(void)
{
	trayIcon->hide();
}


void TrayIcon::CreateActions()
{
    optionsAction = new QAction("Options", this);
    connect(optionsAction, SIGNAL(triggered()), this, SLOT(MenuShowOptionsForm()));

    exitAction = new QAction("Exit", this);
    connect(exitAction, SIGNAL(triggered()), this, SLOT(MenuExit()));
}

void TrayIcon::CreateTrayIcon()
{
	trayIcon = new QSystemTrayIcon(this);

    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(optionsAction);
	trayIconMenu->addSeparator();
    trayIconMenu->addAction(exitAction);

	optionsAction->setParent(trayIconMenu);
	exitAction->setParent(trayIconMenu);

    trayIcon->setIcon(QIcon(":/icons/resources/screenshot.ico"));
	trayIcon->show();

    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
	trayIcon->setContextMenu(trayIconMenu);
}


void TrayIcon::MenuShowOptionsForm()
{
    OptionsForm(this).exec();
};



void TrayIcon::MenuExit()
{
    trayIcon->hide();
    exit(0);
}

void TrayIcon::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::DoubleClick) emit DoubleClick();
}

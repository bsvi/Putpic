#pragma once
#include <QSystemTrayIcon>
#include <QWidget>
#include "mainwindow.h"

class Notifier;

class TrayIcon : public QWidget
{
	Q_OBJECT;

    //static TrayIcon *_tray_icon;
    //MainWindow *_form;

public:

    //static void Dispose() { delete _tray_icon; }

    /*static void AttachTray(MainWindow *form)
	{
		if (_tray_icon == 0) _tray_icon = new TrayIcon(form);
    }*/


    /*static TrayIcon* Instance()
	{
		if (_tray_icon == 0) throw;
		return _tray_icon;
    }*/
    TrayIcon(QWidget *parent);
    ~TrayIcon(void);


protected:
	QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
	QAction *optionsAction;
    QAction *exitAction;

	void CreateActions();
	void CreateTrayIcon();

signals:
    void DoubleClick();


private slots:
	void iconActivated(QSystemTrayIcon::ActivationReason reason);
	void MenuShowOptionsForm();
	void MenuExit();
};


#include "mainwindow.h"
#include "settings.h"
#include "notifier.h"
#include "tray-icon.h"
#include "hookkeyboard.h"
#include "global.h"
#include "capture/CaptureForm.h"
#include "upload/IUploader.h"
#include "serversource.h"

MainWindow *MainWindow::inst = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    captureForm = 0;

    Settings::Instance()->setParent(this);

    icon = new TrayIcon(this);
    connect(icon, SIGNAL(DoubleClick()), this, SLOT(startCapture()));

    HookKeyboard::Instance()->registerHotkey();
    server_source = new ServerSource(this);

    initialize();

}

void MainWindow::initialize()
{
    HookKeyboard::Instance()->unregisterHotkey();
    server_source->stopServer();

    HookKeyboard::Instance()->registerHotkey();

    if (Settings::Instance()->remoteEnable()) {
        server_source->startServer();
    }

    disconnect(HookKeyboard::Instance(), SIGNAL(capturePress()), this, SLOT(startCapture()));
    disconnect(server_source, SIGNAL(ImageRecieved(QPixmap *)), this, SLOT(capture(QPixmap *)));
    connect(HookKeyboard::Instance(), SIGNAL(capturePress()), this, SLOT(startCapture()));
    connect(server_source, SIGNAL(ImageRecieved(QPixmap *)), this, SLOT(capture(QPixmap *)));
}


void MainWindow::capture(QPixmap *pixmap)
{
    try {

        if (captureForm != 0) {


            captureForm->reject();
            delete captureForm;
            captureForm = 0;
        }


        HookKeyboard::Instance()->unregisterHotkey();

        captureForm = new CaptureForm(this, pixmap);
        captureForm->exec();

        if (captureForm != 0 && captureForm->imageValid && askIfUserWantsUpload())
        {
            QString uploader_name = Settings::Instance()->defaultUploader();
            IUploader *uploader = IUploader::CreateByName(uploader_name);
            uploader->Upload(captureForm->image);
            delete uploader;

        }

        delete captureForm;
        captureForm = 0;
        HookKeyboard::Instance()->registerHotkey();

    } catch(...) {
        Notifier::Instance()->ShowMessage("That's an error");
        Notifier::Instance()->HideAfterTimeout();
    }
}


MainWindow::~MainWindow()
{

}


bool MainWindow::askIfUserWantsUpload()
{
    if (Settings::Instance()->askBeforeSend())
    {
        QString appname = appName;
        QMessageBox msgBox(QMessageBox::Question, appName, "Do you really want to upload yout screenshot?", QMessageBox::Yes | QMessageBox::No);
        return msgBox.exec() == QMessageBox::Yes;
    }
    return true;
}


void MainWindow::startCapture() { capture(0); }

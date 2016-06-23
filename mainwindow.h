#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <upload/IUploader.h>

class TrayIcon;
class ServerSource;
class CaptureForm;

class MainWindow : public QMainWindow
{
    Q_OBJECT

    static MainWindow* inst;
    TrayIcon *icon;
    ServerSource *server_source;
    CaptureForm *captureForm;

    bool askIfUserWantsUpload();
    IUploader *uploader;

public:
    static MainWindow *Instance() {
        if (inst == 0) {
            inst = new MainWindow(0);
        }
        return inst;
    }

    MainWindow(QWidget *parent = 0);
    void initialize();
    void uninitialize();
    ~MainWindow();



public slots:
    void startCapture();
    void capture(QPixmap *pixmap);
};

#endif // MAINWINDOW_H

#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "runguard.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(false);

    RunGuard guard( "putpic3" );
    if ( !guard.tryToRun() ) {
        QMessageBox::warning(0, "Warning", "You can't run more than instance of putpic at once");
        return 1;
    }

    //MainWindow w;
    //w.show();
    MainWindow::Instance();

    return a.exec();
}

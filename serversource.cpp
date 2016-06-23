
#include "serversource.h"
#include "notifier.h"
#include "settings.h"
#include "global.h"

ServerSource::ServerSource(QObject *parent) : QObject(parent)
{
    clientSocket = 0;
    buffer = 0;
    timer = new QTimer(this);
    timer->setSingleShot(true);
    connect(timer, SIGNAL(timeout()), this, SLOT(readSlot()));

    tcpServer = new QTcpServer(this);
}


void ServerSource::startServer() {
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(connectSlot()));
    if (!tcpServer->listen(QHostAddress::Any, Settings::Instance()->remotePort()) && server_status==0) {
        qDebug() <<  QObject::tr("Unable to start the server: %1.").arg(tcpServer->errorString());
    }
}

void ServerSource::stopServer()
{
    stop();
    tcpServer->close();
}


void ServerSource::timeout() {
    Notifier::Instance()->ShowMessage("Timeout!");
    stop();
}

void ServerSource::stop()
{
    timer->stop();
    if (clientSocket != 0) {clientSocket->close(); clientSocket->deleteLater(); clientSocket = 0; }
    if (buffer != 0) { delete buffer; buffer = 0;}
    Notifier::Instance()->HideAfterTimeout();
    clientStatus = 0;
}

void ServerSource::connectSlot() {
    Notifier::Instance()->ShowMessage("Remote connection!");

    clientSocket = tcpServer->nextPendingConnection();
    if (clientSocket == 0) {
        Notifier::Instance()->ShowMessage("Connection blocked! (firewall?)");
        Notifier::Instance()->HideAfterTimeout();
        return;
    }

    clientStatus = 0;
    connect(clientSocket, SIGNAL(readyRead()), this, SLOT(readSlot()));
    timer->start(kRemoteConnectionTimeout);
}


void ServerSource::readSlot()
{
    // Get password
    if (clientStatus == 0) {
        char pasword[100];
        int len = clientSocket->readLine(pasword, 100);
        pasword[len-2] = 0;
        QString spassword(pasword);

        if (spassword == Settings::Instance()->remotePassword() ) {
            clientSocket->write("ok\n");
            Notifier::Instance()->ShowMessage("Password accepted.");
            clientStatus = 1;
        } else {
            clientSocket->write("no\n");
            Notifier::Instance()->ShowMessage("Password declined.");
            stop();
        }
        return;
    }

    // Get size
    if (clientStatus == 1) {
        char size[12];
        int len = clientSocket->readLine(size, 10);
        if (len == 0) return;
        if (len > 10) return;
        size[len-2] = 0;
        bytesExpected = QString(size).toInt();
        bytesTotal = bytesExpected;

        Notifier::Instance()->ShowMessage("Size :" + QString(size));

        buffer = new QByteArray();
        clientStatus = 2;
        return;
    }

    // Get data
    if (clientStatus == 2) {
        QByteArray chunk = clientSocket->readAll();
        buffer->append(chunk);
        bytesExpected -= chunk.size();
        qDebug() << "Received chunk of:" << chunk.size();

        float percent = 100.0f * (float)(bytesTotal-bytesExpected)/(float)bytesTotal;
        QString sPercent;
        sPercent.sprintf("%.1f", percent);
        Notifier::Instance()->ShowMessage("Receiving: " + sPercent + "%");

        if (bytesExpected <= 0) {
            clientSocket->write("Thank you!");
            clientSocket->waitForBytesWritten(1000);

            QPixmap *pic = new QPixmap();
            pic->loadFromData(*buffer, "JPG");
            stop();
            emit ImageRecieved(pic);
        }


        return;
    }

}




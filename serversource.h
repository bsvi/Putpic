#ifndef SERVERSOURCE_H
#define SERVERSOURCE_H

#include <QObject>
#include <QtNetwork>
#include <QTcpSocket>
#include <QByteArray>
#include <QDebug>

class ServerSource : public QObject
{
    Q_OBJECT
    int server_status;
    QTcpSocket *clientSocket;
    int clientStatus;
    QTcpServer *tcpServer;

    QByteArray *buffer;

    int bytesExpected;
    int bytesTotal;
    void processImage();

    QTimer *timer;
public:
    ServerSource(QObject *parent);

    void startServer();
    void stopServer();

    void stop();

signals:
    void ImageRecieved(QPixmap *pic);

public slots:
    void timeout();

private slots:
    void connectSlot();
    void readSlot();
};

#endif // SERVERSOURCE_H

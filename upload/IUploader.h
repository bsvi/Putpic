#pragma once

#include <QString>
#include <QPixmap>
#include <QObject>
#include "ImgSaver.h"

class QNetworkReply;
class QEventLoop;

class IUploader : public QObject
{
	Q_OBJECT;

    QEventLoop *loop;
    QNetworkReply *reply;

public:

	virtual bool Upload(const QPixmap &img) = 0;

	IUploader();
	~IUploader(void);

	static IUploader *CreateByName(QString name);

protected:
    ImgSaver *saver;
    bool uploadFile(QString url, QString file);

private slots:
	void replyFinished(QNetworkReply* reply);
	void uploadProgress( qint64 bytesSent, qint64 bytesTotal);
    void timeout();
};


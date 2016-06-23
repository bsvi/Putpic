#include <QHttpPart>
#include <QFile>
#include <QFileInfo>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QClipboard>
#include <QApplication>
#include "IUploader.h"
#include "FileUploader.h"
#include "BsviRuUploader.h"
#include "CustomServerUploader.h"
#include "notifier.h"


IUploader::IUploader()
{
    Notifier::Instance()->ShowMessage("Prepairing...");
    saver = new ImgSaver();
    loop = new QEventLoop(this);
}


IUploader::~IUploader(void)
{
    Notifier::Instance()->HideAfterTimeout();
    delete saver;
}


bool IUploader::uploadFile(QString url, QString filename)
{
	QFileInfo fi(filename);
	QString format = fi.suffix();
	QString filename_clear = fi.fileName();

	QString bound="---- asdfljkhaslkjghdjkb"; //name of the boundary

    QByteArray data(QString("--" + bound + "\r\n").toLatin1());
	data.append("Content-Disposition: form-data; name=\"action\"\r\n\r\n");    
	data.append("put.php\r\n");
	data.append("--" + bound + "\r\n");   //according to rfc 1867
	data.append("Content-Disposition: form-data; name=\"file\"; filename=\""+filename_clear+"\"\r\n");  //name of the input is "uploaded" in my form, next one is a file name.
	
	if (format == "jpg")
		data.append("Content-Type: image/jpeg\r\n\r\n"); //data type
	else
		data.append("Content-Type: image/png\r\n\r\n"); //data type
	
	QFile file(filename);
	if (!file.open(QIODevice::ReadOnly)) return false;

	data.append(file.readAll());   //let's read the file
	data.append("\r\n");
	data.append("--" + bound + "--\r\n");  //closing boundary according to rfc 1867

    QNetworkRequest request = QNetworkRequest(QUrl(url));
    request.setRawHeader(QString("Content-Type").toLatin1(),QString("multipart/form-data; boundary=" + bound).toLatin1());
    request.setRawHeader(QString("Content-Length").toLatin1(), QString::number(data.length()).toLatin1());


    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    reply = manager->post(request, data);
    QTimer *timer = new QTimer(reply);
    timer->setSingleShot(true);;
    timer->start(5000);


    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));

    // loop is used to block thread while transfer is in progress
    loop->connect(manager, SIGNAL(finished(QNetworkReply*)), SLOT(quit()));
    loop->connect(reply, SIGNAL(uploadProgress(qint64,qint64)), this, SLOT(uploadProgress(qint64,qint64)));
    loop->connect(timer, SIGNAL(timeout()), this, SLOT(timeout()) );
    loop->exec();

    return true;
}

void IUploader::timeout()
{
    Notifier::Instance()->ShowMessage("Timeout...");
    reply->close();
    reply->deleteLater();
    reply->manager()->deleteLater();
    loop->quit();
}


void IUploader::replyFinished(QNetworkReply* reply)
{
	if (!reply->error())
	{
		QString answer = QString::fromUtf8(reply->readAll());

		if (answer == "error: no file transfered")
		{
            Notifier::Instance()->ShowMessage("Error: upload failed!");
		}
		else
		{
			QClipboard *clipboard = QApplication::clipboard();
	
			clipboard->setText(answer, QClipboard::Clipboard);
			clipboard->setText(answer, QClipboard::Selection);

            Notifier::Instance()->ShowMessage("Your link is copied to clipboard");
		}
		
	}
	else
	{
        Notifier::Instance()->ShowMessage("Error: upload failed!");
	}

    reply->deleteLater();
	reply->manager()->deleteLater();
}


void IUploader::uploadProgress( qint64 bytesSent, qint64 bytesTotal)
{
	float percent = 100.0f * (float)bytesSent/(float)bytesTotal;
	QString sPercent;
	sPercent.sprintf("%.1f", percent);

    Notifier::Instance()->ShowMessage("Uploading: " + sPercent + "%" );
}




IUploader *IUploader::CreateByName(QString name)
{
	if (name == "Save to file") return new FileUploader();
	if (name == "Upload to bsvi.ru") return new BsviRuUploader();
	if (name == "Upload to custom server") return new CustomServerUploader();

	return new FileUploader();
}

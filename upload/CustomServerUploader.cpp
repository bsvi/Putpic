#include "CustomServerUploader.h"
#include "ImgSaver.h"
#include <QPixmap>
#include "Settings.h"
#include <QMessagebox>
#include <QClipboard>
#include <QApplication>
#include "global.h"
#include <QRegExp>


QString CustomServerUploader::ExtractDirectLink(QString txt)
{
	QRegExp reg("/pp([0-9]{1})([0-9]{2})([0-9]{2})([0-9]{2})([0-9a-z]{6})$");
	if (reg.indexIn(txt))
	{
		QString extension = reg.cap(1) == "1" ? ".jpg" : ".png";
		QString result = Settings::Instance()->customServerUrl() + QString("upload/") + QString("20") + reg.cap(4) + "_" + reg.cap(3) + "_" + reg.cap(2) + "/" + reg.cap(5) + extension;
		return result;
	}
	return "";
}

void CustomServerUploader::ReplaceWithDirectLinkIfRequired()
{
	if (Settings::Instance()->customServerDirectLink())
	{
		QClipboard *clipboard = QApplication::clipboard();
		QString txt = clipboard->text(QClipboard::Clipboard);
		if (txt != "")
		{
			QString answer = ExtractDirectLink(txt);

			if (answer != "")
			{
				clipboard->setText(answer, QClipboard::Clipboard);
				clipboard->setText(answer, QClipboard::Selection);
			}
		}
	}
}

bool CustomServerUploader::Upload(const QPixmap &img)
{
    saver->setQuality(Settings::Instance()->customServerQuality());
    saver->Save(img);

	QString url = Settings::Instance()->customServerUrl() + "put.php";

    if (uploadFile(url, saver->filename()))
	{
		ReplaceWithDirectLinkIfRequired();
	}

    saver->Delete();
	return true;
}

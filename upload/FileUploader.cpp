#include "FileUploader.h"
#include "ImgSaver.h"
#include <QPixmap>
#include <QString>
#include <Settings.h>
#include <QMessageBox>
#include "global.h"
#include "Notifier.h"



bool FileUploader::Upload(const QPixmap &img)
{
	if (Settings::Instance()->saveToFilePath() == "choose")
	{
        Notifier::Instance()->ShowMessage("Choose directory in options.");
		return false;
	}
	

    saver->setDir(Settings::Instance()->saveToFilePath());
    saver->setQuality(Settings::Instance()->saveToFileQuality());

    saver->Save(img);

    Notifier::Instance()->ShowMessage("Saved to " + saver->filename());

	return true;
}

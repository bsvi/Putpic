#include "BsviRuUploader.h"
#include "ImgSaver.h"
#include <QPixmap>


bool BsviRuUploader::Upload(const QPixmap &img)
{
    saver->setQuality(85);
    saver->Save(img);

    uploadFile("http://bsvi.ru/putpic/put.php", saver->filename());

    saver->Delete();
    return true;
}

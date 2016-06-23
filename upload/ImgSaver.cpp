#include "ImgSaver.h"
#include <QDir>
#include <QPixmap>
#include <QFileInfo>


ImgSaver::ImgSaver(void)
{
	prev_filename = "";
	_quality = -1;
}


ImgSaver::~ImgSaver(void)
{
}

void ImgSaver::Delete()
{
	if (prev_filename != "") QFile::remove(prev_filename);
}

QString ImgSaver::PrepareDir(QString dir)
{
	if (dir == "") dir = QDir::tempPath();
	QDir(dir).mkpath(".");

	return dir;
}


int ImgSaver::FindNextUnusedFileNum(QString dir)
{
	QDir save_dir(dir);
	QFileInfoList list = save_dir.entryInfoList();

	int max_file_id = 0;
	foreach (QFileInfo f, list)
	{
       if (f.isFile())
	   {
		   int current_file_id = f.baseName().toInt();
		   if (current_file_id > max_file_id) max_file_id = current_file_id;
	   }
    }

	max_file_id++;

	return max_file_id;
}

QString ImgSaver::GetExtension(const QImage &img)
{
	int colorCount = img.colorCount();
	if (colorCount < 256)
		return "png";
	else
		return "jpg";
}


bool ImgSaver::Save(const QPixmap &img)
{
	QString prepared_dir = PrepareDir(_dir);
	int next_file_id = FindNextUnusedFileNum(prepared_dir);

	if (prepared_dir.right(1) != "/") prepared_dir += "/";

	// подготоавливаем картинку с индексированным цветом, чтобы посчитать количество цветов
	QImage image = img.toImage();
	QImage indexed_image = image.convertToFormat(QImage::Format_Indexed8);
	
	prev_ext = GetExtension(indexed_image);

	QString next_filename = prepared_dir + QString("%1").arg(next_file_id)+"."+prev_ext;


	if (prev_ext == "jpg")
	{
		img.save(next_filename, 0, _quality);
	}
	else
	{
		indexed_image.save(next_filename);
	}
	
	prev_filename = next_filename;

	return true;
}
#pragma once
#include <QString>
class QImage;
class QPixmap;

class ImgSaver
{
	QString prev_filename;
	QString prev_ext;

	int _quality;
	QString _dir;
	
public:
	bool Save(const QPixmap &img);
	void Delete();

	QString filename() { return prev_filename; }
	QString extension() { return prev_ext; }

	
	void setDir(QString dir) { _dir = dir; };
	void setQuality(int quality) { _quality = quality; };

	ImgSaver(void);
	~ImgSaver(void);

protected:
	QString GetExtension(const QImage &img);
	QString PrepareDir(QString dir);
	int FindNextUnusedFileNum(QString dir);

};


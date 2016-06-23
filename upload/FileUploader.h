#pragma once
#include "IUploader.h"
#include <QString>

class FileUploader : public IUploader
{
public:
	bool Upload(const QPixmap &img);
};


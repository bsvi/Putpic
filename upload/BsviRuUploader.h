#pragma once
#include "IUploader.h"

class BsviRuUploader : public IUploader
{
public:
	bool Upload(const QPixmap &img);
};

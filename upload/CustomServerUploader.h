#ifndef CUSTOMSERVERUPLOADER_H
#define CUSTOMSERVERUPLOADER_H

#include <QObject>
#include "IUploader.h"

class CustomServerUploader : public IUploader
{
	Q_OBJECT

public:

	bool Upload(const QPixmap &img);

private:
	QString ExtractDirectLink(QString txt);
	void ReplaceWithDirectLinkIfRequired();

};

#endif // CUSTOMSERVERUPLOADER_H

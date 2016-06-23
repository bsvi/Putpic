#include "settings.h"
#include "global.h"

Settings *Settings::inst = 0;
QSettings *Settings::settings = 0;

Settings* Settings::Instance()
{
    if (settings == 0)
    {
        inst = new Settings(0);
    }
	return inst;
}


bool Settings::autorun()
{
	QSettings settings("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
	return settings.value(appName, "").toString()  != "";
}

void Settings::setAutorun(bool value)
{
	QSettings settings("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);

	if (value) {
		QString value = QCoreApplication::applicationFilePath(); //get absolute path of running exe
		QString apostroph = "\"";
		value.replace("/","\\");
		value = apostroph + value + apostroph;

		settings.setValue(appName, value);
	}
	else
	{
		settings.remove(appName);
	}
}

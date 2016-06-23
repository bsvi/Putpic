#include <QSettings>
#include <QApplication>
#include <QColor>
#include <QObject>
#include <QDir>
#include "qt_windows.h"


class Settings : public QObject
{
	Q_OBJECT
	static Settings *inst;
	static QSettings *settings;

public:
	static Settings  *Instance();
	QString to_bool(bool value) { return value ? "true" : "false"; }

	bool autorun();
	void setAutorun(bool value);

    bool remoteEnable() { return settings->value("remoteEnable", "false") == "true"; }
    void setRemoteEnable(bool value) { settings->setValue("remoteEnable", to_bool(value)); }

    int remotePort() { return settings->value("remotePort", 33333).toInt(); }
    void setRemotePort(int value) { settings->setValue("remotePort", value); }

    QString remotePassword() { return settings->value("remotePassword", "qweqwe").toString(); }
    void setRemotePassword(QString value) { settings->setValue("remotePassword", value); }



	bool askBeforeSend() { return settings->value("AskBeforeSend", "false") == "true"; }
	void setAskBeforeSend(bool value) { settings->setValue("AskBeforeSend", to_bool(value)); }

	QString defaultUploader() { return settings->value("DefaultUploader", "Upload to bsvi.ru").toString(); }
	void setDefaultUploader(QString value) { settings->setValue("DefaultUploader", value); }

	QString saveToFilePath() { return settings->value("SaveToFilePath", "choose").toString(); }
	void setSaveToFilePath(QString value) { settings->setValue("SaveToFilePath", value); }

	int saveToFileQuality() { return settings->value("SaveToFileQuality", 100).toInt(); }
	void setSaveToFileQuality(int value) { settings->setValue("SaveToFileQuality", value); }

	bool checkUpdates() { return settings->value("CheckUpdates", "true") == "true"; }
	void setCheckUpdates(bool value) { settings->setValue("CheckUpdates", to_bool(value)); }

	QColor favColor() { return (QColor)settings->value("FavColor", "#ff0000").toString(); }
	void setFavColor(QColor value) { settings->setValue("FavColor", value); }

	int favLineSize() { return settings->value("FavLineSize", 2).toInt(); }
	void setFavLineSize(int value) { settings->setValue("FavLineSize", value); }

	int favTextSize() { return settings->value("FavTextSize", 12).toInt(); }
	void setFavTextSize(int value) { settings->setValue("FavTextSize", value); }

	bool showMenuByDefault() { return settings->value("ShowMenuByDefault", "true") == "true"; }
	void setShowMenuByDefault(bool value) { settings->setValue("ShowMenuByDefault", to_bool(value)); }

	bool doubleClickDrawing() { return settings->value("DoubleClickDrawing", "false") == "true"; }
	void setDoubleClickDrawing(bool value) { settings->setValue("DoubleClickDrawing", to_bool(value)); }

	int hotkeyMod() { return settings->value("HotkeyMod", MOD_CONTROL | MOD_SHIFT).toInt(); }
	void setHotkeyMod(int value) { settings->setValue("HotkeyMod", value); }

	int hotkey() { return settings->value("Hotkey", VK_SNAPSHOT).toInt(); }
	void setHotkey(int value) { settings->setValue("Hotkey", value); }

	QString hotkeyTxt() { return settings->value("HotkeyTxt", "ctrl + shift + print screen").toString(); }
	void setHotkeyTxt(QString value) { settings->setValue("HotkeyTxt", value); }


	QString serial() { return settings->value("Serial", "").toString(); }
	void setSerial(QString value) { settings->setValue("Serial", value); }

	// Custom server
	QString customServerUrl() { return settings->value("CustomServerUrl", "http://bsvi.ru/putpic/").toString(); }
	void setCustomServerUrl(QString value) { settings->setValue("CustomServerUrl", value); }

	unsigned int customServerQuality() { return settings->value("CustomServerQuality", 90).toUInt(); }
	void setCustomServerQuality(unsigned int value) { settings->setValue("CustomServerQuality", value); }

	bool customServerDirectLink() { return settings->value("CustomServerDirectLink", "false") == "true"; }
	void setCustomServerDirectLink(bool value) { settings->setValue("CustomServerDirectLink", to_bool(value)); }

private:
	Settings(QObject *parent)  : QObject(parent)
	{
		QString path = QDir::homePath () + "/Application Data/Putpic/putpic.ini";
		settings = new QSettings(path, QSettings::IniFormat);
	}

	~Settings() { delete settings; }

	Settings(const Settings&);
	Settings& operator= (const Settings&);
};

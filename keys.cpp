#include "keys.h"
#include "qt_windows.h"
#include <QMap>
#include <QString>
#include <QStringList>

Keys::Keys(QObject *parent) : QObject(parent)
{

	AddPlain(&keys, 0x30, 0x39); //	numbers
	AddPlain(&keys, 0x41, 0x5A); //	letters

	keys[VK_SPACE] = "space";
	keys[VK_ESCAPE] = "escape";
	keys[VK_F1] = "f1";
	keys[VK_F2] = "f2";
	keys[VK_F3] = "f3";
	keys[VK_F4] = "f4";
	keys[VK_F5] = "f5";
	keys[VK_F6] = "f6";
	keys[VK_F7] = "f7";
	keys[VK_F8] = "f8";
	keys[VK_F9] = "f9";
	keys[VK_F10] = "f10";
	keys[VK_F11] = "f11";
	keys[VK_F12] = "f12";

	keys[VK_SNAPSHOT] = "print screen";
	keys[VK_PAUSE] = "pause";
	keys[0x03] = "break";
	keys[VK_SCROLL] = "scroll lock";

	keys[VK_BACK] = "backspace";
	keys[VK_TAB] = "tab";
	keys[VK_RETURN] = "return";


	keys[VK_INSERT] = "insert";
	keys[VK_DELETE] = "delete";
	keys[VK_HOME] = "home";
	keys[VK_END] = "end";
	keys[VK_PRIOR] = "page up";
	keys[VK_NEXT] = "page down";

	keys[VK_LEFT] = "left";
	keys[VK_RIGHT] = "right";
	keys[VK_UP] = "up";
	keys[VK_DOWN] = "down";

	keys[VK_NUMLOCK] = "num lock";	
	keys[VK_NUMPAD0] = "numpad0";
	keys[VK_NUMPAD1] = "numpad1";
	keys[VK_NUMPAD2] = "numpad2";
	keys[VK_NUMPAD3] = "numpad3";
	keys[VK_NUMPAD4] = "numpad4";
	keys[VK_NUMPAD5] = "numpad5";
	keys[VK_NUMPAD6] = "numpad6";
	keys[VK_NUMPAD7] = "numpad7";
	keys[VK_NUMPAD8] = "numpad8";
	keys[VK_NUMPAD9] = "numpad9";
	keys[VK_MULTIPLY] = "multiply";
	keys[VK_DIVIDE] = "divide";
	keys[VK_ADD] = "add";
	keys[VK_SUBTRACT] = "subtract";
	keys[VK_SEPARATOR] = "separator";
	keys[VK_DECIMAL] = "decimal";

	keys[VK_SLEEP] = "sleep";
	keys[VK_VOLUME_MUTE] = "mute";
	keys[VK_VOLUME_UP] = "volume_up";
	keys[VK_VOLUME_DOWN] = "volume_down";
	keys[VK_MEDIA_NEXT_TRACK] = "next track";
	keys[VK_MEDIA_PREV_TRACK] = "prev track";
	keys[VK_MEDIA_STOP] = "stop";
	keys[VK_MEDIA_PLAY_PAUSE] = "play/pause";
	keys[VK_LAUNCH_MAIL] = "mail";
	keys[VK_LAUNCH_MEDIA_SELECT] = "select";
	keys[VK_LAUNCH_APP1] = "app1";
	keys[VK_LAUNCH_APP2] = "app2";

	keys[VK_BROWSER_BACK] = "browser back";
	keys[VK_BROWSER_FORWARD] = "browser forward";
	keys[VK_BROWSER_REFRESH] = "browser refresh";
	keys[VK_BROWSER_STOP] = "browser stop";
	keys[VK_BROWSER_SEARCH] = "browser search";
	keys[VK_BROWSER_FAVORITES] = "browser favorites";
	keys[VK_BROWSER_HOME] = "browser home";
}

Keys::~Keys()
{
}


void Keys::AddPlain(QMap<int, QString> *keys, int form, int to)
{
	for(int i=form; i<=to; i++)
	{
		char symb[2];
		symb[0] = i;
		symb[1] = 0;
        keys->insert(i, QString::fromLatin1(symb));
	}
}

QString Keys::GetModKeysNames(Qt::KeyboardModifiers mod)
{
	QStringList strKeys;

	if (mod & Qt::ControlModifier ) strKeys.push_back("Ctrl");
	if (mod & Qt::AltModifier) strKeys.push_back("Alt");
	if (mod & Qt::ShiftModifier) strKeys.push_back("Shift");

	//int remainder = modKeys & ~(MOD_CONTROL | MOD_SHIFT | MOD_ALT | MOD_WIN);
	//if (remainder) strKeys.push_back(QString::number(remainder));

	return strKeys.join(" + ");
}

int Keys::GetSysModKeys(Qt::KeyboardModifiers modKeys)
{
	int mod = 0;
	if (modKeys & Qt::ControlModifier ) mod |= MOD_CONTROL;
	if (modKeys & Qt::AltModifier) mod |= MOD_ALT;
	if (modKeys & Qt::ShiftModifier) mod |= MOD_SHIFT;

	return mod;
}


QString Keys::GetKeysName(int vk_key)
{
	QString key_name = keys[vk_key];
	if (key_name.isEmpty() && vk_key)
	{
		key_name = QString::number(vk_key);
	}

	return key_name;
}

#include <QDebug>
#include <QKeyEvent>
#include <QApplication>
#include <qt_windows.h>
#include "HotkeyEditor.h"
#include "keys.h"


HotkeyEditor::HotkeyEditor(QWidget *parent)
	: QPlainTextEdit(parent)
{
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	setMaximumSize(10000, 24);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	keys = new Keys(this);
}

void HotkeyEditor::keyPressEvent(QKeyEvent* event)
{
    qDebug() << "keypress" << event->key() << " " << event->modifiers() <<":" <<event->nativeVirtualKey() << ":"<<  event->nativeVirtualKey();

	QString text;
	int vk = event->nativeVirtualKey();
	if (event->key() == VK_SNAPSHOT) vk = VK_SNAPSHOT;

	QString key_name = keys->GetKeysName(vk);
	QString mod_key_name = keys->GetModKeysNames(event->modifiers());

	if (key_name.isEmpty() || vk == VK_MENU || vk == VK_CONTROL || vk == VK_SHIFT)
	{
		_current_key = 0;
		_current_mod = 0;
		setPlainText(mod_key_name + " + none (invalid)");
	}
	else if (mod_key_name.isEmpty())
	{
		_current_key = vk;
		_current_mod = 0;
		setPlainText( key_name);
	}
	else
	{
		_current_key = vk;
		_current_mod = keys->GetSysModKeys(event->modifiers());
		setPlainText( mod_key_name + " + " + key_name);
	}
}

void HotkeyEditor::hoockKeyPress(QKeyEvent *hook_key) {
    keyPressEvent(hook_key);
}

void HotkeyEditor::focusInEvent ( QFocusEvent * event )
{	
    connect(HookKeyboard::Instance(), SIGNAL(keyPress(QKeyEvent *)), this, SLOT( hoockKeyPress(QKeyEvent *)) );
    HookKeyboard::Instance()->startHook();
	QPlainTextEdit::focusInEvent ( event );
}

void HotkeyEditor::focusOutEvent ( QFocusEvent * event )
{
    disconnect(HookKeyboard::Instance(), SIGNAL(keyPress(QKeyEvent *)));
    HookKeyboard::Instance()->endHook();
    QPlainTextEdit::focusOutEvent ( event );
}


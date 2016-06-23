#ifndef HOTKEYEDITOR_H
#define HOTKEYEDITOR_H

#include <QPlainTextEdit>
#include "hookkeyboard.h"

class Keys;

class HotkeyEditor : public QPlainTextEdit
{
	Q_OBJECT

public:
	HotkeyEditor(QWidget *parent);

	int hotkey() { return _current_key; };
	int mod() {return _current_mod; }

	void setHotkey(int hotkey) { _current_key = hotkey; };
	void setMod(int mod) {_current_mod = mod; }

	void keyPressEvent(QKeyEvent* event);

private slots:
    void hoockKeyPress(QKeyEvent *hook_key);

private:
	
	void focusInEvent ( QFocusEvent * event );
	void focusOutEvent ( QFocusEvent * event );
	
	Keys *keys;

    int _current_key;
	int _current_mod;
	QString _current_str;
};

#endif // HOTKEYEDITOR_H

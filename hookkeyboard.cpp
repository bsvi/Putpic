#include <QDebug>
#include <QApplication>
#include <QKeyEvent>
#include "hookkeyboard.h"
#include "settings.h"

HookKeyboard *HookKeyboard::inst = 0;

HookKeyboard::HookKeyboard(QWidget *parent) : QDialog(parent) {
    m_hook_mode = false;
}


void HookKeyboard::startHook()
{
    unregisterHotkey();
    m_hook_mode = true;
    RegisterHotKey((HWND)winId(), 0, 0, VK_SNAPSHOT);
    RegisterHotKey((HWND)winId(), 1, MOD_CONTROL | MOD_SHIFT, VK_SNAPSHOT);
    RegisterHotKey((HWND)winId(), 2, MOD_CONTROL | MOD_ALT, VK_SNAPSHOT);
    RegisterHotKey((HWND)winId(), 3, MOD_SHIFT | MOD_ALT, VK_SNAPSHOT);
    RegisterHotKey((HWND)winId(), 4, MOD_SHIFT | MOD_ALT | MOD_CONTROL, VK_SNAPSHOT);
}


void HookKeyboard::endHook()
{
    for (int i=0; i<5; i++) UnregisterHotKey((HWND)winId(), i);
    m_hook_mode = false;
    registerHotkey();
}


void HookKeyboard::registerHotkey() { RegisterHotKey((HWND)winId(), 0, Settings::Instance()->hotkeyMod(), Settings::Instance()->hotkey()); }
void HookKeyboard::unregisterHotkey() { UnregisterHotKey((HWND)winId(), 0); }


bool HookKeyboard::nativeEvent(const QByteArray & eventType, void * message, long *result)
{
    MSG *msg = reinterpret_cast<MSG*>(message);
    if (msg->message == WM_HOTKEY)
    {
        if (m_hook_mode) {
            unsigned int mods = (unsigned int)Qt::NoModifier;
            mods |= msg->lParam & MOD_ALT ? (unsigned int)Qt::AltModifier : 0;
            mods |= msg->lParam & MOD_CONTROL ? (unsigned int)Qt::ControlModifier : 0;
            mods |= msg->lParam & MOD_SHIFT ? (unsigned int)Qt::ShiftModifier : 0;
            mods |= msg->lParam & MOD_WIN ? (unsigned int)Qt::MetaModifier : 0;
            Qt::KeyboardModifier mod = (Qt::KeyboardModifier)mods;


            QKeyEvent e(QKeyEvent::KeyPress, VK_SNAPSHOT, mod);
            emit keyPress(&e);

        } else {
            emit capturePress();
        }

        return true;
    }

    return false;
}


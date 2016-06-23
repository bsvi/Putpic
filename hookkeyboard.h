#ifndef HOOKKEYBOARD_H
#define HOOKKEYBOARD_H

#include <QDialog>
#include <qt_windows.h>

class HookKeyboard : public QDialog
{
    Q_OBJECT
    bool m_hook_mode;
    static HookKeyboard *inst;

    public:
        static HookKeyboard  *Instance() {
            if (inst == 0)
            {
                inst = new HookKeyboard(0);
            }
            return inst;
        }

        void registerHotkey();
        void unregisterHotkey();

        void startHook();
        void endHook();



    protected:
        HookKeyboard(QWidget *parent = 0);
        bool nativeEvent(const QByteArray & eventType, void * message, long *result);

     signals:
        void keyPress(QKeyEvent *hook_key);
        void capturePress();
};

#endif // HOOKKEYBOARD_H

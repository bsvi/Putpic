#ifndef NOTIFIER_H
#define NOTIFIER_H

#include <QtWidgets>

class Notifier : public QDialog
{
	Q_OBJECT
    static Notifier *inst;

public:
    static Notifier *Instance() {
        if (inst == 0) {
            inst = new Notifier(0);
        }
        return inst;
    }

	Notifier(QWidget *parent);
	~Notifier();

	void HideAfterTimeout();
    void ShowMessage(QString message);

private:
	QLabel *captionLabel;
	QLabel *notificationLabel;
	QLabel *bottomLabel;
    QTimer *timer;

	int _notifyTimeout;

	void mousePressEvent(QMouseEvent *event);

private slots:
	void exit();


};

#endif // NOTIFIER_H

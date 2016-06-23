#ifndef KEYS_H
#define KEYS_H

#include <QObject>
#include <QMap>
#include <QString>
#include <QKeyEvent>

class Keys : public QObject
{
	Q_OBJECT

	QMap<int, QString> keys;

public:
	QString GetModKeysNames(Qt::KeyboardModifiers modKeys);
	int GetSysModKeys(Qt::KeyboardModifiers modKeys);

	QString GetKeysName(int key);

	Keys(QObject *parent);
	~Keys();

private:
	void AddPlain(QMap<int, QString> *keys, int form, int to);
};

#endif // KEYS_H

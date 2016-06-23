#ifndef MYQGRAPHICSVIEW_H
#define MYQGRAPHICSVIEW_H

#include <QObject>

#include <QGraphicsView>
#include <QMouseEvent>

class MyQGraphicsView : public QGraphicsView
{
    Q_OBJECT

	bool _passMessages;
public:
    explicit MyQGraphicsView(QGraphicsScene *scene, QWidget *parent = 0);
	void setMessagePassing(bool value) { _passMessages = value; }

signals:

public slots:
    void mousePressEvent(QMouseEvent * e);
	void mouseReleaseEvent(QMouseEvent * e);
	void mouseMoveEvent(QMouseEvent * e);

signals:
	void MousePressed(QMouseEvent * e);
	void MouseReleased(QMouseEvent * e);
	void MouseMoved(QMouseEvent * e);
};

#endif // MYQGRAPHICSVIEW_H

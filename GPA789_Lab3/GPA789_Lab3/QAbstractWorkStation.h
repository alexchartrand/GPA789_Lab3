#ifndef QABSTRACTWORKSTATION_H
#define QABSTRACTWORKSTATION_H

#include <QGraphicsItem>

class QAbstractWorkStation : public QGraphicsItem
{

public:
	QAbstractWorkStation(int x, int y, int width, int height, QWidget *parent = nullptr);
	~QAbstractWorkStation();

protected:
	QSize mSize;
	QPoint mPos;
};

#endif // QABSTRACTWORKSTATION_H

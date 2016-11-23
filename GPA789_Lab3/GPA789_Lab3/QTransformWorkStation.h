#ifndef QTRANSFORMWORKSTATION_H
#define QTRANSFORMWORKSTATION_H

#include "QAbstractWorkStation.h"

class QTransformWorkStation : public QAbstractWorkStation
{

public:
	QTransformWorkStation(int x, int y, int width, int height, QWidget *parent = nullptr);
	~QTransformWorkStation();

	QRectF boundingRect() const override { return QRect(mPos, mSize); }
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
private:
	
};

#endif // QTRANSFORMWORKSTATION_H

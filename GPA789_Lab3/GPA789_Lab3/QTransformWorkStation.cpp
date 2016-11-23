#include "QTransformWorkStation.h"

#include <QPainter>

QTransformWorkStation::QTransformWorkStation(int x, int y, int width, int height, QWidget *parent)
	: QAbstractWorkStation(x, y, width, height)
{

}

QTransformWorkStation::~QTransformWorkStation()
{

}


void QTransformWorkStation::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	painter->drawRoundRect(QRect(mPos, mSize));
}

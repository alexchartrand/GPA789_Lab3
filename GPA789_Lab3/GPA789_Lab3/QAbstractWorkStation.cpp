#include "QAbstractWorkStation.h"

#include <QPainter>

QAbstractWorkStation::QAbstractWorkStation(int x, int y, int width, int height, QWidget *parent)
	: QGraphicsItem(), mPos(x, y), mSize(width, height)
{
	mColor = Qt::blue;
	mWorkingSpeed = 1000;
}

QAbstractWorkStation::~QAbstractWorkStation()
{

}

void QAbstractWorkStation::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	painter->setPen(QPen(mColor));
	painter->drawRect(QRect(mPos, mSize));
	painter->fillRect(QRect(mPos, mSize), QBrush(mColor, Qt::SolidPattern));
}


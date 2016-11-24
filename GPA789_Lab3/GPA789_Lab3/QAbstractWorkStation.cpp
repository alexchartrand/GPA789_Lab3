#include "QAbstractWorkStation.h"

#include <QPainter>

QAbstractWorkStation::QAbstractWorkStation(int x, int y, int width, int height, WorkMaterialTracker * tracker)
	: QGraphicsItem(), mSize(width, height), mTracker{ tracker }
{
	setByCenter(QPoint(x, y));
	mColor = Qt::blue;
	mWorkingSpeed = 1000;
}

QAbstractWorkStation::~QAbstractWorkStation()
{

}

void QAbstractWorkStation::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	painter->setPen(QPen(mColor));
	painter->drawRect(QRectF(mPos, mSize));
	painter->fillRect(QRectF(mPos, mSize), QBrush(mColor, Qt::SolidPattern));
}


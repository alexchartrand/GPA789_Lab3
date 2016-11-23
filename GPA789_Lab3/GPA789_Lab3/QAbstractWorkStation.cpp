#include "QAbstractWorkStation.h"

QAbstractWorkStation::QAbstractWorkStation(int x, int y, int width, int height, QWidget *parent)
	: QGraphicsItem(), mPos(x, y), mSize(width, height)
{

}

QAbstractWorkStation::~QAbstractWorkStation()
{

}

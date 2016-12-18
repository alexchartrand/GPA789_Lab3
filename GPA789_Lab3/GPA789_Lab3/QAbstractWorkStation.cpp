#include "QAbstractWorkStation.h"

#include <QPainter>

#include "WorkMaterialTracker.h"

QAbstractWorkStation::QAbstractWorkStation(QString name, int x, int y, int width, int height, WorkMaterialTracker * tracker)
	: QGraphicsItem(), mSize(width, height), mTracker{ tracker }, mName{name}
{
	setByCenter(QPoint(x, y));
	mColor = Qt::blue;
	mWorkingSpeed = 1000;

	mProductionTimer = new QTimer(this);

	connect(mProductionTimer, &QTimer::timeout,
		this, &QAbstractWorkStation::handleWorkingMaterial);
	mProductionTimer->start(mWorkingSpeed);
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


#include "QInputWorkStation.h"

#include <QtCore\qmath.h>
#include <qpainter>

QInputWorkStation::QInputWorkStation(int x, int y, int width, int height, QWidget *parent)
	: QAbstractWorkStation(x, y, width, height), mProgressBarSize(qFloor(0.8*width), 10), mProgressBarVisible{true}
{
	mProductionTimer = new QTimer;

	connect(mProductionTimer, SIGNAL(timeout()),
		this, SLOT(handleWorkingMaterial));
	mProductionTimer->start(mWorkingSpeed);

}

QInputWorkStation::~QInputWorkStation()
{
	delete mProductionTimer;
}

void QInputWorkStation::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

	if (mProgressBarVisible) {
	qreal completion = static_cast<qreal>(mWorkingSpeed - mProductionTimer->remainingTime()) / static_cast<qreal>(mWorkingSpeed);
	QPoint progressBarPos(mPos.x() + qFloor(0.1*mProgressBarSize.width()), mPos.y() - 15);

	painter->setPen(QPen(Qt::gray, 2));
	painter->drawRoundRect(QRect(progressBarPos, mProgressBarSize), 15, 15);
	painter->fillRect(QRect(progressBarPos.x(), progressBarPos.y(), qCeil(mProgressBarSize.width()*completion), mProgressBarSize.height()), QBrush(Qt::green, Qt::SolidPattern));
	}

	QAbstractWorkStation::paint(painter, option, widget);

}

void QInputWorkStation::handleWorkingMaterial()
{
	// Create new material
}
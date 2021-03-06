#include "QInputWorkStation.h"
#include "WorkingMaterial.h"

#include <QtCore\qmath.h>
#include <qpainter>

QInputWorkStation::QInputWorkStation(QString name, int x, int y, int width, int height, Qt::GlobalColor matColor, WorkMaterialTracker * tracker)
	: QAbstractWorkStation(name, x, y, width, height, tracker), mProgressBarSize(qFloor(0.8*width), 10), mProgressBarVisible{true}, mMatColor{matColor}
{

}

QInputWorkStation::~QInputWorkStation()
{

}

void QInputWorkStation::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

	if (mProgressBarVisible) {
		qreal completion = static_cast<qreal>(mWorkingSpeed - mProductionTimer->remainingTime()) / static_cast<qreal>(mWorkingSpeed);
		QPoint progressBarPos(mPos.x() + qFloor(0.1*mProgressBarSize.width()), mPos.y() - 15);

		painter->setPen(QPen(Qt::gray, 2));
		painter->drawRoundRect(QRectF(progressBarPos, mProgressBarSize), 15, 15);
		painter->fillRect(QRectF(progressBarPos.x(), progressBarPos.y(), mProgressBarSize.width()*completion, mProgressBarSize.height()), QBrush(Qt::green, Qt::SolidPattern));
	}

	QAbstractWorkStation::paint(painter, option, widget);

}

void QInputWorkStation::handleWorkingMaterial()
{
	// Create new material
	for each (Path * path in mPath) {
		mTracker->addMaterial(path, 20, mMatColor);
		mNumberOfItem++;
		emit nbItemChanged(QString::number(mNumberOfItem));
	}
}
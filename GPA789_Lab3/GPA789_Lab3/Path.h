#pragma once

#include <qpoint>
#include <qlist>
#include <qrect>
#include <qpolygon>

#include "QPathBuilder.h"
#include "QAbstractWorkStation.h"

class Path
{
public:
	Path() = delete;
	Path(qreal size);
	Path(qreal size, QPathBuilder const & pathBuilder);
	~Path();
	void setPath(QPathBuilder const & pathBuilder);
	void connectPath(QAbstractWorkStation * begin, QAbstractWorkStation  * end);
	QPointF getPoint(int i) { return mPoints.at(i); }

private:
	QList<QPointF> mPoints;
	QList<QPair<qreal, qreal>> mVectors;
	QRectF mBoundingBox;
	QPolygonF mShape;
	qreal mSize;
	QAbstractWorkStation * mBeginStation;
	QAbstractWorkStation * mEndStation;
};


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
	Path();
	~Path();
	void setPath(QPathBuilder const & pathBuilder);
	void connectPath(QAbstractWorkStation * begin, QAbstractWorkStation  * end);

private:
	QList<QPointF> mPoints;
	QList<QPair<qreal, qreal>> mVectors;
	QRectF mBoundingBox;
	QPolygonF mShape;
	QAbstractWorkStation * mBeginStation;
	QAbstractWorkStation * mEndStation;
};


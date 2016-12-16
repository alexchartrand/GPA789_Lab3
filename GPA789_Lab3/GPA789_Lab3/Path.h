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
	Path(qreal size, QPathBuilder const & pathBuilder, qreal transx, qreal transy);
	~Path();
	void setPath(QPathBuilder const & pathBuilder);
	void connectPath(QAbstractWorkStation * begin, QAbstractWorkStation  * end);
	QPointF getPoint(int i) { return mPoints.at(i); }
	QPolygonF const & getShape() { return mShape; }
	qreal const & getVectorsDist(int i) { return mVectors.at(i).first; } //Pour venir consulter les vecteurs du path de l'objet
	qreal const & getVectorsRad(int i) { return mVectors.at(i).second; }
	qreal getSpeed() { return mSpeed; };
	void setSpeed(qreal const & speed) { mSpeed = speed; }
	int const & getSizeVectors() { return mVectors.size() - 1; }
	QString name() const { return mName; }

private:
	QList<QPointF> mPoints;
	QList<QPair<qreal, qreal>> mVectors;
	QRectF mBoundingBox;
	QPolygonF mShape;
	qreal mSize;
	qreal mSpeed;
	QAbstractWorkStation * mBeginStation;
	QAbstractWorkStation * mEndStation;
	QString mName;
};


#include "Path.h"
#include "QAbstractWorkStation.h"
#include "WorkingMaterial.h"

#include <stdexcept>
#include <iostream>
#include <qpainter>

Path::Path(QString name,qreal size) : QGraphicsItem(), mBeginStation{nullptr}, mEndStation{nullptr}, mSize{ size }, mSpeed{10}, mLastMat{nullptr}, mName{ name }
{
	
}

Path::Path(QString name, qreal size, QPathBuilder & pathBuilder) : Path(name, size)
{
	setPath(pathBuilder);
}

Path::Path(QString name, qreal size, QPathBuilder & pathBuilder, qreal transx, qreal transy) : Path(name, size)
{
	setPath(pathBuilder);
}

Path::~Path()
{
}

void Path::setPath(QPathBuilder & pathBuilder)
{
	if (pathBuilder.isValid()) {
		mPoints = pathBuilder.points();
		mVectors = pathBuilder.vectors();
		mBoundingBox = pathBuilder.boundingBox();
		mShape = pathBuilder.shape(mSize);
		pathBuilder.reset();
	}
	else
	{
		throw std::invalid_argument("The path must be valid");
	}
}


void Path::connectPath(QAbstractWorkStation * begin, QAbstractWorkStation  * end)
{
	// Need to check if the connection is possible and logical
	if (mPoints.first() == begin->getCenter())
	{
		mBeginStation = begin;
		begin->addPath(this);
	}
	else
	{
		throw std::logic_error("The path must connect with the begin station");
	}
	if (mPoints.last() == end->getCenter())
	{
		mEndStation = end;
		end->addPath(this);
	}
	else
	{
		throw std::logic_error("The path must connect with the end station");
	}
}

WorkingMaterial * Path::getLastMaterial()
{
	WorkingMaterial * temp = mLastMat;
	mLastMat = nullptr;
	return temp;
}

bool Path::setLastMaterial(WorkingMaterial * mat)
{
	if (mLastMat == nullptr)
	{
		mLastMat = mat;
		return true;
	}
	else 
	{
		std::cout << "Too much material have reach the end of the path";
		return false;
	}
}

void Path::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	painter->setPen(QPen(Qt::black));
	painter->setBrush(QBrush(Qt::black, Qt::SolidPattern));
	QPainterPath mPaintPath;
	mPaintPath.addPolygon(mShape);
	painter->drawPath(mPaintPath);
}

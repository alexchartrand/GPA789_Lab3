#include "Path.h"
#include "QAbstractWorkStation.h"
#include "WorkingMaterial.h"

#include <stdexcept>
#include <iostream>

Path::Path(qreal size) : mBeginStation{nullptr}, mEndStation{nullptr}, mSize{ size }, mSpeed{10}, mLastMat{nullptr}
{
}

Path::Path(qreal size, QPathBuilder & pathBuilder) : Path(size)
{
	setPath(pathBuilder);
}

Path::Path(qreal size, QPathBuilder & pathBuilder, qreal transx, qreal transy) : Path(size)
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
#include "Path.h"

#include <stdexcept>

Path::Path(qreal size) : mBeginStation{nullptr}, mEndStation{nullptr}, mSize{ size }
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
	mBeginStation = begin;
	mEndStation = end;
}
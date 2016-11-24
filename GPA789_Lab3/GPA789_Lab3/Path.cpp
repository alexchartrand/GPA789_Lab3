#include "Path.h"

#include <stdexcept>

Path::Path(qreal size) : mBeginStation{nullptr}, mEndStation{nullptr}, mSize{ size }
{
}

Path::Path(qreal size, QPathBuilder const & pathBuilder) : Path(size)
{
	setPath(pathBuilder);
}

Path::~Path()
{
}

void Path::setPath(QPathBuilder const & pathBuilder)
{
	if (pathBuilder.isValid()) {
		mPoints = pathBuilder.points();
		mVectors = pathBuilder.vectors();
		mBoundingBox = pathBuilder.boundingBox();
		mShape = pathBuilder.shape(mSize);
	}
	else
	{
		throw std::invalid_argument("The path must be valid");
	}
}

void Path::connectPath(QAbstractWorkStation * begin, QAbstractWorkStation  * end)
{

}
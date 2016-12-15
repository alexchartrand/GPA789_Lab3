#include "WorkingMaterial.h"

#include <qpainter>

WorkingMaterial::WorkingMaterial(std::shared_ptr<Path> path, int radius, Qt::GlobalColor color) : mCurrentPath{ path }, mRadius{ radius }, mColor{ color }, mCurrentPoint{0}
{
	mPos = mCurrentPath->getPoint(mCurrentPoint);
}

WorkingMaterial::~WorkingMaterial()
{

}

void WorkingMaterial::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	painter->setPen(mColor);
	painter->drawEllipse(mPos, mRadius, mRadius);
}

void WorkingMaterial::updatePos()
{

	mPos.setX(mPos.x() + 1); // to be deleted
}

void WorkingMaterial::calculPos(int i, qreal vPath)
{
	int sizevect = mCurrentPath->getSizeVectors();

	if (i <= sizevect)
	{

		qreal lenght = mCurrentPath->getVectorsDist(i);
		qreal angle = mCurrentPath->getVectorsRad(i);

		if (distvnp > 0) {
			lenght = distvnp;
		}

		if (vPath <= lenght) {
			mPos.setX(mPos.x() + (vPath*cos(angle)));
			mPos.setY(mPos.y() + (vPath*sin(angle)));
			distvnp = lenght - vPath;
			if (lenght == vPath) {
				miPath++;
				distvnp = 0;
			}
		}

		else if (vPath > lenght) {
			vPath = vPath - lenght;
			mPos.setX(mPos.x() + (lenght*cos(angle)));
			mPos.setY(mPos.y() + (lenght*sin(angle)));
			distvnp = 0;
			miPath++;
			calculPos(miPath, vPath);
		}
	}
	else{

	}
}
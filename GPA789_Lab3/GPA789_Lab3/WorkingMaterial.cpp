#include "WorkingMaterial.h"

#include <qpainter>

WorkingMaterial::WorkingMaterial(QPathBuilder * path, int radius, Qt::GlobalColor color) : mCurrentPath{ path }, mRadius{ radius }, mColor{ color }
{
	mPos = mCurrentPath->entryPoint().toPoint();
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
#include "WorkingMaterial.h"

#include <qpainter>
#include <qcolor.h>

WorkingMaterial::WorkingMaterial(Path * path, int radius, Qt::GlobalColor color) : QGraphicsItem(), mCurrentPath{ path }, mRadius{ radius }, mColor{ color }, mCurrentPoint{0}
{
	mPos = mCurrentPath->getPoint(mCurrentPoint);
}

WorkingMaterial::~WorkingMaterial()
{
	
}

void WorkingMaterial::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	painter->setPen(Qt::black);
	painter->setBrush(mColor);
	painter->setBackground(mColor);
	painter->drawEllipse(mPos, mRadius, mRadius);
}

QPainterPath WorkingMaterial::shape() const
{
	QPainterPath path;
	path.addEllipse(boundingRect());
	return path;
}

void WorkingMaterial::calculPos(int i)
{
	qreal vPath = mCurrentPath->getSpeed();
	int sizevect = mCurrentPath->getSizeVectors();
	bool collision = false;
	QList<QGraphicsItem *> collideList = collidingItems(Qt::IntersectsItemBoundingRect);
	
	/* Ca ne marche pas et je sais pas trop quoi faire pour les collision...
	   C'est vraiment long et complexe faire quelque chose qui fonctionne*/
	//for each(QGraphicsItem * i in collideList)
	//{
	//	int type = i->type();
	//	if (type == UserType + 1)
	//	{
	//		collision = true;
	//		break;
	//	}
	//}

	if (!collision)
	{
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
				calculPos(miPath);
			}
		}
		else {
			mCurrentPath->setLastMaterial(this);
		}
	}
}
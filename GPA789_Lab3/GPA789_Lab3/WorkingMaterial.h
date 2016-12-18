#ifndef WORKINGMATERIAL_H
#define WORKINGMATERIAL_H

#include <QGraphicsItem>
#include <memory>

#include "Path.h"

class WorkingMaterial : public QGraphicsItem
{
public:
	WorkingMaterial() = delete;
	WorkingMaterial(Path * path, int radius, Qt::GlobalColor color);
	~WorkingMaterial();

	void updatePos();
	void calculPos(int i);

	QRectF boundingRect() const override { return QRectF(mPos, QSize(mRadius, mRadius)); }
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
	int miPath = 0;

private:
	QPointF mPos;
	int mRadius;
	int mCurrentPoint;
	qreal distvnp = 0;
	
	Qt::GlobalColor mColor;
	Path * mCurrentPath;

};

#endif // WORKINGMATERIAL_H

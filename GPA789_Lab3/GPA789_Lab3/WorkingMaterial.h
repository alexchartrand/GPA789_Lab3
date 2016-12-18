#ifndef WORKINGMATERIAL_H
#define WORKINGMATERIAL_H

#include <QGraphicsItem>
#include <memory>

#include "Path.h"

class WorkingMaterial : public QGraphicsItem
{
public:
	enum { Type = UserType + 1 };

	WorkingMaterial() = delete;
	WorkingMaterial(Path * path, int radius, Qt::GlobalColor color);
	~WorkingMaterial();
	virtual int type() const override {return Type;}

	void calculPos(int i);

	QRectF boundingRect() const override { return QRectF(mPos, QSize(mRadius, mRadius)); }
	virtual QPainterPath shape() const override;
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

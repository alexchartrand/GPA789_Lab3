#ifndef WORKINGMATERIAL_H
#define WORKINGMATERIAL_H

#include <QGraphicsItem>

#include "QPathBuilder.h"

class WorkingMaterial : public QGraphicsItem
{
public:
	WorkingMaterial() = delete;
	WorkingMaterial(QPathBuilder * path, int radius, Qt::GlobalColor color) { mCurrentPath = path; mRadius = radius; mColor = color; }
	~WorkingMaterial();

	void updatePos();

	QRectF boundingRect() const override { return QRect(mPos, QSize(mRadius, mRadius)); }
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
	QPoint mPos;
	int mRadius;
	Qt::GlobalColor mColor;
	QPathBuilder * mCurrentPath;
};

#endif // WORKINGMATERIAL_H

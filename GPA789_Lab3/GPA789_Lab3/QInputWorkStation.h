#ifndef QINPUTWORKSTATION_H
#define QINPUTWORKSTATION_H

#include "QAbstractWorkStation.h"
#include "WorkMaterialTracker.h"
#include "Path.h"
#include <qlist>
#include <memory>

class QInputWorkStation : public QAbstractWorkStation
{
	Q_OBJECT

public:
	QInputWorkStation(QString name, int x, int y, int width, int height, Qt::GlobalColor matColor, WorkMaterialTracker * tracker);
	~QInputWorkStation();

	void enableProgressBar(bool en) { mProgressBarVisible = en; }

	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
	virtual QRectF boundingRect() const override { return QRectF(mPos.x(), mPos.y()-20, mSize.width(), mSize.height()+20); }

private:
	QSizeF mProgressBarSize;
	bool mProgressBarVisible;
	Qt::GlobalColor mMatColor;
	
protected slots:
	virtual void handleWorkingMaterial() override;
	
};

#endif // QINPUTWORKSTATION_H

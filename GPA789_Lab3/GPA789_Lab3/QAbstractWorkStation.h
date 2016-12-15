#ifndef QABSTRACTWORKSTATION_H
#define QABSTRACTWORKSTATION_H

#include <QGraphicsItem>

class WorkMaterialTracker;

class QAbstractWorkStation : public QObject,  public QGraphicsItem
{
	Q_OBJECT
	Q_INTERFACES(QGraphicsItem)

public:
	QAbstractWorkStation(int x, int y, int width, int height, WorkMaterialTracker * tracker);
	~QAbstractWorkStation();

	// getter, setter
	void setSize(int width, int height) { mSize.setWidth(width); mSize.setHeight(height); }
	QSizeF size() const { return mSize; }
	void setPosition(int x, int y) { mPos.setX(x); mPos.setY(y); }
	QPointF Position() const { return mPos; }
	QString name() const { return mName; }
	void setColor(Qt::GlobalColor c) { mColor = c; }
	void setWorkingSpeed(qreal & speed) { mWorkingSpeed = static_cast<int>(1 / speed * 1000); } // item per seconde
	qreal workingSpeed() { return 1 / (static_cast<qreal>(mWorkingSpeed) / 1000); }
	QPoint getCenter() { return QPoint(mPos.x() + mSize.width()/2, mPos.y() + mSize.height()/2); }
	void setByCenter(QPoint & pos) { mPos.setX(pos.x() - mSize.width()/2); mPos.setY(pos.y() - mSize.height()/2); }

	QRectF boundingRect() const override { return QRectF(mPos, mSize); }
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

protected:
	QSizeF mSize;
	QPointF mPos;
	bool mRunning;
	int mWorkingSpeed; // Delta t in ms
	WorkMaterialTracker * mTracker;
	Qt::GlobalColor mColor;

protected slots:
	virtual void handleWorkingMaterial() {} // Will be pure virtual, so must be reimplemented

private:
	QString mName;
};

#endif // QABSTRACTWORKSTATION_H

#ifndef QABSTRACTWORKSTATION_H
#define QABSTRACTWORKSTATION_H

#include <QGraphicsItem>
#include <qtimer>
#include "Path.h"

class WorkMaterialTracker;

class QAbstractWorkStation : public QObject,  public QGraphicsItem
{
	Q_OBJECT
	Q_INTERFACES(QGraphicsItem)

public:
	enum { Type = UserType + 2 };

	QAbstractWorkStation() = delete;
	QAbstractWorkStation(QString name, int x, int y, int width, int height, WorkMaterialTracker * tracker);
	virtual ~QAbstractWorkStation();

	virtual int type() const override { return Type; }

	// getter, setter
	void setSize(int width, int height) { mSize.setWidth(width); mSize.setHeight(height); }
	QSizeF size() const { return mSize; }
	void setPosition(int x, int y) { mPos.setX(x); mPos.setY(y); }
	QPointF Position() const { return mPos; }
	QString name() const { return mName; }
	int numberOfItem() const { return mNumberOfItem; }
	void setColor(Qt::GlobalColor c) { mColor = c; }
	void setWorkingSpeed(qreal speed) { mWorkingSpeed = static_cast<int>(1 / speed * 1000); mProductionTimer->start(mWorkingSpeed);} // item per seconde
	qreal workingSpeed() { return 1 / (static_cast<qreal>(mWorkingSpeed) / 1000); }
	QPoint getCenter() { return QPoint(mPos.x() + mSize.width()/2, mPos.y() + mSize.height()/2); }
	void setByCenter(QPoint & pos) { mPos.setX(pos.x() - mSize.width()/2); mPos.setY(pos.y() - mSize.height()/2); }

	void addPath(Path * path) { mPath.append(path); }
	bool isValid() { return mPath.count() > 0 ? true : false; }

	virtual QRectF boundingRect() const override { return QRectF(mPos, mSize); }
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

signals:
	void nbItemChanged(const QString & nb);

protected:
	QSizeF mSize;
	QPointF mPos;
	bool mRunning;
	int mWorkingSpeed; // Delta t in ms
	int mNumberOfItem;
	QTimer * mProductionTimer;
	WorkMaterialTracker * mTracker;
	Qt::GlobalColor mColor;
	QList<Path *> mPath;

protected slots:
	virtual void handleWorkingMaterial() {}

private:
	QString mName;
};

#endif // QABSTRACTWORKSTATION_H

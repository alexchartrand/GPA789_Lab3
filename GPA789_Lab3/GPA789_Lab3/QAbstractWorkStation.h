#ifndef QABSTRACTWORKSTATION_H
#define QABSTRACTWORKSTATION_H

#include <QGraphicsItem>

class QAbstractWorkStation : public QObject,  public QGraphicsItem
{
	Q_OBJECT
	Q_INTERFACES(QGraphicsItem)

public:
	QAbstractWorkStation(int x, int y, int width, int height, QWidget *parent = nullptr);
	~QAbstractWorkStation();

	// getter, setter
	void setSize(int width, int height) { mSize.setWidth(width); mSize.setHeight(height); }
	QSize size() const { return mSize; }
	void setPosition(int x, int y) { mPos.setX(x); mPos.setY(y); }
	QPoint Position() const { return mPos; }
	QString name() const { return mName; }
	void setColor(Qt::GlobalColor c) { mColor = c; }
	void setWorkingSpeed(qreal speed) { mWorkingSpeed = static_cast<int>(1 / speed * 1000); } // item per seconde
	qreal workingSpeed() { return 1 / (static_cast<qreal>(mWorkingSpeed) / 1000); }
	QPoint getCenter() { return QPoint(mPos.x() + mSize.width(), mPos.y() + mSize.height()); }

	QRectF boundingRect() const override { return QRect(mPos, mSize); }
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

protected:
	QSize mSize;
	QPoint mPos;
	QString mName;
	bool mRunning;
	int mWorkingSpeed; // Delta t in ms
	Qt::GlobalColor mColor;

protected slots:
	virtual void handleWorkingMaterial() {}

private:
};

#endif // QABSTRACTWORKSTATION_H

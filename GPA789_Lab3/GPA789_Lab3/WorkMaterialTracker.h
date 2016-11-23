#ifndef WORKMATERIALTRACKER_H
#define WORKMATERIALTRACKER_H

#include <QObject>
#include <QGraphicsEllipseItem>

class WorkMaterialTracker : public QObject
{
	Q_OBJECT

public:
	WorkMaterialTracker(QObject *parent);
	~WorkMaterialTracker();

	void update();

private:
	QList<QGraphicsEllipseItem *> materialList;
};

#endif // WORKMATERIALTRACKER_H

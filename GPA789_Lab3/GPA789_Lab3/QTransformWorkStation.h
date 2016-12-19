#ifndef QTRANSFORMWORKSTATION_H
#define QTRANSFORMWORKSTATION_H

#include "QAbstractWorkStation.h"
#include "WorkMaterialTracker.h"
#include "QOutputWorkStation.h"
#include "QInputWorkStation.h"

class QTransformWorkStation : public QAbstractWorkStation
{
	Q_OBJECT

public:
	QTransformWorkStation(QString name, int x, int y, int width, int height, Qt::GlobalColor matColor, WorkMaterialTracker * tracker);
	~QTransformWorkStation();
	QInputWorkStation * getTransIn() { return mInStation; }
	QOutputWorkStation * getTransOut() { return mOutStation; }


private:
	QOutputWorkStation * mOutStation;
	QInputWorkStation * mInStation;
};

#endif // QTRANSFORMWORKSTATION_H

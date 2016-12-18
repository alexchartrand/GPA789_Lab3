#ifndef QTRANSFORMWORKSTATION_H
#define QTRANSFORMWORKSTATION_H

#include "QAbstractWorkStation.h"
#include "WorkMaterialTracker.h"

class QTransformWorkStation : public QAbstractWorkStation
{
	Q_OBJECT

public:
	QTransformWorkStation(QString name, int x, int y, int width, int height, WorkMaterialTracker * tracker);
	~QTransformWorkStation();


private:
	//QOutputWorkStation mOutStation;
	//QInputWorkStation mInStation;
};

#endif // QTRANSFORMWORKSTATION_H

#ifndef QTRANSFORMWORKSTATION_H
#define QTRANSFORMWORKSTATION_H

#include "QAbstractWorkStation.h"
#include "WorkMaterialTracker.h"

class QTransformWorkStation : public QAbstractWorkStation
{
	Q_OBJECT

public:
	QTransformWorkStation(int x, int y, int width, int height, WorkMaterialTracker * tracker);
	~QTransformWorkStation();


private:
	
};

#endif // QTRANSFORMWORKSTATION_H

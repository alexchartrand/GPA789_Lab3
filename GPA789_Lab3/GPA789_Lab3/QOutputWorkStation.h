#ifndef QOUTPUTWORKSTATION_H
#define QOUTPUTWORKSTATION_H

#include "QAbstractWorkStation.h"
#include "WorkMaterialTracker.h"

class QOutputWorkStation : public QAbstractWorkStation
{
	Q_OBJECT

public:
	QOutputWorkStation(int x, int y, int width, int height, WorkMaterialTracker * tracker);
	~QOutputWorkStation();

private:
	
};

#endif // QOUTPUTWORKSTATION_H

#ifndef QOUTPUTWORKSTATION_H
#define QOUTPUTWORKSTATION_H

#include "QAbstractWorkStation.h"
#include "WorkMaterialTracker.h"
#include "WorkingMaterial.h"

class QOutputWorkStation : public QAbstractWorkStation
{
	Q_OBJECT

public:
	QOutputWorkStation() = delete;
	QOutputWorkStation(QString name, int x, int y, int width, int height, WorkMaterialTracker * tracker);
	~QOutputWorkStation();

private:


protected slots :
	virtual void handleWorkingMaterial() override;
};

#endif // QOUTPUTWORKSTATION_H

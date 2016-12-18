#include "QOutputWorkStation.h"

QOutputWorkStation::QOutputWorkStation(QString name, int x, int y, int width, int height, WorkMaterialTracker * tracker)
	: QAbstractWorkStation(name, x, y, width, height, tracker)
{

}

QOutputWorkStation::~QOutputWorkStation()
{

}

void QOutputWorkStation::handleWorkingMaterial()
{
	// Delete material
	for each (Path * path in mPath) {
		mTracker->deleteMaterial(path->getLastMaterial());
	}
}

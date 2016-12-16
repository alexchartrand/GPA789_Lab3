#include "QOutputWorkStation.h"

QOutputWorkStation::QOutputWorkStation(int x, int y, int width, int height, WorkMaterialTracker * tracker)
	: QAbstractWorkStation(x, y, width, height, tracker)
{

}

QOutputWorkStation::~QOutputWorkStation()
{

}

void QOutputWorkStation::handleWorkingMaterial()
{
	// Delete material
	for each (std::shared_ptr<Path> path in mPath) {
		mTracker->deleteMaterial(path->getLastMaterial());
	}
}

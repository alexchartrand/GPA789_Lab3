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
		WorkingMaterial * mat = path->getLastMaterial();
		if (mat)
		{
			mTracker->deleteMaterial(mat);
			mNumberOfItem++;
			emit nbItemChanged(QString::number(mNumberOfItem));
		}
	}
}

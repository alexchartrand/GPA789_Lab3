#include "QTransformWorkStation.h"

#include "QInputWorkStation.h"
#include "QOutputWorkStation.h"
#include <QPainter>

QTransformWorkStation::QTransformWorkStation(QString name, int x, int y, int width, int height, WorkMaterialTracker * tracker)
	: QAbstractWorkStation(name, x, y, width, height, tracker)
{
	mOutStation = new QOutputWorkStation(name, x, y, width, height, tracker);
	mInStation = new QInputWorkStation(name, x, y, width, height, Qt::gray, tracker);
}

QTransformWorkStation::~QTransformWorkStation()
{

}


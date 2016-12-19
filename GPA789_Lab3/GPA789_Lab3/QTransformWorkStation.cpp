#include "QTransformWorkStation.h"

#include "QInputWorkStation.h"
#include "QOutputWorkStation.h"
#include <QPainter>

QTransformWorkStation::QTransformWorkStation(QString name, int x, int y, int width, int height,Qt::GlobalColor matColor, WorkMaterialTracker * tracker)
	: QAbstractWorkStation(name, x, y, width, height, tracker)
{
	mOutStation = new QOutputWorkStation(name, x, y, width, height, tracker);
	mInStation = new QInputWorkStation(name, x, y, width, height, matColor, tracker);
}

QTransformWorkStation::~QTransformWorkStation()
{

}


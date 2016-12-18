#include "QTransformWorkStation.h"

#include <QPainter>

QTransformWorkStation::QTransformWorkStation(QString name, int x, int y, int width, int height, WorkMaterialTracker * tracker)
	: QAbstractWorkStation(name, x, y, width, height, tracker)
{

}

QTransformWorkStation::~QTransformWorkStation()
{

}


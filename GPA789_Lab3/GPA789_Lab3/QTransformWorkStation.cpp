#include "QTransformWorkStation.h"

#include <QPainter>

QTransformWorkStation::QTransformWorkStation(int x, int y, int width, int height, WorkMaterialTracker * tracker)
	: QAbstractWorkStation(x, y, width, height, tracker)
{

}

QTransformWorkStation::~QTransformWorkStation()
{

}


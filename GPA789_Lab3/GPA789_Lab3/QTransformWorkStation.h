#ifndef QTRANSFORMWORKSTATION_H
#define QTRANSFORMWORKSTATION_H

#include "QAbstractWorkStation.h"

class QTransformWorkStation : public QAbstractWorkStation
{
	Q_OBJECT

public:
	QTransformWorkStation(int x, int y, int width, int height, QWidget *parent = nullptr);
	~QTransformWorkStation();


private:
	
};

#endif // QTRANSFORMWORKSTATION_H

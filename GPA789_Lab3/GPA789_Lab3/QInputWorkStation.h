#ifndef QINPUTWORKSTATION_H
#define QINPUTWORKSTATION_H

#include "QAbstractWorkStation.h"

class QInputWorkStation : public QAbstractWorkStation
{

public:
	QInputWorkStation(int x, int y, int width, int height, QWidget *parent = nullptr);
	~QInputWorkStation();

private:
	
};

#endif // QINPUTWORKSTATION_H

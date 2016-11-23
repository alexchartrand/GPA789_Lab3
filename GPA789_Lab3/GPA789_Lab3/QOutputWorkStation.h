#ifndef QOUTPUTWORKSTATION_H
#define QOUTPUTWORKSTATION_H

#include "QAbstractWorkStation.h"

class QOutputWorkStation : public QAbstractWorkStation
{

public:
	QOutputWorkStation(int x, int y, int width, int height, QWidget *parent = nullptr);
	~QOutputWorkStation();

private:
	
};

#endif // QOUTPUTWORKSTATION_H

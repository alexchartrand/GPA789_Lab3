#ifndef QINPUTWORKSTATION_H
#define QINPUTWORKSTATION_H

#include "QAbstractWorkStation.h"
#include "WorkMaterialTracker.h"
#include "Path.h"
#include <qtimer>
#include <qlist>
#include <memory>

class QInputWorkStation : public QAbstractWorkStation
{
	Q_OBJECT

public:
	QInputWorkStation(int x, int y, int width, int height, WorkMaterialTracker * tracker);
	~QInputWorkStation();

	void enableProgressBar(bool en) { mProgressBarVisible = en; }

	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
	QList<Path *> mPath;

private:
	QTimer * mProductionTimer;
	QSizeF mProgressBarSize;
	bool mProgressBarVisible;
	//QList<std::shared_ptr<Path>> mPath; //En commentaire pour test
	
protected slots:
	virtual void handleWorkingMaterial() override;
	
};

#endif // QINPUTWORKSTATION_H

#ifndef WORKMATERIALTRACKER_H
#define WORKMATERIALTRACKER_H

#include <QObject>
#include <qgraphicsscene>
#include <QList>

#include "WorkingMaterial.h"

class WorkMaterialTracker : public QObject
{
	Q_OBJECT

public:
	WorkMaterialTracker(QGraphicsScene * scene) : mScene{ scene } {}
	~WorkMaterialTracker();

	void updateMaterial();
	void addMaterial(WorkingMaterial * material);
	void deleteMaterial(WorkingMaterial * material);

private:
	QList<WorkingMaterial *> mMaterialList;
	QGraphicsScene * mScene;
};

#endif // WORKMATERIALTRACKER_H

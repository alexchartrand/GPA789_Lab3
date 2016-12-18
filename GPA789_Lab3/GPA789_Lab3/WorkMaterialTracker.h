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
	WorkMaterialTracker() = default;
	~WorkMaterialTracker();

	void addScene(QGraphicsScene * scene);
	void updateMaterial();
	void addMaterial(Path * path, int radius, Qt::GlobalColor color);
	void deleteMaterial(WorkingMaterial * material);

private:
	QList<WorkingMaterial *> mMaterialList;
	QGraphicsScene * mScene;
};

#endif // WORKMATERIALTRACKER_H

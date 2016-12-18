#include "WorkMaterialTracker.h"


WorkMaterialTracker::~WorkMaterialTracker()
{

}

void WorkMaterialTracker::addScene(QGraphicsScene * scene)
{ 
	if (scene) 
	{ 
		mScene = scene; 
	} 
}


void WorkMaterialTracker::updateMaterial()
{
	for each (WorkingMaterial* mat in mMaterialList)
	{
		mat->calculPos(mat->miPath);
	}
}

void WorkMaterialTracker::addMaterial(Path * path, int radius, Qt::GlobalColor color)
{
	WorkingMaterial * mat = new WorkingMaterial(path, radius, color);
	mMaterialList.append(mat);
	mScene->addItem(mat);

}

void WorkMaterialTracker::deleteMaterial(WorkingMaterial * material)
{
	if (material) {
		/* The delete dont work!!!!
		WHY!!!!!!*/
		mMaterialList.removeOne(material);
		//mScene->removeItem(material);
		delete material;
	}
}

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

void WorkMaterialTracker::addMaterial(WorkingMaterial * material)
{
	if (material) {
		mMaterialList.append(material);
		mScene->addItem(material);
	}
}

void WorkMaterialTracker::deleteMaterial(WorkingMaterial * material)
{
	if (material) {
		/* The delete dont work!!!!
		WHY!!!!!!*/
		mMaterialList.removeOne(material);
		mScene->removeItem(material);
		delete material;
	}
}

#include "WorkMaterialTracker.h"


WorkMaterialTracker::~WorkMaterialTracker()
{

}


void WorkMaterialTracker::updateMaterial()
{
	for each (WorkingMaterial* mat in mMaterialList)
	{
		mat->updatePos();
	}
}

void WorkMaterialTracker::addMaterial(WorkingMaterial * material)
{
	if (material) {
		mMaterialList.append(material);
		mScene.addItem(material);
	}
}

void WorkMaterialTracker::deleteMaterial(WorkingMaterial * material)
{
	if (material) {
		mMaterialList.removeOne(material);
		mScene.removeItem(material);
		delete material;
	}
}

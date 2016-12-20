#ifndef QTRANSFORMWORKSTATION_H
#define QTRANSFORMWORKSTATION_H

#include "QAbstractWorkStation.h"
#include "WorkMaterialTracker.h"
#include "QOutputWorkStation.h"
#include "QInputWorkStation.h"

/* Cette classe n'est pas fonctionnelle et est seulement utilisés pour la démonstration.
   Nous nous sommes rendu compte d'un problème dans notre design un peu tard.
   Vue que cette classe comporte un output et un input en plus d'hériter d'abstract workstation
   elle à trois fois la variable nom, trois fois la variable vitesse, etc.
   Donc, la fonction parent pour ajuster la vitesse et compter le nombre d'itme ne fonctionne pas,
   puisqu'elle ne touche pas au WorkStation contenu dans cet objet*/

class QTransformWorkStation : public QAbstractWorkStation
{
	Q_OBJECT

public:
	QTransformWorkStation(QString name, int x, int y, int width, int height, Qt::GlobalColor matColor, WorkMaterialTracker * tracker);
	~QTransformWorkStation();
	QInputWorkStation * getTransIn() { return mInStation; } // Workaround
	QOutputWorkStation * getTransOut() { return mOutStation; } // Workaround


private:
	QOutputWorkStation * mOutStation;
	QInputWorkStation * mInStation;

protected slots :
	virtual void handleWorkingMaterial() override; //BUG!!!! Mauvais design, revoir l'héritage
};

#endif // QTRANSFORMWORKSTATION_H

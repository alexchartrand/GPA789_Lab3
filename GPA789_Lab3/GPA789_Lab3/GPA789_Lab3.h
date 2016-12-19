#ifndef GPA789_LAB3_H
#define GPA789_LAB3_H


#include <QtWidgets/QMainWindow>
#include "ui_GPA789_Lab3.h"
#include "QPathBuilder.h"
#include "WorkMaterialTracker.h"

#include "QInteractiveGraphicsView.h"
#include <qgraphicsscene>
#include <qgraphicsitem>
#include <qtimer>
#include <qlabel>
#include <qgroupbox>


#include "Path.h"
#include "QAbstractWorkStation.h"


class GPA789_Lab3 : public QMainWindow
{
	Q_OBJECT

public:
	GPA789_Lab3(QWidget *parent = 0);
	~GPA789_Lab3();


private:
	Ui::GPA789_Lab3Class ui;
	QInteractiveGraphicsView * mView;
	QGraphicsScene * mScene;
	QTimer * mRepaintTimer;
	QSlider * mSliderSpeed;
	QLabel * mSliderSpeedTitle;
	QLabel * mSliderSpeedValue;
	WorkMaterialTracker mTracker;
	QGraphicsItem * itemSelect;
	QList<QGraphicsItem *> ListItemScene;
	QLabel * nomItem;
	QLabel * nNMItem;
	Path * mPathSelected;
	QList<Path *> mPathList;
	QAbstractWorkStation * mStationSelected;
	int typeSelectedItem;

	void testFunction(); // will be deleted
	void add(QGroupBox * groupBox, QLabel * & title, QString const & titleText, QWidget * widget, QLabel * & value);
	void add(QGroupBox * groupBox, QLabel * & title, QString const & titleText, QWidget * widget);
	void showMessageBox();


private slots:
	void repaintTick();
	void changeSpeedIntervall();

protected :
	virtual void mousePressEvent(QMouseEvent * mouseEvent) override;
};

#endif // GPA789_LAB3_H

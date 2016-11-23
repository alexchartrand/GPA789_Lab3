#ifndef GPA789_LAB3_H
#define GPA789_LAB3_H

#include <QtWidgets/QMainWindow>
#include "ui_GPA789_Lab3.h"
#include "QPathBuilder.h"

#include "QInteractiveGraphicsView.h"
#include <qgraphicsscene>
#include <qgraphicsitem>
#include <qtimer>

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
	QPathBuilder * pathBuilder;

private slots:
	void repaintTick();
};

#endif // GPA789_LAB3_H

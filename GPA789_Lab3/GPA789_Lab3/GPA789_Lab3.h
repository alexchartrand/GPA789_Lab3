#ifndef GPA789_LAB3_H
#define GPA789_LAB3_H

#include <QtWidgets/QMainWindow>
#include "ui_GPA789_Lab3.h"

#include "QInteractiveGraphicsView.h"
#include <qgraphicsscene>
#include <qgraphicsitem>

class GPA789_Lab3 : public QMainWindow
{
	Q_OBJECT

public:
	GPA789_Lab3(QWidget *parent = 0);
	~GPA789_Lab3();

private:
	Ui::GPA789_Lab3Class ui;
};

#endif // GPA789_LAB3_H

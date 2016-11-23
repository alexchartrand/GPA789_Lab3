#include "GPA789_Lab3.h"
#include "QTransformWorkStation.h"
#include "QInputWorkStation.h"

#include <qlayout>
#include <qrect>


GPA789_Lab3::GPA789_Lab3(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	mScene = new QGraphicsScene();
	mScene->addItem(new QInputWorkStation(0, 50, 100, 300));
	mView = new QInteractiveGraphicsView(mScene);

	QBrush greenBrush(Qt::green);
	QBrush blueBrush(Qt::blue);
	QPen outlinePen(Qt::black);
	outlinePen.setWidth(2);

	//Creation de path
	pathBuilder = new QPathBuilder;

	pathBuilder->addLinear(200);
	pathBuilder->addLShape(100.0, 300.0, 75.0, 7, true);
	pathBuilder->addUShape(150, 100, 250, 12, true);
	pathBuilder->addLinearOffsetAngle(100, -45);
	pathBuilder->addCircular(100, -235, 17);
	QPolygonF shape = pathBuilder->shape(20.0);
	//mScene->addPolygon(shape, outlinePen, blueBrush);

	QHBoxLayout * mainHLayout = new QHBoxLayout;
	mainHLayout->addWidget(mView);

	QWidget * mainWidget = new QWidget;
	mainWidget->setLayout(mainHLayout);

	setCentralWidget(mainWidget);

	mRepaintTimer = new QTimer;

	connect(mRepaintTimer, SIGNAL(timeout()),
		this, SLOT(repaintTick()));

	mRepaintTimer->start(33);
	mView->show();
}

GPA789_Lab3::~GPA789_Lab3()
{
	
}

void GPA789_Lab3::repaintTick()
{
	mView->update();
	mScene->update();
}

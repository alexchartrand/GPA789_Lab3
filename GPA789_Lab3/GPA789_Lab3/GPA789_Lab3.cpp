#include "GPA789_Lab3.h"
#include "QTransformWorkStation.h"
#include "QInputWorkStation.h"

#include <qlayout>
#include <qrect>
#include <memory>



GPA789_Lab3::GPA789_Lab3(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	
	mScene = new QGraphicsScene();
	mView = new QInteractiveGraphicsView(mScene); // Ne fonctionne pas
	mTracker = new WorkMaterialTracker(mScene);

	QHBoxLayout * mainHLayout = new QHBoxLayout;
	mainHLayout->addWidget(mView);

	QWidget * mainWidget = new QWidget;
	mainWidget->setLayout(mainHLayout);

	setCentralWidget(mainWidget);
	testFunction();
	mRepaintTimer = new QTimer;

	connect(mRepaintTimer, SIGNAL(timeout()),
		this, SLOT(repaintTick()));

	mRepaintTimer->start(33);
	mView->show();
}

GPA789_Lab3::~GPA789_Lab3()
{
	delete mTracker;
}

void GPA789_Lab3::testFunction()
{
	QInputWorkStation * inputTest = new QInputWorkStation(0, 50, 75, 75, mTracker);
	mScene->addItem(inputTest); // est-ce que la scene delete tous de qui lui est add?

	QBrush greenBrush(Qt::green);
	QBrush blueBrush(Qt::blue);
	QPen outlinePen(Qt::black);
	outlinePen.setWidth(2);

	std::unique_ptr<QPathBuilder> mPathBuilder(new QPathBuilder);
	//Creation de path

	mPathBuilder->addLinear(200);
	mPathBuilder->addLShape(100.0, 300.0, 75.0, 7, true);
	mPathBuilder->addUShape(150, 100, 250, 12, true);
	mPathBuilder->addLinearOffsetAngle(100, -45);
	mPathBuilder->addCircular(100, -235, 17);
	QPolygonF shape = mPathBuilder->shape(20.0);
	mScene->addPolygon(shape, outlinePen, blueBrush);

}

void GPA789_Lab3::repaintTick()
{
	mView->update();
	mScene->update();
}

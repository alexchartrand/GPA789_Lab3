#include "GPA789_Lab3.h"
#include "QTransformWorkStation.h"
#include "QInputWorkStation.h"
#include "QOutputWorkStation.h"
#include "Path.h"
#include <qgraphicsscene.h>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>

#include <qlayout>
#include <qrect>
#include <qgroupBox>
#include <qevent>
#include <qlabel>



GPA789_Lab3::GPA789_Lab3(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	
	//Simulatuer
	mScene = new QGraphicsScene();
	mView = new QInteractiveGraphicsView(mScene); 
	mTracker.addScene(mScene);

	testFunction();

	//Controleur
	QHBoxLayout * mainHLayout = new QHBoxLayout;
	mainHLayout->addWidget(mView);
	mSliderSpeed = new QSlider;			mSliderSpeed->setOrientation(Qt::Horizontal);		mSliderSpeed->setRange(0, 10);
	QGroupBox * groupBoxSimParam = new QGroupBox("Paramètres de simulation");
	QVBoxLayout * controlsLayout = new QVBoxLayout;
	add(groupBoxSimParam, mSliderSpeedTitle, "Vitesse Path (m/sec)", mSliderSpeed, mSliderSpeedValue);
	controlsLayout->addWidget(groupBoxSimParam);
	QWidget * controlsWidget = new QWidget;
	controlsWidget->setLayout(controlsLayout);
	controlsWidget->setFixedWidth(250);
	mainHLayout->addWidget(controlsWidget);
	nomItem = new QLabel;
	nomItem->setText("Selectionner un Item");
	controlsLayout->addWidget(nomItem);

	QWidget * mainWidget = new QWidget;
	mainWidget->setLayout(mainHLayout);


	setCentralWidget(mainWidget);
	
	mRepaintTimer = new QTimer;

	connect(mRepaintTimer, &QTimer::timeout,
		this, &GPA789_Lab3::repaintTick);

	connect(mSliderSpeed, &QSlider::valueChanged, 
		this, &GPA789_Lab3::changeSpeedIntervall);

	//connect(nomItem, &QLabel::selectedText,
	//	this, &GPA789_Lab3::changeNameItem);

	mRepaintTimer->start(33);
	mView->show();
}

GPA789_Lab3::~GPA789_Lab3()
{
	for each(Path * path in mPathList)
	{
		delete path;
	}
}

void GPA789_Lab3::testFunction()
{

	//Creation des station
	QInputWorkStation * inputA = new QInputWorkStation("InputA", 100, 100, 75, 75, Qt::gray, &mTracker);
	QInputWorkStation * inputB = new QInputWorkStation("InputB", 900, 900, 75, 75, Qt::yellow, &mTracker);

	QOutputWorkStation * outputA = new QOutputWorkStation("OutputA", 100, 900, 75, 75, &mTracker);
	QOutputWorkStation * outputB = new QOutputWorkStation("OutputB", 900, 100, 75, 75, &mTracker);

	QOutputWorkStation * transA = new QOutputWorkStation("TransA", 400, 400, 75, 75, &mTracker);
	QTransformWorkStation * transB = new QTransformWorkStation("TransB", 400, 700, 75, 75, &mTracker);
	
	
	QBrush greenBrush(Qt::green);
	QBrush blueBrush(Qt::blue);
	QPen outlinePen(Qt::black);
	outlinePen.setWidth(2);

	//Creation de path
	QPathBuilder pathBuilder;
	
	//Path1
	pathBuilder.setentrypoint(inputA->getCenter());
	pathBuilder.addLinear(205);
	pathBuilder.addLShape(95.0, 300.0, 75.0, 7, true);
	Path * path1 = new Path("path1",20.0, pathBuilder);

	//Path2
	pathBuilder.setentrypoint(transA->getCenter());
	pathBuilder.addLinearOffsetAngle(300,90);
	Path * path2 = new Path("path2", 20.0, pathBuilder);


	//Path3
	pathBuilder.setentrypoint(transB->getCenter());
	pathBuilder.addLinearOffsetAngle(40,90);
	pathBuilder.addCircularRad(160, qDegreesToRadians(90.0), 15);
	pathBuilder.addLinear(140);
	Path * path3 = new Path("path3", 20.0, pathBuilder);

	
	//Path4
	pathBuilder.setentrypoint(transA->getCenter());
	pathBuilder.addLinear(120);
	pathBuilder.addLShape(100.0, 200.0, 75.0, 7, false);
	pathBuilder.addLShape(100.0, 280.0, 75.0, 7, true);
	Path * path4 = new Path("path4", 20.0, pathBuilder);


	//Path5
	pathBuilder.setentrypoint(inputB->getCenter());
	pathBuilder.addLinearOffsetAngle(175, 180);
	pathBuilder.addLShape(100.0, 100.0, 75.0, 7, true);
	pathBuilder.addLShape(100.0, 225.0, 75.0, 7, false);
	Path * path5 = new Path("path5", 20.0, pathBuilder);



	//Connection Path avec Station
	path1->connectPath(inputA, transA);
	inputA->setWorkingSpeed(0.5);

	path2->connectPath(transA, transB);

	path3->connectPath(transB, outputA);

	path4->connectPath(transA, outputB);

	path5->connectPath(inputB, transB);


	//Draw Path et station
	mScene->addItem(path1);
	mScene->addItem(path2);
	mScene->addItem(path3);
	mScene->addItem(path4);
	mScene->addItem(path5);

	mScene->addItem(inputA);
	mScene->addItem(inputB);
	mScene->addItem(outputA);
	mScene->addItem(outputB);
	mScene->addItem(transA);
	mScene->addItem(transB);

}

void GPA789_Lab3::repaintTick()
{
	mTracker.updateMaterial();

	//mView->update();

	mScene->update();
}

void GPA789_Lab3::add(QGroupBox * groupBox, QLabel * & title, QString const & titleText, QWidget * widget, QLabel * & value)
{
	title = new QLabel(titleText);
	value = new QLabel;
	title->setAlignment(Qt::AlignLeft);
	value->setAlignment(Qt::AlignRight);

	groupBox->setLayout(new QVBoxLayout);
	groupBox->layout()->addWidget(title);
	groupBox->layout()->addWidget(widget);
	groupBox->layout()->addWidget(value);
}

void GPA789_Lab3::add(QGroupBox * groupBox, QLabel * & title, QString const & titleText, QWidget * widget)
{
	title = new QLabel(titleText);
	title->setAlignment(Qt::AlignLeft);

	groupBox->layout()->addWidget(title);
	groupBox->layout()->addWidget(widget);
}

void GPA789_Lab3::changeSpeedIntervall()
{
	mStationSelected->setWorkingSpeed(mSliderSpeed->value());
}

void GPA789_Lab3::changeNameItem()
{
	nomItem->setText(mStationSelected->name());
}

void GPA789_Lab3::mousePressEvent(QMouseEvent * mouseEvent)
{
	itemSelect = mView->itemAt(mouseEvent->pos());
	if ((mStationSelected = dynamic_cast<QAbstractWorkStation*>(itemSelect)))
	{
		nomItem->setText(mStationSelected->name());
		mSliderSpeed->setValue(mStationSelected->workingSpeed());
	}
	if ((mPathSelected = dynamic_cast<Path*>(itemSelect)))
	{
		nomItem->setText(mPathSelected->name());
	}

}

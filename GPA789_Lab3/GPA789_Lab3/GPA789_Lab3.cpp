#include "GPA789_Lab3.h"
#include "QTransformWorkStation.h"
#include "QInputWorkStation.h"
#include "QOutputWorkStation.h"
#include "QTransformWorkStation.h"
#include "Path.h"
#include <qgraphicsscene.h>
#include <qgraphicsscenemouseevent>

#include <qlayout>
#include <qrect>
#include <memory>
#include <qgroupBox>
#include <qevent.h>
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
	mSliderSpeed = new QSlider;			mSliderSpeed->setOrientation(Qt::Horizontal);		mSliderSpeed->setRange(1, 250);
	QGroupBox * groupBoxSimParam = new QGroupBox("Paramètres de simulation");
	QVBoxLayout * controlsLayout = new QVBoxLayout;
	add(groupBoxSimParam, mSliderSpeedTitle, "Vitesse Path (m/sec)", mSliderSpeed, mSliderSpeedValue);
	controlsLayout->addWidget(groupBoxSimParam);
	QWidget * controlsWidget = new QWidget;
	controlsWidget->setLayout(controlsLayout);
	controlsWidget->setFixedWidth(250);
	mainHLayout->addWidget(controlsWidget);
	nomItem = new QLabel;

	QWidget * mainWidget = new QWidget;
	mainWidget->setLayout(mainHLayout);


	setCentralWidget(mainWidget);
	
	mRepaintTimer = new QTimer;

	connect(mRepaintTimer, &QTimer::timeout,
		this, &GPA789_Lab3::repaintTick);

	connect(mSliderSpeed, &QSlider::valueChanged, 
		this, &GPA789_Lab3::changeSpeedIntervall);

	connect(nomItem, &QLabel::selectedText,
		this, &GPA789_Lab3::changeNameItem);

	mRepaintTimer->start(33);
	mView->show();
}

GPA789_Lab3::~GPA789_Lab3()
{
}

void GPA789_Lab3::testFunction()
{

	//Creation des station
	QInputWorkStation * inputA = new QInputWorkStation(100, 100, 75, 75, &mTracker);
	QInputWorkStation * inputB = new QInputWorkStation(900, 900, 75, 75, &mTracker);

	QOutputWorkStation * outputA = new QOutputWorkStation(100, 900, 75, 75, &mTracker);
	QOutputWorkStation * outputB = new QOutputWorkStation(900, 100, 75, 75, &mTracker);

	QTransformWorkStation * transA = new QTransformWorkStation(400, 400, 75, 75, &mTracker);
	QTransformWorkStation * transB = new QTransformWorkStation(400, 700, 75, 75, &mTracker);
	
	
	QBrush greenBrush(Qt::green);
	QBrush blueBrush(Qt::blue);
	QPen outlinePen(Qt::black);
	outlinePen.setWidth(2);

	//Creation de path
	QPathBuilder pathBuilder;
	
	//Path1
	pathBuilder.setentrypoint(inputA->getCenter());
	pathBuilder.addLinear(205);
	pathBuilder.addLShape(95.0, 285.0, 75.0, 7, true);
	auto path1 = std::make_shared<Path>(20.0, pathBuilder);
	QPolygonF shape1 = path1->getShape();
	mPathList.append(path1);

	//Path2
	pathBuilder.setentrypoint(transA->getCenter());
	pathBuilder.addLinearOffsetAngle(270,90);
	auto path2 = std::make_shared<Path>(20.0, pathBuilder);
	QPolygonF shape2 = path2->getShape();
	mPathList.append(path2);

	//Path3
	pathBuilder.setentrypoint(transB->getCenter());
	pathBuilder.addLinearOffsetAngle(45,90);
	pathBuilder.addCircularRad(160, qDegreesToRadians(90.0), 15);
	pathBuilder.addLinear(120);
	auto path3 = std::make_shared<Path>(20.0, pathBuilder);
	QPolygonF shape3 = path3->getShape();
	mPathList.append(path3);
	
	//Path4
	pathBuilder.setentrypoint(transA->getCenter());
	pathBuilder.addLinear(100);
	pathBuilder.addLShape(100.0, 200.0, 75.0, 7, false);
	pathBuilder.addLShape(100.0, 280.0, 75.0, 7, true);
	auto path4 = std::make_shared<Path>(20.0, pathBuilder);
	QPolygonF shape4 = path4->getShape();
	mPathList.append(path4);

	//Path5
	pathBuilder.setentrypoint(inputB->getCenter());
	pathBuilder.addLinearOffsetAngle(170, 180);
	pathBuilder.addLShape(100.0, 100.0, 75.0, 7, true);
	pathBuilder.addLShape(100.0, 235.0, 75.0, 7, false);
	auto path5 = std::make_shared<Path>(20.0, pathBuilder);
	QPolygonF shape5 = path5->getShape();
	mPathList.append(path5);


	//Connection Path avec Station

	path1->connectPath(inputA, transA);
	inputA->addPath(path1);
	inputA->setWorkingSpeed(1);

	path2->connectPath(transA, transB);

	path3->connectPath(transB, outputA);

	path4->connectPath(transA, outputB);

	path5->connectPath(inputB, transB);
	inputB->addPath(path5);


	//Draw Path et station
	mScene->addPolygon(shape1, outlinePen, blueBrush);
	mScene->addPolygon(shape2, outlinePen, greenBrush);
	mScene->addPolygon(shape3, outlinePen, blueBrush);
	mScene->addPolygon(shape4, outlinePen, greenBrush);
	mScene->addPolygon(shape5, outlinePen, blueBrush);

	mScene->addItem(inputA);
	mScene->addItem(inputB);
	mScene->addItem(outputA);
	mScene->addItem(outputB);
	mScene->addItem(transA);
	mScene->addItem(transB);

	ListItemScene.append(inputA);
	ListItemScene.append(inputB);
	ListItemScene.append(outputA);
	ListItemScene.append(outputB);
	ListItemScene.append(transA);
	ListItemScene.append(transB);

}

void GPA789_Lab3::repaintTick()
{
	mTracker.updateMaterial();

	mView->update();

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

}

void GPA789_Lab3::changeNameItem()
{
	
}

void GPA789_Lab3::mousePressEvent(QMouseEvent * mouseEvent)
{

	for (int i = 0; i < ListItemScene.size(); i++)
	{
		if (ListItemScene.at(i)->contains(mouseEvent->pos()))
		{
			itemSelect = ListItemScene.at(i);
			if (itemSelect->type()==5)
			{
				mPathSelected = mPathList.at(i);
			}
			typeSelectedItem = itemSelect->type();
		}
	}

}

void GPA789_Lab3::mouseMoveEvent(QMouseEvent * mouseEvent)
{
	for (int i = 0; i < ListItemScene.size(); i++)
	{
		if (ListItemScene.at(i)->contains(mouseEvent->pos()))
			itemSelect = ListItemScene.at(i);
	}
}

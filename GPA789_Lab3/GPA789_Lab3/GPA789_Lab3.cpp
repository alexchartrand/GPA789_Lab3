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
	mTracker = new WorkMaterialTracker(mScene);

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
	delete mTracker;
}

void GPA789_Lab3::testFunction()
{

	//Creation des station
	QInputWorkStation * inputA = new QInputWorkStation(100, 100, 75, 75, mTracker);
	QInputWorkStation * inputB = new QInputWorkStation(900, 900, 75, 75, mTracker);

	QOutputWorkStation * outputA = new QOutputWorkStation(100, 900, 75, 75, mTracker);
	QOutputWorkStation * outputB = new QOutputWorkStation(900, 100, 75, 75, mTracker);

	QTransformWorkStation * transA = new QTransformWorkStation(400, 400, 75, 75, mTracker);
	QTransformWorkStation * transB = new QTransformWorkStation(400, 700, 75, 75, mTracker);
	
	
	QBrush greenBrush(Qt::green);
	QBrush blueBrush(Qt::blue);
	QPen outlinePen(Qt::black);
	outlinePen.setWidth(2);

	//Creation de path
	//Path1
	std::unique_ptr<QPathBuilder> mPathBuilder1(new QPathBuilder);
	mPathBuilder1->setentrypoint(inputA->getCenter());
	mPathBuilder1->addLinear(205);
	mPathBuilder1->addLShape(95.0, 285.0, 75.0, 7, true);
	//Path test pour faire demo
	/*mPathBuilder1->addLinear(200);
	mPathBuilder1->addLShape(100.0, 300.0, 75.0, 7, true);
	mPathBuilder1->addUShape(150, 100, 250, 12, true);
	mPathBuilder1->addLinearOffsetAngle(100, -45);
	mPathBuilder1->addCircular(100, -235, 17);*/
	Path * path1 = new Path(20.0, *mPathBuilder1);
	QPolygonF shape1 = path1->getShape();
	mPathList.append(path1);

	//Path2
	std::unique_ptr<QPathBuilder> mPathBuilder2(new QPathBuilder);
	mPathBuilder2->setentrypoint(transA->getCenter());
	mPathBuilder2->addLinearOffsetAngle(270,90);
	Path * path2 = new Path(20.0, *mPathBuilder2);
	QPolygonF shape2 = path2->getShape();
	mPathList.append(path2);

	//Path3
	std::unique_ptr<QPathBuilder> mPathBuilder3(new QPathBuilder);
	mPathBuilder3->setentrypoint(transB->getCenter());
	mPathBuilder3->addLinearOffsetAngle(45,90);
	mPathBuilder3->addCircularRad(160, qDegreesToRadians(90.0), 15);
	mPathBuilder3->addLinear(120);
	Path * path3 = new Path(20.0, *mPathBuilder3);
	QPolygonF shape3 = path3->getShape();
	mPathList.append(path3);
	
	//Path4
	std::unique_ptr<QPathBuilder> mPathBuilder4(new QPathBuilder);
	mPathBuilder4->setentrypoint(transA->getCenter());
	mPathBuilder4->addLinear(100);
	mPathBuilder4->addLShape(100.0, 200.0, 75.0, 7, false);
	mPathBuilder4->addLShape(100.0, 280.0, 75.0, 7, true);
	Path * path4 = new Path(20.0, *mPathBuilder4);
	QPolygonF shape4 = path4->getShape();
	mPathList.append(path4);

	//Path5
	std::unique_ptr<QPathBuilder> mPathBuilder5(new QPathBuilder);
	mPathBuilder5->setentrypoint(inputB->getCenter());
	mPathBuilder5->addLinearOffsetAngle(170, 180);
	mPathBuilder5->addLShape(100.0, 100.0, 75.0, 7, true);
	mPathBuilder5->addLShape(100.0, 235.0, 75.0, 7, false);
	Path * path5 = new Path(20.0, *mPathBuilder5);
	QPolygonF shape5 = path5->getShape();
	mPathList.append(path5);


	//Connection Path avec Station

	path1->connectPath(inputA, transA);
	inputA->mPath.append(path1);

	path2->connectPath(transA, transB);

	path3->connectPath(transB, outputA);

	path4->connectPath(transA, outputB);

	path5->connectPath(inputB, transB);
	inputB->mPath.append(path5);


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
	mTracker->updateMaterial();

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

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
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <qmessagebox>


GPA789_Lab3::GPA789_Lab3(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	
	//Simulatuer
	mScene = new QGraphicsScene();
	mView = new QInteractiveGraphicsView(mScene); 
	mTracker.addScene(mScene);

	//Creation de l'usine
	testFunction();

	//Controleur
	QHBoxLayout * mainHLayout = new QHBoxLayout;
	mainHLayout->addWidget(mView);
	mSliderSpeed = new QSlider;			mSliderSpeed->setOrientation(Qt::Horizontal);		mSliderSpeed->setRange(0, 10);
	QGroupBox * groupBoxSimParam = new QGroupBox("Paramètres de simulation");
	QGroupBox * groupBoxSimInfo = new QGroupBox("Informations de simulation");
	QPushButton *aboutButton = new QPushButton("À propos...");
	groupBoxSimParam->setLayout(new QVBoxLayout);
	groupBoxSimInfo->setLayout(new QHBoxLayout);
	mNbItems = new QLabel;
	groupBoxSimInfo->layout()->addWidget(new QLabel("Nombre d'item: "));
	groupBoxSimInfo->layout()->addWidget(mNbItems);
	QVBoxLayout * controlsLayout = new QVBoxLayout;
	nomItem = new QLabel("Selectionner un item.");				nomItem->setAlignment(Qt::AlignLeft);
	nNMItem = new QLabel;										nNMItem->setAlignment(Qt::AlignLeft);
	groupBoxSimParam->layout()->addWidget(nomItem);
	groupBoxSimParam->layout()->addWidget(nNMItem);
	add(groupBoxSimParam, mSliderSpeedTitle, "Vitesse (item/sec)", mSliderSpeed, mSliderSpeedValue);
	controlsLayout->addWidget(groupBoxSimParam);
	controlsLayout->addStretch(1);
	controlsLayout->addWidget(groupBoxSimInfo);
	controlsLayout->addStretch(1);
	controlsLayout->addWidget(aboutButton);
	
	QWidget * controlsWidget = new QWidget;
	controlsWidget->setLayout(controlsLayout);
	controlsWidget->setFixedWidth(250);
	mainHLayout->addWidget(controlsWidget);
	

	QWidget * mainWidget = new QWidget;
	mainWidget->setLayout(mainHLayout);


	setCentralWidget(mainWidget);
	
	mRepaintTimer = new QTimer(this);


	//Connect
	connect(mRepaintTimer, &QTimer::timeout,
		this, &GPA789_Lab3::repaintTick);

	connect(mSliderSpeed, &QSlider::valueChanged, 
		this, &GPA789_Lab3::changeSpeedIntervall);

	connect(aboutButton, &QPushButton::clicked,
		this, &GPA789_Lab3::showMessageBox);

	//Affichage

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

	QTransformWorkStation * transA = new QTransformWorkStation("transA", 400, 400, 75, 75, Qt::magenta, &mTracker);
	QTransformWorkStation * transB = new QTransformWorkStation("transB", 400, 700, 75, 75, Qt::green, &mTracker);
	
	
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
	path1->connectPath(inputA, transA->getTransOut());

	path2->connectPath(transA->getTransIn(), transB->getTransOut());

	path3->connectPath(transB->getTransIn(), outputA);

	path4->connectPath(transA->getTransIn(), outputB);

	path5->connectPath(inputB, transB->getTransOut());


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
	if ((mStationSelected = dynamic_cast<QAbstractWorkStation*>(itemSelect)))
	{
		mStationSelected->setWorkingSpeed(mSliderSpeed->value());
		mSliderSpeedValue->setText(QString("%1").arg(mStationSelected->workingSpeed()));

	}
	if ((mPathSelected = dynamic_cast<Path*>(itemSelect)))
	{
		mPathSelected->setSpeed(mSliderSpeed->value());
		mSliderSpeedValue->setText(QString("%1").arg(mPathSelected->getSpeed()));
	}
}

void GPA789_Lab3::mousePressEvent(QMouseEvent * mouseEvent)
{
	static bool itemSlotConnected = false;
	if (itemSlotConnected)
	{
		disconnect(mStationSelected, &QAbstractWorkStation::nbItemChanged,
			mNbItems, &QLabel::setText);
		mNbItems->clear();
		itemSlotConnected = false;
	}
	itemSelect = mView->itemAt(mouseEvent->pos());
	if ((mStationSelected = dynamic_cast<QAbstractWorkStation*>(itemSelect)))
	{
		nomItem->setText(mStationSelected->name());
		mSliderSpeed->setValue(mStationSelected->workingSpeed());
		QMetaObject::Connection con = connect(mStationSelected, &QAbstractWorkStation::nbItemChanged,
			mNbItems, &QLabel::setText);
		itemSlotConnected = con;
	}
	if ((mPathSelected = dynamic_cast<Path*>(itemSelect)))
	{
		nomItem->setText(mPathSelected->name());
		mSliderSpeed->setValue(mPathSelected->getSpeed());
	}

}

void GPA789_Lab3::showMessageBox()
{
	//QPixmap image = QPixmap("Resource/icon.png");


	QMessageBox  about;
	//about.setIconPixmap(image);
	about.setWindowTitle("À propos de Sim2000");
	//about.setWindowIcon(image);
	about.setText(R"#(Sim2000 est un simulateur d'usine.

Ce programme a été réalisé par :
- Alexandre Chratrand
- Jérôme Combet-Blanc

Dans le cadre du cours :
- GPA 789 - Analyse et conception orientées objet
- Laboratoire 3

Version 1.0)#");

	about.exec();

}

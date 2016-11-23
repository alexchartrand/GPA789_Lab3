#include "GPA789_Lab3.h"

#include <qlayout>
#include <qrect>

GPA789_Lab3::GPA789_Lab3(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	mScene = new QGraphicsScene();
	mScene->addText("Un test");
	mView = new QInteractiveGraphicsView(mScene);

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
}

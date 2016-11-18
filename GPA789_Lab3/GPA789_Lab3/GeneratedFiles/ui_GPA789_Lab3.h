/********************************************************************************
** Form generated from reading UI file 'GPA789_Lab3.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GPA789_LAB3_H
#define UI_GPA789_LAB3_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GPA789_Lab3Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *GPA789_Lab3Class)
    {
        if (GPA789_Lab3Class->objectName().isEmpty())
            GPA789_Lab3Class->setObjectName(QStringLiteral("GPA789_Lab3Class"));
        GPA789_Lab3Class->resize(600, 400);
        menuBar = new QMenuBar(GPA789_Lab3Class);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        GPA789_Lab3Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(GPA789_Lab3Class);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        GPA789_Lab3Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(GPA789_Lab3Class);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        GPA789_Lab3Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(GPA789_Lab3Class);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        GPA789_Lab3Class->setStatusBar(statusBar);

        retranslateUi(GPA789_Lab3Class);

        QMetaObject::connectSlotsByName(GPA789_Lab3Class);
    } // setupUi

    void retranslateUi(QMainWindow *GPA789_Lab3Class)
    {
        GPA789_Lab3Class->setWindowTitle(QApplication::translate("GPA789_Lab3Class", "GPA789_Lab3", 0));
    } // retranslateUi

};

namespace Ui {
    class GPA789_Lab3Class: public Ui_GPA789_Lab3Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GPA789_LAB3_H

/********************************************************************************
** Form generated from reading UI file 'Lab11table.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LAB11TABLE_H
#define UI_LAB11TABLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Lab11tableClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Lab11tableClass)
    {
        if (Lab11tableClass->objectName().isEmpty())
            Lab11tableClass->setObjectName("Lab11tableClass");
        Lab11tableClass->resize(600, 400);
        menuBar = new QMenuBar(Lab11tableClass);
        menuBar->setObjectName("menuBar");
        Lab11tableClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Lab11tableClass);
        mainToolBar->setObjectName("mainToolBar");
        Lab11tableClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(Lab11tableClass);
        centralWidget->setObjectName("centralWidget");
        Lab11tableClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Lab11tableClass);
        statusBar->setObjectName("statusBar");
        Lab11tableClass->setStatusBar(statusBar);

        retranslateUi(Lab11tableClass);

        QMetaObject::connectSlotsByName(Lab11tableClass);
    } // setupUi

    void retranslateUi(QMainWindow *Lab11tableClass)
    {
        Lab11tableClass->setWindowTitle(QCoreApplication::translate("Lab11tableClass", "Lab11table", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Lab11tableClass: public Ui_Lab11tableClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LAB11TABLE_H

/********************************************************************************
** Form generated from reading UI file 'lab13observer.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LAB13OBSERVER_H
#define UI_LAB13OBSERVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_lab13observerClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *lab13observerClass)
    {
        if (lab13observerClass->objectName().isEmpty())
            lab13observerClass->setObjectName("lab13observerClass");
        lab13observerClass->resize(600, 400);
        menuBar = new QMenuBar(lab13observerClass);
        menuBar->setObjectName("menuBar");
        lab13observerClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(lab13observerClass);
        mainToolBar->setObjectName("mainToolBar");
        lab13observerClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(lab13observerClass);
        centralWidget->setObjectName("centralWidget");
        lab13observerClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(lab13observerClass);
        statusBar->setObjectName("statusBar");
        lab13observerClass->setStatusBar(statusBar);

        retranslateUi(lab13observerClass);

        QMetaObject::connectSlotsByName(lab13observerClass);
    } // setupUi

    void retranslateUi(QMainWindow *lab13observerClass)
    {
        lab13observerClass->setWindowTitle(QCoreApplication::translate("lab13observerClass", "lab13observer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class lab13observerClass: public Ui_lab13observerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LAB13OBSERVER_H

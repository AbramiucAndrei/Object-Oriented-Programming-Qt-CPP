/********************************************************************************
** Form generated from reading UI file 'lab14.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LAB14_H
#define UI_LAB14_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_lab14Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *lab14Class)
    {
        if (lab14Class->objectName().isEmpty())
            lab14Class->setObjectName("lab14Class");
        lab14Class->resize(600, 400);
        menuBar = new QMenuBar(lab14Class);
        menuBar->setObjectName("menuBar");
        lab14Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(lab14Class);
        mainToolBar->setObjectName("mainToolBar");
        lab14Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(lab14Class);
        centralWidget->setObjectName("centralWidget");
        lab14Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(lab14Class);
        statusBar->setObjectName("statusBar");
        lab14Class->setStatusBar(statusBar);

        retranslateUi(lab14Class);

        QMetaObject::connectSlotsByName(lab14Class);
    } // setupUi

    void retranslateUi(QMainWindow *lab14Class)
    {
        lab14Class->setWindowTitle(QCoreApplication::translate("lab14Class", "lab14", nullptr));
    } // retranslateUi

};

namespace Ui {
    class lab14Class: public Ui_lab14Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LAB14_H

/********************************************************************************
** Form generated from reading UI file 'EXAMEN.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXAMEN_H
#define UI_EXAMEN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EXAMENClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *EXAMENClass)
    {
        if (EXAMENClass->objectName().isEmpty())
            EXAMENClass->setObjectName("EXAMENClass");
        EXAMENClass->resize(600, 400);
        menuBar = new QMenuBar(EXAMENClass);
        menuBar->setObjectName("menuBar");
        EXAMENClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(EXAMENClass);
        mainToolBar->setObjectName("mainToolBar");
        EXAMENClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(EXAMENClass);
        centralWidget->setObjectName("centralWidget");
        EXAMENClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(EXAMENClass);
        statusBar->setObjectName("statusBar");
        EXAMENClass->setStatusBar(statusBar);

        retranslateUi(EXAMENClass);

        QMetaObject::connectSlotsByName(EXAMENClass);
    } // setupUi

    void retranslateUi(QMainWindow *EXAMENClass)
    {
        EXAMENClass->setWindowTitle(QCoreApplication::translate("EXAMENClass", "EXAMEN", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EXAMENClass: public Ui_EXAMENClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXAMEN_H

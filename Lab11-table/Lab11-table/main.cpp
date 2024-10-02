#include "Lab11table.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qtablewidget.h>
#include <QtWidgets/qlabel.h>
#include <Service.hpp>
#include <mainGUI.h>
#include <Test.hpp>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Test t;
    t.runAll();

    RepoFile repo("date.txt");
    RepoReteta reteta;
    Service srv(repo, reteta);

    QWidget* gui = new mainGUI(srv);

    gui->show();

    return a.exec();
}

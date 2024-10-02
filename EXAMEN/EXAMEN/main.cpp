#include "EXAMEN.h"
#include <mainGUI.h>
#include <Test.h>
#include <QtWidgets/QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Test t("test_data.txt");
    t.run_test();
    
    RepoFile repo("date.txt");
    Validator val;
    Service srv(repo, val);
    mainGUI gui(srv);
    gui.show();
    return a.exec();
}

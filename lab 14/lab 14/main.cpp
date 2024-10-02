#include <QApplication>
#include "Test.hpp"
#include "Gui.hpp"
#include "GuiRecipe.hpp"
#include "Service.hpp"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    Test test;
    test.runAll();

    FarmacyFile farmacy{"medicamente.txt"};
    Recipe recipe;

    Service service{farmacy, recipe};

    // Create the GUI and show it
    GUI gui(service);
    gui.show();


    return a.exec();
}
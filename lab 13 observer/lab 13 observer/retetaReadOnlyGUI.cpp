#include "retetaReadOnlyGUI.hpp"

void retetaReadOnlyGUI::update() {
    repaint();
}

void retetaReadOnlyGUI::initReadOnly() {
    lyMain = new QVBoxLayout;
    setLayout(lyMain);

    retetaList = new QListWidget;
    lyMain->addWidget(retetaList);

}

void retetaReadOnlyGUI::reloadList(vector<Medicament> meds) {
    retetaList->clear();
    for (const auto& med : meds) {
        retetaList->addItem(QString::fromStdString(med.getDenumire() + " " + med.getProducator() + " " +
            med.getSubstActiva() + " " + to_string(med.getPret())));
    }
}



retetaReadOnlyGUI::retetaReadOnlyGUI(Service& s ) :srv{ s } {
    //initReadOnly();
    //reloadList(srv.getAllReteta());
    //paintEvent();
}

retetaReadOnlyGUI::~retetaReadOnlyGUI()
{
    srv.remove_observer(this);
}

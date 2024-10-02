#include "retetaGUI.h"

void retetaGUI::initGUI() {
    wdmain = new QVBoxLayout;
    QWidget::setLayout(wdmain);

    list_secondary = new QListWidget();
    wdmain->addWidget(list_secondary);
    add_new = new QPushButton("Add existing medicament");
    wdmain->addWidget(add_new);
    delete_all = new QPushButton("Clear receipt");
    wdmain->addWidget(delete_all);
    exportBtn = new QPushButton("Export to file");
    wdmain->addWidget(exportBtn);
    generateBtn = new QPushButton("Generate reteta");
    wdmain->addWidget(generateBtn);

    form = new QFormLayout;
    field_denumire = new QLineEdit{};
    form->addRow("Denumire med", field_denumire);
    
    QFormLayout* file = new QFormLayout;
    field_file = new QLineEdit{};
    form->addRow("Denumire fisier ", field_file);

    QFormLayout* nr_meds = new QFormLayout;
    field_nr_meds = new QLineEdit{};
    form->addRow("Numar medicamente ", field_nr_meds);

    wdmain->addLayout(form);

}

void retetaGUI::reload_reteta(vector<Medicament>& some)
{
    list_secondary->clear();
    for (const auto& meds : some) {
        list_secondary->addItem(QString::fromStdString(meds.getDenumire() + " " + meds.getProducator() + " " +
            meds.getSubstActiva() + " " + to_string(meds.getPret())));
    }
}

void retetaGUI::connections()
{
    QObject::connect(add_new, &QPushButton::clicked, [this]() {
        srv.addToReteta(field_denumire->text().toStdString());
        reload_reteta(srv.getAllReteta());
        });

    QObject::connect(delete_all, &QPushButton::clicked, [this]() {
        srv.clearReteta();
        reload_reteta(srv.getAllReteta());
        });

    QObject::connect(exportBtn, &QPushButton::clicked, [this]() {
        srv.exportToFile(field_file->text().toStdString());
        QMessageBox::information(nullptr, "Export", "Exportul a avut succes");

        });

    QObject::connect(generateBtn, &QPushButton::clicked, [this]() {
        srv.generateReteta(field_nr_meds->text().toInt());
        reload_reteta(srv.getAllReteta());
        });
}

void retetaGUI::update()
{
    reload_reteta(srv.getAllReteta());
}

retetaGUI::~retetaGUI()
{
    srv.remove_observer(this);
}



#include "mainGUI.h"
#include <retetaGUI.h>


void mainGUI::initialize_gui() {

    lyMain = new QHBoxLayout;
    lyLeft = new QVBoxLayout;
    lyRight = new QVBoxLayout;
    QWidget::setLayout(lyMain);
    lyMain->addLayout(lyLeft);
    lyMain->addLayout(lyRight);
    //LEFT
    //lyLeft->addWidget(new QPushButton("&1"));
    medlist = new QTableWidget{ 0,4 };
    medlist->setSelectionBehavior (QAbstractItemView::SelectRows);
    medlist->setSelectionMode(QAbstractItemView::SingleSelection);
    //medlist->setColumnCount(4);
    lyLeft->addWidget(medlist);

    listmed = new QListWidget;
    lyLeft->addWidget(listmed);


    removeBtn = new QPushButton{ "Remove selected" };
    lyLeft->addWidget(removeBtn);
    sortByDenumire = new QPushButton{ "Sort by denumire" };
    lyLeft->addWidget(sortByDenumire);
    sortByProducer = new QPushButton{ "Sort by producer" };
    lyLeft->addWidget(sortByProducer);
    sortBySubstance = new QPushButton{ "Sort by substance" };
    lyLeft->addWidget(sortBySubstance);
    sortByPrice = new QPushButton{ "Sort by price" };
    lyLeft->addWidget(sortByPrice);

    //right
    QFormLayout* form = new QFormLayout;
    denumire = new QLineEdit{};
    form->addRow("Denumire ", denumire);

    producer = new QLineEdit{};
    form->addRow("Producer ", producer);

    substance = new QLineEdit{};
    form->addRow("Substance ", substance);

    price = new QLineEdit{};
    form->addRow("Price ", price);
    lyRight->addLayout(form);

    //retetaGUI
    open_reteta_gui = new QPushButton("Open reteta Page");
    lyRight->addWidget(open_reteta_gui);

    open_read_only_gui = new QPushButton("Open read-only reteta Page");
    lyRight->addWidget(open_read_only_gui);

    lyMiddle = new QHBoxLayout;
    
   /* auto the_list = srv.getAll();
    unordered_map<string, int> producatori;
    for (auto& x : the_list) {
        producatori[x.getProducator()]++;
    }*/

    auto the_list = srv.createRaport();

    int nr_prod = the_list.size();
    for (auto it : the_list) {
        auto btn = new QPushButton(QString::fromStdString(it.first));
        QObject::connect(btn, &QPushButton::clicked, [=]() {
            string mesaj ="Numarul de medicamente cu acest producator:" ;
            int numar = it.second;
            QMessageBox::information(this, "info", QString::fromStdString(mesaj+ to_string(numar)));
            });
        lyMiddle->addWidget(btn);
    }
    lyRight->addLayout(lyMiddle);
    //medlist
    filter_subst = new QPushButton{ "Filter by substance" };
    lyRight->addWidget(filter_subst);

    filter_min_price = new QPushButton{ "Filter by min price" };
    lyRight->addWidget(filter_min_price);
    


    add_new = new QPushButton{ "Add Medicament"};
    lyRight->addWidget(add_new);

    to_delete = new QPushButton{ "Delete Medicament" };
    lyRight->addWidget(to_delete);

    modify = new QPushButton{ "Modify Medicament" };
    lyRight->addWidget(modify);

    exitbtn = new QPushButton("Exit");
    lyRight->addWidget(exitbtn);

    


}

void mainGUI::reload_list(vector <Medicament> meds) {

    medlist->clear();
    listmed->clear();
    medlist->setRowCount(meds.size());
    //medlist->setColumnCount(4);
    for (int i = 0; i<meds.size();i++) {
        //medlist->addItem(QString::fromStdString(med.getDenumire()));
        medlist->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(meds[i].getDenumire())));
        medlist->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(meds[i].getProducator())));
        medlist->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(meds[i].getSubstActiva())));
        auto* last = new QTableWidgetItem(QString::fromStdString(to_string(meds[i].getPret())));
        last->setBackground(QBrush{ Qt::red,Qt::SolidPattern });
        medlist->setItem(i, 3, last);

        listmed->addItem(QString::fromStdString(meds[i].getDenumire() + " " + meds[i].getProducator() + " " +
            meds[i].getSubstActiva() + " " + to_string(meds[i].getPret())));
    }
}

void mainGUI::connections() {
    //connect signal-slot
    QObject::connect(removeBtn, &QPushButton::clicked, [&]() {
        auto selected = medlist->selectedItems();
        if (!selected.isEmpty()) {
                srv.deleteMedicament(selected.at(0)->text().toStdString());
                reload_list(srv.getAll());
        }
        });

    QObject::connect(sortByDenumire, &QPushButton::clicked, [&]() {
        vector<Medicament> meds = srv.sortMedicamenteName();
        reload_list(meds);
        });

    QObject::connect(sortByProducer, &QPushButton::clicked, [&]() {
        vector<Medicament> meds = srv.sortMedicamenteProducer();
        reload_list(meds);
        });

    QObject::connect(sortBySubstance, &QPushButton::clicked, [&]() {
        vector<Medicament> meds = srv.sortMedicamenteSubstPrice();
        reload_list(meds);
        });

    QObject::connect(sortByPrice, &QPushButton::clicked, [&]() {
        vector<Medicament> meds = srv.sortMedicamente([&](const Medicament& medicament1, const Medicament& medicament2) {
            return medicament1.getPret() < medicament2.getPret();
            });
        reload_list(meds);
        });

    QObject::connect(medlist, &QTableWidget::itemSelectionChanged, [&]() {
        auto selected = medlist->selectedItems();
        if (selected.isEmpty()) {
            denumire->setText("");
            producer->setText("");
            substance->setText("");
            price->setText("");
        }
        else {
            auto med = selected.at(0);
            
            
            string to_search = med->text().toStdString();

            vector <Medicament> srv_repo = srv.getAll();
            Medicament original = *find_if(srv_repo.begin(), srv_repo.end(), [&](const Medicament& ot) {
                return ot.getDenumire() == to_search; });

            denumire->setText(QString::fromStdString(original.getDenumire()));
            producer->setText(QString::fromStdString(original.getProducator()));
            substance->setText(QString::fromStdString(original.getSubstActiva()));
            price->setText(QString::fromStdString(to_string(original.getPret())));
        }
        });
    QObject::connect(add_new, &QPushButton::clicked, [&]() {
        try {
            srv.addMedicament(denumire->text().toStdString(), producer->text().toStdString(),
                substance->text().toStdString(), price->text().toInt());
            reload_list(srv.getAll());
        }
        catch (exception& e) {
            qDebug() << e.what();
        }
    });

    QObject::connect(to_delete, &QPushButton::clicked, [&]() {
        try {
            srv.deleteMedicament(denumire->text().toStdString());
            reload_list(srv.getAll());
        }
        catch (exception& e) {
            qDebug() << e.what();
        }
        });
    QObject::connect(modify, &QPushButton::clicked, [&]() {
        try {
            srv.updateMedicament(denumire->text().toStdString(), producer->text().toStdString(),
                substance->text().toStdString(), price->text().toInt());
            reload_list(srv.getAll());
        }
        catch (exception& e) {
            qDebug() << e.what();
        }
    });

    QObject::connect(exitbtn, &QPushButton::clicked, &QApplication::exit);

    QObject::connect(filter_subst, &QPushButton::clicked, [&]() {
        vector<Medicament> meds = srv.filterMedicamenteSubst(substance->text().toStdString());
        reload_list(meds);
        });

    QObject::connect(filter_min_price, &QPushButton::clicked, [&]() {
        vector<Medicament> meds = srv.filterMedicamente(price->text().toInt());
        reload_list(meds);
        });

    QObject::connect(open_reteta_gui, &QPushButton::clicked, [this]() {
        retetaGUI* page = new retetaGUI(srv);
        srv.add_observer(page);
        page->show();
        });

    QObject::connect(open_read_only_gui, &QPushButton::clicked, [this]() {
        retetaReadOnlyGUI* page = new retetaReadOnlyGUI(srv);
        srv.add_observer(page);
        page->show();
        });
}
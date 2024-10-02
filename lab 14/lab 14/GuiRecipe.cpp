#include "GuiRecipe.hpp"

void GUIRecipe::initLayout() {
    main_layout = new QVBoxLayout(this);
    list_widget = new QListWidget(this);

    form_layout = new QFormLayout;
    input_denumire = new QLineEdit(this);
    input_pret = new QSlider(Qt::Horizontal, this);
    input_pret->setRange(1, 10);

    form_layout->addRow(new QLabel("Enter the denumire:", this), input_denumire);
    form_layout->addRow(new QLabel("Enter the cantity:", this), input_pret);

    btn_add = new QPushButton("Add", this);
    btn_delete = new QPushButton("Delete All", this);
    btn_populate = new QPushButton("Populate Random", this);
    btn_export_html = new QPushButton("Export HTML", this);
    btn_export_csv = new QPushButton("Export CSV", this);

    form_layout->addRow(btn_add);
    form_layout->addRow(btn_delete);
    form_layout->addRow(btn_populate);
    form_layout->addRow(btn_export_html);
    form_layout->addRow(btn_export_csv);

    main_layout->addWidget(list_widget);
    main_layout->addLayout(form_layout);
}

void GUIRecipe::connectSignals() {
    service.addListener(this);

    connect(btn_add, &QPushButton::clicked, [this]() {
        std::string denumire = input_denumire->text().toStdString();

        try {
            service.addMedicamentRecipe(denumire);
            refreshList();
            QMessageBox::information(this, "Succes", "The element was added in the Recipe");
        } catch (const std::exception &error) {
            QMessageBox::warning(this, "Error", error.what());
        }
    });

    connect(btn_delete, &QPushButton::clicked, [this]() {
        try {
            service.deleteAllMedicamentsRecipe();
            refreshList();
            QMessageBox::information(this, "Succes", "All elements were deleted from the Recipe");
        } catch (const std::exception &error) {
            QMessageBox::warning(this, "Error", error.what());
        }
    });

    connect(btn_populate, &QPushButton::clicked, [this]() {
        int count = input_pret->value();

        try {
            service.populateRandomRecipe(count);
            refreshList();
            QMessageBox::information(this, "Succes", "The Recipe was populated with random medicamente");
        } catch (const std::exception &error) {
            QMessageBox::warning(this, "Error", error.what());
        }
    });

    connect(btn_export_html, &QPushButton::clicked, [this]() {
        try {
            service.exportHTML("../database/export.html");
            QMessageBox::information(this, "Succes", "The Recipe was exported to HTML");
        } catch (const std::exception &error) {
            QMessageBox::warning(this, "Error", error.what());
        }
    });

    connect(btn_export_csv, &QPushButton::clicked, [this]() {
        try {
            service.exportCSV("../database/export.csv");
            QMessageBox::information(this, "Succes", "The Recipe was exported to CSV");
        } catch (const std::exception &error) {
            QMessageBox::warning(this, "Error", error.what());
        }
    });
}

void GUIRecipe::refreshList() {
    list_widget->clear();
    for (const auto &item : service.getAllRecipe()) {
        QString q_string = QString::fromStdString(item.intoString());
        list_widget->addItem(q_string);
    }
}
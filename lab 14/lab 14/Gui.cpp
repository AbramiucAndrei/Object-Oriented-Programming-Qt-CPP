#include "Gui.hpp"
#include "GuiRecipe.hpp"
#include <QLabel>
#include <QMessageBox>

GUI::GUI(Service &service, QWidget *parent) : QMainWindow(parent), service{service} {
    initLayout();
    connectSignals();
    generateProducatorButtons();
}

void GUI::initLayout() {
    main_widget = new QWidget(this);
    main_layout = new QHBoxLayout(main_widget);

    form_layout = new QFormLayout;

    input_denumire = new QLineEdit(this);
    input_producator = new QLineEdit(this);
    input_substanta = new QLineEdit(this);
    input_pret = new QLineEdit(this);
    input_count = new QSlider(Qt::Horizontal, this);
    input_count->setRange(1, 10);

    form_layout->addRow(new QLabel("Denumire:"), input_denumire);
    form_layout->addRow(new QLabel("Producator:"), input_producator);
    form_layout->addRow(new QLabel("Substanta:"), input_substanta);
    form_layout->addRow(new QLabel("Pret:"), input_pret);
    form_layout->addRow(new QLabel("Enter cantity:"), input_count);

    add_btn = new QPushButton{"Add"};
    delete_btn = new QPushButton{"Delete"};
    update_btn = new QPushButton{"Update"};

    search_btn = new QPushButton{"Search by denumire"};
    filter_pret_btn = new QPushButton{"Filter by pret"};

    sort_denumire_btn = new QPushButton{"Sort by denumire"};
    sort_pret_btn = new QPushButton{"Sort by pret"};

    add_recipe_btn = new QPushButton{"Add to Recipe"};
    delete_recipe_btn = new QPushButton{"Delete Recipe"};
    populate_recipe_btn = new QPushButton{"Populate Recipe"};

    undo_btn = new QPushButton{"Undo"};
    refresh_btn = new QPushButton{"Refresh"};
    recipe_window_btn = new QPushButton{"Recipe menu"};
    recipe_drawing_btn = new QPushButton{"Recipe Drawing"};

    auto *button_widget_crud = new QHBoxLayout;
    button_widget_crud->addWidget(add_btn);
    button_widget_crud->addWidget(delete_btn);
    button_widget_crud->addWidget(update_btn);

    auto *button_widget_filter = new QHBoxLayout;
    button_widget_filter->addWidget(search_btn);
    button_widget_filter->addWidget(filter_pret_btn);

    auto *button_widget_recipe = new QHBoxLayout;
    button_widget_recipe->addWidget(add_recipe_btn);
    button_widget_recipe->addWidget(delete_recipe_btn);
    button_widget_recipe->addWidget(populate_recipe_btn);

    auto *button_widget_sort = new QHBoxLayout;
    button_widget_sort->addWidget(sort_denumire_btn);
    button_widget_sort->addWidget(sort_pret_btn);

    auto *button_widget_options = new QHBoxLayout;
    button_widget_options->addWidget(recipe_window_btn);
    button_widget_options->addWidget(recipe_drawing_btn);
    button_widget_options->addWidget(refresh_btn);
    button_widget_options->addWidget(undo_btn);

    form_layout->addRow(button_widget_crud);
    form_layout->addRow(button_widget_filter);
    form_layout->addRow(button_widget_sort);
    form_layout->addRow(button_widget_recipe);

    table_view = new QTableView(this);
    model = new TableModel(service, this);
    table_view->setModel(model);
    table_view->setMinimumWidth(400);
    table_view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    auto *table_layout = new QVBoxLayout;
    table_layout->addWidget(table_view);
    table_layout->addLayout(button_widget_options);

    main_layout->addLayout(form_layout);
    main_layout->addLayout(table_layout);

    this->setCentralWidget(main_widget);
}

void GUI::connectSignals() {
    connect(table_view->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {
        const auto selected = table_view->selectionModel()->selectedRows();

        if (selected.isEmpty()) return;

        const auto index = selected.first();
        input_denumire->setText(model->data(model->index(index.row(), 0)).toString());
        input_producator->setText(model->data(model->index(index.row(), 1)).toString());
        input_substanta->setText(model->data(model->index(index.row(), 2)).toString());
        input_pret->setText(model->data(model->index(index.row(), 3)).toString());
    });

    QObject::connect(add_btn, &QPushButton::clicked, [this]() {
        try {
            service.addMedicamentFarma(input_denumire->text().toStdString(), input_producator->text().toStdString(),
                                       input_substanta->text().toStdString(), input_pret->text().toInt());
            model->refreshModel();

            QMessageBox::information(this, "Succes", "The element was added");
        } catch (const std::exception &error) {
            QMessageBox::warning(this, "Error", error.what());
        }
    });

    QObject::connect(delete_btn, &QPushButton::clicked, [this]() {
        const auto selected = table_view->selectionModel()->selectedRows();

        if (selected.isEmpty()) return;

        const auto index = selected.first();
        const auto Qname = model->data(model->index(index.row(), 0)).toString();

        try {
            service.deleteMedicamentFarma(Qname.toStdString());
            model->refreshModel();

            QMessageBox::information(this, "Succes", "The element was deleted");
        } catch (const std::exception &error) {
            QMessageBox::warning(this, "Error", error.what());
        }
    });

    QObject::connect(update_btn, &QPushButton::clicked, [this]() {
        try {
            service.updateMedicamentFarma(input_denumire->text().toStdString(), input_producator->text().toStdString(),
                                          input_substanta->text().toStdString(), input_pret->text().toInt());
            model->refreshModel();

            QMessageBox::information(this, "Succes", "The element was updated");
        } catch (const std::exception &error) {
            QMessageBox::warning(this, "Error", error.what());
        }
    });

    QObject::connect(search_btn, &QPushButton::clicked, [this]() {
        try {
            auto medicamente = service.findMedicamentFarma(input_denumire->text().toStdString());
            model->setRecords(medicamente);
        } catch (const std::exception &error) {
            QMessageBox::warning(this, "Error", error.what());
        }
    });

    QObject::connect(filter_pret_btn, &QPushButton::clicked, [this]() {
        try {
            auto filter_pret = service.filterMedicamenteFarma(input_pret->text().toInt());
            model->setRecords(filter_pret);
        } catch (const std::exception &error) {
            QMessageBox::warning(this, "Error", error.what());
        }
    });

    QObject::connect(sort_denumire_btn, &QPushButton::clicked, [this]() {
        auto sorted_denumire = service.sortMedicamenteFarma(
                [&](const Medicament &a, const Medicament &b) {
                    return a.getDenumire() <= b.getDenumire();
                });

        model->setRecords(sorted_denumire);
    });

    QObject::connect(sort_pret_btn, &QPushButton::clicked, [this]() {
        auto sorted_pret = service.sortMedicamenteFarma(
                [&](const Medicament &a, const Medicament &b) {
                    return a.getPret() <= b.getPret();
                });

        model->setRecords(sorted_pret);
    });

    QObject::connect(add_recipe_btn, &QPushButton::clicked, [this]() {
        const auto selected = table_view->selectionModel()->selectedRows();

        if (selected.isEmpty()) return;

        const auto index = selected.first();
        const auto Qname = model->data(model->index(index.row(), 0)).toString();

        try {
            service.addMedicamentRecipe(Qname.toStdString());

            QMessageBox::information(this, "Succes", "The element was added to recipe");
        } catch (const std::exception &error) {
            QMessageBox::warning(this, "Error", error.what());
        }
    });

    QObject::connect(delete_recipe_btn, &QPushButton::clicked, [this]() {
        try {
            service.deleteAllMedicamentsRecipe();

            QMessageBox::information(this, "Succes", "All elements were deleted from the recipe");
        } catch (const std::exception &error) {
            QMessageBox::warning(this, "Error", error.what());
        }
    });

    QObject::connect(populate_recipe_btn, &QPushButton::clicked, [this]() {
        int count = input_count->value();

        try {
            service.populateRandomRecipe(count);

            QMessageBox::information(this, "Succes", "The recipe was populated with random medicamente");
        } catch (const std::exception &error) {
            QMessageBox::warning(this, "Error", error.what());
        }
    });

    QObject::connect(recipe_window_btn, &QPushButton::clicked, [this]() {
        auto *window = new GUIRecipe(service);
        window->show();
    });

    QObject::connect(recipe_drawing_btn, &QPushButton::clicked, [this]() {
        auto *window = new RecipeDrawing(service);
        window->show();
    });

    QObject::connect(refresh_btn, &QPushButton::clicked, [this]() {
        model->refreshModel();
    });

    QObject::connect(undo_btn, &QPushButton::clicked, [this]() {
        try {
            service.undo();
            model->refreshModel();

            QMessageBox::information(this, "Succes", "The last operation was undone");
        } catch (const std::exception &error) {
            QMessageBox::warning(this, "Error", error.what());
        }
    });
}

void GUI::generateProducatorButtons() {
    std::unordered_map<std::string, int> raport = service.getProducatorReport();

    for (const auto &entry: raport) {
        const std::string &producator = entry.first;

        auto *producatorButton = new QPushButton(QString::fromStdString(producator));
        form_layout->addRow(producatorButton);

        QObject::connect(producatorButton, &QPushButton::clicked, [&, producator]() {
            auto medicamente = service.filterProducator(producator);
            model->setRecords(medicamente);
        });
    }


}
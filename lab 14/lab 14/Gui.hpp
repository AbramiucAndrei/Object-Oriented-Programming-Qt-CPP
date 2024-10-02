#pragma once

#include "TableModel.hpp"
#include "GuiRecipe.hpp"
#include "RecipeDrawing.hpp"

#include <QApplication>
#include <QHeaderView>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QFormLayout>
#include <QListWidget>
#include <QMessageBox>
#include <QDialog>
#include <QTableWidget>
#include <QMainWindow>

class GUI : public QMainWindow {
private:
    Service &service;
    TableModel *model;

    // Buttons

    QPushButton *add_btn;
    QPushButton *delete_btn;
    QPushButton *update_btn;
    QPushButton *search_btn;

    QPushButton *filter_pret_btn;
    QPushButton *sort_denumire_btn;
    QPushButton *sort_pret_btn;

    QPushButton *add_recipe_btn;
    QPushButton *delete_recipe_btn;
    QPushButton *populate_recipe_btn;

    QPushButton *refresh_btn;
    QPushButton *undo_btn;
    QPushButton *recipe_window_btn;
    QPushButton *recipe_drawing_btn;

    std::unordered_map<std::string, QPushButton *> producator_buttons;

    // Input Boxes

    QLineEdit *input_denumire;
    QLineEdit *input_producator;
    QLineEdit *input_substanta;
    QLineEdit *input_pret;
    QSlider *input_count;

    // Layout and Widget

    QFormLayout *form_layout;
    QTableView *table_view;

    // Main layout

    QWidget *main_widget;
    QHBoxLayout *main_layout;

    /**
     * Allocates the components and constructs the layout of the GUI.
     */
    void initLayout();

    /**
     * Gives functionality to the buttons.
     */
    void connectSignals();

    /*
     * Add method to create producator buttons
     */
    void generateProducatorButtons();
public:
    /**
     * The constructor for the GUI class.
     * @param service the service reference that the class is gonna use.
     */
    explicit GUI(Service &service, QWidget *parent = nullptr);
};
#pragma once
#include <qmainwindow.h>
#include <qwidget.h>
#include <qboxlayout.h>
#include <qpushbutton.h>
#include <qlistwidget.h>
#include <qmessagebox.h>
#include <qformlayout.h>
#include <qlineedit.h>
#include <Observer.hpp>
#include <retetaReadOnlyGUI.hpp>
#include <Service.hpp>
class retetaGUI :
    public QWidget, public Observer
{
    private:
        Service& srv;
        QVBoxLayout* wdmain;

        QPushButton* add_new;
        QPushButton* delete_all;
        QPushButton* exportBtn;
        QPushButton* generateBtn;
        //QListWidget* list_secondary;

        QFormLayout* form;
        QLineEdit* field_denumire;
        QLineEdit* field_file;
        QLineEdit* field_nr_meds;

        void initGUI();
        void reload_reteta(vector<Medicament>& some);
        void connections();
   

    public:
        void update() override;
        QListWidget* list_secondary;
        retetaGUI() = delete;
        retetaGUI(Service& s) :srv{ s } {
            initGUI();
            reload_reteta(srv.getAllReteta());
            connections();
        }
        ~retetaGUI();
};


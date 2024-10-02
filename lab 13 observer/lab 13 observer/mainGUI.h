#pragma once
#include <qwidget.h>
#include <Service.hpp>
#include "Lab11table.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qtablewidget.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qtablewidget.h>
#include <QtWidgets/qabstractitemview.h>
#include <QtWidgets/qmessagebox.h>
#include <QtWidgets/qlayoutitem.h>
#include <QtWidgets/qwidget.h>
class mainGUI :
    public QWidget
{
private:
    Service &srv;
    QHBoxLayout* lyMain;
    QVBoxLayout* lyLeft;
    QVBoxLayout* lyRight;
    QHBoxLayout* lyMiddle;

    //left
    //QListWidget* medlist;
    QTableWidget* medlist;
    QListWidget* listmed;

    QPushButton* removeBtn;
    QPushButton* sortByDenumire;
    QPushButton* sortByProducer;
    QPushButton* sortBySubstance;
    QPushButton* sortByPrice;

    //right
    QLineEdit* denumire;
    QLineEdit* producer;
    QLineEdit* substance;
    QLineEdit* price;

    QPushButton* filter_subst;
    QPushButton* filter_min_price;
    QPushButton* add_new;
    QPushButton* to_delete;
    QPushButton* modify;
    QPushButton* exitbtn;
    // new window
    QPushButton* open_reteta_gui;
    QPushButton* open_read_only_gui;
    
    

    void initialize_gui();
    void reload_list(vector <Medicament> meds);
    void connections();
public:
    mainGUI() = delete;
    mainGUI(Service& serv):srv{serv}{
        initialize_gui();
        connections();
        reload_list(srv.getAll());
    }

};


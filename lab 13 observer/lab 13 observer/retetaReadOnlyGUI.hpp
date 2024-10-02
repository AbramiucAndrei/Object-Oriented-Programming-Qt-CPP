#pragma once
#include <qwidget.h>
#include <qboxlayout.h>
#include <qlistwidget.h>
#include <retetaGUI.h>
#include <Service.hpp>
#include <qpainter.h>
#include <Observer.hpp>
using namespace std;
class retetaReadOnlyGUI :
    public QWidget,public Observer
{
    private:
        //retetaGUI& reteta;
        QVBoxLayout* lyMain ;
        QListWidget* retetaList;
        Service& srv;
        

        void update() override;

        void initReadOnly();

        void reloadList(vector <Medicament> meds);
    public:
        retetaReadOnlyGUI() = delete;
        retetaReadOnlyGUI(Service& s);
        void paintEvent(QPaintEvent* ev) override {
            QPainter p{ this };
            
            int x = 10;
            for (int i = 0; i < srv.getLenReteta();i++) {
                p.drawRect(x, 0, 20, 250);
                x += 40;
            }
        }

        ~retetaReadOnlyGUI();

};


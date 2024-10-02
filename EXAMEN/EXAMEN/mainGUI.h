#pragma once
#include <qwidget.h>
#include <qtablewidget.h>
#include <Service.h>
#include <qpushbutton.h>
#include <qboxlayout.h>
#include <qmessagebox.h>
#include <qformlayout.h>
#include <qlineedit.h>
#include "stareGUI.h"
class mainGUI:public QWidget, public Observer
{
	Service& srv;
	QVBoxLayout* mainLayout;
	//tabel
	QTableWidget* table1;

	//liniile de completat pt a adauga un nou task
	QFormLayout* form;
	QLineEdit* id_line;
	QLineEdit* desc_line;
	QLineEdit* progrs_line;
	QLineEdit* stare_line;
	//add button
	QPushButton* addBtn;

	//filtrare
	QLineEdit* filtreaza;

	stareGUI* to_open;
	stareGUI* to_closed;
	stareGUI* to_inprogress;



	//reincarca tabelul
	void reloadTable(vector<Task> tasks);
	//initializeaza fereastra principala
	void initGUI();
	//conexiuni cu butoanele
	void connections();

public:
	mainGUI(Service& srv) :srv{ srv } {
		initGUI();
		connections();
		reloadTable(srv.get_all());
	}





	// Inherited via Observer
	//reseteaza tabela
	void update() override;
	~mainGUI();

};


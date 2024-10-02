#pragma once
#include <Service.h>
#include <qwidget.h>
#include <qlistwidget.h>
#include <qpushbutton.h>
#include <qboxlayout.h>
class stareGUI:public QWidget,public Observer
{

	Service& srv;
	//tipul ferestrei : open,closed,inprogress
	string type;
	QVBoxLayout* mainl;

	//lista de taskuri
	QListWidget* list;
	QPushButton* open;
	QPushButton* inprogress;
	QPushButton* closed;

	//initializeaza lista
	void initGUI();

	//leaga conexiuni la butoane
	void connections();
	//reincarca lista
	void reloadList();
public:
	stareGUI(Service& srv, string t) :srv{ srv }, type{ t } {
		initGUI();
		connections();
		reloadList();
	}



	// Inherited via Observer
	//reseteaza lista dupa modificari
	void update() override;
	~stareGUI();
};


#include "stareGUI.h"

void stareGUI::initGUI()
{
	mainl= new QVBoxLayout;
	setLayout(mainl);

	list = new QListWidget{};
	mainl->addWidget(list);

	open = new QPushButton{ "OPEN" };
	inprogress = new QPushButton{ "inprogress" };
	closed = new QPushButton{ "closed" };
	mainl->addWidget(open);
	mainl->addWidget(inprogress);
	mainl->addWidget(closed);

	
}

void stareGUI::connections()
{
	

	QObject::connect(open, &QPushButton::clicked, [&]() {
		if (list->selectedItems().size() == 0)
			return;
			srv.set_stare(list->selectedItems().at(0)->data(Qt::UserRole).toInt(), "open");
		});
	QObject::connect(closed, &QPushButton::clicked, [&]() {
		if (list->selectedItems().size() == 0)
			return;
		srv.set_stare(list->selectedItems().at(0)->data(Qt::UserRole).toInt(), "closed");
		});
	QObject::connect(inprogress, &QPushButton::clicked, [&]() {
		if (list->selectedItems().size() == 0)
			return;
		srv.set_stare(list->selectedItems().at(0)->data(Qt::UserRole).toInt(), "inprogress");
		});
}

void stareGUI::reloadList()
{
	list->clear();
	vector<Task> lst;
	if (type == "open")
		lst = srv.get_all_open();
	else if (type == "closed")
		lst = srv.get_all_closed();
	else
		lst = srv.get_all_inprogress();

	for (int i = 0; i < lst.size(); i++) {
		auto noul = new QListWidgetItem{ QString::fromStdString(to_string(lst[i].get_id()) + " " + lst[i].get_descriere() +
																"   " + lst[i].get_stare()) };
		noul->setData(Qt::UserRole, lst[i].get_id());
		list->addItem(noul);
	}
}

void stareGUI::update()
{
	reloadList();
}

stareGUI::~stareGUI()
{
	srv.remove_obs(this);
}



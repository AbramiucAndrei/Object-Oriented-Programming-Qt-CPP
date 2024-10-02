#include "mainGUI.h"



void mainGUI::initGUI()
{
	srv.add_obs(this);

	mainLayout = new QVBoxLayout;
	setLayout(mainLayout);

	table1 = new QTableWidget(0, 4);
	mainLayout->addWidget(table1);
	table1->setSelectionBehavior(QAbstractItemView::SelectRows);
	table1->setSelectionMode(QAbstractItemView::SingleSelection);

	form = new QFormLayout();
	id_line = new QLineEdit;
	form->addRow("ID:", id_line);

	desc_line = new QLineEdit;
	form->addRow("descriere:", desc_line);

	progrs_line = new QLineEdit;
	form->addRow("programatori:", progrs_line);

	stare_line = new QLineEdit;
	form->addRow("stare: ", stare_line);
	mainLayout->addLayout(form);

	addBtn = new QPushButton("ADD NEW");
	mainLayout->addWidget(addBtn);

	to_open = new stareGUI(srv, "open");
	to_closed = new stareGUI(srv, "closed");
	to_inprogress = new stareGUI(srv, "inprogress");

	srv.add_obs(to_open);
	srv.add_obs(to_closed);
	srv.add_obs(to_inprogress);

	to_open->show();
	to_closed->show();
	to_inprogress->show();

	filtreaza = new QLineEdit;
	mainLayout->addWidget(filtreaza);


}

void mainGUI::connections()
{
	QObject::connect(addBtn, &QPushButton::clicked, [&]() {
		try {
			vector<string> pros;
			string string_pros = progrs_line->text().toStdString();
			stringstream str3(string_pros);

			string new_pro;
			while (getline(str3, new_pro, ',')) {
				pros.push_back(new_pro);
			}

			srv.add_new(id_line->text().toInt(), desc_line->text().toStdString(), pros,
				stare_line->text().toStdString());
			reloadTable(srv.get_all());
		}
		catch (exception& e) {
			QMessageBox::warning(nullptr, "!!!", e.what());
		}
	}
	);
	QObject::connect(filtreaza, &QLineEdit::textChanged, [&]() {
		if (filtreaza->text() == "")
			reloadTable(srv.get_all());
		else {
			string the_text = filtreaza->text().toStdString();
			reloadTable(srv.filter_by_progr(the_text));
		}
		});
}

void mainGUI::update()
{
	reloadTable(srv.get_all());
}

mainGUI::~mainGUI()
{
	srv.remove_obs(this);
}

void mainGUI::reloadTable(vector<Task> tasks)
{
	table1->clear();
	table1->setRowCount(tasks.size());
	for (int i = 0; i < tasks.size(); i++) {
		table1->setItem(i, 0, new QTableWidgetItem( QString::fromStdString(to_string(tasks.at(i).get_id()))));
		table1->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(tasks.at(i).get_descriere())));
		table1->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(tasks.at(i).get_stare())));
		table1->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(to_string(tasks.at(i).get_progr().size()))));
	}
}

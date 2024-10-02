#pragma once
#include <RepoFile.h>
#include <Validator.h>
#include <Observer.h>
class Service:public Subject
{
	RepoFile& repo;
	Validator& val;
public:
	Service() = delete;
	Service(RepoFile& r, Validator& v) :repo{ r }, val{ v } {
		//se sorteaza toate alfabetic dupa stare
		sort_by_stare();
	}

	//returneaza lista de taskuri din repo
	vector<Task>& get_all();

	//sorteaza dupa stare taskurile
	void sort_by_stare();

	//adauga un nou task, daca este valid
	void add_new(int id, string denumire, vector<string> ps, string stare);

	//returneaza toate taskurile closed
	vector<Task> get_all_closed();
	//returneaza toate taskurile open
	vector<Task> get_all_open();
	//returneaza toate taskurile inprogress
	vector<Task> get_all_inprogress();
	//seteaza starea pt un anumit task cu id ul dat
	void set_stare(int id, string stare);
	vector<Task> filter_by_progr(string p);
};


#pragma once
#include <Task.h>

#include <sstream>
#include<iostream>
#include <fstream>
class RepoFile
{
	string filename;
	vector<Task> list;

	//ia toate din fisiere si le incarca
	void importAll();

	//salveaza toate in fisier
	void save();
public:
	RepoFile(string fname) :filename{ fname } {
		importAll();
	}
	//get all from repo
	vector<Task>& get_all();
	//store new task
	void store(Task nou);
	//seteaza starea la un anumit task
	void set_stare(int id, string stare);
	
};


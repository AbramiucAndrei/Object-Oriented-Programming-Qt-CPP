#pragma once
#include <vector>
#include <string>
using namespace std;


class Task
{
	int id;//id ul taskului
	string descriere;//descriere task
	vector<string> programatori; //lista de programatori ce au lucrat
	string stare; // open, inprogress,closed

public:
	Task() = delete;
	Task(int i,string d, vector<string>lista,string s):
		id{i},descriere{d},programatori{lista},stare{s}{}

	//getter pt id
	int get_id();
	//getter pt descriere
	string get_descriere();
	//getter pt lista de programatori
	vector<string> get_progr();
	//getter pentru stare
	string get_stare();
	//setter pentru starre
	void set_stare(string stare);
};


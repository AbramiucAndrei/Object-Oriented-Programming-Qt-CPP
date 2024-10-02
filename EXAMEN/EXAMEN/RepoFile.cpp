#include "RepoFile.h"


void RepoFile::importAll()
{
	ifstream fin(filename);
	string line;
	while (fin >> line) {
		stringstream str(line);
		string id, den, stare;
		vector<string>progrs;

		if (line != "") {
			getline(str, id, ';');
			getline(str, den, ';');
			string s_progrs;
			getline(str, s_progrs, ';');
			stringstream str2(s_progrs);
			string new_p;
			while (getline(str2, new_p, ',')) {
				progrs.push_back(new_p);
			}
			getline(str, stare, ';');
			//cout << id<<' ' << den<<' ' << stare<<endl;
			store(Task(stoi(id), den, progrs, stare));
		}
	}
	fin.close();
}

void RepoFile::save()
{
	ofstream fout(filename);

	for (auto& t : list) {
		fout << t.get_id() << ";" << t.get_descriere() << ";";
		for (int i = 0; i < t.get_progr().size(); i++)
		{
			fout << t.get_progr().at(i);
			if (i < t.get_progr().size() - 1)
				fout << ",";
		}
		fout << ";";
		fout << t.get_stare() << endl;
	}

	fout.close();
}

vector<Task>& RepoFile::get_all()
{
	return list;
}

void RepoFile::store(Task nou)
{
	list.push_back(nou);
	save();
}

void RepoFile::set_stare(int id, string stare)
{
	auto it = find_if(list.begin(), list.end(), [id](Task& t) {
		return t.get_id() == id;
		});
	(*it).set_stare(stare);
	save();

}

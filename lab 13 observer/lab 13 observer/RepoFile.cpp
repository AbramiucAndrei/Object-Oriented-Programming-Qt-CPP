#include "RepoFile.h"
#include <fstream>
#include <sstream>

void RepoFile::readFile()
{
	ifstream fin(file_name);
	if (!fin.is_open())
		throw RepoExp("Nu s a deschis fisierul pentru citire!");

	string line;
	while (getline(fin,line)) {
		string denumire;
		string producator;
		string substActiva;
		string pret;
		int real_pret;

		//string line;
		// >> line;
		//if (line == "") break;
		stringstream streamm(line);

		getline(streamm, denumire, ';');
		getline(streamm, producator, ';');
		getline(streamm, substActiva, ';');
		getline(streamm, pret, ';');
		real_pret=stoi(pret);

		Repository1::addMedicament(Medicament(denumire, producator, substActiva, real_pret));
	}
	fin.close();
}

void RepoFile::writeFile() {
	
	ofstream fout(file_name);
	if (!fout.is_open())
		throw RepoExp("Nu s a deschis pentru scriere!");

	vector<Medicament> lista = Repository1::getMedicamente();
	for (const Medicament& med : lista) {
		fout << med.getDenumire() + ";" << med.getProducator() + ";" << med.getSubstActiva() + ";" << med.getPret() << '\n';
	}
	fout.close();
}

void RepoFile::addMedicament(const Medicament& medicament) {
	Repository1::addMedicament(medicament); 
	writeFile();
}

Medicament RepoFile::deleteMedicament(const string& denumire) {
	Medicament deleted = Repository1::deleteMedicament(denumire);
	writeFile();
	return deleted;
}

Medicament RepoFile::updateMedicament(const string& denumire, const Medicament& new_medicament) {
	Medicament updated = Repository1::updateMedicament(denumire, new_medicament);
	writeFile();
	return updated;
}
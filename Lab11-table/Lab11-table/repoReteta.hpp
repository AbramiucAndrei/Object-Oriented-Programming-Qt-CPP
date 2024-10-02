#include "Medicament.hpp"

#include <vector>
#include <fstream>
using std::vector;
using std::string;
class RepoReteta {

	vector <Medicament> reteta;
public:
	//sterge toate medicamentele din reteta
	void deleteAll() noexcept;

	//adauga medicament pe reteta
	void addMed(const Medicament& new_med);

	void Export(const string& file_name);

	vector<Medicament>& getAll() { return reteta; }

	size_t getLenReteta() { return reteta.size(); }

	//vector<Medicament>::iterator findMedicament(const string& denumire);
};
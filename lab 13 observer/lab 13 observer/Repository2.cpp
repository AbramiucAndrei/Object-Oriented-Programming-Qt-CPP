#include "Repository2.h"
#include <random>
vector<Medicament> Repository2::getMedicamente() {
    
    vector<Medicament> lista_med;
    for (const auto& pair : dict) {
        lista_med.push_back(pair.second);
    }

    return lista_med;
}
[[nodiscard]] size_t Repository2::getLen() const {
    return dict.size();
}

/// Adds a Medicament object to the repository
void Repository2::addMedicament(const Medicament& medicament)  {
    throw_error();
    auto search = find_if(dict.begin(), dict.end(), [=](const pair<string, Medicament>& ot) {
        return ot.second.getDenumire() == medicament.getDenumire();
        });
    if (search != dict.end())
        throw RepoExp("Medicamentul exsita deja!");

    dict[medicament.getDenumire()] = medicament;

}


Medicament Repository2::updateMedicament(const string& denumire, const Medicament& new_medicament) {
    throw_error();
    auto search = find_if(dict.begin(), dict.end(), [=](const pair<string, Medicament>& ot) {
        return ot.second.getDenumire() == denumire;
        });
    if (search == dict.end())
        throw RepoExp("Medicamentul nu exista!");

    Medicament to_return = dict[denumire];
    dict[denumire] = new_medicament;
    return to_return;
}


Medicament Repository2::deleteMedicament(const string& denumire) {
    throw_error();
    auto search = find_if(dict.begin(), dict.end(), [=](const pair<string, Medicament>& ot) {
        return ot.second.getDenumire() == denumire;
        });
    if (search == dict.end())
        throw RepoExp("Medicamentul nu exista!");

    Medicament to_Return = (*search).second;
    dict.erase(denumire);
    return to_Return;
}

void Repository2::throw_error() {
    std::mt19937 gen(std::random_device{}());
    std::uniform_real_distribution<> distribution(0, 1);


    double random_number = distribution(gen);
    if (random_number < probability) {
        throw runtime_error("The random prob is " + std::to_string(random_number));
    }
}
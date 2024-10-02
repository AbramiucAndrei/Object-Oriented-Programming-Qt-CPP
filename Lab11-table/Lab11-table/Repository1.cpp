#include "Repository1.h"
#include <iostream>
#include "repoException.h"

vector<Medicament> Repository1::getMedicamente(){
    return items;
}

size_t Repository1::getLen() const {
    return items.size();
}

void Repository1::addMedicament(const Medicament& medicament) {
    auto search = findMedicament(medicament.getDenumire());
    if (search != items.end())
        throw RepoExp("Medicamentul exista deja!");

    items.push_back(medicament);
}

Medicament Repository1::updateMedicament(const string& denumire, const Medicament& new_medicament) {

    //*position = new_medicament;

    auto med = findMedicament(denumire);
    if (med == items.end())
        throw RepoExp("Medicamentul nu a fost gasit!");

    Medicament to_return = *med;
    *med = new_medicament;
    return to_return;

}

Medicament Repository1::deleteMedicament(const string& denumire){
    auto med = findMedicament(denumire);
    if (med == items.end())
        throw RepoExp("Medicamentul nu a fost gasit!");

    Medicament to_return = *med;
    items.erase(med);
    return to_return;
}

vector<Medicament>::iterator Repository1::findMedicament(const std::string& denumire) {
    return std::find_if(items.begin(), items.end(), [=](const Medicament& medicament) {
        return medicament.getDenumire() == denumire;
        });
}
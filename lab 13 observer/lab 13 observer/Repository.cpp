//
//#include "Repository.hpp"
//#include <iostream>
//#include "repoException.h"
//
//vector<Medicament> &Repository::getMedicamente() {
//    return items;
//}
//
//size_t Repository::getLen() const {
//    return items.size();
//}
//
//void Repository::addMedicament(const Medicament &medicament) {
//    items.push_back(medicament);
//}
//
//Medicament Repository::updateMedicament(const string& denumire, const Medicament& new_medicament) {
//
//    //*position = new_medicament;
//
//    auto med = findMedicament(denumire);
//    if (med == items.end())
//        throw RepoExp("Medicamentul nu a fost gasit!");
//
//    Medicament to_return = *med;
//    *med = new_medicament;
//    return to_return;
//    
//}
//
//Medicament Repository::deleteMedicament(const string& denumire) {
//    auto med = findMedicament(denumire);
//    if (med == items.end())
//        throw RepoExp("Medicamentul nu a fost gasit!");
//
//    Medicament to_return = *med;
//    items.erase(med);
//    return to_return;
//}
//
//vector<Medicament>::iterator Repository::findMedicament(const std::string &denumire) {
//    return std::find_if(items.begin(), items.end(),[=](const Medicament &medicament) {
//        return medicament.getDenumire() == denumire;
//    });
//}
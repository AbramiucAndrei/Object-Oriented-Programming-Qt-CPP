//
// Created by Mihai Adomnitei on 13.04.2024.
//

#include "Service.hpp"
#include "Validator.hpp"
#include "serviceException.hpp"
#include <algorithm>
#include <random>

Service::Service(Repository& repo, RepoReteta& reporeteta) : repo(repo), repoReteta{ reporeteta } {}

vector<Medicament> Service::getAll() {
    return repo.getMedicamente();
}

void Service::addMedicament(const std::string &denumire, const std::string &producator, const std::string &substActiva, int pret) {

    Medicament new_medicament(denumire, producator, substActiva, pret);
    Validator::validateMedicament(new_medicament);
    repo.addMedicament(new_medicament);
    undo.push_back(make_unique<UndoAdauga>(repo, new_medicament));
}

void Service::updateMedicament(const std::string &denumire, const std::string &new_producator, const std::string &new_substActiva, int new_pret) {
    
    Medicament new_medicament(denumire, new_producator, new_substActiva, new_pret);
    Validator::validateMedicament(new_medicament);
    
    Medicament before_update = repo.updateMedicament(denumire, new_medicament);
    undo.push_back(make_unique<UndoModifica>(repo, new_medicament, before_update));
    
}

void Service::deleteMedicament(const std::string &denumire) {
    Medicament deleted = repo.deleteMedicament(denumire);
    undo.push_back(make_unique<UndoSterge>(repo, deleted));
}

vector<Medicament> Service::findMedicament(const std::string &denumire) {
    vector<Medicament> list = repo.getMedicamente();
    vector<Medicament> foundMedicamente(list.size());

    auto iter = copy_if(list.begin(), list.end(), foundMedicamente.begin(), [&](const Medicament& medicament) {
        return medicament.getDenumire() == denumire;
        });
    foundMedicamente.erase(iter, foundMedicamente.end());

    //for(const auto &book : repo.getMedicamente()){
    //    if (book.getDenumire() == denumire){
    //        foundMedicamente.push_back(book);
    //    }
    //}

    return foundMedicamente;
}

vector<Medicament> Service::filterMedicamente(int min_price) {
    vector<Medicament> filteredMedicamente;
    vector <Medicament> repo_list = repo.getMedicamente();

    copy_if(repo_list.begin(), repo_list.end(), back_inserter(filteredMedicamente),
        [=](const Medicament& ot) {return ot.getPret() >= min_price; });

    //for(const auto &book : repo.getMedicamente()){
    //    if (book.getPret() >= min_price){
    //        filteredMedicamente.push_back(book);
    //    }
    //}

    return filteredMedicamente;
}

vector<Medicament> Service::filterMedicamenteSubst(const std::string &substActiva) {
    vector<Medicament> filteredMedicamente;
    vector <Medicament> repo_list = repo.getMedicamente();

    copy_if(repo_list.begin(), repo_list.end(), back_inserter(filteredMedicamente),
        [&](const Medicament& ot) {return ot.getSubstActiva() == substActiva; });

    //for(const auto &book : repo.getMedicamente()){
    //    if (book.getSubstActiva() == substActiva){
    //        filteredMedicamente.push_back(book);
    //    }
    //}

    return filteredMedicamente;
}

vector<Medicament> Service::sortMedicamente(const std::function<bool(const Medicament &, const Medicament &)> &compare) {
    vector<Medicament> sortedMedicamente = repo.getMedicamente();
    //size_t len = sortedMedicamente.size();

    //for(size_t i = 0; i < len - 1; i++){
    //    for(size_t j = i + 1; j < len; j++){
    //        Medicament &medicament1 = sortedMedicamente[i];
    //        Medicament &medicament2 = sortedMedicamente[j];

    //        if (compare(medicament1, medicament2)){
    //            Medicament temp = sortedMedicamente[i];
    //            sortedMedicamente[i] = sortedMedicamente[j];
    //            sortedMedicamente[j] = temp;
    //        }
    //    }
    //}
    sort(sortedMedicamente.begin(), sortedMedicamente.end(), compare);
    return sortedMedicamente;
}

vector<Medicament> Service::sortMedicamenteSubstPrice() {
    vector<Medicament> sortedMedicamente = repo.getMedicamente();
    /*size_t len = sortedMedicamente.size();

    for(size_t i = 0; i < len - 1; i++){
        for(size_t j = i + 1; j < len; j++){
            Medicament &medicament1 = sortedMedicamente[i];
            Medicament &medicament2 = sortedMedicamente[j];

            
            if (medicament1.getSubstActiva() > medicament2.getSubstActiva()) {
                Medicament temp = sortedMedicamente[i];
                sortedMedicamente[i] = sortedMedicamente[j];
                sortedMedicamente[j] = temp;
            }
            else if (medicament1.getSubstActiva() == medicament2.getSubstActiva()) {
                if (medicament1.getPret() > medicament2.getPret()) {
                    Medicament temp = sortedMedicamente[i];
                    sortedMedicamente[i] = sortedMedicamente[j];
                    sortedMedicamente[j] = temp;
                }
            }
        }
    }*/
    sort(sortedMedicamente.begin(), sortedMedicamente.end(),[](const Medicament& a, const Medicament& b) {
        if (a.getSubstActiva() == b.getSubstActiva()) {
            if (a.getPret() < b.getPret())
                return true;
            else
                return false;
        }
        else if (a.getSubstActiva() < b.getSubstActiva())
            return true;
        else
            return false;
            });
    return sortedMedicamente;
}

vector<Medicament> Service::sortMedicamenteName() {
    vector<Medicament> sortedMedicamente = repo.getMedicamente();
    /*size_t len = sortedMedicamente.size();

    for(size_t i = 0; i < len - 1; i++){
        for(size_t j = i + 1; j < len; j++){
            Medicament &medicament1 = sortedMedicamente[i];
            Medicament &medicament2 = sortedMedicamente[j];

            if (medicament1.getDenumire() > medicament2.getDenumire()){
                Medicament temp = sortedMedicamente[i];
                sortedMedicamente[i] = sortedMedicamente[j];
                sortedMedicamente[j] = temp;
            }

        }
    }*/
    sort(sortedMedicamente.begin(), sortedMedicamente.end(), [](const Medicament& a, const Medicament& b) {
        return a.getDenumire() < b.getDenumire();
        });
    return sortedMedicamente;
}

vector<Medicament> Service::sortMedicamenteProducer() {
    vector<Medicament> sortedMedicamente = repo.getMedicamente();
    /*size_t len = sortedMedicamente.size();

    for(size_t i = 0; i < len - 1; i++){
        for(size_t j = i + 1; j < len; j++) {
            Medicament &medicament1 = sortedMedicamente[i];
            Medicament &medicament2 = sortedMedicamente[j];

            if (medicament1.getProducator() > medicament2.getProducator()) {
                Medicament temp = sortedMedicamente[i];
                sortedMedicamente[i] = sortedMedicamente[j];
                sortedMedicamente[j] = temp;
            }
        }
    }*/
    sort(sortedMedicamente.begin(), sortedMedicamente.end(), [](const Medicament& a, const Medicament& b) {
        return a.getProducator() < b.getProducator();
        });

    return sortedMedicamente;
}


void Service::clearReteta() noexcept {
    repoReteta.deleteAll();
    notify();
}

void Service::addToReteta(const string& denumire) {
    vector <Medicament> repo_list = repo.getMedicamente();
    auto x= find_if(repo_list.begin(), repo_list.end(), [=](const Medicament& medicament) {
        return medicament.getDenumire() == denumire;
        });

    if (x == repo_list.end())
        throw ServiceExp("Medicamentul nu exista!");

    repoReteta.addMed(*x);
    notify();
}

void Service::exportToFile(const string& file_name) {
    repoReteta.Export(file_name);
}

void Service::generateReteta(const int& nrmed) {
    if (nrmed == 0)
        throw ServiceExp("Numar de medicamente invalid!");
    if (repo.getLen() == 0)
        throw ServiceExp("Nu exista medicamente in farmacie!");

    repoReteta.deleteAll();

    vector <Medicament> repo_list = repo.getMedicamente();
    for (int i = 0; i < nrmed; i++) {
        std::mt19937 mt{ std::random_device{}() };
        std::uniform_int_distribution<> dist(0, int(repo_list.size() - 1));
        int rndNr = dist(mt);// numar aleator intre [0,size-1]

        repoReteta.addMed(repo_list[rndNr]);
    }

    notify();
}

map <string, int> Service::createRaport() const {
    map <string, int> raport;
    for (const Medicament& med : repo.getMedicamente()) {
        raport[med.getProducator()]++;
    }
    return raport;
}

map <string, int> Service::createRaportReteta() const {
    map <string, int> raport;
    for (const Medicament& med : repoReteta.getAll() ) {
        raport[med.getProducator()]++;
    }
    return raport;
}

void Service::executeUndo() {
    if (undo.size() == 0)
        throw ServiceExp("Nu se mai poate face undo!");

    undo.back()->doUndo();
    undo.pop_back();
}
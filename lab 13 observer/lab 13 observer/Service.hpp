

#pragma once
using namespace std;

#include "Repository.hpp"
#include "Repository1.h"
#include "Repository2.h"
#include "RepoFile.h"
#include "repoReteta.hpp"
#include "undo.hpp"
#include <map>
#include <Observer.hpp>
#include <memory>

class Service : public Subject{
    private:
    Repository &repo; // Reference to the repository
    RepoReteta &repoReteta;//reference to the reteta repository
    vector<unique_ptr<ActiuneUndo>> undo;
    
    public:
    /// Constructor

    explicit Service(Repository &repo, RepoReteta& repoReteta);

    /// Retrieves all the Medicament objects from the repository
    vector<Medicament> getAll();

    /// Adds a Medicament object to the repository
    void addMedicament(const std::string &denumire, const std::string &producator, const std::string &substActiva, int pret);

    /// Updates a Medicament object from the repository
    void updateMedicament(const std::string &denumire, const std::string &new_producator, const std::string &new_substActiva, int new_pret);

    /// Deletes a Medicament object from the repository
    void deleteMedicament(const std::string &denumire);

    /// Find a Medicament object in the repository
    vector<Medicament> findMedicament(const std::string &denumire);

    /// Filter the Medicament objects from the repository by price
    vector<Medicament> filterMedicamente(int min_price);

    ///Filter the Medicament objects from the repository by substance
    vector<Medicament> filterMedicamenteSubst(const std::string &substActiva);

    /// Sort the Medicament objects from the repository by price
    vector<Medicament> sortMedicamente(const std::function<bool(const Medicament &, const Medicament &)> &compare);

    /// Sort the medicament objects by name
    vector<Medicament> sortMedicamenteName(); 

    /// Sort the medicament objects by producer
    vector<Medicament> sortMedicamenteProducer();

    /// Sort the medicament objects by substance and price
    vector<Medicament> sortMedicamenteSubstPrice();

    //do undo
    void executeUndo();

    //Clear "reteta"
    void clearReteta() noexcept;

    void addToReteta(const string& denumire);
    
    void exportToFile(const string& file_name);

    void generateReteta(const int& nrmed);

    size_t getLenReteta() { return repoReteta.getLenReteta(); }

    map <string, int> createRaport() const;

    map <string, int> createRaportReteta() const;

    vector <Medicament>& getAllReteta() { return repoReteta.getAll(); }

};
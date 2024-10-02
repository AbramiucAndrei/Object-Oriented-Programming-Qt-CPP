#pragma once
#include"Repository.hpp"
#include "repoException.h"
#include <unordered_map>
class Repository2:public Repository
{
private:
	unordered_map<string, Medicament> dict;
    double probability;
    void throw_error();
	
public:
    Repository2() = delete;
    Repository2(double p): probability{p}{}
    /// Retrieves all the Medicament objects
    vector<Medicament> getMedicamente() override;

    /// Retrieves the length of the repository
    [[nodiscard]] size_t getLen() const override;

    /// Adds a Medicament object to the repository
    void addMedicament(const Medicament& medicament) override;

    /// Updates a Medicament object from the repository
    //returns old medicament
    Medicament updateMedicament(const string& denumire, const Medicament& new_medicament) override;
      

    /// Deletes a Medicament object from the repository
    //returns deleted medicament
    Medicament deleteMedicament(const string& denumire) override;


      ~Repository2() override = default;
    /// Finds a Medicament object in the repository
    //vector<Medicament>::iterator findMedicament(const std::string &denumire);
};


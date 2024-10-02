

#pragma once
using namespace std;
#include "Medicament.hpp"
#include "Repository.hpp"
//#include "Vector.hpp"
//#include "Iterator.hpp"
#include <vector>
#include <functional>

class Repository1:public Repository {
private:
    vector<Medicament> items; // Vector of Medicament objects

public:

    /// Default constructor
    Repository1() = default;

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

    /// Finds a Medicament object in the repository
    vector<Medicament>::iterator findMedicament(const std::string& denumire) ;
};
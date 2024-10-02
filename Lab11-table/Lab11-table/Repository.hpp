
#pragma once
using namespace std;
#include "Medicament.hpp"
//#include "Vector.hpp"
//#include "Iterator.hpp"
#include <vector>
#include <functional>

class Repository {

public:

    /// Retrieves all the Medicament objects
    virtual vector<Medicament> getMedicamente() =0;

    /// Retrieves the length of the repository
    [[nodiscard]]virtual size_t getLen() const =0;

    /// Adds a Medicament object to the repository
    virtual void addMedicament(const Medicament &medicament)=0;

    /// Updates a Medicament object from the repository
    //returns old medicament
    virtual Medicament updateMedicament(const string &denumire, const Medicament& new_medicament)=0;

    /// Deletes a Medicament object from the repository
    //returns deleted medicament
    virtual Medicament deleteMedicament(const string &denumire)=0;
    
    virtual ~Repository() = default;
    /// Finds a Medicament object in the repository
    //vector<Medicament>::iterator findMedicament(const std::string &denumire);
};
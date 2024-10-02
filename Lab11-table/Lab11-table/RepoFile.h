#pragma once
#include "Repository1.h"
#include "repoException.h"
class RepoFile :    public Repository1
{
private:
    string file_name;
    void readFile();
    void writeFile();
public:
    RepoFile() = delete;
    RepoFile(string fname) : file_name{ fname } {
        readFile();
    } 

    /// Adds a Medicament object to the repository
    void addMedicament(const Medicament& medicament) override;

    /// Updates a Medicament object from the repository
    //returns old medicament
    Medicament updateMedicament(const string& denumire, const Medicament& new_medicament) override;

    /// Deletes a Medicament object from the repository
    //returns deleted medicament
    Medicament deleteMedicament(const string& denumire) override;
};


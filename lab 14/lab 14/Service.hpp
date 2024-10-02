// Created by Mihai Adomnitei on 27.03.2024.

#pragma once

#include "Undo.hpp"
#include "Validator.hpp"
#include "Observer.hpp"

#include <functional>
#include <unordered_map>
#include <random>

class ServiceError : public std::runtime_error {
public:
    explicit ServiceError(const std::string &message) : std::runtime_error(message) {}
};

class Service : public Subject {
private:
    AbstractFarmacy &farmacy; // Reference to a Repository object
    Recipe &recipe; // Reference to a Recipe object

    std::vector<std::unique_ptr<AbstractUndo>> history; // Vector containing all modifications of farmacy

public:
    Service(AbstractFarmacy &farmacy, Recipe &recipe);

    std::vector<Medicament> getAllFarma();
    std::vector<Medicament> &getAllRecipe();

    void addMedicamentFarma(const std::string &denumire,const std::string &producator,const std::string &substActiva,int pret);
    void updateMedicamentFarma(const std::string &denumire, const std::string &new_producator, const std::string &new_substActiva,int new_pret);
    void deleteMedicamentFarma(const std::string &denumire);
    std::vector<Medicament> findMedicamentFarma(const std::string &denumire);
    std::vector<Medicament> filterMedicamenteFarma(int min_pret);
    std::vector<Medicament> filterProducator(const std::string &producator);
    std::vector<Medicament>sortMedicamenteFarma(const std::function<bool(const Medicament &, const Medicament &)> &compare);

    void addMedicamentRecipe(const std::string &denumire);
    void deleteAllMedicamentsRecipe();
    void populateRandomRecipe(size_t medicament_count);

    void exportHTML(const std::string &file_name);
    void exportCSV(const std::string &filename);

    int getMedCountByProducator(const std::string& producator);

    std::vector<std::string>getAllProducatori();

    std::unordered_map<std::string, int> getProducatorReport();

    void undo();
};
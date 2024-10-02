#pragma once

#include "Medicament.hpp"

#include <vector>
#include <unordered_map>
#include <exception>
#include <stdexcept>
#include <vcruntime.h>


class RepositoryError : public std::runtime_error {
public:
    explicit RepositoryError(const std::string &message) : std::runtime_error(message) {}
};

/*
 * ABSTRACT REPOSITORY
 */

class AbstractFarmacy {
public:
    AbstractFarmacy() = default;
    virtual ~AbstractFarmacy() = default;
    virtual std::vector<Medicament> getMedicamente() = 0;
    [[nodiscard]] virtual size_t getLen() const = 0;
    virtual void addMedicament(const Medicament &medicament) = 0;
    virtual Medicament deleteMedicament(const std::string &denumire) = 0;
    virtual Medicament updateMedicament(const std::string &denumire, const Medicament &new_medicament) = 0;
    virtual bool findMedicament(const std::string &denumire) = 0;
};

/*
 * FARMACY REPOSITORY
 */

class FarmacyVector : public AbstractFarmacy {
protected:
    std::vector<Medicament> items;
public:
    ~FarmacyVector() override = default;
    std::vector<Medicament> getMedicamente() override;
    [[nodiscard]] size_t getLen() const override;
    void addMedicament(const Medicament &medicament) override;
    Medicament deleteMedicament(const std::string &denumire) override;
    Medicament updateMedicament(const std::string &denumire, const Medicament &new_medicament) override;
    bool findMedicament(const std::string &denumire) override;
};

/*
 * FARMACY DICT
 */

class FarmacyDict : public AbstractFarmacy {
private:
    std::unordered_map<std::string, Medicament> items;
    double probability;
public:
    explicit FarmacyDict(double probability);
    ~FarmacyDict() override = default;
    std::vector<Medicament> getMedicamente() override;
    [[nodiscard]] size_t getLen() const override;
    void addMedicament(const Medicament &medicament) override;
    Medicament deleteMedicament(const std::string &denumire) override;
    Medicament updateMedicament(const std::string &denumire, const Medicament &new_medicament) override;
    bool findMedicament(const std::string &denumire) override;
    void throwError() const;
};

/*
 * FARMACY FILE REPOSITORY
 */

class FarmacyFile : public FarmacyVector {
private:
    std::string file_name;
    void loadFromFile();
    void writeToFile();
public:
    explicit FarmacyFile(std::string file_name);
    void addMedicament(const Medicament &medicament) override;
    Medicament deleteMedicament(const std::string &denumire) override;
    Medicament updateMedicament(const std::string &denumire, const Medicament &new_medicament) override;
};

/*
 * RECIPE REPOSITORY
 */

class Recipe {
private:
    std::vector<Medicament> items;
public:
    Recipe() = default;
    std::vector<Medicament> &getMedicamente();
    [[nodiscard]] size_t getLen() const;
    void addMedicament(const Medicament &medicament);
    void deleteAllMedicamente();
};
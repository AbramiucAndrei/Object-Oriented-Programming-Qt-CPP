#include "Repository.hpp"

#include <fstream>
#include <utility>
#include <sstream>
#include <random>

/*
 * FARMACY REPOSITORY
 */

std::vector<Medicament> FarmacyVector::getMedicamente() {
    return items;
}

size_t FarmacyVector::getLen() const {
    return items.size();
}

void FarmacyVector::addMedicament(const Medicament &medicament) {
    items.push_back(medicament);
}

Medicament FarmacyVector::deleteMedicament(const std::string &denumire) {
    auto it = std::find_if(items.begin(), items.end(), [&denumire](const Medicament &medicament) {
        return medicament.getDenumire() == denumire;
    });

    Medicament deleted_medicament = *it;
    items.erase(it);
    return deleted_medicament;
}

Medicament FarmacyVector::updateMedicament(const std::string &denumire, const Medicament &new_medicament) {
    auto it = std::find_if(items.begin(), items.end(), [&denumire](const Medicament &medicament) {
        return medicament.getDenumire() == denumire;
    });

    Medicament previous_medicament = *it;
    *it = new_medicament;
    return previous_medicament;
}

bool FarmacyVector::findMedicament(const std::string &denumire) {
    auto it = std::find_if(items.begin(), items.end(), [&denumire](const Medicament &medicament) {
        return medicament.getDenumire() == denumire;
    });

    return it != items.end();
}

/*
 * FARMACY DICT
 */

FarmacyDict::FarmacyDict(double probability) : probability{probability} {}

std::vector<Medicament> FarmacyDict::getMedicamente() {
    throwError();

    std::vector<Medicament> output;

    for (const auto &pair : items) {
        output.push_back(pair.second);
    }

    return output;
}

size_t FarmacyDict::getLen() const {
    return items.size();
}

void FarmacyDict::addMedicament(const Medicament &medicament) {
    throwError();
    items[medicament.getDenumire()] = medicament;
}

Medicament FarmacyDict::deleteMedicament(const std::string &denumire) {
    throwError();
    auto it = items.find(denumire);

    Medicament deleted_medicament = it->second;
    items.erase(it);
    return deleted_medicament;
}

Medicament FarmacyDict::updateMedicament(const std::string &denumire, const Medicament &new_medicament) {
    throwError();
    auto it = items.find(denumire);

    Medicament previous_medicament = it->second;
    it->second = new_medicament;
    return previous_medicament;
}

bool FarmacyDict::findMedicament(const std::string &denumire) {
    throwError();
    return items.find(denumire) != items.end();
}

void FarmacyDict::throwError() const {
    std::mt19937 gen(std::random_device{}());
    std::uniform_real_distribution<> distribution(0, 1);

    double random_number = distribution(gen);
    if (random_number < probability) {
        throw RepositoryError("The random prob is " + std::to_string(random_number));
    }
}

/*
 * FARMACY FILE REPOSITORY
 */

void FarmacyFile::loadFromFile() {
    std::ifstream in(file_name);
    if (!in.is_open()) {
        throw RepositoryError("Can't open file: " + file_name);
    }

    std::string line;
    while (std::getline(in, line)) {
        std::stringstream stream(line);

        std::string token;
        std::vector<std::string> split;

        while (getline(stream, token, ',')) {
            split.push_back(token);
        }

        if (split.size() == 4) {
            std::string denumire = split[0];
            std::string producator = split[1];
            std::string substActiva = split[2];
            int pret = stoi(split[3]);

            FarmacyVector::addMedicament({denumire, producator, substActiva, pret});
        }
    }

    in.close();
}

void FarmacyFile::writeToFile() {
    std::ofstream out(file_name);

    for (const Medicament &medicament : items) {
        out << medicament.getDenumire() << ','
            << medicament.getProducator() << ','
            << medicament.getSubstActiva() << ','
            << medicament.getPret() << '\n';
    }

    out.close();
}

FarmacyFile::FarmacyFile(std::string file_name) : FarmacyVector(), file_name{std::move(file_name)} {
    loadFromFile();
}

void FarmacyFile::addMedicament(const Medicament &medicament) {
    FarmacyVector::addMedicament(medicament);
    writeToFile();
}

Medicament FarmacyFile::deleteMedicament(const std::string &denumire) {
    auto deleted_medicament = FarmacyVector::deleteMedicament(denumire);
    writeToFile();
    return deleted_medicament;
}

Medicament FarmacyFile::updateMedicament(const std::string &denumire, const Medicament &new_medicament) {
    auto updated_medicament = FarmacyVector::updateMedicament(denumire, new_medicament);
    writeToFile();
    return updated_medicament;
}

/*
 * RECIPE REPOSITORY
 */

std::vector<Medicament> &Recipe::getMedicamente() {
    return items;
}

size_t Recipe::getLen() const {
    return items.size();
}

void Recipe::addMedicament(const Medicament &medicament) {
    items.push_back(medicament);
}

void Recipe::deleteAllMedicamente() {
    items.clear();
}
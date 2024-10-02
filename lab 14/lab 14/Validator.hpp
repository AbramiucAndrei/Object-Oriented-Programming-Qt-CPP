//
// Created by Mihai Adomnitei on 13.04.2024.
//

#pragma once

#include <string>
#include "Medicament.hpp"

class Validator {
private:
    /// Check if denumire is valid
    static bool isValidDenumire(const std::string &denumire);

    /// Check if producator is valid
    static bool isValidProducator(const std::string &producator);

    /// Check if substActiva is valid
    static bool isValidSubstActiva(const std::string &substActiva);

    /// Check if pret is valid
    static bool isValidPret(int pret);

public:
    /// Check if a medicament is valid
    static void validateMedicament(const Medicament &medicament);
};
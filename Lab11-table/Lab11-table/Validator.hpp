//
// Created by Mihai Adomnitei on 13.04.2024.
//

#pragma once

#include <string>
#include "Medicament.hpp"

class Validator {
private:
    /// Check if a string is a valid name
    static bool isValidName(const std::string &name);

    static bool isValidPrice(int price);

public:
    /// Check if a medicament is valid
    static void validateMedicament(const Medicament &medicament);
};
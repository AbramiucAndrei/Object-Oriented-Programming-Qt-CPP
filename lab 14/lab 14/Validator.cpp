//
// Created by Mihai Adomnitei on 13.04.2024.
//

#include "Validator.hpp"
#include <stdexcept>

bool Validator::isValidDenumire(const std::string &denumire) {
    return isupper(denumire[0]) && !denumire.empty();
}

bool Validator::isValidProducator(const std::string &producator) {
    return !producator.empty();
}

bool Validator::isValidSubstActiva(const std::string &substActiva) {
    return !substActiva.empty();
}

bool Validator::isValidPret(int pret) {
    return 0 <= pret && pret <= 10000;
}

void Validator::validateMedicament(const Medicament &medicament) {
    std::string error;

    if (!isValidDenumire(medicament.getDenumire())) {
        error.append("Denumire invalida\n");
    }

    if (!isValidProducator(medicament.getProducator())) {
        error.append("Producator invalid\n");
    }

    if (!isValidSubstActiva(medicament.getSubstActiva())) {
        error.append("Substanta activa invalida\n");
    }

    if (!isValidPret(medicament.getPret())) {
        error.append("Pret invalid\n");
    }

    if(!error.empty()){
        throw std::runtime_error(error);
    }
}
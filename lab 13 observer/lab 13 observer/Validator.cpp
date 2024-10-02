
#include "Validator.hpp"
#include "Vector.hpp"
#include "validatorException.hpp"

bool Validator::isValidName(const std::string &name) {
    return isupper(name[0]);
}

bool Validator::isValidPrice(int price) {
    return 0 <= price && price <= 3000;
}

void Validator::validateMedicament(const Medicament &medicament) {
    std::string error;

    if (!isValidName(medicament.getDenumire())) {
        error.append("Denumire invalida\n");
    }
    if (!isValidName(medicament.getProducator())) {
        error.append("Producator invalid\n");
    }

    if (!isValidName(medicament.getSubstActiva())) {
        error.append("Substanta activa invalida\n");
    }

    if (!isValidPrice(medicament.getPret())) {
        error.append("Pret invalid\n");
    }

    if (!error.empty()) {
        throw ValidatorExp(error);
    }
}

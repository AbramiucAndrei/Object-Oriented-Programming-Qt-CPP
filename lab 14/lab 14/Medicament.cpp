//
// Created by Mihai Adomnitei on 13.04.2024.
//

#include "Medicament.hpp"
#include <sstream>
#include <utility>

/// Constructors


Medicament::Medicament(std::string denumire, std::string producator, std::string substActiva, int pret)
        : denumire(std::move(denumire)), producator(std::move(producator)), substActiva(std::move(substActiva)), pret(pret) {
    // constructor body (if any)
}


std::string Medicament::intoString() const {
    std::stringstream string_stream;
    string_stream << "Denumire: " << denumire << ", Producator: " << producator << ", Substanta activa: " << substActiva << ", Pret: " << pret;
    return string_stream.str();
}

/// Getters

std::string Medicament::getDenumire() const {
    return denumire;
}

std::string Medicament::getProducator() const {
    return producator;
}

std::string Medicament::getSubstActiva() const {
    return substActiva;
}

int Medicament::getPret() const {
    return pret;
}

/// Setters

[[maybe_unused]] void Medicament::setDenumire(const std::string &new_denumire) {
    this->denumire = new_denumire;
}

[[maybe_unused]] void Medicament::setProducator(const std::string &new_producator) {
    this->producator = new_producator;
}

[[maybe_unused]] void Medicament::setSubstActiva(const std::string &new_substActiva) {
    this->substActiva = new_substActiva;
}

[[maybe_unused]] void Medicament::setPret(int new_pret) {
    this->pret = new_pret;
}

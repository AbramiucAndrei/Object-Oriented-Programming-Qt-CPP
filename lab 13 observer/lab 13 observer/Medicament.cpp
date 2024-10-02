//
// Created by Mihai Adomnitei on 13.04.2024.
//

#include "Medicament.hpp"
#include <sstream>

Medicament::Medicament(std::string denumire,const std::string producator, const std::string substActiva, int pret)
    : denumire(std::move(denumire)), producator(std::move(producator)), substActiva(std::move(substActiva)), pret(pret) {}

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

void Medicament::setDenumire(const std::string &new_denumire) {
    this->denumire = new_denumire;
}

void Medicament::setProducator(const std::string &new_producator) {
    this->producator = new_producator;
}

void Medicament::setSubstActiva(const std::string &new_substActiva) {
    this->substActiva = new_substActiva;
}

void Medicament::setPret(int new_pret) {
    this->pret = new_pret;
}

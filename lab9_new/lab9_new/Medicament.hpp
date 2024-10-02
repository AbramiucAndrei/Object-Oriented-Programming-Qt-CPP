

#pragma once
#include <iostream>
#include <string>

class Medicament {
    private:
        std::string denumire;
        std::string producator;
        std::string substActiva;
        int pret;

    public:

    /// Default constructor
    Medicament() = default;

    /// Constructor
    Medicament(std::string denumire, std::string producator, std::string substActiva, int pret);

    /// Convert the medicament into a string
    [[nodiscard]] std :: string intoString() const;

    /// Getter for the denumire
    [[nodiscard]] std :: string getDenumire() const;

    /// Getter for the producator
    [[nodiscard]] std :: string getProducator() const;

    /// Getter for the substActiva
    [[nodiscard]] std :: string getSubstActiva() const;

    /// Getter for the pret
    [[nodiscard]] int getPret() const;

    /// Setter for the denumire
    void setDenumire(const std::string &new_denumire);

    /// Setter for the producator
    void setProducator(const std::string &new_producator);

    /// Setter for the substActiva
    void setSubstActiva(const std::string &new_substActiva);

    /// Setter for the pret
    void setPret(int new_pret);

};
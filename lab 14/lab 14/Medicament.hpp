
//
// Created by Mihai Adomnitei on 13.04.2024.
//

#pragma once

#include <string>

class Medicament {
private:
    std::string denumire;
    std::string producator;
    std::string substActiva;
    int pret{0};

public:
    /**
    * The default constructor.
    */
    Medicament() = default;

    /**
     * The default constructor.
     * @param denumire the denumire of the medicament
     * @param producator the producator of the medicament
     * @param substActiva the substActiva of the medicament
     * @param pret the pret of the medicament
     */
    Medicament(std::string denumire, std::string producator, std::string substActiva, int pret);

    /**
     * Converts the medicament into a string
     * @return a string with all the proprieties of a medicament
     */
    [[nodiscard]] std::string intoString() const;

    /**
     * Getter for the denumire
     * @return the denumire of the medicament
     */
    [[nodiscard]] std::string getDenumire() const;

    /**
     * Getter for the producator
     * @return the producator of the medicament
     */
    [[nodiscard]] std::string getProducator() const;

    /**
     * Getter for the substActiva
     * @return the substActiva of the medicament
     */
    [[nodiscard]] std::string getSubstActiva() const;

    /**
     * Getter for the pret
     * @return the pret of the medicament
     */
    [[nodiscard]] int getPret() const;

    /**
     * Setter for the denumire
     * @param new_denumire the new denumire of the medicament
     */
    void setDenumire(const std::string &new_denumire);

    /**
     * Setter for the producator
     * @param new_producator the new producator of the medicament
     */
    void setProducator(const std::string &new_producator);

    /**
     * Setter for the substActiva
     * @param new_substActiva the new substActiva of the medicament
     */
    void setSubstActiva(const std::string &new_substActiva);

    /**
     * Setter for the pret
     * @param new_pret the new pret of the medicament
     */
    void setPret(int new_pret);
};

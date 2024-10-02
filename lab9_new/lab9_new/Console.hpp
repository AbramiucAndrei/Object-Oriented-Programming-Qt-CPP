

#pragma once

#include "Service.hpp"

class Console {
private:
    /// Reference to the service
    Service &service;

    /// Prints the menu
    static void printMenu();

    /// Reads the user input
    static char getUserInput();

    /// Prints all the Medicament objects
    void uiPrintMedicamente();

    /// Adds a Medicament object
    void uiAddMedicament();

    /// Updates a Medicament object
    void uiUpdateMedicament();

    /// Deletes a Medicament object
    void uiDeleteMedicament();

    /// Finds a Medicament object
    void uiFindMedicament();

    /// Filters the Medicament objects
    void uiFilterMedicamente();

    ///Filters the Medicament objects by substance
    void uiFilterMedicamenteSubst();

    /// Sorts the Medicament objects
    void uiSortMedicamente();

    /// Sorts the medicament objects by name
    void uiSortMedicamenteName();

    /// Sorts the medicament objects by producer
    void uiSortMedicamenteProducer();

    /// Sorts the medicament objects by substance and price
    void uiSortMedicamenteSubstPrice();

    //do undo
    void uiUndo();


    void uiDeleteAllFromReteta() noexcept;
    void uiAddMedToReteta();
    void exportReteta();
    void uiGenerateReteta();
    void uiGenerateRaport();

    public:
    /// Constructor for the Console class
    explicit Console(Service &service);

    /// Runs the console
    void run();

};

// Created by Mihai Adomnitei on 27.04.2024.
//

#pragma once

#include "Service.hpp"

class UiError : public std::runtime_error {
public:
    explicit UiError(const std::string &message) : std::runtime_error(message) {}
};

class Console {
private:
    Service &service; // Reference to a Service object

    /**
     * Prints the menu options to the console.
     */
    static void printMenu();

    /**
    * Prints the recipe menu options to the console.
    */
    static void printRecipeMenu();

    /**
     * Retrieves user input from the console.
     * @return Character representing user input
     */
    static char getUserInput();

    /**
     * Displays all medicaments in the farmacy to the console.
     */
    void uiPrintMedicamente();

    /**
     * Adds a new medicament to the farmacy based on user input.
     */
    void uiAddMedicament();

    /**
     * Updates information of an existing medicament based on user input.
     */
    void uiUpdateMedicament();

    /**
     * Deletes a medicament from the farmacy based on user input.
     */
    void uiDeleteMedicament();

    /**
     * Finds a medicament from the farmacy based on user input.
     */
    void uiFindMedicament();

    /**
     * Filters medicaments from the farmacy based on user input.
     */
    void uiFilterMedicamente();

    /**
     * Sorts medicaments from the farmacy based on user input.
     */
    void uiSortMedicamente();

    /*
     * Main menu for recipe actions .
     */
    void uiRecipeMenu();

    /*
     * Prints all the medicaments in the recipe based on user input.
     */
    void uiPrintRecipe();

    /*
     * Adds medicament to recipe based on user input.
     */
    void uiAddToRecipe();

    /*
     * Deletes all medicaments from the recipe based on user input.
     */
    void uiDeleteAllMedicamentsRecipe();

    /*
     * Populates the recipe with random medicaments based on user input.
     */
    void uiPopulateRandomRecipe();

    /*
     * Exports all the recipe to a CSV file
     */
    void uiExportRecipeToCSV();

    /*
     * Generates a report containing the number of medicaments per producator.
     */
    void uiShowRaport();

    /*
     * Undo the last action performed.
     */
    void uiUndo();

    void uiExportToHTML();

    void uiExportToCSV();

public:
    /**
     * Constructor for the Console class.
     * @param service Reference to a Service object
     */
    explicit Console(Service &service);

    /**
     * Runs the console application, displaying the menu and handling user input.
     */
    void run();
};
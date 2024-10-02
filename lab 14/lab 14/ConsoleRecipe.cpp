#include "Console.hpp"
#include <iostream>

void Console::printRecipeMenu() {
    std::cout << "----------------RECIPE MENU----------------\n"
              << "Enter 1 for adding a medicament to your recipe.\n"
              << "Enter 2 for deleting all the items in your recipe\n"
              << "Enter 3 for populating recipe with random medicamente\n"
              << "Enter 4 for exporting all the medicamente in a html page\n"
              << "Enter 5 for exporting all the medicamente in a csv file\n"
              << "Enter p for viewing your recipe.\n"
              << "Enter q to exit this menu.\n";
}

void Console::uiPrintRecipe() {
    auto &all_recipe = service.getAllRecipe();

    if (all_recipe.empty()) {
        throw UiError("There are no medicamente in the recipe.");
    }

    std::cout << "The medicamente are:\n";
    for (const Medicament &medicament : all_recipe) {
        std::cout << medicament.intoString() << "\n";
    }
}

void Console::uiAddToRecipe() {
    std::string denumire;

    std::cout << "Enter the denumire of the medicament you want to add in the recipe: ";
    std::getline(std::cin, denumire);

    service.addMedicamentRecipe(denumire);
    std::cout << "The medicament was added in the recipe\n";
}

void Console::uiDeleteAllMedicamentsRecipe() {
    service.deleteAllMedicamentsRecipe();
    std::cout << "The medicamente from the recipe were deleted.\n";
}

void Console::uiPopulateRandomRecipe() {
    size_t medicament_count{0};

    std::cout << "Enter the number of medicamente you want to add random: ";
    std::cin >> medicament_count;

    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw UiError("Invalid input for number of medicamente.");
    }

    service.populateRandomRecipe(medicament_count);
    std::cout << "The medicamente were added in the recipe\n";
}

void Console::uiExportToHTML() {
    service.exportHTML("../database/export.html");
    std::cout << "The recipe was exported successfully.\n";
}

void Console::uiExportToCSV() {
    service.exportCSV("../database/export.csv");
    std::cout << "The recipe was exported successfully.\n";
}

void Console::uiRecipeMenu() {
    printRecipeMenu();

    char option = getUserInput();

    switch (option) {
        case '1': {
            uiAddToRecipe();
            break;
        }
        case '2': {
            uiDeleteAllMedicamentsRecipe();
            break;
        }
        case '3': {
            uiPopulateRandomRecipe();
            break;
        }
        case '4': {
            uiExportToHTML();
            break;
        }
        case '5': {
            uiExportToCSV();
            break;
        }
        case 'p': {
            uiPrintRecipe();
            break;
        }
        case 'q': {
            return;
        }
        default: {
            std::cout << "The option was not yet implemented.\n";
        }
    }
}
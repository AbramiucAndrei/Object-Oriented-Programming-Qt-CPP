//
// Created by Mihai Adomnitei on 27.04.2024.
//
#include "Console.hpp"
#include <iostream>

Console::Console(Service &service) : service{service} {}

void Console::printMenu() {
    std::cout << "\nOPTION MENU\n"
              << "Enter 1 for adding a medicament.\n"
              << "Enter 2 for updating a medicament.\n"
              << "Enter 3 for deleting a medicament.\n"
              << "Enter 4 for finding medicaments.\n"
              << "Enter 5 for filtering medicaments.\n"
              << "Enter 6 for sorting medicaments.\n"
              << "Enter 7 for a report of medicaments by producator.\n"
              << "Enter c for the recipe menu.\n"
              << "Enter p for printing the medicament list.\n"
              << "Enter z for undoing the last operation.\n"
              << "Enter q for exiting the app.\n";
}

void Console::uiPrintMedicamente() {
    auto all_medicamente = service.getAllFarma();

    if (all_medicamente.empty()) {
        throw UiError("There are no medicaments in the farmacy.");
    }

    std::cout << "The medicaments are:\n";
    for (const Medicament &medicament : all_medicamente) {
        std::cout << medicament.intoString() << "\n";
    }
}

void Console::uiAddMedicament() {
    std::string denumire, producator, substActiva;
    int pret{0};

    std::cout << "Enter the denumire: ";
    std::getline(std::cin, denumire);

    std::cout << "Enter the producator: ";
    std::getline(std::cin, producator);

    std::cout << "Enter the substActiva: ";
    std::getline(std::cin, substActiva);

    std::cout << "Enter the pret: ";
    std::cin >> pret;

    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw UiError("Invalid input for pret.");
    }

    service.addMedicamentFarma(denumire, producator, substActiva, pret);
    std::cout << "The medicament was added.\n";
}

void Console::uiUpdateMedicament() {
    std::string denumire, new_producator, new_substActiva;
    int new_pret{0};

    std::cout << "Enter the denumire of the medicament you want to update: ";
    std::getline(std::cin, denumire);

    std::cout << "\nEnter the new information:\n";

    std::cout << "Enter the new producator: ";
    std::getline(std::cin, new_producator);

    std::cout << "Enter the new substActiva: ";
    std::getline(std::cin, new_substActiva);

    std::cout << "Enter the new pret: ";
    std::cin >> new_pret;

    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw UiError("Invalid input for pret.");
    }

    service.updateMedicamentFarma(denumire, new_producator, new_substActiva, new_pret);
    std::cout << "The medicament was updated.\n";

}

void Console::uiDeleteMedicament() {
    std::string denumire;

    std::cout << "Enter the denumire of the medicament you want to delete: ";
    std::getline(std::cin, denumire);

    service.deleteMedicamentFarma(denumire);
    std::cout << "The medicament was deleted\n";
}

void Console::uiFindMedicament() {
    std::string denumire;

    std::cout << "Enter the denumire of the medicament you want to find: ";
    std::getline(std::cin, denumire);

    auto found_medicamente = service.findMedicamentFarma(denumire);

    if (found_medicamente.empty()) {
        throw UiError("There are no medicaments that fit the description.");
    }

    std::cout << "The found medicaments are:\n";
    for (const Medicament &medicament : found_medicamente) {
        std::cout << medicament.intoString() << "\n";
    }
}

void Console::uiFilterMedicamente() {
    int pret{0};

    std::cout << "Enter the pret: ";
    std::cin >> pret;

    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw UiError("Invalid input for pret.");
    }

    auto filtered_medicamente = service.filterMedicamenteFarma(pret);

    if (filtered_medicamente.empty()) {
        throw UiError("There are no medicaments with pret " + std::to_string(pret));
    }

    std::cout << "The filtered medicaments are:\n";
    for (const Medicament &medicament : filtered_medicamente) {
        std::cout << medicament.intoString() << "\n";
    }
}

void Console::uiSortMedicamente() {
    auto sorted_medicamente = service.sortMedicamenteFarma([](const Medicament &m1, const Medicament &m2) {
        return m1.getPret() < m2.getPret();
    });

    if (sorted_medicamente.empty()) {
        throw UiError("There are no medicaments to sort.");
    }

    std::cout << "The sorted medicaments are:\n";
    for (const Medicament &medicament : sorted_medicamente) {
        std::cout << medicament.intoString() << "\n";
    }
}

void Console::uiShowRaport() {
    auto raport = service.getProducatorReport();

    if (raport.empty()) {
        throw UiError("There are no medicaments in the farmacy.");
    }

    std::cout << "The producator, count pairs are:\n";
    for (const auto &x : raport) {
        std::cout << "The producator " << x.first << " has " << x.second << " medicaments\n";
    }
}

void Console::uiUndo() {
    service.undo();
    std::cout << "Undoing the last action...\n";
}

char Console::getUserInput() {
    char option{};

    while (true) {
        std::cout << "\n>>> ";
        std::cin >> option;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "Invalid input. Please enter a single character.\n";
        } else if (std::cin.peek() != '\n') {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "Invalid input. Please enter only one character.\n";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return option;
        }
    }
}

void Console::run() {
    while (true) {
        printMenu();

        try {
            char option = getUserInput();

            switch (option) {
                case '1': {
                    uiAddMedicament();
                    break;
                }
                case '2': {
                    uiUpdateMedicament();
                    break;
                }
                case '3': {
                    uiDeleteMedicament();
                    break;
                }
                case '4': {
                    uiFindMedicament();
                    break;
                }
                case '5': {
                    uiFilterMedicamente();
                    break;
                }
                case '6': {
                    uiSortMedicamente();
                    break;
                }
                case '7': {
                    uiShowRaport();
                    break;
                }
                case 'c': {
                    uiRecipeMenu();
                    break;
                }
                case 'z': {
                    uiUndo();
                    break;
                }
                case 'p': {
                    uiPrintMedicamente();
                    break;
                }
                case 'q': {
                    std::cout << "Exiting the app...";
                    return;
                }
                default: {
                    std::cerr << "Invalid option. Please try again.\n";
                }
            }
        }
        catch (const UiError &exception) {
            std::cerr << exception.what() << "\n";
        }
    }
}
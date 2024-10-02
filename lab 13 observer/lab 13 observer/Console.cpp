

#include "Console.hpp"
#include <iostream>

Console::Console(Service &service) : service(service) {}

void Console::printMenu() {
    std::cout << "\n ----------------- MENU ----------------- \n";
    std::cout << "1.Add a medicament.\n";
    std::cout << "2.Update a medicament.\n";
    std::cout << "3.Delete a medicament.\n";
    std::cout << "4.Find a medicament.\n";
    std::cout << "5.Filter medicaments after price.\n";
    std::cout << "6.Sort medicaments by price.\n";
    std::cout << "7.Print all medicaments.\n";
    std::cout << "8.Filter medicaments after substance.\n";
    std::cout << "9.Sort medicaments by name.\n";
    std::cout << "s.Sort medicaments by producer.\n";
    std::cout << "t.Sort medicaments by substance and price.\n";
    std::cout << "u.Do undo\n";
    std::cout << "\nd.Delete all from reteta\n";
    std::cout << "a.Add existing medicament to \"reteta\"\n";
    std::cout << "e.Export to file\n";
    std::cout << "g.Generate reteta\n";
    std::cout << "r.Generate raport\n";
    std::cout << "0.Exit.\n";
}

void Console::uiPrintMedicamente() {
    auto all_medicamente = service.getAll();

    if (all_medicamente.size() == 0) {
        std::cout << "Nu sunt medicamente in lista.\n";
        return;
    }

    std::cout << "Medicamentele sunt:\n";
    for (const Medicament &medicament: all_medicamente) {
        std::cout << medicament.intoString() << "\n";
    }
}

void Console::uiAddMedicament() {
    std::string denumire, producator, substActiva;
    int pret{0};

    try{
        std::cout << "Denumire: ";
        //std::cin.ignore();
        std::getline(std::cin, denumire);

        std::cout << "Producator: ";
        std::getline(std::cin, producator);

        std::cout << "Substanta activa: ";
        std::getline(std::cin, substActiva);

        std::cout << "Pret: ";
        std::cin >> pret;

       if(std::cin.fail()){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            throw std::runtime_error("Pret invalid!\n");
        }

        service.addMedicament(denumire, producator, substActiva, pret);
        std::cout << "Medicament adaugat cu succes!\n";
}catch (const std::exception &e){
         throw std::runtime_error("Eroare la adaugare medicament: " + std::string(e.what()));
    }
}

void Console::uiUpdateMedicament() {
    std::string denumire, new_producator, new_substActiva;
    int new_pret{0};

    try{
        std::cout << "Denumirea medicamentului pe care vrei sa il modifici: ";
       // std::cin.ignore();
        std::getline(std::cin, denumire);

        std::cout << "Noul producator: ";
        std::getline(std::cin, new_producator);

        std::cout << "Noua substanta activa: ";
        std::getline(std::cin, new_substActiva);

        std::cout << "Noul pret: ";
        std::cin >> new_pret;

        if(std::cin.fail()){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            throw std::runtime_error("Pret invalid !\n");
        }

        service.updateMedicament(denumire, new_producator, new_substActiva, new_pret);
        std::cout << "Medicament modificat cu succes!\n";
    }catch (const std::exception &e){
        throw std::runtime_error("Eroare la modificare medicament: " + std::string(e.what()));
    }
}

void Console::uiDeleteMedicament() {
    std::string denumire;

    try{
        std::cout << "Denumirea medicamentului pe care vrei sa il stergi: ";
        //std::cin.ignore();
        std::getline(std::cin, denumire);

        service.deleteMedicament(denumire);
        std::cout << "Medicament sters cu succes!\n";
    }catch (const std::exception &e){
        throw std::runtime_error("Eroare la stergere medicament: " + std::string(e.what()));
    }
}

void Console::uiFindMedicament() {
    std::string denumire;

    try{
        std::cout << "Denumirea medicamentului pe care vrei sa il cauti: ";
        //std::cin.ignore();
        std::getline(std::cin, denumire);

        auto foundMedicamente = service.findMedicament(denumire);

        if (foundMedicamente.size() == 0) {
            std::cout << "Nu exista medicamente cu denumirea " << denumire << ".\n";
            return;
        }

        std::cout << "Medicamentele cu denumirea " << denumire << " sunt:\n";
        for (const Medicament &medicament: foundMedicamente) {
            std::cout << medicament.intoString() << "\n";
        }
    }catch (const std::exception &e){
        throw std::runtime_error("Eroare la cautare medicament: " + std::string(e.what()));
    }
}

void Console::uiFilterMedicamente() {
    int min_price{0};

    try{
        std::cout << "Pretul minim: ";
        std::cin >> min_price;

        if(std::cin.fail()){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            throw std::runtime_error("Pret invalid!\n");
        }

        auto filteredMedicamente = service.filterMedicamente(min_price);

        if (filteredMedicamente.size() == 0) {
            std::cout << "Nu exista medicamente cu pretul mai mare sau egal cu " << min_price << ".\n";
            return;
        }

        std::cout << "Medicamentele cu pretul mai mare sau egal cu " << min_price << " sunt:\n";
        for (const Medicament &medicament: filteredMedicamente) {
            std::cout << medicament.intoString() << "\n";
        }
    }catch (const std::exception &e){
        throw std::runtime_error("Eroare la filtrare medicamente: " + std::string(e.what()));
    }
}

void Console::uiFilterMedicamenteSubst() {
    std::string substActiva;

    try{
        std::cout << "Substanta activa: ";
        //std::cin.ignore();
        std::getline(std::cin, substActiva);

        auto filteredMedicamente = service.filterMedicamenteSubst(substActiva);

        if (filteredMedicamente.size() == 0) {
            std::cout << "Nu exista medicamente cu substanta activa " << substActiva << ".\n";
            return;
        }

        std::cout << "Medicamentele cu substanta activa " << substActiva << " sunt:\n";
        for (const Medicament &medicament: filteredMedicamente) {
            std::cout << medicament.intoString() << "\n";
        }
    }catch (const std::exception &e){
        throw std::runtime_error("Eroare la filtrare medicamente: " + std::string(e.what()));
    }
}

void Console::uiSortMedicamente() {
    try{
        auto sortedMedicamente = service.sortMedicamente([&](const Medicament &medicament1, const Medicament &medicament2) {
            return medicament1.getPret() <  medicament2.getPret();
        });

        if(sortedMedicamente.size() == 0){
            std::cout << "Nu exista medicamente in lista!\n";
            return;
        }

        std::cout << "Medicamentele sortate dupa pret sunt:\n";
        for (const Medicament &medicament: sortedMedicamente) {
            std::cout << medicament.intoString() << "\n";
        }
    }catch (const std::exception &e) {
        throw std::runtime_error("Eroare la sortare medicamente: " + std::string(e.what()));
    }
}

void Console::uiSortMedicamenteName() {
    try{
        auto sortedMedicamente = service.sortMedicamenteName( );

        if(sortedMedicamente.size() == 0){
            std::cout << "Nu exista medicamente in lista!\n";
            return;
        }

        std::cout << "Medicamentele sortate dupa nume sunt:\n";
        for (const Medicament &medicament: sortedMedicamente) {
            std::cout << medicament.intoString() << "\n";
        }
    }catch (const std::exception &e) {
        throw std::runtime_error("Eroare la sortare medicamente: " + std::string(e.what()));
    }
}

void Console::uiSortMedicamenteSubstPrice() {
    try{
        auto sortedMedicamente = service.sortMedicamenteSubstPrice();

        if(sortedMedicamente.size() == 0){
            std::cout << "Nu exista medicamente in lista!\n";
            return;
        }

        std::cout << "Medicamentele sortate dupa substanta activa si pret sunt:\n";
        for (const Medicament &medicament: sortedMedicamente) {
            std::cout << medicament.intoString() << "\n";
        }
    }catch (const std::exception &e) {
        throw std::runtime_error("Eroare la sortare medicamente: " + std::string(e.what()));
    }
}

void Console::uiSortMedicamenteProducer() {
    try{
        auto sortedMedicamente = service.sortMedicamenteProducer();

        if(sortedMedicamente.size() == 0){
            std::cout << "Nu exista medicamente in lista!\n";
            return;
        }

        std::cout << "Medicamentele sortate dupa producator sunt:\n";
        for (const Medicament &medicament: sortedMedicamente) {
            std::cout << medicament.intoString() << "\n";
        }
    }catch (const std::exception &e) {
        throw std::runtime_error("Eroare la sortare medicamente: " + std::string(e.what()));
    }
}

void Console::uiDeleteAllFromReteta() noexcept{
    service.clearReteta();
    std::cout << "\nReteta a fost golita!\n";
}

void Console::uiAddMedToReteta() {
    std::cout << "Introduceti numele medicamentului: ";

    string denumire;
    std::getline(std::cin, denumire);
    try {
        service.addToReteta(denumire);
        std::cout << "Medicament adaugat cu succes!\n";
    }
    catch (exception& e) {
        std::cout << e.what() << endl;
    }
}

void Console::exportReteta() {
    std::cout << "Introduceti numele fisierului: ";

    string file_name;
    std::getline(std::cin, file_name);

    service.exportToFile(file_name);
    std::cout << "Export-ul a avut succes!\n";
}

void Console::uiGenerateReteta() {
    try {
        std::cout << "Introduceti numarul de medicamente de introdus: ";
        int nrmed;
        std::cin >> nrmed;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            throw std::runtime_error("Numar invalid!\n");
        }
        service.generateReteta(nrmed);

        std::cout << "Generarea a avut succes!\n";
    }
    catch (exception& e) {
        std::cout << e.what();
    }
}

void Console::uiGenerateRaport() {
    try {
        auto raport = service.createRaport();
        for (const pair<string, int>& dual : raport) {
            std::cout << dual.first<< ':' << dual.second << endl;
        }
    }
    catch (exception& e) {
        std::cout << e.what();
    }
}

void Console::uiUndo() {
    try {
        service.executeUndo();
        std::cout << "Undo a fost executat cu succes!\n";
    }
    catch (exception& e) {
        std::cout << e.what()<<endl;
    }
}



char Console::getUserInput() {
    char option{};

    while(true){
        std::cout << "Optiunea ta: ";
        std::cin >> option;

        if(std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "Optiune invalida!\n";
        }else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return option;
        }
    }
}

void Console::run() {
    while (true){
        printMenu();
        char option = getUserInput();
        try{
            switch (option) {
                case '1':
                    uiAddMedicament();
                    break;
                case '2':
                    uiUpdateMedicament();
                    break;
                case '3':
                    uiDeleteMedicament();
                    break;
                case '4':
                    uiFindMedicament();
                    break;
                case '5':
                    uiFilterMedicamente();
                    break;
                case '6':
                    uiSortMedicamente();
                    break;
                case '7':
                    uiPrintMedicamente();
                    break;
                case '8':
                    uiFilterMedicamenteSubst();
                    break;
                case '9':
                    uiSortMedicamenteName();
                    break;
                case 's':
                    uiSortMedicamenteProducer();
                    break;
                case 't':
                    uiSortMedicamenteSubstPrice();
                    break;
                case 'd':
                    uiDeleteAllFromReteta();
                    
                    break;
                case 'a':
                    uiAddMedToReteta();
                    break;
                case 'e':
                    exportReteta();
                    break;
                case 'g':
                    uiGenerateReteta();
                    break;
                case 'r':
                    uiGenerateRaport();
                    break;
                case 'u':
                    uiUndo();
                    break;
                case '0':
                    std::cout << "La revedere!\n";
                    return;
                    
                default:
                    std::cout << "Optiune invalida!\n";
            }
            string nrTot = "Numar total medicamente de pe reteta: ";
            std::cout << nrTot <<service.getLenReteta()<< endl;
        }catch (const std::exception &e){
            std::cerr << e.what() << std::endl;
        }
    }
}
#include "Test.hpp"

#include "Medicament.hpp"
#include "Validator.hpp"
#include "Repository.hpp"
#include "Service.hpp"

#include <iostream>
#include <fstream>
#include <cassert>
#include <cstdio>

Test::Test() {
    const int PRET = 1890;
    const int OTHER_PRET = 1910;

    denumire = "Nurofen";
    producator = "Reckitt Benckiser";
    substActiva = "Ibuprofen";
    pret = PRET;

    other_denumire = "Paracetamol";
    other_producator = "Zentiva";
    other_substActiva = "Paracetamol";
    other_pret = OTHER_PRET;
}

void Test::testDomain() {
    Medicament new_medicament(denumire, producator, substActiva, pret);

    assert(new_medicament.getDenumire() == denumire);
    assert(new_medicament.getProducator() == producator);
    assert(new_medicament.getSubstActiva() == substActiva);
    assert(new_medicament.getPret() == pret);

    assert(new_medicament.intoString() == "Denumire: Nurofen, Producator: Reckitt Benckiser, Substanta activa: Ibuprofen, Pret: 1890");

    new_medicament.setDenumire(other_denumire);
    new_medicament.setProducator(other_producator);
    new_medicament.setSubstActiva(other_substActiva);
    new_medicament.setPret(other_pret);

    assert(new_medicament.getDenumire() == other_denumire);
    assert(new_medicament.getProducator() == other_producator);
    assert(new_medicament.getSubstActiva() == other_substActiva);
    assert(new_medicament.getPret() == other_pret);

    std::cout << "Domain tests ran successfully.\n";
}

void Test::testRepository() {
    /*
     * TEST FARMACY
     */

    FarmacyVector repo;
    Medicament new_medicament(denumire, producator, substActiva, pret);
    Medicament other_medicament(other_denumire, other_producator, other_substActiva, other_pret);

    // TEST ADD

    repo.addMedicament(new_medicament);
    assert(repo.getLen() == 1);
    repo.addMedicament(other_medicament);
    assert(repo.getLen() == 2);

    // TEST DELETE

    repo.deleteMedicament(denumire);
    assert(repo.getLen() == 1);

    // TEST UPDATE

    repo.updateMedicament(other_denumire, new_medicament);
    assert(repo.getLen() == 1);

    auto all = repo.getMedicamente();
    assert(all[0].getDenumire() == denumire);
    assert(all[0].getProducator() == producator);
    assert(all[0].getSubstActiva() == substActiva);
    assert(all[0].getPret() == pret);


    // TEST FIND

    assert(repo.findMedicament("Nurofen") == true);

    /*
     * TEST RECIPE
     */

    Recipe recipe;

    // TEST DELETE ALL

    recipe.addMedicament(new_medicament);
    recipe.addMedicament(other_medicament);
    assert(recipe.getLen() == 2);

    recipe.deleteAllMedicamente();
    assert(recipe.getLen() == 0);

    // TEST FILE REPO

    std::ofstream out("test.txt");
    out.close();

    FarmacyFile farmacy_file{"test.txt"};

    try {
        FarmacyFile bad_farmacy{"random_name"};
        assert(false);
    } catch (const std::exception &e) {}

    // TEST ADD

    farmacy_file.addMedicament(new_medicament);
    assert(farmacy_file.getLen() == 1);
    farmacy_file.addMedicament(other_medicament);
    assert(farmacy_file.getLen() == 2);

    // TEST DELETE

    farmacy_file.deleteMedicament(denumire);
    assert(farmacy_file.getLen() == 1);

    // TEST UPDATE

    farmacy_file.updateMedicament(other_denumire, new_medicament);
    assert(farmacy_file.getLen() == 1);

    FarmacyFile new_repo("test.txt");
    std::remove("test.txt");

    // TEST RANDOM EXCEPTION

    FarmacyDict farmacy_dict{1};

    try {
        farmacy_dict.addMedicament(new_medicament);
        assert(false);
    } catch (const std::exception &e) {
        assert(farmacy_dict.getLen() == 0);
    }

    std::cout << "Repository tests ran successfully.\n";
}

void Test::testValidator() {
    Test test;
    Medicament good_medicament(test.denumire, test.producator, test.substActiva, test.pret);
    Validator::validateMedicament(good_medicament);

    const int BAD_PRET = 205000;
    std::string bad_denumire = "nurofen";
    std::string bad_producator;
    std::string bad_substActiva;
    int bad_pret = BAD_PRET;

    Medicament bad_medicament(bad_denumire, bad_producator, bad_substActiva, bad_pret);

    try {
        Validator::validateMedicament(bad_medicament);
        assert(false);
    }
    catch (const std::exception &e) {
        std::string correct_error =
                "Denumire invalida\nProducator invalid\nSubstanta activa invalida\nPret invalid\n";
        assert(e.what() == correct_error);
    }

    std::cout << "Validator tests ran successfully.\n";
}

void Test::testService() {
    FarmacyDict repo{0};
    Recipe recipe;
    Service service(repo, recipe);

    // TEST ADD

    service.addMedicamentFarma(denumire, producator, substActiva, pret);
    assert(service.getAllFarma().size() == 1);
    assert(repo.getLen() == 1);
    try {
        service.addMedicamentFarma(denumire, other_producator, other_substActiva, other_pret);
        assert(false);
    } catch (const std::exception &e) {
        assert(service.getAllFarma().size() == 1);
        assert(repo.getLen() == 1);
    }

    // TEST UPDATE

    service.updateMedicamentFarma(denumire, other_producator, other_substActiva, other_pret);
    assert(service.getAllFarma().size() == 1);

    auto all_repo = repo.getMedicamente();
    assert(all_repo[0].getDenumire() == denumire);
    assert(all_repo[0].getProducator() == other_producator);
    assert(all_repo[0].getSubstActiva() == other_substActiva);
    assert(all_repo[0].getPret() == other_pret);

    try {
        service.updateMedicamentFarma(other_denumire, producator, substActiva, pret);
        assert(false);
    } catch (const std::exception &e) {
        assert(service.getAllFarma().size() == 1);

        auto all = service.getAllFarma();
        assert(all[0].getDenumire() == denumire);
        assert(all[0].getProducator() == other_producator);
        assert(all[0].getSubstActiva() == other_substActiva);
        assert(all[0].getPret() == other_pret);
    }

    // TEST DELETE

    service.deleteMedicamentFarma(denumire);
    assert(service.getAllFarma().empty());

    try {
        service.addMedicamentFarma(denumire, other_producator, other_substActiva, other_pret);
        service.deleteMedicamentFarma(other_denumire);
        assert(false);
    } catch (const std::exception &e) {
        assert(service.getAllFarma().size() == 1);
    }

    // TEST FIND

    auto list = service.findMedicamentFarma(other_denumire);
    assert(list.empty());

    list = service.findMedicamentFarma(denumire);
    assert(list.size() == 1);

    // TEST FILTER

    const int GOOD_MIN_PRET = 1900;
    const int BAD_MIN_PRET = 2000;

    auto filter = service.filterMedicamenteFarma(GOOD_MIN_PRET);
    assert(filter.size() == 1);

    filter = service.filterMedicamenteFarma(BAD_MIN_PRET);
    assert(filter.empty());

    // TEST SORT

    service.deleteMedicamentFarma(denumire);
    service.addMedicamentFarma(other_denumire, other_producator, other_substActiva, other_pret);
    service.addMedicamentFarma(denumire, producator, substActiva, pret);

    auto sorted = service.sortMedicamenteFarma([](const Medicament &m1, const Medicament &m2) {
        return m1.getPret() < m2.getPret();
    });

    assert(sorted.size() == 2);
    assert(sorted[0].getDenumire() == denumire);
    assert(sorted[0].getProducator() == producator);
    assert(sorted[0].getSubstActiva() == substActiva);
    assert(sorted[0].getPret() == pret);

    // TEST ADD RECIPE

    service.addMedicamentRecipe(denumire);
    assert(service.getAllRecipe().size() == 1);

    service.addMedicamentRecipe(other_denumire);
    assert(service.getAllRecipe().size() == 2);

    std::string nonexistent_medicament = "Metamorphosis";
    try {
        service.addMedicamentRecipe(nonexistent_medicament);
        assert(false);
    } catch (const std::exception &e) {
        assert(recipe.getLen() == 2);
        assert(service.getAllRecipe().size() == 2);
    }

    // TEST DELETE RECIPE

    service.deleteAllMedicamentsRecipe();
    assert(service.getAllRecipe().empty());

    // TEST POPULATE RANDOM

    const int number = 12;
    service.populateRandomRecipe(number);
    assert(service.getAllRecipe().size() == number);

    service.exportHTML("../database/test.html");
    std::remove("../database/test.html");
    service.exportCSV("../database/test.csv");
    std::remove("../database/test.csv");

    service.populateRandomRecipe(number);
    assert(service.getAllRecipe().size() == number * 2);

    service.deleteAllMedicamentsRecipe();
    service.deleteMedicamentFarma(denumire);
    service.deleteMedicamentFarma(other_denumire);

    try {
        service.populateRandomRecipe(number);
        assert(false);
    } catch (const std::exception &e) {
        assert(service.getAllRecipe().empty());
    }

    try {
        service.deleteAllMedicamentsRecipe();
        assert(false);
    } catch (const std::exception &e) {
        assert(service.getAllRecipe().empty());
    }

    // TEST RAPORT

    const std::string new_denumire = "Hannibal";
    service.addMedicamentFarma(other_denumire, other_producator, other_substActiva, other_pret);
    service.addMedicamentFarma(denumire, producator, substActiva, pret);
    service.addMedicamentFarma(new_denumire, producator, substActiva, other_pret);

    auto map = service.getProducatorReport();

    assert(map[other_producator] == 1);
    assert(map[producator] == 2);


    // TEST UNDO

    FarmacyVector other_repo;
    Recipe other_recipe;
    Service other_service(other_repo, other_recipe);

    other_service.addMedicamentFarma(denumire, producator, substActiva, pret);
    other_service.addMedicamentFarma(other_denumire, other_producator, other_substActiva, other_pret);
    assert(other_service.getAllFarma().size() == 2);
    other_service.undo();
    assert(other_service.getAllFarma().size() == 1);

    other_service.deleteMedicamentFarma(denumire);
    assert(other_service.getAllFarma().empty());
    other_service.undo();
    assert(other_service.getAllFarma().size() == 1);

    other_service.updateMedicamentFarma(denumire, other_producator, other_substActiva, other_pret);
    other_service.undo();
    assert(other_service.getAllFarma().size() == 1);
    assert(other_service.getAllFarma()[0].getDenumire() == denumire);
    assert(other_service.getAllFarma()[0].getProducator() == producator);
    assert(other_service.getAllFarma()[0].getSubstActiva() == substActiva);
    assert(other_service.getAllFarma()[0].getPret() == pret);

    other_service.undo();
    assert(other_service.getAllFarma().empty());

    try {
        other_service.undo();
        assert(false);
    } catch (const std::exception &e) {
        assert(other_service.getAllFarma().empty());
    }

    std::cout << "Service tests ran successfully.\n";
}

void Test::runAll() {
    testDomain();
    testRepository();
    testValidator();
    testService();
    std::cout << "All tests ran successfully.\n";
    }
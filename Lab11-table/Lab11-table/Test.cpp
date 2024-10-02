

#include "Test.hpp"
using namespace std;
#include "Medicament.hpp"
#include "Repository1.h"
#include "Repository2.h"
#include "Service.hpp"
#include "serviceException.hpp"
#include "validatorException.hpp"
#include <cassert>
#include <map>
#include <cstring>

Test::Test() {
    denumire = "Paracetamol";
    producator = "Zentiva";
    substActiva = "Paracetamol";
    pret = 10;

    other_denumire = "Nurofen";
    other_producator = "Reckitt Benckiser";
    other_substActiva = "Ibuprofen";
    other_pret = 15;
}

void Test::testDomain() {
    Medicament new_medicament(denumire, producator, substActiva, pret);
    assert(new_medicament.getDenumire() == denumire);
    assert(new_medicament.getProducator() == producator);
    assert(new_medicament.getSubstActiva() == substActiva);
    assert(new_medicament.getPret() == pret);

    assert(new_medicament.intoString() == "Denumire: Paracetamol, Producator: Zentiva, Substanta activa: Paracetamol, Pret: 10");

    new_medicament.setDenumire(other_denumire);
    new_medicament.setProducator(other_producator);
    new_medicament.setSubstActiva(other_substActiva);
    new_medicament.setPret(other_pret);

    assert(new_medicament.getDenumire() == other_denumire);
    assert(new_medicament.getProducator() == other_producator);
    assert(new_medicament.getSubstActiva() == other_substActiva);
    assert(new_medicament.getPret() == other_pret);

    std::cout << "Domain tests passed!" << std::endl;
}

void Test::testRepository() {
    Repository1 repo;

    Medicament new_medicament(denumire, producator, substActiva, pret);
    Medicament other_medicament(other_denumire, other_producator, other_substActiva, other_pret);

    /// Test add
    repo.addMedicament(new_medicament);
    assert(repo.getLen() == 1);
    repo.addMedicament(other_medicament);
    assert(repo.getLen() == 2);

    /// Test delete
    //auto medicament_position = repo.findMedicament(denumire);
    //assert(medicament_position!=repo.getMedicamente().end());
    repo.deleteMedicament(denumire);
    assert(repo.getLen() == 1);

    /// Test update
    //auto new_medicament_position = repo.findMedicament(other_denumire);
    repo.updateMedicament(other_denumire, new_medicament);
    assert(repo.getLen() == 1);

    auto all = repo.getMedicamente();
    assert(all[0].getDenumire() == denumire);
    assert(all[0].getProducator() == producator);
    assert(all[0].getSubstActiva() == substActiva);
    assert(all[0].getPret() == pret);

    std::cout << "Repository1 tests passed!" << std::endl;
}

void Test::testRepository2() {
    Repository2 repo(0);

    Medicament new_medicament(denumire, producator, substActiva, pret);
    Medicament other_medicament(other_denumire, other_producator, other_substActiva, other_pret);

    /// Test add
    repo.addMedicament(new_medicament);
    assert(repo.getLen() == 1);
    try {
        repo.addMedicament(new_medicament);
        assert(false);
    }
    catch (RepoExp& e) {

        assert(strcmp(e.what(), "RepoException: Medicamentul exsita deja!")==0);
        assert(true);
    }


    repo.addMedicament(other_medicament);
    assert(repo.getLen() == 2);

    /// Test delete
    //auto medicament_position = repo.findMedicament(denumire);
    //assert(medicament_position!=repo.getMedicamente().end());
    repo.deleteMedicament(denumire);
    assert(repo.getLen() == 1);
    try {
        repo.deleteMedicament(denumire);
        assert(false);
    }
    catch (RepoExp&) {
        assert(true);
    }

    /// Test update
    //auto new_medicament_position = repo.findMedicament(other_denumire);

    repo.updateMedicament(other_denumire, new_medicament);
    assert(repo.getLen() == 1);

    try {
        repo.updateMedicament("ROSPEITJJFODPR", other_medicament);
        assert(false);
    }
    catch (exception&) {
        assert(true);
    }

    auto all = repo.getMedicamente();
    assert(all[0].getDenumire() == denumire);
    assert(all[0].getProducator() == producator);
    assert(all[0].getSubstActiva() == substActiva);
    assert(all[0].getPret() == pret);

    std::cout << "Repository2 tests passed!" << std::endl;
}

void Test::testService() {
    Repository1 repo;
    RepoReteta repo2;
    Service service(repo,repo2);

    /// Test Validator
    std::string bad_denumire = "paracetamol";
    std::string bad_producator = "zentiva";
    std::string bad_substActiva = "ibuprofen";
    int bad_pret = -10;

    try{
        service.addMedicament(bad_denumire,bad_producator,bad_substActiva,bad_pret);
        assert(false);
    }
    catch(const exception & e){
        assert(strcmp(e.what(),"\nValidatorException: Denumire invalida\nProducator invalid\nSubstanta activa invalida\nPret invalid\n")==0);
    }

    /// Test add
    service.addMedicament(denumire, producator, substActiva, pret);
    assert(service.getAll().size() == 1);
    assert(repo.getLen() == 1);
    try{
        service.addMedicament(denumire,other_producator,other_substActiva,other_pret);
        assert(false);
    } catch (const std::exception &){
        assert(service.getAll().size() == 1);
        assert(repo.getLen() == 1);
    }

    /// Test update
    service.updateMedicament(denumire, other_producator, other_substActiva, other_pret);
    assert(service.getAll().size() == 1);

    auto all_repo = repo.getMedicamente();
    assert(all_repo[0].getDenumire() == denumire);
    assert(all_repo[0].getProducator() == other_producator);
    assert(all_repo[0].getSubstActiva() == other_substActiva);
    assert(all_repo[0].getPret() == other_pret);

    try{
        service.updateMedicament(other_denumire, producator, substActiva, pret);
        assert(false);
    } catch (const std::exception &){
        assert(service.getAll().size() == 1);

        auto all = service.getAll();
        assert(all[0].getDenumire() == denumire);
        assert(all[0].getProducator() == other_producator);
        assert(all[0].getSubstActiva() == other_substActiva);
        assert(all[0].getPret() == other_pret);

    }

    /// Test delete
    service.deleteMedicament(denumire);
    assert(service.getAll().size() == 0);

    try{
        service.addMedicament(denumire,other_producator,other_substActiva,other_pret);
        service.deleteMedicament(other_denumire);
        assert(false);
    } catch (const std::exception &){
        assert(service.getAll().size() == 1);
    }

    /// Test find

    auto list = service.findMedicament(other_denumire);
    assert(list.size() == 0);

    list = service.findMedicament(denumire);
    assert(list.size() == 1);

    list = service.filterMedicamente(15);
    assert(list.size() == 1);
    /// Test filter
    const int good_pret = 10;
    bad_pret= 20;

    auto filter = service.filterMedicamente(good_pret);
    assert(filter.size() == 1);

    filter = service.filterMedicamente(bad_pret);
    assert(filter.size() == 0);

    
    

    /// Test sort

    service.deleteMedicament(denumire);
    service.addMedicament(other_denumire, other_producator, other_substActiva, other_pret);
    service.addMedicament(denumire, producator, substActiva, pret);

    auto sorted = service.sortMedicamente([&](const Medicament &a, const Medicament &b){
        return a.getPret() < b.getPret();
    });

    assert(sorted.size() == 2);
    assert(sorted[0].getDenumire() == denumire);
    assert(sorted[0].getProducator() == producator);
    assert(sorted[0].getSubstActiva() == substActiva);
    assert(sorted[0].getPret() == pret);
    service.addMedicament("AAA", "BBB", "Ibuprofen", 10);
    


    auto lista=service.sortMedicamenteName();
    assert(lista[0].getDenumire() == "AAA");
    assert(lista[1].getDenumire() == "Nurofen");
    assert(lista.size() == 3);

    lista = service.sortMedicamenteProducer();
    assert(lista[0].getProducator() == "BBB");
    assert(lista.size() == 3);

    service.addMedicament("DD", "Reckitt Benckise", "EEE", 60);
    lista = service.sortMedicamenteSubstPrice();
    assert(lista[0].getPret() == 60);
    assert(lista[1].getPret() == 10);
   assert(lista[1].getSubstActiva() == lista[2].getSubstActiva());

    assert(service.filterMedicamenteSubst("Ibuprofen").size() == 2);

    //Test new repo options

    try {
        service.generateReteta(0);
        assert(false);
    }
    catch (const exception& ) {
        assert(true);
    }

    service.generateReteta(4);
    assert(service.getLenReteta() == 4);
    service.clearReteta();
    assert(service.getAllReteta().size() == 0);
    try {
        service.addToReteta("Azitrox");
        assert(false);
    }
    catch (ServiceExp &) {
        assert(true);
    }

    service.addToReteta("Nurofen");
    assert(service.getLenReteta() == 1);

    service.addMedicament("DDD", "Reckitt Benckiser", "EEE", 14);
    service.addToReteta("DDD");
    auto raport = service.createRaport();
    //for (const pair<string, int>& dual : raport) {
    //    std::cout << dual.first << ':' << dual.second << endl;
    //}
    assert(raport.size() == 4);
    assert(raport["Reckitt Benckiser"] == 2);

    service.exportToFile("indexx.html");

    Repository1 r1;
    RepoReteta r2;
    Service s(r1, r2);
    try {
        s.generateReteta(10);
        assert(false);
    }
    catch (ServiceExp& e) {
        assert(strcmp(e.what(), "ServiceException: Nu exista medicamente in farmacie!") == 0);
    }

    //Nurofen Reckitt Benckiser Ibuprofen 15
    //    Paracetamol Zentiva Paracetamol 10
    //    AAA BBB Ibuprofen 10

    //TEST UNDO
    Repository1 rr1;
    RepoReteta rr2;
    Service servicee(rr1, rr2);

    vector<Medicament> ver;
    servicee.addMedicament("DEN", "PROD", "SUB", 15);
    servicee.updateMedicament("DEN", "PROD2", "SUB2", 16);
    ver = servicee.findMedicament("DEN");
    if (ver.size() == 1) {
        assert(ver[0].getSubstActiva() == "SUB2");
    }
    else {
        assert(false);
    }
    servicee.deleteMedicament("DEN");

    //assert(service.undo.size() == 3);
    assert(servicee.findMedicament("DEN").size() == 0);
    servicee.executeUndo();
    ver = servicee.findMedicament("DEN");
    assert(ver.size() == 1);
    assert(ver[0].getPret() == 16);


    servicee.executeUndo();
    ver = servicee.findMedicament("DEN");
    assert(ver.size() == 1);
    assert(ver[0].getPret() == 15);
    assert(ver[0].getSubstActiva() == "SUB");

    servicee.executeUndo();
    ver = servicee.findMedicament("DEN");
    assert(ver.size() == 0);

    try {
        servicee.executeUndo();
        //assert(false);
    }
    catch (exception& ) {
        assert(true);
    }

    
    std::cout << "Service tests passed!" << std::endl;
}

void Test::testServiceforRepo2() {
    Repository2 repo(0);
    RepoReteta repo2;
    Service service(repo, repo2);

    /// Test Validator
    std::string bad_denumire = "paracetamol";
    std::string bad_producator = "zentiva";
    std::string bad_substActiva = "ibuprofen";
    int bad_pret = -10;

    try {
        service.addMedicament(bad_denumire, bad_producator, bad_substActiva, bad_pret);
        assert(false);
    }
    catch (const exception& e) {
        assert(strcmp(e.what(), "\nValidatorException: Denumire invalida\nProducator invalid\nSubstanta activa invalida\nPret invalid\n") == 0);
    }

    /// Test add
    service.addMedicament(denumire, producator, substActiva, pret);
    assert(service.getAll().size() == 1);
    assert(repo.getLen() == 1);
    try {
        service.addMedicament(denumire, other_producator, other_substActiva, other_pret);
        assert(false);
    }
    catch (const std::exception&) {
        assert(service.getAll().size() == 1);
        assert(repo.getLen() == 1);
    }

    /// Test update
    service.updateMedicament(denumire, other_producator, other_substActiva, other_pret);
    assert(service.getAll().size() == 1);

    auto all_repo = repo.getMedicamente();
    assert(all_repo[0].getDenumire() == denumire);
    assert(all_repo[0].getProducator() == other_producator);
    assert(all_repo[0].getSubstActiva() == other_substActiva);
    assert(all_repo[0].getPret() == other_pret);

    try {
        service.updateMedicament(other_denumire, producator, substActiva, pret);
        assert(false);
    }
    catch (const std::exception&) {
        assert(service.getAll().size() == 1);

        auto all = service.getAll();
        assert(all[0].getDenumire() == denumire);
        assert(all[0].getProducator() == other_producator);
        assert(all[0].getSubstActiva() == other_substActiva);
        assert(all[0].getPret() == other_pret);

    }

    /// Test delete
    service.deleteMedicament(denumire);
    assert(service.getAll().size() == 0);

    try {
        service.addMedicament(denumire, other_producator, other_substActiva, other_pret);
        service.deleteMedicament(other_denumire);
        assert(false);
    }
    catch (const std::exception&) {
        assert(service.getAll().size() == 1);
    }

    /// Test find

    auto list = service.findMedicament(other_denumire);
    assert(list.size() == 0);

    list = service.findMedicament(denumire);
    assert(list.size() == 1);

    list = service.filterMedicamente(15);
    assert(list.size() == 1);
    /// Test filter
    const int good_pret = 10;
    bad_pret = 20;

    auto filter = service.filterMedicamente(good_pret);
    assert(filter.size() == 1);

    filter = service.filterMedicamente(bad_pret);
    assert(filter.size() == 0);




    /// Test sort

    service.deleteMedicament(denumire);
    service.addMedicament(other_denumire, other_producator, other_substActiva, other_pret);
    service.addMedicament(denumire, producator, substActiva, pret);

    auto sorted = service.sortMedicamente([&](const Medicament& a, const Medicament& b) {
        return a.getPret() < b.getPret();
        });

    assert(sorted.size() == 2);
    assert(sorted[0].getDenumire() == denumire);
    assert(sorted[0].getProducator() == producator);
    assert(sorted[0].getSubstActiva() == substActiva);
    assert(sorted[0].getPret() == pret);
    service.addMedicament("AAA", "BBB", "Ibuprofen", 10);



    auto lista = service.sortMedicamenteName();
    assert(lista[0].getDenumire() == "AAA");
    assert(lista[1].getDenumire() == "Nurofen");
    assert(lista.size() == 3);

    lista = service.sortMedicamenteProducer();
    assert(lista[0].getProducator() == "BBB");
    assert(lista.size() == 3);

    service.addMedicament("DD", "Reckitt Benckise", "EEE", 60);
    lista = service.sortMedicamenteSubstPrice();
    assert(lista[0].getPret() == 60);
    assert(lista[1].getPret() == 10);
    assert(lista[1].getSubstActiva() == lista[2].getSubstActiva());

    assert(service.filterMedicamenteSubst("Ibuprofen").size() == 2);

    //Test new repo options

    try {
        service.generateReteta(0);
        assert(false);
    }
    catch (const exception&) {
        assert(true);
    }

    service.generateReteta(4);
    assert(service.getLenReteta() == 4);
    service.clearReteta();
    assert(service.getAllReteta().size() == 0);
    try {
        service.addToReteta("Azitrox");
        assert(false);
    }
    catch (ServiceExp&) {
        assert(true);
    }

    service.addToReteta("Nurofen");
    assert(service.getLenReteta() == 1);

    service.addMedicament("DDD", "Reckitt Benckiser", "EEE", 14);
    service.addToReteta("DDD");
    auto raport = service.createRaport();
    //for (const pair<string, int>& dual : raport) {
    //    std::cout << dual.first << ':' << dual.second << endl;
    //}
    assert(raport.size() == 4);
    assert(raport["Reckitt Benckiser"] == 2);

    service.exportToFile("indexx.html");

    Repository1 r1;
    RepoReteta r2;
    Service s(r1, r2);
    try {
        s.generateReteta(10);
        assert(false);
    }
    catch (ServiceExp& e) {
        assert(strcmp(e.what(), "ServiceException: Nu exista medicamente in farmacie!") == 0);
    }

    //Nurofen Reckitt Benckiser Ibuprofen 15
    //    Paracetamol Zentiva Paracetamol 10
    //    AAA BBB Ibuprofen 10

    //TEST UNDO
    Repository1 rr1;
    RepoReteta rr2;
    Service servicee(rr1, rr2);

    vector<Medicament> ver;
    servicee.addMedicament("DEN", "PROD", "SUB", 15);
    servicee.updateMedicament("DEN", "PROD2", "SUB2", 16);
    ver = servicee.findMedicament("DEN");
    if (ver.size() == 1) {
        assert(ver[0].getSubstActiva() == "SUB2");
    }
    else {
        assert(false);
    }
    servicee.deleteMedicament("DEN");

    //assert(service.undo.size() == 3);
    assert(servicee.findMedicament("DEN").size() == 0);
    servicee.executeUndo();
    ver = servicee.findMedicament("DEN");
    assert(ver.size() == 1);
    assert(ver[0].getPret() == 16);


    servicee.executeUndo();
    ver = servicee.findMedicament("DEN");
    assert(ver.size() == 1);
    assert(ver[0].getPret() == 15);
    assert(ver[0].getSubstActiva() == "SUB");

    servicee.executeUndo();
    ver = servicee.findMedicament("DEN");
    assert(ver.size() == 0);

    try {
        servicee.executeUndo();
        //assert(false);
    }
    catch (exception&) {
        assert(true);
    }


    std::cout << "Service for dict repo tests passed!" << std::endl;
}

void Test::runAll() {
    testDomain();
    testRepository();
    testRepository2();
    testService();
    testServiceforRepo2();
}
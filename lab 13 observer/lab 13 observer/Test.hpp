

#pragma once

#include <string>

class Test {
    private:
    std::string denumire;
    std::string producator;
    std::string substActiva;
    int pret;

    std::string other_denumire;
    std::string other_producator;
    std::string other_substActiva;
    int other_pret;

    /// Test the Domain
    void testDomain();

    /// Test the Repository
    void testRepository();

    //Test the Repository (undordered map)
    void testRepository2();

    /// Test the Service
    void testService();

    //test Service for dict Repository
    void testServiceforRepo2();

    public:
    /// Constructor
    Test();

    /// Run all the tests
    void runAll();


};

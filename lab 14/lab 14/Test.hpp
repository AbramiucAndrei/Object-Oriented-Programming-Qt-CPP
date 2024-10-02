//
// Created by Mihai Adomnitei on 26.04.2024.
//

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

    /**
     * Tests the domain module.
     */
    void testDomain();

    /**
     * Tests the repository module.
     */
    void testRepository();

    /**
     * Tests the validator module.
     */
    static void testValidator();

    /**
     * Tests the service module.
     */
    void testService();

public:
    /*!
     * The constructor.
     */
    Test();

    /**
     * Runs all the tests.
     */
    void runAll();
};
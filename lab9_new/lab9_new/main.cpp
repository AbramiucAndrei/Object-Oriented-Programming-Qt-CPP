
#include "Test.hpp"
#include "Console.hpp"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>


int main() {
    
    {
        Test test;
        test.runAll();

        Repository1 repo;
        //Repository2 repo(0.5);
        //RepoFile repo("date.txt");
        
        RepoReteta repoReteta;
        Service service(repo,repoReteta);
        Console console(service);
        console.run();
    }

    _CrtDumpMemoryLeaks();
    
    return 0;
}
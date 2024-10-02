#include "Test.h"

void Test::run_test()
{	//task test
	Task t(15, "Primul", vector<string>{"Ana", "Dana"}, "open");
	assert(t.get_id() == 15);
	assert(t.get_descriere() == "Primul");
	assert(t.get_progr().size() == 2);
	assert(t.get_stare() == "open");


	//repo test
	RepoFile repo(filename);
	assert(repo.get_all().size() == 10);
	//id 3 e closed
	repo.set_stare(3, "open");

	assert((*find_if(repo.get_all().begin(), repo.get_all().end(), [](Task& t) {
		return t.get_id() == 3;
		})).get_stare() == "open");

	repo.set_stare(3, "closed");

	//SERVICE
	Validator val;
	Service srv(repo, val);
	assert(srv.get_all_closed().size() == 4);
	assert(srv.get_all_open().size() == 3);
	assert(srv.get_all_inprogress().size() == 3);
}

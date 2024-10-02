#include "Service.h"
#include <algorithm>
vector<Task>& Service::get_all()
{
    // TODO: insert return statement here
    return repo.get_all();
}

void Service::sort_by_stare()
{
    sort(repo.get_all().begin(), repo.get_all().end(), [](Task& unu,Task& doi) {
        return unu.get_stare() < doi.get_stare();
        });
}

void Service::add_new(int id, string denumire, vector<string> ps, string stare)
{
    //search id
    for (auto& t : repo.get_all()) {
        if (t.get_id() == id)
            throw exception("Id-ul exista deja!");
    }

    //validator
    Task t(id, denumire, ps, stare);
    val.validate(t);
    //store
    repo.store(t);
    sort_by_stare();
    notify();
}

vector<Task> Service::get_all_closed()
{
    vector<Task> to_ret;
    for (auto& t : repo.get_all()) {
        if (t.get_stare() == "closed")
            to_ret.push_back(t);
    }
    return to_ret;
}

vector<Task> Service::get_all_open()
{
    vector<Task> to_ret;
    for (auto& t : repo.get_all()) {
        if (t.get_stare() == "open")
            to_ret.push_back(t);
    }
    return to_ret;
}

vector<Task> Service::get_all_inprogress()
{
    vector<Task> to_ret;
    for (auto& t : repo.get_all()) {
        if (t.get_stare() == "inprogress")
            to_ret.push_back(t);
    }
    return to_ret;
}

void Service::set_stare(int id, string stare)
{
    repo.set_stare(id, stare);
    sort_by_stare();
    notify();
}

vector<Task> Service::filter_by_progr(string p)
{
    vector<Task> lst;
    for (auto& t : repo.get_all()) {
        for(auto& pro : t.get_progr())
            if (pro.find(p)!=string::npos) {
                lst.push_back(t);
                break;
            }
    }
    return lst;
}


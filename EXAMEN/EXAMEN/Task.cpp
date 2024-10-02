#include "Task.h"

int Task::get_id()
{
    return id;
}

string Task::get_descriere()
{
    return descriere;
}

vector<string> Task::get_progr()
{
    return programatori;
}

string Task::get_stare()
{
    return stare;
}

void Task::set_stare(string stare)
{
    this->stare = stare;
}

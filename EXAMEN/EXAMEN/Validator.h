#pragma once
#include <Task.h>
class Validator
{
public:
	//validator de task
	void validate(Task& t) {

		//string de errori
		string errors;
		if (t.get_descriere() == "")
			errors += "Descrierea este vida!\n";
		string stare = t.get_stare();
		if (!(stare == "open" or stare == "closed" or stare == "inprogress"))
			errors += "Stare invalida\n";
		if (!(t.get_progr().size() >= 1 and t.get_progr().size() <= 4))
			errors += "Numar invalid de programatori\n";

		//se arunca exceptie
		if (errors != "")
			throw exception(errors.c_str());
	}
};


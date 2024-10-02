#pragma once
#include <vector>
using std::vector;
class Observer
{
public:
	virtual void update() = 0;

};

class Subject {

	vector<Observer*> obs;
public:
	//notifica observerii
	void notify();
	//adauga observer la lista
	void add_obs(Observer* o);
	//sterge observer din lista 
	void remove_obs(Observer* o);
};


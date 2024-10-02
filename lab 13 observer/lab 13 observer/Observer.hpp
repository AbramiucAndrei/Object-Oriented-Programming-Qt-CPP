#pragma once
#include <vector>
using namespace std;
class Observer
{
public:
	virtual void update() = 0;
};

class Subject {
	private:
		vector<Observer*> list;

	protected:

		void notify();

	public:
		void add_observer(Observer* new_obs);

		void remove_observer(Observer* to_delete);
};
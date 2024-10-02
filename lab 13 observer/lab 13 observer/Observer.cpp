#include "Observer.hpp"

void Subject::notify() {
	for (auto obs : list)
		obs->update();
}

void Subject::add_observer(Observer* new_obs) {
	list.push_back(new_obs);
}

void Subject::remove_observer(Observer* to_delete)
{
	list.erase(std::remove(list.begin(), list.end(), to_delete));
}

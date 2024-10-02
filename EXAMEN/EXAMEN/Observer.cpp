#include "Observer.h"

void Subject::notify()
{
	for (auto o : obs)
		o->update();
}

void Subject::add_obs(Observer* o)
{
	obs.push_back(o);
}

void Subject::remove_obs(Observer* o)
{
	obs.erase(find(obs.begin(), obs.end(), o));
}

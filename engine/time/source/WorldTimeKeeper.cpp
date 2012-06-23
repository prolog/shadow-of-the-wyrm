#include "WorldTimeKeeper.hpp"

using std::map;
using std::string;

WorldTimeKeeper::WorldTimeKeeper()
: seconds_counter(0)
{
}

void WorldTimeKeeper::register_observer(ITimeObserverPtr new_observer)
{
  if (new_observer)
  {
    observers.insert(make_pair(new_observer->get_id(), new_observer));
  }
}

void WorldTimeKeeper::deregister_observer(ITimeObserverPtr old_observer)
{
  if (old_observer)
  {
    observers.erase(old_observer->get_id());
  }
}

void WorldTimeKeeper::reset()
{
  observers.clear();
}

void WorldTimeKeeper::tick(const double seconds)
{
  seconds_counter += seconds;
  
  while (seconds_counter > 60)
  {
    notify_all(1 /* one minutes has passed */);
    
    seconds_counter -= 60; 
  }  
}

void WorldTimeKeeper::notify_all(const int minutes_passed)
{
  for (map<string, ITimeObserverPtr>::iterator o_it = observers.begin(); o_it != observers.end(); o_it++)
  {
    ITimeObserverPtr observer = o_it->second;

    if (observer)
    {
      observer->notify(minutes_passed);
    }
  }
}

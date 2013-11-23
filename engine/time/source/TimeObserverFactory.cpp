#include "CreatureTimeObserver.hpp"
#include "SeasonsTimeObserver.hpp"
#include "TimeObserverFactory.hpp"

using namespace std;

TimeObserverSerializationMap TimeObserverFactory::time_observer_map;

TimeObserverFactory::TimeObserverFactory()
{
}

TimeObserverFactory::~TimeObserverFactory()
{
}

ITimeObserverPtr TimeObserverFactory::create_time_observer(const ClassIdentifier ci)
{
  ITimeObserverPtr time_observer;

  // Construct on first use
  if (time_observer_map.empty())
  {
    initialize_time_observer_map();
  }

  TimeObserverSerializationMap::iterator t_it = time_observer_map.find(ci);

  if (t_it != time_observer_map.end())
  {
    time_observer = ITimeObserverPtr(t_it->second->clone());
  }

  return time_observer;
}

void TimeObserverFactory::initialize_time_observer_map()
{
  time_observer_map.clear();

  ITimeObserverPtr creature = std::make_shared<CreatureTimeObserver>();
  ITimeObserverPtr seasons  = std::make_shared<SeasonsTimeObserver>();

  time_observer_map.insert(make_pair(CLASS_ID_CREATURE_TIME_OBSERVER, creature));
  time_observer_map.insert(make_pair(CLASS_ID_SEASONS_TIME_OBSERVER, seasons));
}


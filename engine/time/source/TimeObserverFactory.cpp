#include "CreatureTimeObserver.hpp"
#include "MapTimeObserver.hpp"
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
  else
  {
    const auto time_obs_end = time_observer_map.end();
    BOOST_ASSERT_MSG(t_it == time_obs_end, "Could not find time observer from class id!");
  }

  return time_observer;
}

void TimeObserverFactory::initialize_time_observer_map()
{
  time_observer_map.clear();

  ITimeObserverPtr creature = std::make_shared<CreatureTimeObserver>();
  ITimeObserverPtr seasons = std::make_shared<SeasonsTimeObserver>();
  ITimeObserverPtr map_observer = std::make_shared<MapTimeObserver>();

  time_observer_map = TimeObserverSerializationMap{{CLASS_ID_CREATURE_TIME_OBSERVER, creature},
                                                   {CLASS_ID_MAP_TIME_OBSERVER, map_observer},
                                                   {CLASS_ID_SEASONS_TIME_OBSERVER, seasons}};
}


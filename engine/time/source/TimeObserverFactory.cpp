#include "AgeTimeObserver.hpp"
#include "CreatureTimeObserver.hpp"
#include "MapTimeObserver.hpp"
#include "SeasonsTimeObserver.hpp"
#include "ShopsTimeObserver.hpp"
#include "SpecialDayObserver.hpp"
#include "TileTransformObserver.hpp"
#include "TimeObserverFactory.hpp"
#include "WorldTimeObserver.hpp"

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
    BOOST_ASSERT_MSG(t_it == time_observer_map.end(), "Could not find time observer from class id!");
  }

  return time_observer;
}

void TimeObserverFactory::initialize_time_observer_map()
{
  time_observer_map.clear();

  ITimeObserverPtr creature = std::make_shared<CreatureTimeObserver>();
  ITimeObserverPtr seasons = std::make_shared<SeasonsTimeObserver>();
  ITimeObserverPtr map_observer = std::make_shared<MapTimeObserver>();
  ITimeObserverPtr age_observer = std::make_shared<AgeTimeObserver>();
  ITimeObserverPtr tile_transform_observer = std::make_shared<TileTransformObserver>();
  ITimeObserverPtr special_day_observer = std::make_shared<SpecialDayObserver>();
  ITimeObserverPtr shops_observer = std::make_shared<ShopsTimeObserver>();
  ITimeObserverPtr world_time_observer = std::make_shared<WorldTimeObserver>();

  time_observer_map = TimeObserverSerializationMap{{ClassIdentifier::CLASS_ID_CREATURE_TIME_OBSERVER, creature},
                                                   {ClassIdentifier::CLASS_ID_MAP_TIME_OBSERVER, map_observer},
                                                   {ClassIdentifier::CLASS_ID_SEASONS_TIME_OBSERVER, seasons},
                                                   {ClassIdentifier::CLASS_ID_AGE_TIME_OBSERVER, age_observer},
                                                   {ClassIdentifier::CLASS_ID_TILE_TRANSFORM_OBSERVER, tile_transform_observer},
                                                   {ClassIdentifier::CLASS_ID_SPECIAL_DAY_OBSERVER, special_day_observer},
                                                   {ClassIdentifier::CLASS_ID_SHOPS_TIME_OBSERVER, shops_observer},
                                                   {ClassIdentifier::CLASS_ID_WORLD_TIME_OBSERVER, world_time_observer}};
}


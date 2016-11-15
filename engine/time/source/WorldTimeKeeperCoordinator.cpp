#include "AgeTimeObserver.hpp"
#include "CreatureTimeObserver.hpp"
#include "MapTimeObserver.hpp"
#include "SeasonsTimeObserver.hpp"
#include "SpecialDayObserver.hpp"
#include "TileTransformObserver.hpp"
#include "WorldTimeKeeperCoordinator.hpp"
#include "WorldTimeKeeper.hpp"
#include "WorldTimeObserver.hpp"

// Set up all the in game observers.
//
// E.g.:
// - Creature observers
// - Tile observers
// - Season observers
// -- etc
void WorldTimeKeeperCoordinator::setup_time_keeper(WorldTimeKeeper& time_keeper)
{
  ITimeObserverPtr creature_minute_tick = std::make_shared<CreatureTimeObserver>();
  ITimeObserverPtr seasons = std::make_shared<SeasonsTimeObserver>();
  ITimeObserverPtr map_observer = std::make_shared<MapTimeObserver>();
  ITimeObserverPtr age_observer = std::make_shared<AgeTimeObserver>();
  ITimeObserverPtr tile_transform_observer = std::make_shared<TileTransformObserver>();
  ITimeObserverPtr special_day_observer = std::make_shared<SpecialDayObserver>();
  ITimeObserverPtr world_time_observer = std::make_shared<WorldTimeObserver>();

  time_keeper.register_observer(1, creature_minute_tick);
  
  // Four times per day, add new creatures to the active map, if it supports 
  // that.  Some maps, like custom maps defined in XML, should not be updated.
  time_keeper.register_observer(360, map_observer);

  // Every hour, do various world time related checks (dusk, dawn, etc).
  time_keeper.register_observer(60, world_time_observer);

  // Once a day, check to see if the season needs to be incremented - necessary because the game itself
  // will eventually start on a random day, so we can't key in on the fact that the game always starts on
  // the first of the month.
  time_keeper.register_observer(1440, seasons);

  // As well, daily, check to see if this is one of the special, in-game days.
  time_keeper.register_observer(1440, special_day_observer);

  // Also daily, check each map to see what tile transformations need to occur.
  time_keeper.register_observer(1440, tile_transform_observer);

  // Once a year, age everything touched by time.
  time_keeper.register_observer(525600, age_observer);
}

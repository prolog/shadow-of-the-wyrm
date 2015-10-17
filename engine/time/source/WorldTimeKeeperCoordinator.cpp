#include "AgeTimeObserver.hpp"
#include "CreatureTimeObserver.hpp"
#include "MapTimeObserver.hpp"
#include "SeasonsTimeObserver.hpp"
#include "WorldTimeKeeperCoordinator.hpp"
#include "WorldTimeKeeper.hpp"

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

  time_keeper.register_observer(1, creature_minute_tick);
  
  // Four times per day, add new creatures to the active map, if it supports 
  // that.  Some maps, like custom maps defined in XML, should not be updated.
  time_keeper.register_observer(360, map_observer);

  // Once a day, check to see if the season needs to be incremented - necessary because the game itself
  // will eventually start on a random day, so we can't key in on the fact that the game always starts on
  // the first of the month.
  time_keeper.register_observer(1440, seasons);

  // Once a year, age everything touched by time.
  time_keeper.register_observer(250 /*525600*/, age_observer);
}

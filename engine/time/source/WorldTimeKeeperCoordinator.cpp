#include <boost/make_shared.hpp>
#include "CreatureTimeObserver.hpp"
#include "SeasonsTimeObserver.hpp"
#include "WorldTimeKeeperCoordinator.hpp"
#include "WorldTimeKeeper.hpp"

using boost::make_shared;

// Set up all the in game observers.
//
// E.g.:
// - Creature observers
// - Tile observers
// - Season observers
// -- etc
void WorldTimeKeeperCoordinator::setup_time_keeper(WorldTimeKeeper& time_keeper)
{
  ITimeObserverPtr creature_minute_tick = make_shared<CreatureTimeObserver>();
  ITimeObserverPtr seasons  = make_shared<SeasonsTimeObserver>();

  time_keeper.register_observer(1, creature_minute_tick);
  
  // Once a day, check to see if the season needs to be incremented - necessary because the game itself
  // will eventually start on a random day, so we can't key in on the fact that the game always starts on
  // the first of the month.
  time_keeper.register_observer(1440, seasons);
}

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
  ITimeObserverPtr hp_regen = make_shared<CreatureTimeObserver>();
  ITimeObserverPtr seasons  = make_shared<SeasonsTimeObserver>();

  time_keeper.register_observer(1, hp_regen);
  time_keeper.register_observer(43200, seasons);
}

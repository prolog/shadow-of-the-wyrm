#include <boost/make_shared.hpp>
#include "CreatureTimeObserver.hpp"
#include "WorldTimeKeeperCoordinator.hpp"
#include "WorldTimeKeeper.hpp"

using boost::make_shared;

// Set up all the in game observers.
//
// E.g.:
// - Creature observers
// - Tile observers
// - etc
void WorldTimeKeeperCoordinator::setup_time_keeper(WorldTimeKeeper& time_keeper)
{
  ITimeObserverPtr hp_regen = make_shared<CreatureTimeObserver>();

  time_keeper.register_observer(hp_regen);
}

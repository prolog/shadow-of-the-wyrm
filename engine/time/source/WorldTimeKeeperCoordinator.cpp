#include <boost/make_shared.hpp>
#include "HPRegenerationTimeObserver.hpp"
#include "WorldTimeKeeperCoordinator.hpp"
#include "WorldTimeKeeper.hpp"

using boost::make_shared;

// Set up all the in game observers.
//
// E.g.:
// - HP regeneration
// - AP regeneration
// - Status effect checkers
void WorldTimeKeeperCoordinator::setup_time_keeper(WorldTimeKeeper& time_keeper)
{
  ITimeObserverPtr hp_regen = make_shared<HPRegenerationTimeObserver>();

  time_keeper.register_observer(hp_regen);
}

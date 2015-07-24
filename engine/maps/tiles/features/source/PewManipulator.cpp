#include "PewManipulator.hpp"
#include "Game.hpp"

using namespace std;

PewManipulator::PewManipulator(FeaturePtr feature)
: IFeatureManipulator(feature)
{
}

// Pews are a good feature, and only the good deities care about the
// desecration of pews.
void PewManipulator::kick(CreaturePtr creature, MapPtr current_map, TilePtr feature_tile, FeaturePtr feature)
{
  Game::instance().get_deity_action_manager_ref().notify_action(creature, CreatureActionKeys::ACTION_DESECRATE_GOOD, false);
}

bool PewManipulator::handle(TilePtr tile, CreaturePtr creature)
{
  return true;
}


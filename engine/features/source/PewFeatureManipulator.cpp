#include "PewFeatureManipulator.hpp"
#include "Game.hpp"

using namespace std;

// Pews are a good feature, and only the good deities care about the
// desecration of pews.
void PewFeatureManipulator::kick(CreaturePtr creature, MapPtr current_map, TilePtr feature_tile, FeaturePtr feature)
{
  Game::instance().get_deity_action_manager_ref().notify_action(creature, CreatureActionKeys::ACTION_DESECRATE_GOOD, false);
}


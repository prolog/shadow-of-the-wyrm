#include "NeutralAltarManipulator.hpp"
#include "Game.hpp"

using namespace std;

NeutralAltarManipulator::NeutralAltarManipulator(FeaturePtr feature)
: AltarManipulator(feature)
{
}

void NeutralAltarManipulator::kick(CreaturePtr creature, MapPtr current_map, TilePtr feature_tile, FeaturePtr feature)
{
  Game::instance().get_deity_action_manager_ref().notify_action(creature, CreatureActionKeys::ACTION_DESECRATE_NEUTRAL, false);
}


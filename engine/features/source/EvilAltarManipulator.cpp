#include "EvilAltarManipulator.hpp"
#include "Game.hpp"

using namespace std;

EvilAltarManipulator::EvilAltarManipulator(FeaturePtr feature)
: AltarManipulator(feature)
{
}

void EvilAltarManipulator::kick(CreaturePtr creature, MapPtr current_map, TilePtr feature_tile, FeaturePtr feature)
{
  Game::instance().get_deity_action_manager_ref().notify_action(creature, CreatureActionKeys::ACTION_DESECRATE_EVIL, false);
}


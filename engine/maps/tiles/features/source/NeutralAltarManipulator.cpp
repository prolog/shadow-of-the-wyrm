#include "NeutralAltarManipulator.hpp"
#include "Game.hpp"

using namespace std;

NeutralAltarManipulator::NeutralAltarManipulator(FeaturePtr feature)
: AltarManipulator(feature)
{
}

string NeutralAltarManipulator::get_creature_action_key() const
{
  return CreatureActionKeys::ACTION_DESECRATE_NEUTRAL;
}
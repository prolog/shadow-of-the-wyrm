#include "EvilAltarManipulator.hpp"
#include "Game.hpp"

using namespace std;

EvilAltarManipulator::EvilAltarManipulator(FeaturePtr feature)
: AltarManipulator(feature)
{
}

string EvilAltarManipulator::get_creature_action_key() const
{
  return CreatureActionKeys::ACTION_DESECRATE_EVIL;
}

#ifdef UNIT_TESTS
#include "unit_tests/EvilAltarManipulator_test.cpp"
#endif


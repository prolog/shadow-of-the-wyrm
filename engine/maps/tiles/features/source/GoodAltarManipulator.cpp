#include "GoodAltarManipulator.hpp"
#include "Game.hpp"

using namespace std;

GoodAltarManipulator::GoodAltarManipulator(FeaturePtr feature)
: AltarManipulator(feature)
{
}

string GoodAltarManipulator::get_creature_action_key() const
{
  return CreatureActionKeys::ACTION_DESECRATE_GOOD;
}

#ifdef UNIT_TESTS
#include "unit_tests/GoodAltarManipulator_test.cpp"
#endif


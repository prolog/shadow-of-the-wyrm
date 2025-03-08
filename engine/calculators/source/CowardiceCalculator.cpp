#include "CowardiceCalculator.hpp"

const int CowardiceCalculator::BASE_PCT_CHANCE_TURN_TO_FIGHT = 10;
const int CowardiceCalculator::BASE_PCT_CHANCE_RAGE_FIGHT = 10;

int CowardiceCalculator::get_pct_chance_turn_to_fight(CreaturePtr /*creature*/) const
{
  return BASE_PCT_CHANCE_TURN_TO_FIGHT;
}

int CowardiceCalculator::get_pct_chance_rage_fight(CreaturePtr /*creature*/) const
{
  return BASE_PCT_CHANCE_RAGE_FIGHT;
}

#ifdef UNIT_TESTS
#include "unit_tests/CowardiceCalculator_test.cpp"
#endif


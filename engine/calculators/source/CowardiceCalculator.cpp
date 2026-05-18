#include "CowardiceCalculator.hpp"
#include "CreatureProperties.hpp"

const int CowardiceCalculator::BASE_PCT_CHANCE_TURN_TO_FIGHT = 10;
const int CowardiceCalculator::BASE_PCT_CHANCE_RAGE_FIGHT = 10;

int CowardiceCalculator::get_pct_chance_turn_to_fight(CreaturePtr creature) const
{
  int chance = BASE_PCT_CHANCE_TURN_TO_FIGHT;

  if (creature != nullptr && creature->has_additional_property(CreatureProperties::CREATURE_PROPERTIES_PERMANENT_COWARD))
  {
    chance = 0;
  }

  return chance;
}

int CowardiceCalculator::get_pct_chance_rage_fight(CreaturePtr creature) const
{
  int chance = BASE_PCT_CHANCE_RAGE_FIGHT;

  if (creature != nullptr && creature->has_additional_property(CreatureProperties::CREATURE_PROPERTIES_PERMANENT_COWARD))
  {
    chance = 0;
  }

  return chance;
}

#ifdef UNIT_TESTS
#include "unit_tests/CowardiceCalculator_test.cpp"
#endif


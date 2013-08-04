#include "ExposedCalculator.hpp"
#include "Random.hpp"

const int ExposedCalculator::BASE_EXPOSED_DURATION_MEAN = 4;
const int ExposedCalculator::BASE_EXPOSED_PCT_CHANCE = 15;

// For every 7 points of agility, the percent chance of being exposed
// (lower evade) decreases by 1.
const int ExposedCalculator::BASE_EXPOSED_CHANCE_AGILITY_MODIFIER = 7;

int ExposedCalculator::calculate_pct_chance_effect(CreaturePtr creature) const
{
  int pct_chance = BASE_EXPOSED_PCT_CHANCE;

  if (creature)
  {
    int agility_bonus = creature->get_agility().get_current() / BASE_EXPOSED_CHANCE_AGILITY_MODIFIER;

    double pierce_multiplier = std::max<double>(0.0, creature->get_resistances().get_resistance_value(DAMAGE_TYPE_PIERCE));

    pct_chance -= agility_bonus;
    pct_chance = static_cast<int>(pct_chance * pierce_multiplier);
  }

  return pct_chance;
}

int ExposedCalculator::calculate_duration_in_minutes(CreaturePtr creature) const
{
  PoissonDistribution p(BASE_EXPOSED_DURATION_MEAN);
  int duration = p.next();

  return duration;
}

#ifdef UNIT_TESTS
#include "unit_tests/ExposedCalculator_test.cpp"
#endif

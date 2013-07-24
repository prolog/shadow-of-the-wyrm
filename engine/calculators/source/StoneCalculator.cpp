#include "StoneCalculator.hpp"
#include "Random.hpp"

const int StoneCalculator::BASE_STONE_DURATION_MEAN = 10;
const int StoneCalculator::BASE_STONE_PCT_CHANCE = 5;

// For every 20 points of health, the percent chance of being petrified
// decreases by 1.
const int StoneCalculator::BASE_STONE_CHANCE_HEALTH_MODIFIER = 20;

// Calculate the chance that this creature gets petrified.
int StoneCalculator::calculate_pct_chance_effect(CreaturePtr creature) const
{
  int pct_chance = BASE_STONE_PCT_CHANCE;

  if (creature)
  {
    int health_bonus = creature->get_health().get_current() / BASE_STONE_CHANCE_HEALTH_MODIFIER;

    double shadow_multiplier = std::max<double>(0.0, creature->get_resistances().get_resistance_value(DAMAGE_TYPE_SHADOW));

    pct_chance -= health_bonus;
    pct_chance = static_cast<int>(pct_chance * shadow_multiplier);
  }

  return pct_chance;
}

int StoneCalculator::calculate_duration_in_minutes(CreaturePtr creature) const
{
  PoissonDistribution p(BASE_STONE_DURATION_MEAN);
  int duration = p.next();

  return duration;
}

#ifdef UNIT_TESTS
#include "unit_tests/StoneCalculator_test.cpp"
#endif

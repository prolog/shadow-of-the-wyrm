#include "SlownessCalculator.hpp"
#include "Random.hpp"

const int SlownessCalculator::BASE_SLOWNESS_DURATION_MEAN = 6;
const int SlownessCalculator::BASE_SLOWNESS_PCT_CHANCE = 34;

// For every 3 points of Agility, the percent chance of being slowed
// decreases by 1.
const int SlownessCalculator::BASE_SLOWNESS_CHANCE_AGILITY_MODIFIER = 3;

// Calculate the chance that this creature is slowed.
int SlownessCalculator::calculate_pct_chance_effect(CreaturePtr creature) const
{
  int pct_chance = BASE_SLOWNESS_PCT_CHANCE;

  // More nimble and cold resistant creatures are resistant to being 
  // slowed by the cold.
  if (creature)
  {
    int agility_bonus = (creature->get_agility().get_current() / BASE_SLOWNESS_CHANCE_AGILITY_MODIFIER);
    double cold_multiplier = std::max<double>(0, creature->get_resistances().get_resistance_value(DAMAGE_TYPE_COLD));

    pct_chance -= agility_bonus;
    pct_chance = static_cast<int>(pct_chance * cold_multiplier);
  }

  return pct_chance;
}

int SlownessCalculator::calculate_duration_in_minutes(CreaturePtr creature) const
{
  PoissonDistribution p(BASE_SLOWNESS_DURATION_MEAN);
  int duration = p.next();

  return duration;
}

#ifdef UNIT_TESTS
#include "unit_tests/SlownessCalculator_test.cpp"
#endif

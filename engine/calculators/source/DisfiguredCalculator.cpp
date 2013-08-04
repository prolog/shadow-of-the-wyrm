#include "DisfiguredCalculator.hpp"
#include "Random.hpp"

const int DisfiguredCalculator::BASE_DISFIGURED_DURATION_MEAN = 20;
const int DisfiguredCalculator::BASE_DISFIGURED_PCT_CHANCE = 15;

// For every 7 points of health, the percent chance of being disfigured
// (reduced stats) decreases by 1.
const int DisfiguredCalculator::BASE_DISFIGURED_CHANCE_HEALTH_MODIFIER = 7;

int DisfiguredCalculator::calculate_pct_chance_effect(CreaturePtr creature) const
{
  int pct_chance = BASE_DISFIGURED_PCT_CHANCE;

  if (creature)
  {
    int health_bonus = creature->get_health().get_current() / BASE_DISFIGURED_CHANCE_HEALTH_MODIFIER;

    double acid_multiplier = std::max<double>(0.0, creature->get_resistances().get_resistance_value(DAMAGE_TYPE_ACID));

    pct_chance -= health_bonus;
    pct_chance = static_cast<int>(pct_chance * acid_multiplier);
  }

  return pct_chance;
}

int DisfiguredCalculator::calculate_duration_in_minutes(CreaturePtr creature) const
{
  PoissonDistribution p(BASE_DISFIGURED_DURATION_MEAN);
  int duration = p.next();

  return duration;
}

#ifdef UNIT_TESTS
#include "unit_tests/DisfiguredCalculator_test.cpp"
#endif

#include "MutenessCalculator.hpp"
#include "Random.hpp"

const int MutenessCalculator::BASE_MUTENESS_DURATION_MEAN = 180;
const int MutenessCalculator::BASE_MUTENESS_PCT_CHANCE = 30;

// For every 4 points of charisma, the percent chance of being muted
// decreases by 1.
const int MutenessCalculator::BASE_MUTENESS_CHANCE_CHARISMA_MODIFIER = 4;

// Calculate the chance that this creature gets muted.
int MutenessCalculator::calculate_pct_chance_effect(CreaturePtr creature) const
{
  int pct_chance = BASE_MUTENESS_PCT_CHANCE;

  // More charismatic and holy creature are resistant to being dumbstruck by
  // divine beings.
  if (creature)
  {
    int charisma_bonus = creature->get_charisma().get_current() / BASE_MUTENESS_CHANCE_CHARISMA_MODIFIER;
    double holiness_multiplier = std::max<double>(0.0, creature->get_resistances().get_resistance_value(DamageType::DAMAGE_TYPE_HOLY));

    pct_chance -= charisma_bonus;
    pct_chance = static_cast<int>(pct_chance * holiness_multiplier);
  }

  return pct_chance;
}

int MutenessCalculator::calculate_duration_in_minutes(CreaturePtr creature) const
{
  // Muteness duration is described by a Poisson distribution, with the
  // average muteness lasting several hours.
  PoissonDistribution p(calculate_muteness_duration_mean(creature));
  int duration = p.next();

  return duration;
}

// Calculate the mean of the Muteness Poisson distribution, which is affected
// by the creature's health.
int MutenessCalculator::calculate_muteness_duration_mean(CreaturePtr creature) const
{
  int base_mean = BASE_MUTENESS_DURATION_MEAN;
  return base_mean;
}

#ifdef UNIT_TESTS
#include "unit_tests/MutenessCalculator_test.cpp"
#endif

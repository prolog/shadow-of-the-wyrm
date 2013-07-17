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

  // More charismatic creatures are resistant to being dumbstruck by
  // divine beings.
  if (creature)
  {
    int cha_bonus = std::min<int>((creature->get_charisma().get_current() / BASE_MUTENESS_CHANCE_CHARISMA_MODIFIER), BASE_MUTENESS_PCT_CHANCE);

    pct_chance -= cha_bonus;
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

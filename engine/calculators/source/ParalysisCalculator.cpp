#include "ParalysisCalculator.hpp"
#include "Random.hpp"

const int ParalysisCalculator::BASE_PARALYSIS_DURATION_MEAN = 5;
const int ParalysisCalculator::BASE_PARALYSIS_PCT_CHANCE = 15;

// For every 7 points of health, the percent chance of being paralyzed
// decreases by 1.
const int ParalysisCalculator::BASE_PARALYSIS_CHANCE_HEALTH_MODIFIER = 7;

// Calculate the chance that this creature gets paralyzed.
int ParalysisCalculator::calculate_pct_chance_effect(CreaturePtr creature) const
{
  int pct_chance = BASE_PARALYSIS_PCT_CHANCE;

  // More charismatic creatures are resistant to being dumbstruck by
  // divine beings.
  if (creature)
  {
    int hea_bonus = std::min<int>((creature->get_health().get_current() / BASE_PARALYSIS_CHANCE_HEALTH_MODIFIER), BASE_PARALYSIS_PCT_CHANCE);

    pct_chance -= hea_bonus;
  }

  return pct_chance;
}

int ParalysisCalculator::calculate_duration_in_minutes(CreaturePtr creature) const
{
  // Paralysis duration is described by a Poisson distribution, with the
  // average lasting a few minutes (otherwise, the character is basically
  // at the mercy of nearby monsters - this gives them, hopefully, a
  // chance to survive).
  PoissonDistribution p(BASE_PARALYSIS_DURATION_MEAN);
  int duration = p.next();

  return duration;
}

#ifdef UNIT_TESTS
#include "unit_tests/ParalysisCalculator_test.cpp"
#endif

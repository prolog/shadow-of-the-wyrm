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

  // More charismatic and shock-resistance creatures are resistant to being 
  // paralyzed via electricity.
  if (creature)
  {
    int health_bonus = (creature->get_health().get_current() / BASE_PARALYSIS_CHANCE_HEALTH_MODIFIER);
    double lightning_multiplier = std::max<double>(0, creature->get_resistances().get_resistance_value(DAMAGE_TYPE_LIGHTNING));

    pct_chance -= health_bonus;
    pct_chance = static_cast<int>(pct_chance * lightning_multiplier);
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

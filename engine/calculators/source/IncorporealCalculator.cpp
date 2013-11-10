#include "IncorporealCalculator.hpp"
#include "Random.hpp"

const int IncorporealCalculator::BASE_INCORPOREAL_DURATION_MEAN = 20;
const int IncorporealCalculator::BASE_INCORPOREAL_PCT_CHANCE = 100;

int IncorporealCalculator::calculate_pct_chance_effect(CreaturePtr creature) const
{
  return BASE_INCORPOREAL_PCT_CHANCE;
}

int IncorporealCalculator::calculate_duration_in_minutes(CreaturePtr creature) const
{
  PoissonDistribution p(BASE_INCORPOREAL_DURATION_MEAN);
  int duration = p.next();

  return duration;
}


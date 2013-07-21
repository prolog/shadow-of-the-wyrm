#include "HasteCalculator.hpp"
#include "Random.hpp"

const int HasteCalculator::BASE_HASTE_DURATION_MEAN = 12;
const int HasteCalculator::BASE_HASTE_PCT_CHANCE = 100;

int HasteCalculator::calculate_pct_chance_effect(CreaturePtr creature) const
{
  return BASE_HASTE_PCT_CHANCE;
}

int HasteCalculator::calculate_duration_in_minutes(CreaturePtr creature) const
{
  PoissonDistribution p(BASE_HASTE_DURATION_MEAN);
  int duration = p.next();

  return duration;
}

